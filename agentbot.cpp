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
        ammount = m_euros / Market::getMarketInstance().getBid(); // Reduce ammount to how much can we afford
        eurosToSpend = m_euros;
    }
    m_currency += ammount;
    m_euros -= eurosToSpend;
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

void AgentBot::mutate()
{
    for(Gen* gen : m_gens)
    {
        gen->mutate();
    }
}

QString AgentBot::toString() const
{
    QString answer;
    for(int i = 0; i < m_gens.size(); ++i)
    {
        answer += "Gen" + QString::number(i) + ":" + m_gens[i]->toString() + " ";
    }
    return answer;
}
