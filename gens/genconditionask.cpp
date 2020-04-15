#include "math.h"
#include "genconditionask.h"
#include "market.h"

GenConditionAsk::GenConditionAsk(double initialStrikeAsk)
    : m_strikeAsk(initialStrikeAsk)
{
    Q_ASSERT(std::isnan(initialStrikeAsk) == false);
}

bool GenConditionAsk::operator()()
{
    return m_strikeAsk < Market::getMarketInstance().getAsk();
}

void GenConditionAsk::mutate()
{
    m_strikeAsk = mutatecoeffNoNegative(m_strikeAsk);

    if(m_strikeAsk > Market::getMarketInstance().getMaxAsk())
        m_strikeAsk = Market::getMarketInstance().getMaxAsk();
    if(m_strikeAsk < Market::getMarketInstance().getMinAsk())
        m_strikeAsk = Market::getMarketInstance().getMinAsk();
}

QString GenConditionAsk::toString() const
{
    return QString("ask ") + QString::number(m_strikeAsk);
}

Mutatable *GenConditionAsk::copy() const
{
    return new GenConditionAsk(m_strikeAsk);
}

QJsonObject GenConditionAsk::serialize() const
{
    QJsonObject result;
    result["name"]      = metaObject()->className();
    result["ask"] = m_strikeAsk;
    return result;
}

void GenConditionAsk::deserialize(const QJsonObject &object)
{
    Q_ASSERT(object.contains("ask"));
    m_strikeAsk = object.value("ask").toDouble();
}
