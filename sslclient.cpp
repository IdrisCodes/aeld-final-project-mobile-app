#include "sslclient.h"
#include <QFile>
#include <QSslKey>
#include <QSslConfiguration>
SslClient::SslClient(QObject *parent)
    : QObject{parent}
{
    connect(&m_socket, &QSslSocket::encrypted,
            this, &SslClient::connectedToServer);
    connect(&m_socket, &QSslSocket::sslErrors,
            this, &SslClient::error);
    connect(&m_socket, &QSslSocket::stateChanged,
            this, &SslClient::stateChanged);
    //m_socket.setPeerVerifyMode(QSslSocket::QueryPeer);
}

void SslClient::setCertificate(const QString &path)
{
    QFile file(path);
    file.open(QFile::OpenModeFlag::ReadOnly);
    m_socket.setLocalCertificate(QSslCertificate(file.readAll()));
}
void SslClient::setPrivateKey(const QString &path, const QString &passphrase)
{
    QFile file(path);
    file.open(QFile::OpenModeFlag::ReadOnly);
    QSslKey key(file.readAll(), QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, passphrase.toUtf8());
    m_socket.setPrivateKey(key);
}

void SslClient::setCA(const QString &path)
{

    QFile file(path);
    file.open(QFile::OpenModeFlag::ReadOnly);
    QSslCertificate ca(file.readAll());

    auto sslConfig{m_socket.sslConfiguration()};
    sslConfig.addCaCertificate(ca);
    m_socket.setSslConfiguration(sslConfig);

    QList<QSslCertificate> chain{ca};
    m_socket.setLocalCertificateChain(chain);
}

void SslClient::setServerHostName(const QString &host)
{
    m_hostname = host;
}

void SslClient::unlock()
{
    m_socket.connectToHostEncrypted(m_hostname, 4433, "Aorus-15-XE5");
}

void SslClient::connectedToServer()
{
    /* Connected sucsessfully*/
    qDebug() << "Writing";
    if(m_socket.write("Unlock\n") ==-1)
    {
        qDebug() << "Error writing to socket";
    }
    else
        m_socket.flush();
    m_socket.disconnectFromHost();
}

void SslClient::disconnectedFromServer()
{

}

void SslClient::error(const QList<QSslError> &errors)
{
    qDebug()<< "Error occurred";
    for(const auto & error : errors)
    {
        qDebug() << error;
    }

}

void SslClient::stateChanged(QAbstractSocket::SocketState newState)
{
    if(newState == QAbstractSocket::ConnectedState)
    {
        qDebug() << "Connected";
    }
    else if(newState == QAbstractSocket::HostLookupState)
    {
        qDebug() << "HostLookupState";
    }
    else if(newState == QAbstractSocket::UnconnectedState)
    {
        qDebug() << "UnconnectedState";
    }
    else if(newState == QAbstractSocket::ConnectingState)
    {
        qDebug() << "ConnectingState";
    }
    else
        qDebug() << newState;
}


