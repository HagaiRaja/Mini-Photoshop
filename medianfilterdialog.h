#ifndef MEDIANFILTERDIALOG_H
#define MEDIANFILTERDIALOG_H

#include <QDialog>

namespace Ui {
class MedianFilterDialog;
}

class MedianFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedianFilterDialog(QWidget *parent = nullptr);
    ~MedianFilterDialog();
    uint xSize, ySize = 0;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::MedianFilterDialog *ui;
};

#endif // MEDIANFILTERDIALOG_H
