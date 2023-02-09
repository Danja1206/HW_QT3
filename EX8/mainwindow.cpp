#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

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

void MainWindow::on_pushButton_clicked()
{
    QString url = "https://yandex.ru";
    QString html = getHtml(url);

    ui->plainTextEdit->setPlainText(html);
}

QString MainWindow::getHtml( QString &url)
{
    QNetworkAccessManager manager;

    return "response->readAll()";
}

