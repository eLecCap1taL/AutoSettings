#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QPixmap>
#include <QParallelAnimationGroup>

void MainWindow::Setup_MenuBT(){
    MenuBT = new QUniqueButtonGroup(this);
    MenuBT->addButton(ui->MenuBT0);
    MenuBT->addButton(ui->MenuBT1);
    MenuBT->addButton(ui->MenuBT2);
    MenuBT->addButton(ui->MenuBT3);

    MenuBT->addSwitchDisable([this]()->bool{
        return this->ui->RightStacked->askIfAnimating();
    });

    std::shared_ptr<QQSSChanger> MenuBT_QSS(new QQSSChanger());
    MenuBT_QSS->addEffect("background-color",{255,255,255},{233,239,255},{"rgb(",")"});
    MenuBT_QSS->addEffect("color",{77,77,77},{27, 89, 249},{"rgb(",")"});
    MenuBT_QSS->addEffect("border-radius: 10px;\npadding-left: 15px");
    MenuBT->setChangerFromProcess(MenuBT_QSS);
    ui->MenuBT0->buttonPressed(true);
    connect(ui->MenuBT0,&QKeepButton::buttonEnabled,ui->RightStacked,&FadeQStackedWidget::SwitchPageToSlot);
    connect(ui->MenuBT1,&QKeepButton::buttonEnabled,ui->RightStacked,&FadeQStackedWidget::SwitchPageToSlot);
    connect(ui->MenuBT2,&QKeepButton::buttonEnabled,ui->RightStacked,&FadeQStackedWidget::SwitchPageToSlot);
    connect(ui->MenuBT3,&QKeepButton::buttonEnabled,ui->RightStacked,&FadeQStackedWidget::SwitchPageToSlot);

    ui->MenuBT0->setSVGPath(":/home.svg");
    ui->MenuBT1->setSVGPath(":/settings.svg");
    ui->MenuBT2->setSVGPath(":/download.svg");
    ui->MenuBT3->setSVGPath(":/add.svg");
}

// int GetAnother(int l,int r,int x){
//     if(l>r) std::swap(l,r);
//     return r-(x-l);
// }
// int GetAnotherToRange(int l,int r,int x,int L,int R){
//     if(l>r) std::swap(l,r);
//     if(L>R) std::swap(L,R);
//     x=r-(x-l);
//     return (int)(L+(double)(R-L+1)*(double)(x-l+1)/(double)(r-l+1)-1);
// }
// int ToRange(int l,int r,int x,int L,int R){
//     if(l>r) std::swap(l,r);
//     if(L>R) std::swap(L,R);
//     return (int)(L+(double)(R-L+1)*(double)(x-l+1)/(double)(r-l+1)-1);
// }
// QString MenuBTStyleType::styleSheet(){
//     QString ret;
//     ret+="background-color: rgb(";
//     ret+=QString::number(r);
//     ret+=", ";
//     ret+=QString::number(g);
//     ret+=", 255);\ncolor: rgb(";
//     ret+=QString::number(GetAnotherToRange(MainWindow::MenuBTStyle[0].r,MainWindow::MenuBTStyle[1].r,r,52,255));
//     ret+=", ";
//     ret+=QString::number(GetAnotherToRange(MainWindow::MenuBTStyle[0].g,MainWindow::MenuBTStyle[1].g,g,70,255));
//     ret+=", 255);\nborder-radius: ";
//     ret+=QString::number(ra);
//     ret+="px;\nborder: ";
//     ret+=QString::number(ToRange(MainWindow::MenuBTStyle[0].r,MainWindow::MenuBTStyle[1].r,r,0,2));
//     ret+="px solid rgb(";
//     ret+=QString::number(GetAnotherToRange(MainWindow::MenuBTStyle[0].r,MainWindow::MenuBTStyle[1].r,r,170,196));
//     ret+=", ";
//     ret+=QString::number(GetAnotherToRange(MainWindow::MenuBTStyle[0].g,MainWindow::MenuBTStyle[1].g,g,190,212));
//     ret+=", 255)";
//     return ret;
// }
// MenuBTStyleType MenuBTStyleType::ChangeY(int _Y){
//     return MenuBTStyleType(r,g,ra,_Y);
// }
// MenuBTStyleType MainWindow::MenuBTStyle[2]={
//     MenuBTStyleType(226,232,4,0),
//     MenuBTStyleType(102,130,20,-50)
// };
// void MainWindow::Setup_MenuBT(){
//     MenuBTls.push_back(ui->MenuBT0);
//     MenuBTls.push_back(ui->MenuBT1);
//     MenuBTls.push_back(ui->MenuBT2);
//     MenuBTls.push_back(ui->MenuBT3);

//     ui->MenuBT0->setProperty("bt_index",0);
//     ui->MenuBT1->setProperty("bt_index",1);
//     ui->MenuBT2->setProperty("bt_index",2);
//     ui->MenuBT3->setProperty("bt_index",3);
//     for(auto &bt:MenuBTls){
//         if(bt->objectName()=="MenuBT0"){
//             bt->setProperty("Enabled",1);
//             bt->setProperty("LstEnabled",1);
//             bt->setProperty("styleSheet",MenuBTStyle[1].styleSheet());
//             bt->setProperty("my_styleSheet",QVariant::fromValue(MenuBTStyle[1].ChangeY(bt->y())));
//             bt->setProperty("styleSheet",bt->property("my_styleSheet").value<MenuBTStyleType>().styleSheet());
//             QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//             shadow->setBlurRadius(15);
//             shadow->setXOffset(0);
//             shadow->setYOffset(0);
//             // bt->setGraphicsEffect(shadow);
//         }else{
//             bt->setProperty("Enabled",0);
//             bt->setProperty("LstEnabled",0);
//             bt->setProperty("styleSheet",MenuBTStyle[0].styleSheet());
//             bt->setProperty("my_styleSheet",QVariant::fromValue(MenuBTStyle[0].ChangeY(bt->y())));
//             bt->setProperty("styleSheet",bt->property("my_styleSheet").value<MenuBTStyleType>().styleSheet());
//             QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//             shadow->setBlurRadius(0);
//             shadow->setXOffset(0);
//             shadow->setYOffset(0);
//             // bt->setGraphicsEffect(shadow);
//         }
//     }
//     return ;

//     connect(ui->MenuBT0, SIGNAL(clicked()), this, SLOT(MenuBTClicked()));
//     connect(ui->MenuBT1, SIGNAL(clicked()), this, SLOT(MenuBTClicked()));
//     connect(ui->MenuBT2, SIGNAL(clicked()), this, SLOT(MenuBTClicked()));
//     connect(ui->MenuBT3, SIGNAL(clicked()), this, SLOT(MenuBTClicked()));
// }
// void MainWindow::UpdateMenuBTStatus(){
//     for(auto &bt:MenuBTls){
//         if(bt->property("LstEnabled")==bt->property("Enabled")) continue;
//         bt->setProperty("styleSheet",bt->property("my_styleSheet").value<MenuBTStyleType>().styleSheet());
//     }
// }
// void MainWindow::MenuBTClicked(){
//     if(ui->RightStacked->isAnimating)   return ;
//     for(auto &bt:MenuBTls){
//         bt->setProperty("LstEnabled",bt->property("Enabled"));
//         bt->setProperty("Enabled",(sender()->objectName()==bt->objectName()?1:0));
//     }
//     for(auto &bt:MenuBTls){
//         if(bt->property("LstEnabled")!=bt->property("Enabled")){
//             //deal with animation

//             auto ani=new QPropertyAnimation(bt,"my_styleSheet");
//             ani->setDuration(200);
//             ani->setStartValue(QVariant::fromValue(MenuBTStyle[bt->property("LstEnabled").toBool()]));
//             ani->setEndValue(QVariant::fromValue(MenuBTStyle[bt->property("Enabled").toBool()]));
//             connect(ani, &QPropertyAnimation::valueChanged, this, &MainWindow::UpdateMenuBTStatus);
//             ani->start();

//             auto gbani=new QPropertyAnimation(qobject_cast<QGraphicsDropShadowEffect*>(bt->graphicsEffect()),"blurRadius");
//             gbani->setDuration(200);
//             gbani->setStartValue(bt->property("LstEnabled").toBool()?15:0);
//             gbani->setEndValue(bt->property("Enabled").toBool()?15:0);
//             gbani->setEasingCurve(QEasingCurve::InOutQuad);
//             gbani->start();
//         }
//         if(bt->property("Enabled").toBool()){
//             //change page

//             int index=bt->property("bt_index").toInt();
//             if(ui->RightStacked->currentIndex()!=index) ui->RightStacked->SwitchPageTo(index);
//         }
//     }
// }
