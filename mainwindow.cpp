#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QString>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->window_resize();
    ui->maze->setRowCount(rows);
    ui->maze->setColumnCount(columns);
    connect(ui->maze, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_set_wall_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_set_start_clicked()
{
    if(ui->maze->currentRow() == i_finish && ui->maze->currentColumn() == j_finish)
    {
        return;
    }
    QTableWidgetItem * item = new QTableWidgetItem;
    ui->set_start->setDisabled(true);
    item->setBackgroundColor(QColor(90, 239, 85));
    item->setData(Qt::UserRole, flag_start);
    item->setTextAlignment(Qt::AlignCenter);
    item->setData(Qt::DisplayRole, "S");
    ui->maze->setItem(ui->maze->currentRow(), ui->maze->currentColumn(), item);
    this->i_start = ui->maze->currentRow();
    this->j_start = ui->maze->currentColumn();
    ui->statusBar->showMessage("Start is pinned", 3000);
}

void MainWindow::on_set_finish_clicked()
{
    if(ui->maze->currentRow() == i_start && ui->maze->currentColumn() == j_start)
    {
        return;
    }
    QTableWidgetItem * item = new QTableWidgetItem;
    item->setBackgroundColor(QColor(239,66,66));
    item->setData(Qt::UserRole, flag_finish);
    item->setTextAlignment(Qt::AlignCenter);
    item->setData(Qt::DisplayRole, "F");
    ui->maze->setItem(ui->maze->currentRow(), ui->maze->currentColumn(), item);
    this->i_finish = ui->maze->currentRow();
    this->j_finish = ui->maze->currentColumn();
    ui->set_finish->setDisabled(true);
    ui->statusBar->showMessage("Finish is pinned", 3000);
}

void MainWindow::on_set_wall_clicked()
{
    if((ui->maze->currentRow() == i_start && ui->maze->currentColumn() == j_start) ||
       (ui->maze->currentRow() == i_finish && ui->maze->currentColumn() == j_finish))
    {
        return;
    }
    QTableWidgetItem * wall = new QTableWidgetItem;
    wall->setBackgroundColor(QColor(210,210,210));
    wall->setData(Qt::UserRole, flag_wall);
    wall->setData(Qt::DisplayRole, "W");
    wall->setTextAlignment(Qt::AlignCenter);
    ui->maze->setItem(ui->maze->currentRow(), ui->maze->currentColumn(), wall);
    ui->statusBar->showMessage("Wall is pinned", 3000);
}

void MainWindow::on_but_start_clicked()
{
   if(i_start == -1)
   {
       QMessageBox::warning(this, "Error", "You must to install Start");
       return;
   }
   else if(i_finish == -1)
   {
       QMessageBox::warning(this, "Error", "You must to install Finish");
       return;
   }
   ui->maze->clearSelection();
   ui->maze->setDisabled(true);
   ui->but_start->setDisabled(true);
   ui->set_wall->setDisabled(true);
   for(int i{}; i < ui->maze->rowCount(); ++i)
   {
       for(int j{}; j < ui->maze->columnCount(); ++j)
       {
           if(ui->maze->item(i, j) == nullptr)
           {
               QTableWidgetItem * item = new QTableWidgetItem;
               item->setData(Qt::UserRole, flag_free);
               item->setTextAlignment(Qt::AlignCenter);
               ui->maze->setItem(i, j, item);
           }
       }
   }
   int dot{};
   int limit(ui->maze->rowCount() * ui->maze->columnCount());
   while((ui->maze->item(i_finish, j_finish)->data(Qt::UserRole).toInt()) == flag_finish)
   {
       if(dot > limit)
       {
           QMessageBox::information(this, "Result", "No way!");
           return;
       }
       for(int i{}; i < ui->maze->rowCount(); ++i)
       {
           for(int j{}; j < ui->maze->columnCount(); ++j)
           {
               if(ui->maze->item(i, j)->data(Qt::UserRole).toInt() == dot)
               {
                   if(i - 1 >= 0 && (ui->maze->item(i-1, j)->data(Qt::UserRole).toInt() == flag_free ||
                      ui->maze->item(i-1, j)->data(Qt::UserRole).toInt() == flag_finish))
                   {
                       if(ui->maze->item(i-1, j)->data(Qt::UserRole).toInt() == flag_finish)
                       {
                            ui->maze->item(i-1, j)->setData(Qt::UserRole, dot+1);
                       }
                       else
                       {
                            ui->maze->item(i-1, j)->setData(Qt::UserRole, dot + 1);
                       }
                   }
                   if(i + 1 < ui->maze->rowCount() &&
                      (ui->maze->item(i+1, j)->data(Qt::UserRole).toInt() == flag_free ||
                      ui->maze->item(i+1, j)->data(Qt::UserRole).toInt() == flag_finish))
                   {
                       if(ui->maze->item(i + 1, j)->data(Qt::UserRole).toInt() == flag_finish)
                       {
                            ui->maze->item(i + 1, j)->setData(Qt::UserRole, dot+1);
                       }
                       else
                       {
                            ui->maze->item(i+1, j)->setData(Qt::UserRole, dot + 1);
                       }
                   }
                   if(j - 1 >= 0 && (ui->maze->item(i, j-1)->data(Qt::UserRole).toInt() == flag_free ||
                      ui->maze->item(i, j-1)->data(Qt::UserRole).toInt() == flag_finish))
                   {
                       if(ui->maze->item(i, j-1)->data(Qt::UserRole).toInt() == flag_finish)
                       {
                            ui->maze->item(i, j-1)->setData(Qt::UserRole, dot+1);
                       }
                       else
                       {
                           ui->maze->item(i, j-1)->setData(Qt::UserRole, dot + 1);
                       }
                   }
                   if(j + 1 < ui->maze->columnCount() &&
                     (ui->maze->item(i, j + 1)->data(Qt::UserRole).toInt() == flag_free ||
                      ui->maze->item(i, j + 1)->data(Qt::UserRole).toInt() == flag_finish))
                   {
                       if(ui->maze->item(i, j+1)->data(Qt::UserRole).toInt() == flag_finish)
                       {
                            ui->maze->item(i, j+1)->setData(Qt::UserRole, dot+1);
                       }
                       else
                       {
                           ui->maze->item(i, j + 1)->setData(Qt::UserRole, dot + 1);
                       }
                   }
               }
           }
       }
       ++dot;
   }
   int const flag_way{ 1000 };
   ui->maze->item(i_finish, j_finish)->setData(Qt::UserRole, flag_way);
   int i{i_finish};
   int j{j_finish};
   while((ui->maze->item(i_start, j_start)->data(Qt::UserRole).toInt()) == flag_start)
   {
       if(dot < 0)
       {
           break;
       }
       if(ui->maze->item(i,j)->data(Qt::UserRole).toInt() == flag_way)
       {
           if (i - 1 >= 0 && (ui->maze->item(i - 1, j)->data(Qt::UserRole).toInt() == dot - 1 ||
               ui->maze->item(i - 1, j)->data(Qt::UserRole).toInt() == flag_start))
           {
                if(ui->maze->item(i - 1, j)->data(Qt::UserRole).toInt() == flag_start)
                {
                    break;
                }
                ui->maze->item(i-1,j)->setData(Qt::UserRole, flag_way);
                ui->maze->item(i-1,j)->setData(Qt::DisplayRole, "↓");
                ui->maze->item(i-1,j)->setBackgroundColor(QColor(255,184,60));
                --i;
           }
           else if (i + 1 < ui->maze->rowCount() && (ui->maze->item(i + 1, j)->data(Qt::UserRole).toInt() == dot - 1 ||
                    ui->maze->item(i + 1, j)->data(Qt::UserRole).toInt() == flag_start))
           {
               if(ui->maze->item(i + 1, j)->data(Qt::UserRole).toInt() == flag_start)
               {
                   break;
               }
               ui->maze->item(i+1,j)->setData(Qt::UserRole, flag_way);
               ui->maze->item(i+1,j)->setData(Qt::DisplayRole, "↑");
               ui->maze->item(i+1,j)->setBackgroundColor(QColor(255,184,60));
               ++i;
           }
           else if (j + 1 < ui->maze->columnCount() && (ui->maze->item(i, j + 1)->data(Qt::UserRole).toInt() == dot - 1 ||
                    ui->maze->item(i, j + 1)->data(Qt::UserRole).toInt() == flag_start))
           {
               if(ui->maze->item(i, j+1)->data(Qt::UserRole).toInt() == flag_start)
               {
                   break;
               }
               ui->maze->item(i,j+1)->setData(Qt::UserRole, flag_way);
               ui->maze->item(i,j+1)->setData(Qt::DisplayRole, "←");
               ui->maze->item(i,j+1)->setBackgroundColor(QColor(255,184,60));
                ++j;
           }
           else if (j - 1 >= 0 && (ui->maze->item(i, j - 1)->data(Qt::UserRole).toInt() == dot - 1 ||
                          ui->maze->item(i, j - 1)->data(Qt::UserRole).toInt() == flag_start))
           {
               if(ui->maze->item(i, j-1)->data(Qt::UserRole).toInt() == flag_start)
               {
                   break;
               }
               ui->maze->item(i,j-1)->setData(Qt::UserRole, flag_way);
               ui->maze->item(i,j-1)->setData(Qt::DisplayRole, "→");
               ui->maze->item(i,j-1)->setBackgroundColor(QColor(255,184,60));
               --j;
           }
       }
       --dot;
   }
   ui->statusBar->showMessage("Complete");
}

void MainWindow::on_actionClear_triggered()
{
    ui->maze->clear();
    ui->statusBar->clearMessage();
    this->window_resize();
    ui->maze->setRowCount(rows);
    ui->maze->setColumnCount(columns);
    ui->maze->setEnabled(true);
    ui->set_start->setEnabled(true);
    ui->set_finish->setEnabled(true);
    ui->set_wall->setEnabled(true);
    ui->but_start->setEnabled(true);
    this->i_start = -1;
    this->j_start = -1;
    this->i_finish = -1;
    this->j_finish = -1;
}

void MainWindow::on_actionSize_triggered()
{
    Dialog * window = new Dialog;
    window->show();
    connect(window, SIGNAL(give_size(int,int)), this, SLOT(change_size(int,int)));
}

void MainWindow::change_size(const int _row, const int _col)
{
    this->rows = _row;
    ui->maze->setRowCount(rows);
    this->columns = _col;
    ui->maze->setColumnCount(columns);
    this->on_actionClear_triggered();
}

void MainWindow::window_resize()
{
    QMainWindow::resize(columns + 500, rows + 440);
}

const int MainWindow::flag_finish = 2000;
const int MainWindow::flag_start = 0;
const int MainWindow::flag_wall = -2;
const int MainWindow::flag_free = -1;
