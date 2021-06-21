#include "Window.hpp"

#include "QWebSocketIODevice.hpp"
#include "ui_Window.h"

#include <QIODevice>

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
}

Window::~Window()
{
    delete ui;
}

void Window::on_checkBox_stateChanged(int)
{
    handler.setSomebool(ui->checkBox->isChecked());
}

void Window::on_plainTextEdit_textChanged()
{
    handler.setString(ui->plainTextEdit->toPlainText());
}

void Window::on_pushButton_clicked()
{
    QObject::connect(&server, &QWebSocketServer::newConnection, &b, [this]() { //
        b.addHostSideConnection(new QWebSocketIODevice(server.nextPendingConnection()));
        b.enableRemoting(&handler);
    });
    b.setHostUrl(server.serverAddress().toString(), QRemoteObjectHost::AllowExternalRegistration);
    server.listen(QHostAddress::Any, ui->portSB->value());
    connect(&handler, &MyTypeSource::someboolChanged, ui->checkBox, &QCheckBox::setChecked);
}
