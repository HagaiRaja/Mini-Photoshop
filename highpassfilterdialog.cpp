#include "highpassfilterdialog.h"
#include "ui_highpassfilterdialog.h"

HighPassFilterDialog::HighPassFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighPassFilterDialog)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/rebellion/Documents/Kuliah stuff/2019(2)/Image/Mini-Photoshop/img/High Pass Filters.png");
    ui->image->setPixmap(pix);
    ui->buttonGroup->setId(ui->choice1, 1);
    ui->buttonGroup->setId(ui->choice1, 2);
    ui->buttonGroup->setId(ui->choice1, 3);
    ui->buttonGroup->setId(ui->choice1, 4);
    ui->buttonGroup->setId(ui->choice1, 5);
    ui->buttonGroup->setId(ui->choice1, 6);
}

HighPassFilterDialog::~HighPassFilterDialog()
{
    delete ui;
}

void HighPassFilterDialog::on_buttonBox_accepted() {
    choice = static_cast<uint>(ui->buttonGroup->checkedId());
}
