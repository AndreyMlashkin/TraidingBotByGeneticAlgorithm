#include "genconditionnoop.h"

bool GenConditionNoop::operator()() { return true; }

QString GenConditionNoop::toString() const { return "no condition"; }

Mutatable *GenConditionNoop::copy() const { return new GenConditionNoop(); }

QJsonObject GenConditionNoop::serialize() const
{
    QJsonObject result;
    result["name"]      = metaObject()->className();
    return result;
}

void GenConditionNoop::deserialize(const QJsonObject &object)
{
    Q_UNUSED(object);
}
