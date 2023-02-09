#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "qssl.h"
#include <QtNetwork>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getHtml(const QString &url)
{
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    response->deleteLater();
    return response->readAll();
}

QStringList MainWindow::getData(const QString &html)
{
    QStringList list;
    QRegExp regex("(<div class\"rate__currency ccj-bcbg-ov6yem\">)([\\d,]+)(</div>)");
    QRegExp regex2("(<span class\"weather__temp-period ccj-bcbg-4uusib\">)([\\d,]+)(</span>)");
    int lastPos = 0;
    int lastPos2 = 0;
    while((lastPos =regex.indexIn(html,lastPos)) != -1)
    {
        lastPos+=regex.matchedLength();
        list.append(regex.cap(2));
    }
    while((lastPos2 =regex2.indexIn(html,lastPos)) != -1)
    {
        lastPos2+=regex2.matchedLength();
        list.append(regex2.cap(2));
    }
    return list;
}

void MainWindow::on_pushButton_clicked()
{
    QString url = "https://yandex.ru";
    QString html = getHtml(url);
    if(html.isEmpty())
    {
        ui->plainTextEdit->setPlainText("Ошибка");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        return;
    }
    QStringList data = getData(html);

    ui->plainTextEdit->setPlainText(html);
    ui->lineEdit->setText(data[0]);
    ui->lineEdit->setText(data[1]);
}
