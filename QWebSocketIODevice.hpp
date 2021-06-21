#pragma once

#include <QIODevice>
#include <QWebSocket>

class QWebSocketIODevice : public QIODevice
{
    Q_OBJECT
  public:
    QWebSocketIODevice(QWebSocket *websocket, QObject *parent = nullptr) : QIODevice(parent)
    {
        QIODevice::open(ReadWrite);
        this->pSocket = websocket;
        connect(pSocket, &QWebSocket::disconnected, this, &QWebSocketIODevice::disconnected);
        connect(pSocket, &QWebSocket::bytesWritten, this, &QWebSocketIODevice::bytesWritten);
        connect(pSocket, &QWebSocket::binaryMessageReceived, [this](const QByteArray &message) {
            buffer.append(message);
            emit readyRead();
        });
    }

    bool isSequential() const override
    {
        return true;
    }

    qint64 bytesAvailable() const override
    {
        return QIODevice::bytesAvailable() + buffer.size();
    }

    qint64 readData(char *data, qint64 maxlen) override
    {
        auto sz = std::min(maxlen, qint64(buffer.size()));
        if (sz <= 0)
            return sz;
        memcpy(data, buffer.constData(), size_t(sz));
        buffer.remove(0, sz);
        return sz;
    }

    qint64 writeData(const char *data, qint64 len) override
    {
        return pSocket->sendBinaryMessage(QByteArray{ data, int(len) });
    }

  signals:
    void disconnected();

  private:
    QWebSocket *pSocket;
    QByteArray buffer;
};
