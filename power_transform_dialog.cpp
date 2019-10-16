#include "power_transform_dialog.h"
#include "ui_power_transform_dialog.h"

Power_transform_dialog::Power_transform_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Power_transform_dialog)
{
    ui->setupUi(this);
    ui->gamma_input->setValidator( new QDoubleValidator(0.04, 25, 2, this) );
    ui->constant_input->setValidator( new QIntValidator(1, 5, this) );
}

Power_transform_dialog::~Power_transform_dialog()
{
    delete ui;
}

void Power_transform_dialog::on_gamma_input_textChanged(const QString &arg1)
{
    gamma = arg1.toDouble();
}

void Power_transform_dialog::on_constant_input_textChanged(const QString &arg1)
{
    constant = arg1.toInt();
}
