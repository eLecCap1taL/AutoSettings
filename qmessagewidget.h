#ifndef QMESSAGEWIDGET_H
#define QMESSAGEWIDGET_H

#include <QWidget>

class QMessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QMessageWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event)override;
signals:
};

#endif // QMESSAGEWIDGET_H
