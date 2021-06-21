#pragma once

#include "rep_common_rep_merged.h"

#include <QMainWindow>

namespace Ui
{
    class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

  public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::Window *ui;
    MyTypeReplica *r;
    QRemoteObjectNode n;
};
