#ifndef QKEEPBUTTON_H
#define QKEEPBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QPropertyAnimation>
#include "qqsschanger.h"
#include <QLabel>

class QKeepButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QKeepButton(QWidget *parent = nullptr,int ANIMATION = 200);

    bool isPressed;
    QPropertyAnimation* ani,svg_ani;
    QString svgPath;
    std::shared_ptr<QQSSChanger> changerFromProcess;
    QLabel* lbsvg;
    QLabel* lbtext;

    void setSVGPath(QString s);
    void setChangerFromProcess(std::shared_ptr<QQSSChanger> cg);
    void addSwitchDisable(std::function<bool()> func);

private:
    int ANIMATION_TIME;
    std::vector<std::function<bool()>> disls;
public slots:
    void buttonPressed(bool FORCE = 0);
    void buttonReleased(bool FORCE = 0);
    void refreshStyleSheetFromProperty();
    void refreshPattleFromProperty();
    void prepareToDeleteLater();
    void setPressProcess(qreal dt = 0);
    void stopAnimation();
protected:
    void paintEvent(QPaintEvent* event)override;
    void showEvent(QShowEvent* event)override;
protected slots:
    void checkDis();
signals:
    void buttonEnabled();
    void buttonDisabled();
    void buttonAnimating(qreal dt);
};

#endif // QKEEPBUTTON_H
