#include "modify_exit.h"
#include "ui_modify_exit.h"

modify_exit::modify_exit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_exit)
{
    ui->setupUi(this);
}

modify_exit::~modify_exit()
{
    delete ui;
}

void modify_exit::on_id_exit_valueChanged(int arg1)
{

}

void modify_exit::on_buttonBox_accepted()
{

}
