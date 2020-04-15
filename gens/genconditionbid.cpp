#include "math.h"

#include "genconditionbid.h"
#include "market.h"

GenConditionBid::GenConditionBid(double initialStrikeBid)
    : m_strikeBid(initialStrikeBid)
{
    Q_ASSERT(std::isnan(initialStrikeBid) == false);
}

bool GenConditionBid::operator()()
{
    return m_strikeBid < Market::getMarketInstance().getBid();
}

void GenConditionBid::mutate()
{
    m_strikeBid = mutatecoeffNoNegative(m_strikeBid);

    if(m_strikeBid > Market::getMarketInstance().getMaxBid())
        m_strikeBid = Market::getMarketInstance().getMaxBid();
    if(m_strikeBid < Market::getMarketInstance().getMinBid())
        m_strikeBid = Market::getMarketInstance().getMinBid();
}

QString GenConditionBid::toString() const
{
    return QString("bid ") + QString::number(m_strikeBid);
}

Mutatable *GenConditionBid::copy() const
{
    return new GenConditionBid(m_strikeBid);
}

QJsonObject GenConditionBid::serialize() const
{
    QJsonObject result;
    result["name"]      = metaObject()->className();
    result["bid"] = m_strikeBid;
    return result;
}

void GenConditionBid::deserialize(const QJsonObject &object)
{
    Q_ASSERT(object.contains("bid"));
    m_strikeBid = object.value("bid").toDouble();
}
