#include "qpopmessage.h"
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

QPopMessage::QPopMessage(QWidget *parent,QString tx,int LIVINGTIME,int ANIMATION)
    : QWidget{parent},
    ANIMATION_TIME(ANIMATION)
{
    //can not exit
    if(LIVINGTIME<ANIMATION_TIME*2) exit(1);

    //fadeout timer
    auto tm=new QTimer();
    tm->start(LIVINGTIME-ANIMATION_TIME);
    connect(tm,&QTimer::timeout,this,&QPopMessage::Animation_Fadeout);

    auto layout=new QVBoxLayout();
    auto lb=new QLabel(tx);
    this->setLayout(layout);
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    this->setStyleSheet("background-color: #4CAF50;\ncolor: white");
    lb->setStyleSheet("background: transparent");
    layout->addWidget(lb);

    this->Animation_Fadein();
}

void QPopMessage::Animation_Fadein(){
    auto effect=new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.0);
    this->setGraphicsEffect(effect);

    auto ani=new QPropertyAnimation(effect,"opacity");
    ani->setDuration(ANIMATION_TIME);
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
    ani->setDuration(ANIMATION_TIME);
    ani->setStartValue(1.0);
    ani->setEndValue(0.0);
    ani->setEasingCurve(QEasingCurve::InOutQuad);
    ani->start(QAbstractAnimation::DeleteWhenStopped);

    connect(ani,&QPropertyAnimation::finished,this,[this](){
        emit this->FadeoutFinished();
        this->deleteLater();
    });
}

/*
 * [0,0] 构造
 * [0,ANIMATIONTIME] 播放FadeIn动画
 * [ANIMATIONTIME,LIVINGTIME-ANIMATIONTIME] 持续
 * [LIVINGTIME-ANIMATIONTIME] 播放FadeOut动画
 * [LIVINGTIME,LIVINGTIME] 构析 发出信号Fadeouted
*/
