#ifndef FADEQSTACKEDWIDGET_H
#define FADEQSTACKEDWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QPropertyAnimation>

class FadeQStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit FadeQStackedWidget(QWidget *parent = nullptr,int ANIMATION = 300);
    bool isAnimating = false;

    const int ANIMATION_TIME;

public slots:
    void SwitchPageTo(int index);
    void ReFreshAllPages();

private:
    QPropertyAnimation* PageFadeIn(QWidget *widget);

protected:
    void resizeEvent(QResizeEvent* event)override;

};

#endif // FADEQSTACKEDWIDGET_H
