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

    QStringListModel* todos = new QStringListModel();
    QStringList todo;
    todos->setStringList(todo);
    QListView *l = new QListView(this);
    l->setModel(todos);

    connect(add_todo_button, &QPushButton::clicked, this, [=] () {
        if (line->hasAcceptableInput()) {
            QString entered_line = line->text();
            line->clear();
            int last = todos->rowCount();
            todos->insertRow(last);
            todos->setData(todos->index(last), entered_line);
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
