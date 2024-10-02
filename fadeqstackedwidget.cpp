#include "fadeqstackedwidget.h"
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

FadeQStackedWidget::FadeQStackedWidget(QWidget *parent,int ANIMATION)
    : QStackedWidget{parent},
    ANIMATION_TIME(ANIMATION)
{}
void FadeQStackedWidget::SwitchPageToSlot(){
    qDebug()<<sender()->objectName()<<"\n";
    // if(sender()->objectName()=="MenuBT0")   setCurrentIndex(0);
    // if(sender()->objectName()=="MenuBT1")   setCurrentIndex(1);
    // if(sender()->objectName()=="MenuBT2")   setCurrentIndex(2);
    // if(sender()->objectName()=="MenuBT3")   setCurrentIndex(3);
    // return ;
    if(sender()->objectName()=="MenuBT0")   SwitchPageTo(0);
    if(sender()->objectName()=="MenuBT1")   SwitchPageTo(1);
    if(sender()->objectName()=="MenuBT2")   SwitchPageTo(2);
    if(sender()->objectName()=="MenuBT3")   SwitchPageTo(3);
}
void FadeQStackedWidget::SwitchPageTo(int index) {
    if (index < 0 || index >= count()) exit(0);
    if(index==currentIndex())   return ;
    if (isAnimating)    return ;

    QWidget *curWidget = currentWidget();
    QWidget *nextWidget = widget(index);

    //refresh before animation
    auto curindex=currentIndex();
    setCurrentIndex(index);
    setCurrentIndex(curindex);

    if (curWidget) {
        isAnimating = true;

        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(curWidget);
        curWidget->setGraphicsEffect(effect);
        effect->setOpacity(1.0);

        QPropertyAnimation *fadeOutAnimation = new QPropertyAnimation(effect, "opacity");
        fadeOutAnimation->setDuration(ANIMATION_TIME);
        fadeOutAnimation->setStartValue(1.0);
        fadeOutAnimation->setEndValue(0.0);
        fadeOutAnimation->setEasingCurve(QEasingCurve::InOutQuad);
        fadeOutAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        // qDebug()<<"begin fadeout\n";

        nextWidget->show();
        auto fadein=PageFadeIn(nextWidget);

        connect(fadein, &QPropertyAnimation::finished, this, [this, index, nextWidget](){
            setCurrentIndex(index);
        });
    } else {
        nextWidget->show();
        auto fadein=PageFadeIn(nextWidget);
        connect(fadein, &QPropertyAnimation::finished, this, [this, index, nextWidget](){
            setCurrentIndex(index);
        });
    }
}
QPropertyAnimation* FadeQStackedWidget::PageFadeIn(QWidget *widget) {
    // qDebug()<<"begin fadein\n";
    if (!widget){
        this->isAnimating=0;
        return nullptr;
    }

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);
    effect->setOpacity(0.0);

    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(ANIMATION_TIME);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animation,&QPropertyAnimation::finished,this,[this](){
        this->isAnimating=false;
    });

    return animation;
}
void FadeQStackedWidget::ReFreshAllPages(){
    // int index=currentIndex();
    // for(int i=0;i<count();i++){
    //     setCurrentIndex(i);
    // }
    // setCurrentIndex(index);
}
void FadeQStackedWidget::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);
    ReFreshAllPages();
}
bool FadeQStackedWidget::askIfAnimating(){
    return this->isAnimating;
}
