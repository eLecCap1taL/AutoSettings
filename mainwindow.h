#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <qboxlayout.h>
#include <vector>
#include "qstylescrollarea.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MenuBTStyleType{
public:
    int r,g,ra,Y;
    MenuBTStyleType(int _r=0,int _g=0,int _ra=0,int _Y=0):r(_r),g(_g),ra(_ra),Y(_Y){}
    QString styleSheet();
    MenuBTStyleType ChangeY(int Y);
};
Q_DECLARE_METATYPE(MenuBTStyleType)

typedef std::pair<bool,QString> QStringRequest;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QNetworkAccessManager* net;

    static MenuBTStyleType MenuBTStyle[2];
    bool QueryQStringFromUrl(const QUrl &url,std::function<void(const QStringRequest& )> callback,int TIMELIMIT = 5000,bool FORCE = false);
    void RefreshCheckLabel();

public slots:
    void MenuBTClicked();
    void UpdateMenuBTStatus();
    void UpdateCheckButtonClicked();

private:
    Ui::MainWindow *ui;
    void Setup_MenuBT();
    void Setup_update();
    int IsQuerying;

protected:
    std::vector<QPushButton*> MenuBTls;
    std::vector<QStyleScrollArea*> RightScrollAreas;
    std::vector<QVBoxLayout*> RightScrollContent;
    void showEvent(QShowEvent* event)override;
    void resizeEvent(QResizeEvent* event)override;

    QString CURMANAGERVERSION = QString("v1.0");
    QString CURCSRMVERSION = QString("v2.53");
    QString LSTMANAGERVERSION = QString(tr("暂未获取"));
    QString LSTCSRMVERSION = QString(tr("暂未获取"));

private slots:
};
#endif // MAINWINDOW_H

#define POPTEXT(x,y) ui->Overlay->AddMessage(tr(x),y);
