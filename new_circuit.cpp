#include "new_circuit.h"
#include "ui_new_circuit.h"

new_circuit::new_circuit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_circuit)
{
    ui->setupUi(this);
}

new_circuit::~new_circuit()
{
    delete ui;
}

void new_circuit::on_number_input_valueChanged(const QString &arg1)
{

}

void new_circuit::on_number_input_valueChanged(int arg1)
{

}

void new_circuit::on_number_exit_valueChanged(int arg1)
{

}

void new_circuit::on_number_door_valueChanged(int arg1)
{

}
