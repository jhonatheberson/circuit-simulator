#ifndef MODIFY_DOOR_H
#define MODIFY_DOOR_H

#include <QDialog>

namespace Ui {
class modify_door;
}

class modify_door : public QDialog
{
    Q_OBJECT

public:
    explicit modify_door(QWidget *parent = nullptr);
    ~modify_door();

private slots:
    void on_group_box_activated(const QString &arg1);

    void on_Number_input_valueChanged(int arg1);

    void on_input_one_valueChanged(int arg1);

    void on_input_two_valueChanged(int arg1);

    void on_input_three_valueChanged(int arg1);

    void on_input_four_valueChanged(int arg1);

private:
    Ui::modify_door *ui;
};

#endif // MODIFY_DOOR_H
