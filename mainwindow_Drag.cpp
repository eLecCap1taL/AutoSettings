#include "mainwindow.h"
// #include "ui_mainwindow.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QTextEdit>
#include <QTextBrowser>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QFile>
#include <QTimer>
#include <QRegion>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPainter>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDragEnterEvent>
#include <QMimeData>

void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    // 判断是否为文件拖拽
    qDebug()<<"1\n";
    if (event->mimeData()->hasUrls()) {
        // 检查是否为压缩包
        const QUrl url = event->mimeData()->urls().first();
        if (url.toLocalFile().endsWith(".zip")) {
            event->acceptProposedAction();  // 接受该拖拽操作
        }
    }
}
void MainWindow::dropEvent(QDropEvent *event){
    const QUrl url = event->mimeData()->urls().first();
    QString zipFilePath = url.toLocalFile();

    // 调用解压处理
    processZipFile(zipFilePath);
}
void MainWindow::processZipFile(const QString &zipFilePath) {
    QString outputDir = "f:/";  // 临时文件夹
    QProcess unzipProcess;

    // 使用 QProcess 调用系统 unzip 命令
    unzipProcess.start(":/7za.exe", QStringList() << " x " << zipFilePath << " -o " << outputDir << " -aoa");
    unzipProcess.waitForFinished();

    // 检查是否成功
    if (unzipProcess.exitStatus() == QProcess::NormalExit) {
        QString infoJsonPath = outputDir + "/info.json";

        // 读取并解析 info.json
        QFile jsonFile(infoJsonPath);
        if (jsonFile.open(QIODevice::ReadOnly)) {
            QByteArray jsonData = jsonFile.readAll();
            jsonFile.close();

            // 解析 JSON 数据
            QJsonDocument doc = QJsonDocument::fromJson(jsonData);
            if (doc.isObject()) {
                QJsonObject jsonObj = doc.object();
                qDebug() << "Parsed info.json content:" << jsonObj;
                // 进一步处理 jsonObj
            } else {
                qWarning() << "Invalid JSON in info.json.";
            }
        } else {
            qWarning() << "Failed to open info.json.";
        }
    } else {
        qWarning() << "Failed to unzip file.";
    }
}
