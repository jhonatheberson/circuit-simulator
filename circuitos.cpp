#include "circuitos.h"
#include "ui_circuitos.h"
#include "QLabel"
#include "circuito.h"
#include <QFile>
#include <QTextStream>
#include<QFileDialog>
#include <QMessageBox>



Circuitos::Circuitos(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Circuitos),
    cir(),
    new_cir(), door(), exit()

{

    QLabel *circuit;
    QLabel *truth;
    QLabel *exit;
    ui->setupUi(this);

    ui->Table_circuit->setRowCount(0);
    ui->Table_circuit->setColumnCount(0);
    ui->Table_circuit->QTableWidget::setEnabled(false);
    ui->Table_circuit->setSelectionMode(QAbstractItemView::NoSelection);
    ui->Table_circuit->setTabKeyNavigation(false);
    ui->Table_circuit->setEnabled(true);
    ui->Table_circuit->setHorizontalHeaderLabels(QStringList() <<"TIPO" << "Nº \n ENTR" << "ENTR \n 1" << "ENTR \n 2" << "ENTR \n 3" << "ENTR \n 4");

  /*
    ui->Table_truth->setRowCount(5);
    ui->Table_truth->setColumnCount(5);
    ui->Table_truth->QTableWidget::setEnabled(false);
    ui->Table_truth->setSelectionMode(QAbstractItemView::NoSelection);
    ui->Table_truth->setTabKeyNavigation(false);
    ui->Table_truth->setSpan(0,0,1,3);
    ui->Table_truth->setSpan(0,3,1,3);
    ui->Table_truth->setEnabled(false);

    */

    ui->Table_exit->setRowCount(0);
    ui->Table_exit->setColumnCount(0);
    ui->Table_exit->QTableWidget::setEnabled(false);
    ui->Table_exit->setSelectionMode(QAbstractItemView::NoSelection);
    ui->Table_exit->setTabKeyNavigation(false);
    ui->Table_exit->setEnabled(true);
    ui->Table_exit->setHorizontalHeaderLabels(QStringList() <<"ORG \n SAÍDA");



/*

    for(unsigned j=0; j<7; j++)
    {
        circuit = new QLabel;
        circuit->setAlignment(Qt::AlignCenter);
        circuit->setGeometry(0,0,10,10);
        circuit->setStyleSheet("background:white");
        if(j==0)
        {
            circuit->setText("TIPO");
        }
        else
            if(j==1)
            {
                circuit->setText("Nº \n ENTR");
            }
            else
                if(j==2)
                {
                    circuit->setText("ENTR \n 1");
                }
                else
                    if(j==3)
                    {
                        circuit->setText("ENTR \n 2");
                    }
                    else
                        if(j==4)
                        {
                            circuit->setText("ENTR \n 3");
                        }
                        else
                            {
                                circuit->setText("ENTR \n 4");
                            }

        ui->Table_circuit->setCellWidget(0,j,circuit);

    }
*/
    /*for(unsigned j=0; j<4; j++)
    {
        truth = new QLabel;
        truth->setAlignment(Qt::AlignCenter);
        truth->setGeometry(0,0,10,10);
        truth->setStyleSheet("background:white");
        if(j==2)
        {
            truth->setText("ENTRADAS");
        }
        else
            if(j==3)
            {
                truth->setText("SAÍDAS");
            }

        ui->Table_truth->setCellWidget(0,j,truth);

    }

    */


        exit = new QLabel;
        exit->setAlignment(Qt::AlignCenter);
        exit->setGeometry(0,0,10,10);
        exit->setStyleSheet("background:white");
        exit->setText("ORIG \n SAÍDA");
        ui->Table_exit->setCellWidget(0,0,exit);


}


Circuitos::~Circuitos()
{
    delete ui;
}

void Circuitos::on_actionNovo_triggered()
{
    new_cir.show();
}
/*

void Circuitos::imprimirEntrada(int i,int j, int valor)
{
    for(int i=0; i<9; i++) for(int j=0; j<9; j++)
    {
        QLabel *prov = (QLabel*)(ui->Table_truth->cellWidget(i,j));
        if(valor ==0) prov->setText("");
        else prov->setNum(valor);
    }
}

void Circuitos::imprimirSaidas()
{

    for(int i=0; i<9; i++) for(int j=0; j<9; j++)
    {
        QLabel *prov = (QLabel*)(ui->tabela_inicial->cellWidget(i,j));
        if(valor ==0) prov->setText("");
        else prov->setNum(valor);
    }

}
*/

void Circuitos::on_actionLer_triggered()
{
     //cir.ler("circuito_right0.txt");
     //cir.imprimirEntradas();
     //cir.imprimirSaidas();
}

void Circuitos::on_actionSalvar_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this,"Save File", QString(), tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
      if (!fileName.isEmpty())
      {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
          // error message
        }
        else
        {

          cir.salvar(fileName.toStdString());

        }
      }

}


void Circuitos::on_actionSair_triggered()
{
     QCoreApplication::quit();
}


void Circuitos::on_actionGerar_tabela_triggered()
{
    cir.gerarTabela();

}

void Circuitos::on_Table_circuit_cellDoubleClicked(int row, int column)
{
    door.show();
}
void Circuitos::on_Table_exit_cellDoubleClicked(int row, int column)
{
    exit.show();

}
