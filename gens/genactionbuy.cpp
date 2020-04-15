#include "math.h"

#include <QRandomGenerator>

#include "genactionbuy.h"
#include "agentbot.h"


GenActionBuy::GenActionBuy(double ammount) :
    m_ammount(ammount)
{
    Q_ASSERT(std::isnan(ammount) == false);
}

void GenActionBuy::operator()(AgentBot& parent)
{
    parent.buy(m_ammount);
}

void GenActionBuy::mutate()
{
    m_ammount = mutatecoeffNoNegative(m_ammount);
    if(m_ammount < 1)
        m_ammount = 1;
    if(m_ammount > 2000)
        m_ammount = 2000;
}

QString GenActionBuy::toString() const
{
    return QString("buy ") + QString::number(m_ammount);
}

Mutatable *GenActionBuy::copy() const
{
    return new GenActionBuy(m_ammount);
}

QJsonObject GenActionBuy::serialize() const
{
    QJsonObject result;
    result["name"]      = metaObject()->className();
    result["ammount"] = m_ammount;
    return result;
}

void GenActionBuy::deserialize(const QJsonObject &object)
{
    Q_ASSERT(object.contains("ammount"));
    m_ammount = object.value("ammount").toDouble();
}
