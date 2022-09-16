#include "qsslnetaccessmanager.h"

#include <QSslSocket>

QSslNetAccessManager::QSslNetAccessManager(QObject *parent)
    : QNetworkAccessManager(parent)
{
    // nothing to do here
}

QSslNetAccessManager::~QSslNetAccessManager()
{
    // nothing to do here
}

QString QSslNetAccessManager::sslLibraryBuildVersionString()
{
    return QSslSocket::sslLibraryBuildVersionString();
}
