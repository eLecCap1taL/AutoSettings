#include "qkeepbutton.h"
#include <QPalette>
#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
#include <QImage>
#include <QGraphicsEffect>
#include <QGraphicsColorizeEffect>

QKeepButton::QKeepButton(QWidget *parent,int ANIMATION)
    : QPushButton(parent),
    ANIMATION_TIME(ANIMATION),
    ani(nullptr)
{
    auto lay=new QHBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    lbsvg=new QLabel(this);
    lbtext=new QLabel(this);
    lbtext->setStyleSheet("background-color: rbga(0,0,0,0);\ntext-align: left;\nfont: 10pt Microsoft YaHei UI;\nfont-weight: bold;padding-left: 0px");
    lbsvg->setStyleSheet("background-color: rbga(0,0,0,0);");
    lbsvg->setMaximumWidth(50);
    this->setLayout(lay);
    lay->addWidget(lbsvg);
    lay->addWidget(lbtext);

    this->setChangerFromProcess(std::shared_ptr<QQSSChanger>(new QQSSChanger()));

    this->setPressProcess(0.0);

    this->isPressed=false;

    connect(this,&QPushButton::clicked,this,&QKeepButton::checkDis);
}
void QKeepButton::checkDis(){
    for(auto &func:disls){
        if(func())  return ;
    }
    this->buttonPressed(false);
}
void QKeepButton::setSVGPath(QString s){
    this->svgPath=s;
    this->refreshStyleSheetFromProperty();
}
void QKeepButton::showEvent(QShowEvent* event){
    QPushButton::showEvent(event);
    lbtext->setText(this->text());
    this->setText("");
}
void QKeepButton::refreshStyleSheetFromProperty(){
    this->setStyleSheet(changerFromProcess->getQSS(this->property("pressProcess").toReal()));
    if(this->svgPath!=""){
        // set svg
        auto res=changerFromProcess->getInner(this->property("pressProcess").toReal());
        auto cl=QColor(res[1][0],res[1][1],res[1][2]);
        QPixmap pixmap(svgPath);
        auto ef=new QGraphicsColorizeEffect(lbsvg);
        ef->setColor(cl);
        lbsvg->setGraphicsEffect(ef);
        lbsvg->setPixmap(pixmap);
    }
}
void QKeepButton::refreshPattleFromProperty(){
    auto res=changerFromProcess->getInner(this->property("pressProcess").toReal());
    auto pal=this->palette();
    pal.setColor(QPalette::Button,QColor(res[0][0],res[0][1],res[0][2]));
    pal.setColor(QPalette::ButtonText,QColor(res[1][0],res[1][1],res[1][2]));
    this->setPalette(pal);
    this->update();
}
void QKeepButton::setChangerFromProcess(std::shared_ptr<QQSSChanger> cg){
    changerFromProcess=cg;
}
void QKeepButton::stopAnimation(){
    if(ani!=nullptr){
        ani->stop();
        ani->deleteLater();
        ani=nullptr;
    }
}
void QKeepButton::setPressProcess(qreal dt){
    this->setProperty("pressProcess",dt);
    this->refreshStyleSheetFromProperty();
}
void QKeepButton::buttonPressed(bool FORCE){
    if(isPressed == true)   return ;
    isPressed = true;
    emit buttonEnabled();
    qDebug()<<this->objectName()<<" press\n";
    stopAnimation();
    qDebug()<<"press 0\n";
    if(FORCE){
        setPressProcess(1.0);
        return ;
    }
    ani=new QPropertyAnimation(this,"pressProcess");
    ani->setDuration(ANIMATION_TIME);
    ani->setStartValue(this->property("pressProcess").toReal());
    ani->setEndValue(qreal(1.0));
    ani->setEasingCurve(QEasingCurve::InOutQuad);
    ani->start();
    connect(ani,&QPropertyAnimation::valueChanged,this,&QKeepButton::refreshStyleSheetFromProperty);
}
void QKeepButton::buttonReleased(bool FORCE){
    if(isPressed == false)  return ;
    isPressed = false;
    emit buttonDisabled();
    qDebug()<<this->objectName()<<" release\n";
    stopAnimation();
    qDebug()<<"release 0\n";
    if(FORCE){
        setPressProcess(0.0);
        return ;
    }
    ani=new QPropertyAnimation(this,"pressProcess");
    ani->setDuration(ANIMATION_TIME);
    ani->setStartValue(this->property("pressProcess").toReal());
    ani->setEndValue(qreal(0.0));
    ani->setEasingCurve(QEasingCurve::InOutQuad);
    ani->start();
    connect(ani,&QPropertyAnimation::valueChanged,this,&QKeepButton::refreshStyleSheetFromProperty);
}
void QKeepButton::addSwitchDisable(std::function<bool()> func){
    disls.push_back(func);
}
void QKeepButton::prepareToDeleteLater(){
    ani->deleteLater();
    this->deleteLater();
}

void QKeepButton::paintEvent(QPaintEvent* event){
    QPushButton::paintEvent(event);
}
