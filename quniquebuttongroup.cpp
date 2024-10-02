#include "quniquebuttongroup.h"

QUniqueButtonGroup::QUniqueButtonGroup(QObject *parent)
    : QObject{parent}
{
    this->transfromFunction=std::shared_ptr<QQSSChanger>(new QQSSChanger());
}
void QUniqueButtonGroup::addButton(QKeepButton* bt){
    ls.push_back(bt);
    for(auto &dis:disls){
        bt->addSwitchDisable(dis);
    }
    bt->setChangerFromProcess(this->transfromFunction);
    connect(bt,&QKeepButton::buttonEnabled,this,&QUniqueButtonGroup::buttonPressed);
}
void QUniqueButtonGroup::buttonPressed(){
    qDebug()<<"emit detected\n";
    qDebug()<<sender()->objectName()<<"\n";
    for(auto &bt:ls){
        if(bt->objectName()!=sender()->objectName()){
            qDebug()<<"TRY RELEASE "<<bt->objectName()<<"\n";
            qDebug()<<bt->property("pressProcess")<<"\n";
            qDebug()<<bt->property("pressProcess").toReal()<<"\n";
            bt->buttonReleased();
        }
    }
}
void QUniqueButtonGroup::addSwitchDisable(std::function<bool()> func){
    for(auto &bt:ls){
        bt->addSwitchDisable(func);
    }
    this->disls.push_back(func);
}
void QUniqueButtonGroup::setChangerFromProcess(std::shared_ptr<QQSSChanger> cg){
    this->transfromFunction=cg;
    for(auto &bt:ls){
        bt->setChangerFromProcess(cg);
    }
}
