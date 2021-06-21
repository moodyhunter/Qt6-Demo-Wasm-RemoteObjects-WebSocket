#include "Window.hpp"

#include "QWebSocketIODevice.hpp"
#include "ui_Window.h"

#include <QWebSocket>

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
};

Window::~Window()
{
    delete ui;
}

void Window::on_pushButton_clicked()
{
    QWebSocket *socket = new QWebSocket;
    QObject::connect(socket, &QWebSocket::connected, &n, [socket, this]() { //
        n.addClientSideConnection(new QWebSocketIODevice(socket));
    });
    socket->open(QUrl{ ui->lineEdit->text() });

    r = n.acquire<MyTypeReplica>();
    connect(r, &MyTypeReplica::someboolChanged, [](bool b) { qDebug() << "Somebool: " << b; });
    connect(r, &MyTypeReplica::stringChanged, [this](const QString &s) { ui->label->setText(s); });
}
