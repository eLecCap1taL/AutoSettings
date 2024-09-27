#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QParallelAnimationGroup>

void MainWindow::Setup_RightStacked(){

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->RightStacked->setCurrentIndex(0);

    Setup_MenuBT();
    Setup_RightStacked();
}



MainWindow::~MainWindow()
{
    delete ui;
}


