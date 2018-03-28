#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_set_start_clicked();
    void on_set_finish_clicked();
    void on_actionClear_triggered();
    void on_but_start_clicked();
    void on_set_wall_clicked();
    void on_actionSize_triggered();
    void change_size(const int, const int);
private:
    Ui::MainWindow *ui;
    int i_start{-1};
    int j_start{-1};
    int i_finish{-1};
    int j_finish{-1};
    int rows{8};
    int columns{13};
    static const int flag_finish;
    static const int flag_start;
    static const int flag_wall;
    static const int flag_free;
    void window_resize();
};

#endif // MAINWINDOW_H
