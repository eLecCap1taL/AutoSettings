#include "mainwindow.h"
#include <QPropertyAnimation>
#include <QApplication>

// QVariant MenuBTAnimation(const MenuBTStyleType &start,const MenuBTStyleType &end,qreal dt){
//     MenuBTStyleType ret(0,0,0,0);
//     ret.r=start.r+(int)((double)(end.r-start.r)*dt);
//     ret.g=start.g+(int)((double)(end.g-start.g)*dt);
//     ret.ra=start.ra+(int)((double)(end.ra-start.ra)*dt);
//     ret.Y=start.Y+(int)((double)(end.Y-start.Y)*dt);
//     // qDebug()<<ret.Y<<Qt::endl;
//     return QVariant::fromValue(ret);
// }

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    QApplication a(argc, argv);
    // qRegisterAnimationInterpolator<MenuBTStyleType>(MenuBTAnimation);
    MainWindow w;
    // QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    w.show();
    return a.exec();
}
