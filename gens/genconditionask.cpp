#include "genconditionask.h"
#include "market.h"

GenConditionAsk::GenConditionAsk(double initialStrikeAsk)
    : m_strikeAsk(initialStrikeAsk)
{

}

bool GenConditionAsk::operator()()
{
    return m_strikeAsk < Market::getMarketInstance().getAsk();
}

void GenConditionAsk::mutate()
{
    m_strikeAsk = mutatecoeffNoNegative(m_strikeAsk);
}

QString GenConditionAsk::toString() const
{
    return QString("ask ") + QString::number(m_strikeAsk);
}

Mutatable *GenConditionAsk::copy() const
{
    return new GenConditionAsk(m_strikeAsk);
}
