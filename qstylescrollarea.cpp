#include "qstylescrollarea.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTextBrowser>

QStyleScrollArea::QStyleScrollArea(QWidget *parent)
    : QScrollArea{parent}
{}

void QStyleScrollArea::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);
    return ;
    // widget()->adjustSize();
    if(widget()->layout()->count()==0)  return ;
    auto w=qobject_cast<QWidget*>(widget()->layout()->itemAt(0)->widget());
    auto l=qobject_cast<QTextBrowser*>(w->layout()->itemAt(0)->widget());
    l->adjustSize();
    widget()->setFixedWidth(width());
    // qDebug()<<l->rect()<<Qt::endl;
    qDebug()<<w->rect()<<Qt::endl;
    // qDebug()<<qobject_cast<QWidget*>(widget()->layout()->itemAt(1)->spacerItem()->)<<Qt::endl;
    // qDebug()<<widget()->rect()<<Qt::endl;
    qDebug()<<Qt::endl;
}
