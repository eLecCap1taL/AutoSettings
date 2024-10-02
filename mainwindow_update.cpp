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


void MainWindow::RefreshCheckLabel(){
    ui->UpdateCheckLabel->setText(QString(tr("<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">更新检查</span></p><p><span style=\" font-size:10pt; font-weight:700;\">CSRM  CFG Manager 版本</span></p><p>当前版本：%1</p><p>最新版本：%2</p><p><span style=\" font-size:10pt; font-weight:700;\">CSRM CFG 版本</span></p><p>当前版本：%3</p><p>最新版本：%4</p></body></html>")).arg(CURMANAGERVERSION,LSTMANAGERVERSION,CURCSRMVERSION,LSTCSRMVERSION));
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
    qDebug()<<ui->MenuBT1->styleSheet()<<Qt::endl;
    qDebug()<<ui->MenuBT2->styleSheet()<<Qt::endl;
    POPTEXT("查询最新版本……",QPopMessage::NORMAL);
    bool firstqr=QueryQStringFromUrl(QUrl("https://cap1tal.top/CSRM/ManagerVersion.html"),[this](const QStringRequest& ret){
        if(ret.first==false){
            POPTEXT("获取 Manager 版本失败",QPopMessage::ERROR);
            return ;
        }
        POPTEXT("获取 Manager 版本成功",QPopMessage::SUCCESS);
        this->LSTMANAGERVERSION=ret.second;
        this->RefreshCheckLabel();
    },5000,false);
    if(!firstqr){
        POPTEXT("上一次请求尚未结束",QPopMessage::WARING);
        return ;
    }
    QueryQStringFromUrl(QUrl("https://cap1tal.top/CSRM/CSRMVersion.html"),[this](const QStringRequest& ret){
        if(ret.first==false){
            POPTEXT("获取 CSRM 版本失败",QPopMessage::ERROR);
            return ;
        }
        POPTEXT("获取 CSRM 版本成功",QPopMessage::SUCCESS);
        this->LSTCSRMVERSION=ret.second;
        this->RefreshCheckLabel();
    },5000,true);
}
void MainWindow::Setup_update(){
    connect(ui->CheckUpdateButton,&QPushButton::clicked,this,&MainWindow::UpdateCheckButtonClicked);
    RefreshCheckLabel();
    net=new QNetworkAccessManager(this);
    IsQuerying=0;
}
