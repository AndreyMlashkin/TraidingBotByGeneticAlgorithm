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
