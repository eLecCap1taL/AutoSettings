#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建主窗口
    QMainWindow *mainWindow = new QMainWindow;

    // 创建中央 widget
    QWidget *centralWidget = new QWidget(mainWindow);
    mainWindow->setCentralWidget(centralWidget);

    // 左侧按钮
    QPushButton *button1 = new QPushButton("Button 1");
    QPushButton *button2 = new QPushButton("Button 2");
    QPushButton *button3 = new QPushButton("Button 3");

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addWidget(button3);

    // 右侧 QStackedWidget
    QStackedWidget *stackedWidget = new QStackedWidget;

    QWidget *page1 = new QWidget;
    QVBoxLayout *layout1 = new QVBoxLayout(page1);
    layout1->addWidget(new QLabel("Menu 1"));

    QWidget *page2 = new QWidget;
    QVBoxLayout *layout2 = new QVBoxLayout(page2);
    layout2->addWidget(new QLabel("Menu 2"));

    QWidget *page3 = new QWidget;
    QVBoxLayout *layout3 = new QVBoxLayout(page3);
    layout3->addWidget(new QLabel("Menu 3"));

    stackedWidget->addWidget(page1);
    stackedWidget->addWidget(page2);
    stackedWidget->addWidget(page3);

    // 添加竖线
    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    // 总体布局
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(line);  // 添加竖线
    mainLayout->addWidget(stackedWidget);

    // 连接按钮和 QStackedWidget
    QObject::connect(button1, &QPushButton::clicked, [stackedWidget]() {
        stackedWidget->setCurrentIndex(0);  // 切换到第1个菜单
    });

    QObject::connect(button2, &QPushButton::clicked, [stackedWidget]() {
        stackedWidget->setCurrentIndex(1);  // 切换到第2个菜单
    });

    QObject::connect(button3, &QPushButton::clicked, [stackedWidget]() {
        stackedWidget->setCurrentIndex(2);  // 切换到第3个菜单
    });

    mainWindow->show();
    return app.exec();
}
