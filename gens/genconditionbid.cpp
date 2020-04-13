#include "genconditionbid.h"
#include "market.h"

GenConditionBid::GenConditionBid(double initialStrikeBid)
    : m_strikeBid(initialStrikeBid)
{

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
