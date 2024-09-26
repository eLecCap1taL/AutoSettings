#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QParallelAnimationGroup>


int GetAnother(int l,int r,int x){
    if(l>r) std::swap(l,r);
    return r-(x-l);
}
int GetAnotherToRange(int l,int r,int x,int L,int R){
    if(l>r) std::swap(l,r);
    if(L>R) std::swap(L,R);
    x=r-(x-l);
    return (int)(L+(double)(R-L+1)*(double)(x-l+1)/(double)(r-l+1)-1);
}
int ToRange(int l,int r,int x,int L,int R){
    if(l>r) std::swap(l,r);
    if(L>R) std::swap(L,R);
    return (int)(L+(double)(R-L+1)*(double)(x-l+1)/(double)(r-l+1)-1);
}
QString MenuBTStyleType::styleSheet(){
    QString ret;
    ret+="background-color: rgb(";
    ret+=QString::number(r);
    ret+=", ";
    ret+=QString::number(g);
    ret+=", 255);\ncolor: rgb(";
    ret+=QString::number(GetAnotherToRange(MainWindow::MenuBTStyle[0].r,MainWindow::MenuBTStyle[1].r,r,52,255));
    ret+=", ";
    ret+=QString::number(GetAnotherToRange(MainWindow::MenuBTStyle[0].g,MainWindow::MenuBTStyle[1].g,g,70,255));
    ret+=", 255);\nborder-radius: ";
    ret+=QString::number(ra);
    ret+="px;\nborder: ";
    ret+=QString::number(ToRange(MainWindow::MenuBTStyle[0].r,MainWindow::MenuBTStyle[1].r,r,0,2));
    ret+="px solid rgb(";
    ret+=QString::number(GetAnotherToRange(MainWindow::MenuBTStyle[0].r,MainWindow::MenuBTStyle[1].r,r,170,196));
    ret+=", ";
    ret+=QString::number(GetAnotherToRange(MainWindow::MenuBTStyle[0].g,MainWindow::MenuBTStyle[1].g,g,190,212));
    ret+=", 255);\n";
    ret+="box-shadow: 0px 0px 10px #404040bd";
    return ret;
}
MenuBTStyleType MenuBTStyleType::ChangeY(int _Y){
    return MenuBTStyleType(r,g,ra,_Y);
}
MenuBTStyleType MainWindow::MenuBTStyle[2]={
    MenuBTStyleType(196,212,4,0),
    MenuBTStyleType(102,130,20,-50)
};
void MainWindow::Setup_MenuBT(){
    MenuBTls.push_back(ui->MenuBT1);
    MenuBTls.push_back(ui->MenuBT2);
    MenuBTls.push_back(ui->MenuBT3);

    for(auto &bt:MenuBTls){
        bt->setProperty("Enabled",0);
        bt->setProperty("LstEnabled",0);
        bt->setProperty("styleSheet",MenuBTStyle[0].styleSheet());
        bt->setProperty("my_styleSheet",QVariant::fromValue(MenuBTStyle[0].ChangeY(bt->y())));
        bt->setProperty("styleSheet",bt->property("my_styleSheet").value<MenuBTStyleType>().styleSheet());
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(0);
        shadow->setXOffset(0);
        shadow->setYOffset(0);
        bt->setGraphicsEffect(shadow);
    }

    connect(ui->MenuBT1, SIGNAL(clicked()), this, SLOT(MenuBTClicked()));
    connect(ui->MenuBT2, SIGNAL(clicked()), this, SLOT(MenuBTClicked()));
    connect(ui->MenuBT3, SIGNAL(clicked()), this, SLOT(MenuBTClicked()));
}
void MainWindow::UpdateMenuBTStatus(){
    for(auto &bt:MenuBTls){
        if(bt->property("LstEnabled")==bt->property("Enabled")) continue;
        bt->setProperty("styleSheet",bt->property("my_styleSheet").value<MenuBTStyleType>().styleSheet());
    }
}
void MainWindow::MenuBTClicked(){
    for(auto &bt:MenuBTls){
        bt->setProperty("LstEnabled",bt->property("Enabled"));
        bt->setProperty("Enabled",(sender()->objectName()==bt->objectName()?1:0));
    }
    for(auto &bt:MenuBTls){
        if(bt->property("LstEnabled")!=bt->property("Enabled")){
            auto ani=new QPropertyAnimation(bt,"my_styleSheet");
            ani->setDuration(200);
            ani->setStartValue(QVariant::fromValue(MenuBTStyle[bt->property("LstEnabled").toBool()]));
            ani->setEndValue(QVariant::fromValue(MenuBTStyle[bt->property("Enabled").toBool()]));
            connect(ani, &QPropertyAnimation::valueChanged, this, &MainWindow::UpdateMenuBTStatus);
            ani->start();

            auto gbani=new QPropertyAnimation(qobject_cast<QGraphicsDropShadowEffect*>(bt->graphicsEffect()),"blurRadius");
            gbani->setDuration(200);
            gbani->setStartValue(bt->property("LstEnabled").toBool()?15:0);
            gbani->setEndValue(bt->property("Enabled").toBool()?15:0);
            gbani->setEasingCurve(QEasingCurve::InOutQuad);
            gbani->start();
        }
    }
}
