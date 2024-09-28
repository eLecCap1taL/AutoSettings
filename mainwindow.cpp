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

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet=tr(file.readAll());
    this->setStyleSheet(styleSheet);

    connect(ui->CheckUpdateButton,&QPushButton::clicked,this,&MainWindow::UpdateCheckButtonClicked);

    RefreshCheckLabel();

    net=new QNetworkAccessManager(this);
    IsQuerying=0;

    Setup_MenuBT();

    ui->RightStacked->setCurrentIndex(0);
}

void MainWindow::RefreshCheckLabel(){
    ui->UpdateCheckLabel->setText(QString(tr("<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">更新检查</span></p><p><span style=\" font-size:10pt; font-weight:700;\">CSRM  CFG Manager 版本</span></p><p>当前版本：%1</p><p>最新版本：%2</p><p><span style=\" font-size:10pt; font-weight:700;\">CSRM CFG 版本</span></p><p>当前版本：%3</p><p>最新版本：%4</p></body></html>")).arg(CURMANAGERVERSION,LSTMANAGERVERSION,CURCSRMVERSION,LSTCSRMVERSION));
}

void MainWindow::showEvent(QShowEvent* event){
    QMainWindow::showEvent(event);

    ui->RightStacked->ReFreshAllPages();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::QueryQStringFromUrl(const QUrl &url,std::function<void(const QStringRequest& )> callback,int TIMELIMIT,bool FORCE){
    if(IsQuerying>0 && !FORCE)  return false;
    IsQuerying++;

    QNetworkRequest request(url);
    QNetworkReply *reply = net->get(request);

    QTimer* tm=new QTimer(this);
    tm->start(TIMELIMIT);
    connect(tm,&QTimer::timeout,this,[reply,callback,this,tm]{
        reply->abort();
        this->IsQuerying--;
        tm->deleteLater();
        reply->deleteLater();
        QStringRequest ret(false,"TIMEOUT");
        callback(ret);
    });
    connect(reply,&QNetworkReply::finished,this,[reply,tm,callback,this]{
        if(tm==nullptr || reply==nullptr)   return ;
        tm->stop();
        QStringRequest ret;
        if(reply->error() == QNetworkReply::NoError){
            ret.first=true;
            ret.second=QString::fromUtf8(reply->readAll());
        }else{
            ret.first=false;
            ret.second=reply->errorString();
        }
        this->IsQuerying--;
        reply->deleteLater();
        tm->deleteLater();
        if(ret.second=="Operation canceled")    return ;
        callback(ret);
    });
    return true;
}

void MainWindow::UpdateCheckButtonClicked(){
    bool firstqr=QueryQStringFromUrl(QUrl("https://eleccap1tal.github.io/CSRM/ManagerVersion.html"),[this](const QStringRequest& ret){
        qDebug()<<ret.first<<' '<<ret.second<<Qt::endl;
        if(ret.first==false)   return ;
        this->LSTMANAGERVERSION=ret.second;
        this->RefreshCheckLabel();
    },5000,false);
    if(!firstqr)    return ;
    QueryQStringFromUrl(QUrl("https://eleccap1tal.github.io/CSRM/CSRMVersion.html"),[this](const QStringRequest& ret){
        qDebug()<<ret.first<<' '<<ret.second<<Qt::endl;
        if(ret.first==false)   return ;
        this->LSTCSRMVERSION=ret.second;
        this->RefreshCheckLabel();
    },5000,true);
    qDebug()<<"Done\n";
}

