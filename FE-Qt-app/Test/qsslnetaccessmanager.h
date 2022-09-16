#ifndef QSSLNETACCESSMANAGER_H
#define QSSLNETACCESSMANAGER_H

#include <QNetworkReply>
#include <QNetworkAccessManager>

class QSslNetAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit QSslNetAccessManager(QObject *parent = nullptr);
    virtual ~QSslNetAccessManager();
    static QString sslLibraryBuildVersionString();
};

#endif // QSSLNETACCESSMANAGER_H
