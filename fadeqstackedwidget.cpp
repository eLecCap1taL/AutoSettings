#include "fadeqstackedwidget.h"
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

FadeQStackedWidget::FadeQStackedWidget(QWidget *parent)
    : QStackedWidget{parent}
{}

void FadeQStackedWidget::SwitchPageTo(int index) {
    if (index < 0 || index >= count()) exit(0);
    if (isAnimating)    return ;

    QWidget *curWidget = currentWidget();
    QWidget *nextWidget = widget(index);

    if (curWidget) {
        isAnimating = true;

        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(curWidget);
        curWidget->setGraphicsEffect(effect);
        effect->setOpacity(1.0);

        QPropertyAnimation *fadeOutAnimation = new QPropertyAnimation(effect, "opacity");
        fadeOutAnimation->setDuration(300);
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
        setCurrentIndex(index);
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
    animation->setDuration(300);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animation,&QPropertyAnimation::finished,this,[this](){
        this->isAnimating=false;
    });

    return animation;
}
