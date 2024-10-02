#ifndef QUNIQUEBUTTONGROUP_H
#define QUNIQUEBUTTONGROUP_H

#include <QObject>
#include "qkeepbutton.h"

class QUniqueButtonGroup : public QObject
{
    Q_OBJECT
public:
    explicit QUniqueButtonGroup(QObject *parent = nullptr);
    void addButton(QKeepButton* bt);
    void addSwitchDisable(std::function<bool()> func);
    void setChangerFromProcess(std::shared_ptr<QQSSChanger> cg);

public slots:
    void buttonPressed();

protected:
    std::vector<QKeepButton*> ls;
    std::vector<std::function<bool()>> disls;
    std::shared_ptr<QQSSChanger> transfromFunction;
signals:
};

#endif // QUNIQUEBUTTONGROUP_H
