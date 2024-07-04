#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttonGroup.setParent(this);
    buttonGroup.addButton(ui->site_0, 0);
    buttonGroup.addButton(ui->site_1, 1);
    buttonGroup.addButton(ui->site_2, 2);
    buttonGroup.addButton(ui->site_3, 3);
    buttonGroup.addButton(ui->site_4, 4);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_setButton_clicked()
{
    ui->widget_home->hide();
    this->setStyleSheet("background-color: rgb(255, 255, 213)");
}


void MainWindow::on_homeButton_clicked()
{
    ui->widget_home->show();
    this->setStyleSheet("backgroundcolor: rgb(240, 240, 240)");
}

