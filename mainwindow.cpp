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
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::Init()
{
    m_central_widget = new QWidget(this);
    setCentralWidget(m_central_widget);

    m_line = new QLineEdit(this);
    m_line->setMaxLength(256);

    m_task_add_button = new QPushButton("Add", this);

    m_todo_model = new QStandardItemModel(this);

    m_todo_view = new QListView(this);
    m_todo_view->setModel(m_todo_model);
    m_todo_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_layout = new QVBoxLayout(m_central_widget);
}

void MainWindow::SetLayout()
{
    m_layout->addWidget(m_line);
    m_layout->addWidget(m_task_add_button);
    m_layout->addWidget(m_todo_view);
}

void MainWindow::MakeConnections()
{
    connect(m_task_add_button, &QPushButton::clicked, this, [this] () {
        if (m_line->hasAcceptableInput()) {
            QString entered_line = m_line->text();
            if (entered_line.isEmpty() == false) {
                m_line->clear();
                QStandardItem *item = new QStandardItem(entered_line);
                item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
                item->setData(Qt::Unchecked, Qt::CheckStateRole);
                m_todo_model->appendRow(item);
            }
        }
    });

    connect(m_line, &QLineEdit::returnPressed, m_task_add_button, &QPushButton::click);

    connect(m_todo_view, &QAbstractItemView::doubleClicked, this, [this] (const QModelIndex& index) {
        QString current = index.data(Qt::DisplayRole).toString();
        bool ok{};
        QString updated_todo = QInputDialog::getText(this, "Edit Todo", "Enter new todo", QLineEdit::Normal, current, &ok);
        if (ok && !updated_todo.isEmpty()) {
            m_todo_model->setData(index, updated_todo);
        }
    });
}
