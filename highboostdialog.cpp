#include "highboostdialog.h"
#include "ui_highboostdialog.h"

HighBoostDialog::HighBoostDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighBoostDialog)
{
    ui->setupUi(this);
}

HighBoostDialog::~HighBoostDialog()
{
    delete ui;
}

void HighBoostDialog::on_buttonBox_accepted() {
    constant = ui->constantTextBox->text().toDouble();
}