#include <QRandomGenerator>

#include "math.h"
#include "genactionsellpercent.h"
#include "agentbot.h"

GenActionSellPercent::GenActionSellPercent(double percent)
    : m_percent(percent)
{
    Q_ASSERT(std::isnan(m_percent) == false);
    Q_ASSERT(m_percent < 1);
    Q_ASSERT(m_percent > 0);
}

void GenActionSellPercent::mutate()
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

QString GenActionSellPercent::toString() const
{
    return QString("sell percent: ") + QString::number(m_percent);
}

Mutatable *GenActionSellPercent::copy() const
{
    return new GenActionSellPercent(m_percent);
}

QJsonObject GenActionSellPercent::serialize() const
{
    QJsonObject result;
    result["name"]      = metaObject()->className();
    result["percent"] = m_percent;
    return result;
}

void GenActionSellPercent::deserialize(const QJsonObject &object)
{
    Q_ASSERT(object.contains("percent"));
    m_percent = object.value("percent").toDouble();
}

void GenActionSellPercent::operator ()(AgentBot & parent)
{
    parent.sell(parent.getCurrency() * m_percent);
}
