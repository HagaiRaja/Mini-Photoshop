#include "canny_dialog.h"
#include "ui_canny_dialog.h"
#include <string>
using namespace std;

Canny_dialog::Canny_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Canny_dialog)
{
    ui->setupUi(this);
}

Canny_dialog::~Canny_dialog()
{
    delete ui;
}

void Canny_dialog::on_t_slider_valueChanged(int value)
{
    threshold = value;
    ui->t_val->setText(QString(to_string(value).c_str()));
}
