#ifndef CIRCUITOS_H
#define CIRCUITOS_H

#include <QMainWindow>
#include <circuito.h>
#include <modify_exit.h>
#include <modify_door.h>
#include <new_circuit.h>
#include <QLabel>

namespace Ui {
class Circuitos;
}

class Circuitos : public QMainWindow
{
    Q_OBJECT

public:
    explicit Circuitos(QWidget *parent = nullptr);
    ~Circuitos();

private slots:
    void on_actionNovo_triggered();

    void on_actionLer_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

    void on_actionGerar_tabela_triggered();

    void on_Table_circuit_cellDoubleClicked(int row, int column);

    void on_Table_exit_cellDoubleClicked(int row, int column);

private:
    Ui::Circuitos *ui;
    Circuito cir;
    new_circuit new_cir;
    modify_door door;
    modify_exit exit;
    QLabel NumIn;
    QLabel NumCun;


};

#endif // CIRCUITOS_H
