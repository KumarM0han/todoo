#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QListView>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void Init();
    void SetLayout();
    void MakeConnections();
    ~MainWindow();

private:
    QWidget* m_central_widget = nullptr;
    QLineEdit* m_line = nullptr;
    QPushButton* m_task_add_button = nullptr;
    QStandardItemModel* m_todo_model = nullptr;
    QListView* m_todo_view = nullptr;
    QVBoxLayout* m_layout = nullptr;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
