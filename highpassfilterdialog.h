#ifndef HIGHPASSFILTERDIALOG_H
#define HIGHPASSFILTERDIALOG_H

#include <QDialog>

namespace Ui {
class HighPassFilterDialog;
}

class HighPassFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HighPassFilterDialog(QWidget *parent = nullptr);
    ~HighPassFilterDialog();
    uint choice = 0;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::HighPassFilterDialog *ui;
};

#endif // HIGHPASSFILTERDIALOG_H
