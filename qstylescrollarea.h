#ifndef QSTYLESCROLLAREA_H
#define QSTYLESCROLLAREA_H

#include <QScrollArea>
#include <QWidget>

class QStyleScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit QStyleScrollArea(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event)override;
};

#endif // QSTYLESCROLLAREA_H
