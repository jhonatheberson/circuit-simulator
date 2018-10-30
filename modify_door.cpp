#include "modify_door.h"
#include "ui_modify_door.h"

modify_door::modify_door(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_door)
{
    ui->setupUi(this);
}

modify_door::~modify_door()
{
    delete ui;
}

void modify_door::on_group_box_activated(const QString &arg1)
{

}

void modify_door::on_Number_input_valueChanged(int arg1)
{

}

void modify_door::on_input_one_valueChanged(int arg1)
{

}

void modify_door::on_input_two_valueChanged(int arg1)
{

}

void modify_door::on_input_three_valueChanged(int arg1)
{

}

void modify_door::on_input_four_valueChanged(int arg1)
{

}
