#ifndef FADEQSTACKEDWIDGET_H
#define FADEQSTACKEDWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QPropertyAnimation>

class FadeQStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit FadeQStackedWidget(QWidget *parent = nullptr);
    bool isAnimating = false;

public slots:
    void SwitchPageTo(int index);

private:
    QPropertyAnimation* PageFadeIn(QWidget *widget);

};

#endif // FADEQSTACKEDWIDGET_H
