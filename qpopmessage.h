#ifndef QPOPMESSAGE_H
#define QPOPMESSAGE_H

#include <QWidget>
#include <QString>

class QPopMessage : public QWidget
{
    Q_OBJECT
public:
    explicit QPopMessage(QWidget *parent = nullptr,QString tx="",int LIVINGTIME=2000,int ANIMATION=300);

private:
    int ANIMATION_TIME;
private slots:
    void Animation_Fadein();
    void Animation_Fadeout();
signals:
    void FadeinFinished();
    void FadeoutFinished();
    void Fading();
};

#endif // QPOPMESSAGE_H
