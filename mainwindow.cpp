#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QObject>
#include <QListView>
#include <QVBoxLayout>
#include <QStringListModel>
#include <QStringList>
#include <QLineEdit>
#include <QShortcut>
#include <QPushButton>
#include <QInputDialog>

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
    QStringListModel* todos = new QStringListModel(this);
    QStringList todo;
    todos->setStringList(todo);
    QListView *l = new QListView(this);
    l->setModel(todos);
    l->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(l, &QAbstractItemView::doubleClicked, this, [=] (const QModelIndex& index) {
        QString current = index.data(Qt::DisplayRole).toString();
        bool ok{};
        QString updated_todo = QInputDialog::getText(this, "Edit Todo", "Enter new todo", QLineEdit::Normal, current, &ok);
        if (ok && !updated_todo.isEmpty()) {
            todos->setData(index, updated_todo);
        }
    });

    connect(add_todo_button, &QPushButton::clicked, this, [=] () {
        if (line->hasAcceptableInput()) {
            QString entered_line = line->text();
            if (entered_line.isEmpty() == false) {
                line->clear();
                int last = todos->rowCount();
                todos->insertRow(last);
                todos->setData(todos->index(last), entered_line);
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
