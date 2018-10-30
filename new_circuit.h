#ifndef NEW_CIRCUIT_H
#define NEW_CIRCUIT_H

#include <QDialog>

namespace Ui {
class new_circuit;
}

class new_circuit : public QDialog
{
    Q_OBJECT

public:
    explicit new_circuit(QWidget *parent = nullptr);
    ~new_circuit();

private slots:
    void on_number_input_valueChanged(const QString &arg1);

    void on_number_input_valueChanged(int arg1);

    void on_number_exit_valueChanged(int arg1);

    void on_number_door_valueChanged(int arg1);

private:
    Ui::new_circuit *ui;
};

#endif // NEW_CIRCUIT_H
