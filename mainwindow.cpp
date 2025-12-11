#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QObject>
#include <QListView>
#include <QVBoxLayout>
#include <QStringList>
#include <QLineEdit>
#include <QShortcut>
#include <QPushButton>
#include <QInputDialog>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    QLineEdit* line = new QLineEdit;
    line->setMaxLength(256);

    QPushButton *add_todo_button = new QPushButton("Add", this);
    QStandardItemModel* todos_model = new QStandardItemModel(this);
    QListView *l = new QListView(central_widget);
    l->setModel(todos_model);
    l->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(l, &QAbstractItemView::doubleClicked, this, [=] (const QModelIndex& index) {
        QString current = index.data(Qt::DisplayRole).toString();
        bool ok{};
        QString updated_todo = QInputDialog::getText(this, "Edit Todo", "Enter new todo", QLineEdit::Normal, current, &ok);
        if (ok && !updated_todo.isEmpty()) {
            todos_model->setData(index, updated_todo);
        }
    });

    connect(add_todo_button, &QPushButton::clicked, this, [=] () {
        if (line->hasAcceptableInput()) {
            QString entered_line = line->text();
            if (entered_line.isEmpty() == false) {
                line->clear();
                QStandardItem *item = new QStandardItem(entered_line);
                item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
                item->setData(Qt::Unchecked, Qt::CheckStateRole);
                todos_model->appendRow(item);
            }
        }
    });

    connect(line, &QLineEdit::returnPressed, add_todo_button, &QPushButton::click);

    QVBoxLayout *layout = new QVBoxLayout(central_widget);
    layout->addWidget(line);
    layout->addWidget(add_todo_button);
    layout->addWidget(l);
    central_widget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
