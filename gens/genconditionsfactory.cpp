#include <QRandomGenerator>

#include "genconditionsfactory.h"
#include "market.h"
#include "agentbot.h"
#include "gen.h"

GenFactory::GenFactory()
{

}

Gen *GenFactory::getRandomGen()
{
    Gen* gen = new Gen(getRandomGenCondition(), getRandomGenAction());
    return gen;
}

GenCondition *GenFactory::getRandomGenCondition()
{
    int random = QRandomGenerator::global()->generate();
    const int variants = 3;
    random %= variants;

    switch (random)
    {
    case 0: return new GenConditionNoop();
    case 1: return new GenConditionAsk();
    case 2: return new GenConditionBid();
    }
    Q_ASSERT(false);
    return nullptr;
}

GenAction *GenFactory::getRandomGenAction()
{
    int random = QRandomGenerator::global()->generate();
    const int variants = 2;
    random %= variants;

    switch (random)
    {
    case 0: return new GenActionBuy();
    case 1: return new GenActionSell();
    }
    Q_ASSERT(false);
    return nullptr;
}

GenConditionBid::GenConditionBid(double initialStrikeBid)
    : m_strikeBid(initialStrikeBid)
{

}

bool GenConditionBid::operator()()
{
    return m_strikeBid < Market::getMarketInstance().getBid();
}

GenConditionAsk::GenConditionAsk(double initialStrikeAsk)
    : m_strikeAsk(initialStrikeAsk)
{

}

bool GenConditionAsk::operator()()
{
    return m_strikeAsk < Market::getMarketInstance().getAsk();
}

GenActionBuy::GenActionBuy(double ammount) :
    m_ammount(ammount)
{
}

void GenActionBuy::operator()(AgentBot& parent)
{
    parent.buy(m_ammount);
}

GenActionSell::GenActionSell(double ammount) :
    m_ammount(ammount)
{
}

void GenActionSell::operator()(AgentBot& parent)
{
    parent.sell(m_ammount);
}
