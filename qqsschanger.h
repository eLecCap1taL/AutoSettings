#ifndef QQSSCHANGER_H
#define QQSSCHANGER_H

#include <QObject>
#include <QString>

class QQSSChanger : public QObject
{
    Q_OBJECT
public:
    explicit QQSSChanger(QObject *parent = nullptr);
    void addEffect(QString name,std::vector<int> st,std::vector<int> ed,std::pair<QString,QString> rg = std::make_pair(QString(),QString()),QString suf = "");
    void addEffect(QString name);
    QString getQSS(qreal dt);
    std::vector<std::vector<int>> getInner(qreal dt);
protected:
    class Effect{
    public:
        bool Single;
        QString name;
        std::vector<int> st;
        std::vector<int> ed;
        std::pair<QString,QString> rg;
        QString suf;
        Effect(QString name_,std::vector<int> st_,std::vector<int> ed_,std::pair<QString,QString> rg_ = std::make_pair(QString(),QString()),QString suf_ = "");
        Effect(QString content_);
        QString getQSS(qreal dt);
        std::vector<int> getInner(qreal dt);
    };
    std::vector<Effect> ls;
signals:
};

#endif // QQSSCHANGER_H
