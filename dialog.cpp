#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent),ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->but_ok, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(ui->but_cancel, SIGNAL(clicked()), this, SLOT(close()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::okClicked()
{
    emit give_size(ui->spin_rows->value(), ui->spin_columns->value());
    close();
}
