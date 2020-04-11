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
    m_strikeBid = mutatecoeff(m_strikeBid);
}
