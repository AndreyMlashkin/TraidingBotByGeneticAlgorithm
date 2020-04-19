#include <QRandomGenerator>
#include <QJsonArray>

#include "agentbot.h"
#include "market.h"
#include "gen.h"
#include "gens/genconditionsfactory.h"

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
    m_currency -= ammount;
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
    int randomOperation = QRandomGenerator::global()->generate() % (m_gens.count() + 1);
    if(randomOperation == m_gens.count())
    {
        randomOperation = QRandomGenerator::global()->generate() % (m_gens.count() + 1);
        if(gensCount() > 2 && randomOperation != m_gens.count())
        {
            delete m_gens[randomOperation];
            m_gens.removeAt(randomOperation);
        }
        else
            m_gens << GenFactory::getRandomGen();
    }
    else
    {
        m_gens[randomOperation]->mutate();
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

Mutatable *AgentBot::copy() const
{
    QList<Gen*> gensCopy;
    for(Gen* gen : m_gens)
        gensCopy << dynamic_cast<Gen*>(gen->copy());

    return new AgentBot(gensCopy, m_euros, m_currency);
}

QJsonObject AgentBot::serialize() const
{
    QJsonObject result;
    result["name"]      = metaObject()->className();

    QJsonArray gens;
    for(Gen* gen : m_gens)
    {
        gens.push_back(gen->serialize());
    }
    result["gens"] = gens;;
    return result;
}

void AgentBot::deserialize(const QJsonObject &object)
{
    qDeleteAll(m_gens);
    Q_ASSERT(object.contains("gens"));
    QJsonArray gens = object.value("gens").toArray();
    for(const QJsonValue& value : gens)
    {
        Gen* newGen = new Gen(nullptr, nullptr);
        newGen->deserialize(value.toObject());
        m_gens << newGen;
    }
}

AgentBot *AgentBot::crossover(AgentBot *partner) const
{
    QList<Gen*> parentalGens = partner->gens();
    parentalGens.append(m_gens);

    while(parentalGens.size() >= 6)
    {
        int randomOperation = QRandomGenerator::global()->generate() % (m_gens.count());
        parentalGens.removeAt(randomOperation);
    }

    QList<Gen*> childsGens;
    for(Gen* gen : parentalGens)
    {
        childsGens << dynamic_cast<Gen*>(gen->copy());
    }
    return new AgentBot(childsGens);
}

void AgentBot::setEuros(double ammount)
{
    m_euros = ammount;
}

void AgentBot::setCurrency(double ammount)
{
    m_currency = ammount;
}

int AgentBot::gensCount() const
{
    return m_gens.count();
}

const QList<Gen *> AgentBot::gens() const
{
    return m_gens;
}
