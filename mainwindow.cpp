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
#include <QRegion>
#include <QPainterPath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    EDGERESIZE(20)
{

    ui->setupUi(this);

    Setup_Frameless();

    // Total styleSheet
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet=tr(file.readAll());
    this->setStyleSheet(styleSheet);
    qDebug()<<styleSheet<<"\n";

    //Setup Menu
    auto ge=new QGraphicsDropShadowEffect(this);
    ge->setBlurRadius(80);
    ge->setColor(QColor(0, 0, 0, 30));
    ui->LeftWidget->setGraphicsEffect(ge);
    // ui->verticalWidget->setAttribute(Qt::WA_TranslucentBackground);

    //Setup Overlay
    ui->Overlay->setAttribute(Qt::WA_TransparentForMouseEvents);

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

    // int cornerRadius = 25;
    // QPainterPath path;
    // path.addRoundedRect(0, 0, width(), height(), cornerRadius, cornerRadius);
    // setMask(QRegion(path.toFillPolygon(QTransform()).toPolygon()));

    auto G=rect();
    auto T=G;
    T.setLeft(G.left()+10);
    T.setRight(G.right()-10);
    T.setTop(G.top()+10);
    T.setBottom(G.bottom()-10);
    // qDebug()<<T<<Qt::endl;
    // T=G;
    // ui->MainLayout->setGeometry(T);
    ui->ShadowFrame->setGeometry(T);
    ui->ContentLayout->setGeometry(T);
    ui->Overlay->setGeometry(T);
}



