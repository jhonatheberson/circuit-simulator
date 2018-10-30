#ifndef MODIFY_EXIT_H
#define MODIFY_EXIT_H

#include <QDialog>

namespace Ui {
class modify_exit;
}

class modify_exit : public QDialog
{
    Q_OBJECT

public:
    explicit modify_exit(QWidget *parent = nullptr);
    ~modify_exit();

private slots:
    void on_id_exit_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::modify_exit *ui;
};

#endif // MODIFY_EXIT_H
