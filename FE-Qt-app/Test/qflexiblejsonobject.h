#ifndef QFLEXIBLEJSONOBJECT_H
#define QFLEXIBLEJSONOBJECT_H

#include <QJsonValue>
#include <QJsonObject>

class QFlexibleJsonObject : public QJsonObject
{
public:
    explicit QFlexibleJsonObject(const QJsonObject &origin);
    virtual ~QFlexibleJsonObject();
    QJsonValue value(const QString &myKey) const;
};

#endif // QFLEXIBLEJSONOBJECT_H
