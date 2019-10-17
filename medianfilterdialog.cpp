#include "medianfilterdialog.h"
#include "ui_medianfilterdialog.h"
#include <QValidator>

MedianFilterDialog::MedianFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedianFilterDialog)
{
    ui->setupUi(this);
    ui->xSizeTextBox->setValidator(new QIntValidator());
    ui->ySizeTextBox->setValidator(new QIntValidator());
}

MedianFilterDialog::~MedianFilterDialog()
{
    delete ui;
}

void MedianFilterDialog::on_buttonBox_accepted()
{
    xSize = ui->xSizeTextBox->text().toUInt();
    ySize = ui->ySizeTextBox->text().toUInt();
}
