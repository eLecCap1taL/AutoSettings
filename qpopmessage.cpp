#include "qpopmessage.h"
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QFrame>
#include <QPoint>
#include <QGraphicsColorizeEffect>

int QPopMessage::SUCCESS=1;
int QPopMessage::ERROR=2;
int QPopMessage::WARING=3;
int QPopMessage::NORMAL=0;

QPopMessage::QPopMessage(QWidget *parent,QString tx,int status,int LIVINGTIME,int FADEANIMATION,int MOVEANIMATION)
    : QFrame{parent},
    FADEANIMATION_TIME(FADEANIMATION),
    MOVEANIMATION_TIME(MOVEANIMATION),
    moving_ani(nullptr),
    MOVED(false)
{
    LIVINGTIME*=(double)tx.length()/7.5;
    //can not exit
    if(LIVINGTIME<FADEANIMATION_TIME*2) exit(1);

    //fadeout timer
    auto tm=new QTimer();
    tm->start(LIVINGTIME-FADEANIMATION_TIME);
    connect(tm,&QTimer::timeout,this,&QPopMessage::Animation_Fadeout);

    auto layout=new QVBoxLayout();
    auto lb=new QLabel(tx);
    layout->setContentsMargins(10,5,10,5);
    // this->setStyleSheet("padding-left: 30px");
    this->setLayout(layout);
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    if(status==1){
        this->setStyleSheet("background-color: rgba(76, 175, 80, 230)"); //success
    }else if(status==2){
        this->setStyleSheet("background-color: rgba(255, 0, 0, 230)"); //error
    }else if(status==3){
        this->setStyleSheet("background-color: rgba(255, 193, 7, 230)"); //warn
    }else{
        this->setStyleSheet("background-color: rgba(33, 150, 243, 230)"); //normal
    }
    lb->setStyleSheet("background: rgba(255,255,255,0);\nfont-weight: bold;\nfont: 11pt \"微软雅黑\";\ncolor: white");
    layout->addWidget(lb);

    this->setProperty("opacity",0.0);

    // connect(this,&QPopMessage::Fading,this,&QPopMessage::setColor);

    this->Animation_Fadein();
}

void QPopMessage::Animation_Fadein(){
    auto effect=new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.0);
    this->setGraphicsEffect(effect);

    auto ani=new QPropertyAnimation(effect,"opacity");
    ani->setDuration(FADEANIMATION_TIME);
    ani->setStartValue(0.0);
    ani->setEndValue(1.0);
    ani->setEasingCurve(QEasingCurve::InOutQuad);
    ani->start(QAbstractAnimation::DeleteWhenStopped);

    connect(ani,&QPropertyAnimation::finished,this,&QPopMessage::FadeinFinished);
    connect(ani,&QPropertyAnimation::valueChanged,this,&QPopMessage::Fading);
}
void QPopMessage::Animation_Fadeout(){
    auto effect=new QGraphicsOpacityEffect(this);
    effect->setOpacity(1.0);
    this->setGraphicsEffect(effect);

    auto ani=new QPropertyAnimation(effect,"opacity");
    ani->setDuration(FADEANIMATION_TIME);
    ani->setStartValue(1.0);
    ani->setEndValue(0.0);
    ani->setEasingCurve(QEasingCurve::InOutQuad);
    ani->start(QAbstractAnimation::DeleteWhenStopped);

    connect(ani,&QPropertyAnimation::finished,this,[this](){
        emit this->FadeoutFinished();
    });
    connect(ani,&QPropertyAnimation::valueChanged,this,&QPopMessage::Fading);
}
void QPopMessage::setColor(){
    qreal dt = 1.0-this->property("opacity").toReal();
    int alpha=100*dt;
    auto cl=QColor(255,255,255,alpha);
    auto g=new QGraphicsColorizeEffect(this);
    g->setColor(cl);
    // this->setGraphicsEffect(g);
}
void QPopMessage::PrepareToDeleteLater(){
    if(moving_ani!=nullptr){
        moving_ani->stop();
        moving_ani->deleteLater();
    }
    this->deleteLater();
}

void QPopMessage::MoveToGeometry(const QRect st,const QRect tg,bool IM){
    // MOVED=0;
    if(!MOVED || IM){
        this->setGeometry(tg);
        MOVED=1;
        return ;
    }
    if(moving_ani!=nullptr){
        moving_ani->stop();
        moving_ani->deleteLater();
        moving_ani=nullptr;
    }
    moving_ani=new QPropertyAnimation(this,"geometry");
    moving_ani->setDuration(MOVEANIMATION_TIME);
    moving_ani->setStartValue(st);
    // qDebug()<<st<<Qt::endl;
    moving_ani->setEndValue(tg);
    moving_ani->setEasingCurve(QEasingCurve::InOutQuad);
    moving_ani->start();
}

/*
 * [0,0] 构造
 * [0,ANIMATIONTIME] 播放FadeIn动画
 * [ANIMATIONTIME,LIVINGTIME-ANIMATIONTIME] 持续
 * [LIVINGTIME-ANIMATIONTIME] 播放FadeOut动画
 * [LIVINGTIME,LIVINGTIME] 发出信号Fadeouted !!交由槽函数构析!!
*/
