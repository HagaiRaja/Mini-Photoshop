#include "mainwindow.h"
#include "image.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <QStringBuilder>
using namespace std;

const QString picturesFolder = "/home/hagairaja/Documents/Pengcit/miniphotoshop/test";
Image *picture;
QString fileTitle;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea(this);  // init QMdiArea
    // configure scrollbars
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // Set Mdi Area as the central widget
    setCentralWidget(mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QDir dir1(picturesFolder);
    QString path = (dir1.exists()) ? picturesFolder : QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", path,
                                                    tr("Image (*.pgm *.ppm *.pbm *.bmp *.raw)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }

    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    // IMPLEMENT READ FILE HEREE
    QByteArray ba = fileName.toLocal8Bit();
    char *c_str2 = ba.data();
    picture = new Image(c_str2);
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QStringList pieces = fileName.split( "/" );
    fileTitle = pieces.value( pieces.length() - 1 );
    widget->setWindowTitle(fileTitle);
    // And show the widget
    widget->show();

    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    QByteArray ba = fileName.toLocal8Bit();
    char *c_str2 = ba.data();
    picture->save(c_str2);
    QStringList pieces = fileName.split( "/" );
    fileTitle = pieces.value( pieces.length() - 1 );
    setWindowTitle(fileTitle);
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNegative_triggered()
{
    // Create a widget that will be a window
    QWidget *widget = new QWidget(mdiArea);
    // Adding layout to it
    QGridLayout *gridLayout = new QGridLayout(widget);
    widget->setLayout(gridLayout);
    // Adding an label with the picture to the widget
    QLabel *label = new QLabel(widget);

    picture->negatify();
    label->setPixmap(QPixmap::fromImage(picture->getImage()));
    gridLayout->addWidget(label);

    // Adding a widget as a sub window in the Mdi Area
    mdiArea->addSubWindow(widget);
    // Set the window title
    QString negative("Negative - ");
    widget->setWindowTitle(negative % fileTitle);
    // And show the widget
    widget->show();
}
