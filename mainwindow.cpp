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
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Total styleSheet
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet=tr(file.readAll());
    // this->setStyleSheet(styleSheet);

    //Setup Menu
    auto ge=new QGraphicsDropShadowEffect(this);
    ge->setBlurRadius(80);
    ge->setColor(QColor(0, 0, 0, 30));
    ui->LeftWidget->setGraphicsEffect(ge);

    //Setup Overlay
    ui->Overlay->setAttribute(Qt::WA_TransparentForMouseEvents);

    Setup_MenuBT();
    // Setup_update();

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
    ui->Overlay->setGeometry(ui->MainLayout->rect());
}



