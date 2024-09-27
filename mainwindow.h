#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <vector>

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MenuBTStyleType MenuBTStyle[2];

public slots:
    void MenuBTClicked();
    void UpdateMenuBTStatus();

private:
    Ui::MainWindow *ui;
    void Setup_MenuBT();
    void Setup_RightStacked();

protected:
    std::vector<QPushButton*> MenuBTls;
    std::vector<QScrollArea*> RightStackedPages;

};
#endif // MAINWINDOW_H
