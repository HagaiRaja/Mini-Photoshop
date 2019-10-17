#ifndef LOGTRANSFORMDIALOG_H
#define LOGTRANSFORMDIALOG_H

#include <QDialog>

namespace Ui {
class LogTransformDialog;
}

class LogTransformDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogTransformDialog(QWidget *parent = nullptr);
    ~LogTransformDialog();
    bool inverse = false;
    double constant;

private slots:
    void on_inverseButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::LogTransformDialog *ui;
};

#endif // LOGTRANSFORMDIALOG_H
