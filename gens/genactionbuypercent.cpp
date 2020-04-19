#include <QRandomGenerator>

#include "math.h"
#include "genactionbuypercent.h"
#include "agentbot.h"

GenActionBuyPercent::GenActionBuyPercent(double percent)
    : m_percent(percent)
{
    Q_ASSERT(std::isnan(m_percent) == false);
    Q_ASSERT(m_percent < 1);
    Q_ASSERT(m_percent > 0);
}

void GenActionBuyPercent::mutate()
{
    bool increase = QRandomGenerator::global()->generate() % 2;
    if(increase)
    {
        double upperLimit = (1 - m_percent);
        double randomKoeff = QRandomGenerator::global()->generateDouble() * upperLimit;
        m_percent += randomKoeff;
    }
    else
    {
        double randomKoeff = QRandomGenerator::global()->generateDouble() * m_percent;
        m_percent -= randomKoeff;
        if(m_percent < 0.001)
            m_percent = 0.01;
    }
}

QString GenActionBuyPercent::toString() const
{
    return QString("buy percent: ") + QString::number(m_percent);
}

Mutatable *GenActionBuyPercent::copy() const
{
    return new GenActionBuyPercent(m_percent);
}

QJsonObject GenActionBuyPercent::serialize() const
{
    QJsonObject result;
    result["name"]      = metaObject()->className();
    result["percent"] = m_percent;
    return result;
}

void GenActionBuyPercent::deserialize(const QJsonObject &object)
{
    Q_ASSERT(object.contains("percent"));
    m_percent = object.value("percent").toDouble();
}

void GenActionBuyPercent::operator ()(AgentBot & parent)
{
    parent.buy(parent.getEuros() * m_percent);
}
