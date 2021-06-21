#pragma once

#include "rep_common_rep_merged.h"

#include <QMainWindow>
#include <QRemoteObjectHost>
#include <QtWebSockets>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Window;
}
QT_END_NAMESPACE

class QSOHandler : public MyTypeSimpleSource
{
    Q_OBJECT
  public slots:
    void test()
    {
        qDebug() << "TEST";
    }
};
class Window : public QMainWindow
{
    Q_OBJECT

  public:
    Window(QWidget *parent = nullptr);
    ~Window();

  private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_plainTextEdit_textChanged();

    void on_pushButton_clicked();

  private:
    QSOHandler handler;
    Ui::Window *ui;
    QRemoteObjectHost b;
    //
    // Create the server and listen outside of QtRO
    QWebSocketServer server{ "default", QWebSocketServer::NonSecureMode };
};
