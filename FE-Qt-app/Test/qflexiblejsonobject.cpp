#include "qflexiblejsonobject.h"

QFlexibleJsonObject::QFlexibleJsonObject(const QJsonObject &origin)
    : QJsonObject(origin)
{
    // nothing to do here
}

QFlexibleJsonObject::~QFlexibleJsonObject()
{
    // nothing to do here
}

QJsonValue QFlexibleJsonObject::value(const QString &myKey) const
{
    for (const QString &currentKey : keys())
    {
        if (currentKey.toLower() == myKey.toLower())
        {
            return QJsonObject::value(currentKey);
        }
    }
    return QJsonValue();
}
