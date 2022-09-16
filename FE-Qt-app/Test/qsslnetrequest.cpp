#include "qsslnetrequest.h"

#include <QSslConfiguration>

QSslNetRequest::QSslNetRequest()
{
    init();
}

QSslNetRequest::QSslNetRequest(const QUrl &url)
{
    init();
    setUrl(url);
}

QSslNetRequest::~QSslNetRequest()
{
    // nothing to do here
}

void QSslNetRequest::init()
{
    setPeerVerifyModeToNone();
    setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

void QSslNetRequest::setPeerVerifyModeToNone()
{
    QSslConfiguration conf = sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    setSslConfiguration(conf);
}
