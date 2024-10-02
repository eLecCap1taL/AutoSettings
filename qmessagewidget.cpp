#include "qmessagewidget.h"
#include <QTimer>

QMessageWidget::QMessageWidget(QWidget *parent,int SPACEL,int BEGINL)
    : QWidget{parent},
    SPACE(SPACEL),
    BEGIN(BEGINL)
{}

void QMessageWidget::SomeMessageDeleted(){
    this->ls.erase(std::remove(ls.begin(),ls.end(),sender()),ls.end());
    this->RebuildMessages();
    // qDebug()<<"MEG DEL\n";
    qobject_cast<QPopMessage*>(sender())->PrepareToDeleteLater();
}

void QMessageWidget::RebuildMessages(bool IM){
    // qDebug()<<"Rebuild Begin\n";
    auto br=this->rect().bottomRight();
    br.setY(br.y()-BEGIN);
    for(int i=0;i<ls.size();i++){
        br-=QPoint(0,ls[i]->rect().height());
        br-=QPoint(0,SPACE);
        auto st=QRect(ls[i]->mapToParent(QPoint(0,0)),ls[i]->size());
        auto tg=QRect(br.x()-ls[i]->width()+1,br.y(),ls[i]->width(),ls[i]->height());
        ls[i]->MoveToGeometry(st,tg,IM);
        // qDebug()<<st.topLeft()<<' '<<tg.topLeft()<<'\n';
    }
    // this->repaint();
}

void QMessageWidget::AddMessage(const QString tx,int status){
    auto pme=new QPopMessage(this,tx,status);
    pme->show();
    connect(pme,&QPopMessage::FadeoutFinished,this,&QMessageWidget::SomeMessageDeleted);
    ls.push_front(pme);
    QTimer::singleShot(0,this,[this]{
        this->RebuildMessages();
    });
}

void QMessageWidget::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);

    this->RebuildMessages(true);
}
