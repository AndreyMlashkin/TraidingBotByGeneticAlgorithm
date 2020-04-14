#pragma once

#include <QObject>
#include <QMetaObject>
#include <QString>
#include <QJsonObject>

class Mutatable : public QObject
{
public:
    Mutatable();
    virtual ~Mutatable() {}

    virtual void mutate() = 0;
    virtual QString toString() const = 0;
    virtual Mutatable* copy() const = 0;

    virtual QJsonObject serialize() const = 0;
    virtual void deserialize(const QJsonObject& object) = 0;

    static double mutatecoeff(double original);
    static double mutatecoeffNoNegative(double original);
};
