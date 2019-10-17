#ifndef HIGHBOOSTDIALOG_H
#define HIGHBOOSTDIALOG_H

#include <QDialog>

namespace Ui {
class HighBoostDialog;
}

class HighBoostDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HighBoostDialog(QWidget *parent = nullptr);
    ~HighBoostDialog();
    double constant;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::HighBoostDialog *ui;
};

#endif // HIGHBOOSTDIALOG_H
