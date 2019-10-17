#include "logtransformdialog.h"
#include "ui_logtransformdialog.h"

LogTransformDialog::LogTransformDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogTransformDialog)
{
    ui->setupUi(this);
}

LogTransformDialog::~LogTransformDialog()
{
    delete ui;
}

void LogTransformDialog::on_inverseButton_clicked() {
    inverse = !inverse;
}

void LogTransformDialog::on_buttonBox_accepted() {
    constant = ui->constantTextBox->text().toDouble();
}
