#ifndef QMESSAGEWIDGET_H
#define QMESSAGEWIDGET_H

#include <QWidget>
#include <deque>
#include "qpopmessage.h"

class QMessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QMessageWidget(QWidget *parent = nullptr,int SPACEL = 10,int BEGIN = 30);
    void AddMessage(const QString tx,int status = 0);
    void RebuildMessages(bool IM = 0);
public slots:
    void SomeMessageDeleted();
protected:
    void resizeEvent(QResizeEvent* event)override;

    std::deque<QPopMessage*> ls;
    int SPACE;
    int BEGIN;
signals:
};

#endif // QMESSAGEWIDGET_H
