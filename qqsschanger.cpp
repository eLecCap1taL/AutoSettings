#include "qqsschanger.h"

QQSSChanger::QQSSChanger(QObject *parent)
    : QObject{parent}
{}
QQSSChanger::Effect::Effect(QString name_,std::vector<int> st_,std::vector<int> ed_,std::pair<QString,QString> rg_,QString suf_)
    : name(name_),
    st(st_),
    ed(ed_),
    rg(rg_),
    suf(suf_),
    Single(false)
{}
QQSSChanger::Effect::Effect(QString content_)
    : name(content_),
    st(),
    ed(),
    rg(),
    suf(),
    Single(true)
{}

void QQSSChanger::addEffect(QString name,std::vector<int> st,std::vector<int> ed,std::pair<QString,QString> rg,QString suf){
    Effect ef(name,st,ed,rg,suf);
    ls.push_back(ef);
}
void QQSSChanger::addEffect(QString name){
    Effect ef(name);
    ls.push_back(ef);
}
QString QQSSChanger::getQSS(qreal dt){
    QString ret;
    for(int i=0;i<ls.size();i++){
        ret+=ls[i].getQSS(dt);
        if(i+1<ls.size())   ret+=";";
    }
    return ret;
}
std::vector<std::vector<int>> QQSSChanger::getInner(qreal dt){
    std::vector<std::vector<int>> ret;
    for(int i=0;i<ls.size();i++){
        ret.push_back(ls[i].getInner(dt));
    }
    return ret;
}
QString QQSSChanger::Effect::getQSS(qreal dt){
    if(Single)  return name+";";
    QString ret=name + ": " + rg.first;
    for(int i=0;i<st.size();i++){
        ret+=QString::number(st[i]+(int)((ed[i]-st[i])*dt));
        if(i+1<st.size())   ret+=" ,";
    }
    ret+=rg.second + " " + suf;
    return ret;
}
std::vector<int> QQSSChanger::Effect::getInner(qreal dt){
    if(Single)  return std::vector<int>();
    std::vector<int> ret;
    for(int i=0;i<st.size();i++){
        ret.push_back((int)(st[i]+(int)((ed[i]-st[i])*dt)));
    }
    return ret;
}

