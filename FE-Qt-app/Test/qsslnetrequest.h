#ifndef QSSLNETREQUEST_H
#define QSSLNETREQUEST_H

#include <QUrl>
#include <QNetworkRequest>

class QSslNetRequest : public QNetworkRequest
{
public:
    QSslNetRequest();
    QSslNetRequest(const QUrl &url);
    virtual ~QSslNetRequest();
private:
    void init();
    void setPeerVerifyModeToNone();
};

#endif // QSSLNETREQUEST_H
