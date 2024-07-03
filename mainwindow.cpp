#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttonGroup.setParent(this);
    buttonGroup.addButton(ui->site_0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

