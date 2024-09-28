#include "qstylewidget.h"
#include <QString>
#include <qboxlayout.h>

QStyleWidget::QStyleWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setProperty("styleSheet",QString("background-color: rgba(255, 255, 255, 150);\nborder-radius: 20px; padding: 12px;"));
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);
    this->setLayout(new QVBoxLayout(this));
}
