#include "genactionsell.h"
#include "agentbot.h"

GenActionSell::GenActionSell(double ammount) :
    m_ammount(ammount)
{
}

void GenActionSell::operator()(AgentBot& parent)
{
    parent.sell(m_ammount);
}

void GenActionSell::mutate()
{
    m_ammount = mutatecoeffNoNegative(m_ammount);
    if(m_ammount < 1)
        m_ammount = 1;
    if(m_ammount > 2000)
        m_ammount = 2000;
}

QString GenActionSell::toString() const
{
    return QString("sell ") + QString::number(m_ammount);
}

Mutatable *GenActionSell::copy() const
{
    return new GenActionSell(m_ammount);
}

QJsonObject GenActionSell::serialize() const
{
    QJsonObject result;
    result["name"]      = metaObject()->className();
    result["ammount"] = m_ammount;
    return result;
}

void GenActionSell::deserialize(const QJsonObject &object)
{
    Q_ASSERT(object.contains("ammount"));
    m_ammount = object.value("ammount").toDouble();
}
