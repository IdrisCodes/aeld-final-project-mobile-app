#ifndef SSLCLIENT_H
#define SSLCLIENT_H

#include <QObject>
#include <QSslSocket>

class SslClient : public QObject
{
    Q_OBJECT
private:
    QSslSocket m_socket;
    QString m_hostname;
public:
    explicit SslClient(QObject *parent = nullptr);
    void setCertificate(const QString& path);
    void setPrivateKey(const QString& path, const QString& passphrase);
    void setCA(const QString& path);
    void setServerHostName(const QString& host);
public slots:
    void unlock();
    void connectedToServer();
    void disconnectedFromServer();
    void error(const QList<QSslError> &errors);
    void stateChanged(QAbstractSocket:: SocketState);
signals:
};

#endif // SSLCLIENT_H
