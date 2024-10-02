#ifndef QPOPMESSAGE_H
#define QPOPMESSAGE_H

#include <QWidget>
#include <QString>
#include <QFrame>
#include <QPropertyAnimation>

class QPopMessage : public QFrame
{
    Q_OBJECT
public:
    explicit QPopMessage(QWidget *parent = nullptr,QString tx="",int status = 0,int LIVINGTIME=2000,int FADEANIMATION=300,int MOVEANIMATION=100);
    void PrepareToDeleteLater();

    void MoveToGeometry(const QRect st,const QRect tg,bool IM);

    static int SUCCESS;
    static int ERROR;
    static int WARING;
    static int NORMAL;

private:
    int FADEANIMATION_TIME;
    int MOVEANIMATION_TIME;
    QPropertyAnimation* moving_ani;
    bool MOVED;
private slots:
    void Animation_Fadein();
    void Animation_Fadeout();
    void setColor();
signals:
    void FadeinFinished();
    void FadeoutFinished();
    void Fading();
};



#endif // QPOPMESSAGE_H
