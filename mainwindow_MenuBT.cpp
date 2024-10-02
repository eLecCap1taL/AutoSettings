#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QPixmap>
#include <QParallelAnimationGroup>

void MainWindow::Setup_MenuBT(){
    //Setup Menu
    auto ge=new QGraphicsDropShadowEffect(this);
    ge->setBlurRadius(80);
    ge->setColor(QColor(0, 0, 0, 30));
    ui->LeftWidget->setGraphicsEffect(ge);

    MenuBT = new QUniqueButtonGroup(this);
    MenuBT->addButton(ui->MenuBT0);
    MenuBT->addButton(ui->MenuBT1);
    MenuBT->addButton(ui->MenuBT2);
    MenuBT->addButton(ui->MenuBT3);

    MenuBT->addSwitchDisable([this]()->bool{
        return this->ui->RightStacked->askIfAnimating();
    });
    ui->MenuBT4->addSwitchDisable([]()->bool{
        return true;
    });

    std::shared_ptr<QQSSChanger> MenuBT_QSS(new QQSSChanger());
    MenuBT_QSS->addEffect("background-color",{255,255,255},{233,239,255},{"rgb(",")"});
    MenuBT_QSS->addEffect("color",{77,77,77},{27, 89, 249},{"rgb(",")"});
    MenuBT_QSS->addEffect("border-radius: 10px;\npadding-left: 15px");
    MenuBT->setChangerFromProcess(MenuBT_QSS);
    ui->MenuBT4->setChangerFromProcess(MenuBT_QSS);

    ui->MenuBT0->buttonPressed(true);
    connect(ui->MenuBT0,&QKeepButton::buttonEnabled,ui->RightStacked,&FadeQStackedWidget::SwitchPageToSlot);
    connect(ui->MenuBT1,&QKeepButton::buttonEnabled,ui->RightStacked,&FadeQStackedWidget::SwitchPageToSlot);
    connect(ui->MenuBT2,&QKeepButton::buttonEnabled,ui->RightStacked,&FadeQStackedWidget::SwitchPageToSlot);
    connect(ui->MenuBT3,&QKeepButton::buttonEnabled,ui->RightStacked,&FadeQStackedWidget::SwitchPageToSlot);
    connect(ui->MenuBT4,&QPushButton::clicked,&QApplication::quit);

    ui->MenuBT0->setSVGPath(":/home.svg");
    ui->MenuBT1->setSVGPath(":/settings.svg");
    ui->MenuBT2->setSVGPath(":/download.svg");
    ui->MenuBT3->setSVGPath(":/add.svg");
    ui->MenuBT4->setSVGPath(":/exit.svg");

    ui->RightStacked->setCurrentIndex(0);
}
