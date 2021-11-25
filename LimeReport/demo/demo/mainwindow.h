#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_QPointerTest_clicked();

    void on_QSharedPointerTest_clicked();

    void on_btnLimeReport_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
