#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QTextEdit>
#include <QTextBrowser>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QFile>
#include <QTimer>
#define SHOWOVERLAY
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Total styleSheet
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet=tr(file.readAll());
    this->setStyleSheet(styleSheet);

    //Setup Overlay
    ui->OverLay->setAttribute(Qt::WA_TransparentForMouseEvents);

    #ifdef SHOWOVERLAY
    ui->OverLay->setStyleSheet("background-color: rgba(85, 255, 127, 0)");
    #else
    ui->OverLay->setStyleSheet("background-color: rgba(85, 255, 127, 100)");
    #endif

    Setup_MenuBT();
    Setup_update();

    ui->RightStacked->setCurrentIndex(0);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showEvent(QShowEvent* event){
    QMainWindow::showEvent(event);
}
void MainWindow::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);

    ui->ContentLayout->setGeometry(ui->MainLayout->rect());
    ui->OverLay->setGeometry(ui->MainLayout->rect());
}



