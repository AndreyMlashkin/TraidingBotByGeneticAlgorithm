#include "agentbot.h"
#include "market.h"
#include "gen.h"

AgentBot::AgentBot(const QList<Gen *> gens, double euros, double currency) :
    m_euros(euros),
    m_currency(currency),
    m_gens(gens)
{

}

AgentBot::~AgentBot()
{
    qDeleteAll(m_gens);
}


void AgentBot::buy(double ammount)
{
    double eurosToSpend = Market::getMarketInstance().getBid() * ammount;
    if(eurosToSpend > m_euros)
    {
        ammount = m_euros; // Reduce ammount to actual euro ammount
        m_euros = 0;
    }
    m_currency += ammount;
}

void AgentBot::sell(double ammount)
{
    if(m_currency < ammount)
    {
        ammount = m_currency;
        m_currency = 0;
    }
    m_euros += Market::getMarketInstance().getAsk() * ammount;
}

void AgentBot::nextTick()
{
    for(Gen* gen : m_gens)
    {
        if(gen->condition())
            gen->action(*this);
    }
}

double AgentBot::getEuros() const
{
    return m_euros;
}

double AgentBot::getEurosEstimation() const
{
    return m_euros + Market::getMarketInstance().getAsk() * m_currency;
}
