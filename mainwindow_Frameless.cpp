#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    // return ;
    // setAttribute(Qt::WA_Hover,true);
    // int cornerRadius = 25;
    // QPainterPath path;
    // path.addRoundedRect(0, 0, width(), height(), cornerRadius, cornerRadius);
    // setMask(QRegion(path.toFillPolygon(QTransform()).toPolygon()));
    // setStyleSheet("border: 2px solid black; border-radius: 25px; background-color: white;");
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    // ui->MaLayout->setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);
    effect->setColor(Qt::gray);
    effect->setBlurRadius(20);
    ui->ShadowFrame->setGraphicsEffect(effect);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    MoveCounter=0;
    dragging=1;
    dragStartPos=event->pos();
    dragStartGeo=geometry();
    // event->accept();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    auto mp=mapToGlobal(event->pos());
    auto &D=dragStartPos;
    auto &G=dragStartGeo;
    auto Min=minimumSize();
    if(lstResizeCur){
        if(MoveCounter!=15){
            MoveCounter++;
            return ;
        }
        MoveCounter=0;
        qDebug()<<resizeDirection<<"\n";
        QRect tg=G;
        if(resizeDirection%3==0){
            tg.setLeft(std::min(G.right()-Min.width()+1,mp.x()-D.x()));
        }else if(resizeDirection%3==2){
            tg.setRight(std::max(G.left()+Min.width()-1,mp.x()+G.width()-D.x()));
        }
        if(resizeDirection/3==0){
            tg.setTop(std::min(G.bottom()-Min.height()+1,mp.y()-D.y()));
        }else if(resizeDirection/3==2){
            tg.setBottom(std::max(G.top()+Min.height()-1,mp.y()+G.height()-D.y()));
        }
        if(geometry()!=tg){
            qDebug()<<tg<<"\n";
            setGeometry(tg);
        }
    }else{
        QRect tg(mp-D,G.size());
        if(geometry()!=tg){
            qDebug()<<tg<<"\n";
            setGeometry(tg);
        }
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    auto mp=mapToGlobal(event->pos());
    auto &D=dragStartPos;
    auto &G=dragStartGeo;
    auto Min=minimumSize();
    if(lstResizeCur){
        qDebug()<<resizeDirection<<"\n";
        QRect tg=G;
        if(resizeDirection%3==0){
            tg.setLeft(std::min(G.right()-Min.width()+1,mp.x()-D.x()));
        }else if(resizeDirection%3==2){
            tg.setRight(std::max(G.left()+Min.width()-1,mp.x()+G.width()-D.x()));
        }
        if(resizeDirection/3==0){
            tg.setTop(std::min(G.bottom()-Min.height()+1,mp.y()-D.y()));
        }else if(resizeDirection/3==2){
            tg.setBottom(std::max(G.top()+Min.height()-1,mp.y()+G.height()-D.y()));
        }
        if(geometry()!=tg){
            qDebug()<<tg<<"\n";
            setGeometry(tg);
        }
    }
    dragging=0;
    // event->accept();
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

        // qDebug()<<W<<' '<<H<<Qt::endl;

        auto setCur = [this,W,H]()->void{
            // qDebug()<<W<<' '<<H<<Qt::endl;
            // qDebug()<<lstResizeCur<<Qt::endl;
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



