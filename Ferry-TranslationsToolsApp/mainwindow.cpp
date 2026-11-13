#include "mainwindow.h"
#include "projectSetupDialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ProjectSetupDialog projectSetupDialog(this);
    projectSetupDialog.exec();
}
