#include "mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QTextEdit>
#include <QTextBrowser>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QFile>
#include <QTimer>
#include <QRegion>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPainter>

void MainWindow::Setup_Frameless(){
    setAttribute(Qt::WA_Hover,true);
    int cornerRadius = 25;
    QPainterPath path;
    path.addRoundedRect(0, 0, width(), height(), cornerRadius, cornerRadius);
    setMask(QRegion(path.toFillPolygon(QTransform()).toPolygon()));
    setWindowFlags(Qt::FramelessWindowHint);
}
void MainWindow::mousePressEvent(QMouseEvent *event) {
    dragging=1;
    event->accept();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    auto g=geometry();
    g.setBottomRight(g.bottomRight()+QPoint(1,1));
    setGeometry(g);
    return ;
    QMainWindow::mouseMoveEvent(event);
    qDebug()<<size()<<"\n";
    auto mp=mapToGlobal(event->pos());
    if(lstResizeCur){
        qDebug()<<resizeDirection<<"\n";
        QSize ts=size();
        QPoint tp=this->pos();
        qDebug()<<ts<<' '<<tp<<' '<<mp<<"\n";
        // if(resizeDirection%3==0){
        //     ts.setWidth(tp.x()+ts.width()-mp.x());
        //     tp.setX(mp.x());
        // }
        ts=QSize(1000,1000);
        resize(ts);
        update();
        // setGeometry(QRect(tp,ts));
    }
    // event->accept();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    dragging=0;
    event->accept();
}
// void MainWindow::enterEvent(QEnterEvent *event) {
//     QMainWindow::enterEvent(event);
// }
// void MainWindow::leaveEvent(QEvent *event) {
//     QMainWindow::leaveEvent(event);
// }
bool MainWindow::event(QEvent* e){
    if(QEvent::HoverMove == e->type() && !dragging)
    {
        auto ts=QSize(1000,1000);
        resize(ts);
        update();
        QHoverEvent *hoverEvent = static_cast<QHoverEvent*>(e);

        auto mp=hoverEvent->oldPos();
        int W=0,H=0;
        if(mp.x()<=EDGERESIZE)  W=-1;
        if(mp.x()+EDGERESIZE>width())   W=1;
        if(mp.y()<=EDGERESIZE)  H=-1;
        if(mp.y()+EDGERESIZE>height())  H=1;
        if(mp.x()<=EDGERESIZE*2 && mp.y()<=EDGERESIZE*2)    W=-1,H=-1;
        if(mp.x()+EDGERESIZE*2>width() && mp.y()<=EDGERESIZE*2)    W=1,H=-1;
        if(mp.x()<=EDGERESIZE*2 && mp.y()+EDGERESIZE*2>height())    W=-1,H=1;
        if(mp.x()+EDGERESIZE*2>width() && mp.y()+EDGERESIZE*2>height())    W=1,H=1;

        resizeDirection=(1+W)+(1+H)*3;

        qDebug()<<W<<' '<<H<<Qt::endl;

        auto setCur = [this,W,H]()->void{
            qDebug()<<W<<' '<<H<<Qt::endl;
            qDebug()<<lstResizeCur<<Qt::endl;
            if(W*H==1){
                this->setCursor(Qt::SizeFDiagCursor);
                lstResizeCur=1;
                return ;
            }
            if(W*H==-1){
                this->setCursor(Qt::SizeBDiagCursor);
                lstResizeCur=1;
                return ;
            }
            if(W==0 && H==0){
                if(lstResizeCur)    this->setCursor(Qt::ArrowCursor),lstResizeCur=0;
                return ;
            }
            if(W==0){
                this->setCursor(Qt::SizeVerCursor);
                lstResizeCur=1;
                return ;
            }
            if(H==0){
                this->setCursor(Qt::SizeHorCursor);
                lstResizeCur=1;
                return ;
            }
        };
        setCur();
    }
    return QWidget::event(e);
}


