#include "graylevel_slicing_dialog.h"
#include "ui_graylevel_slicing_dialog.h"
#include <string>
using namespace std;

Graylevel_slicing_dialog::Graylevel_slicing_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graylevel_slicing_dialog)
{
    ui->setupUi(this);
}

Graylevel_slicing_dialog::~Graylevel_slicing_dialog()
{
    delete ui;
}

void Graylevel_slicing_dialog::on_left_valueChanged(int value)
{
    if (ui->right->value() < value) ui->right->setValue(value);
    ui->start_val->setText(QString(to_string(ui->left->value()).c_str()));
    ui->end_val->setText(QString(to_string(ui->right->value()).c_str()));
    start = ui->left->value();
    end = ui->right->value();
}

void Graylevel_slicing_dialog::on_right_valueChanged(int value)
{
    if (ui->left->value() > value) ui->left->setValue(value);
    ui->start_val->setText(QString(to_string(ui->left->value()).c_str()));
    ui->end_val->setText(QString(to_string(ui->right->value()).c_str()));
    start = ui->left->value();
    end = ui->right->value();
}

void Graylevel_slicing_dialog::on_radioButton_clicked(bool checked)
{
    preserve = checked;
}
