#include <QRandomGenerator>

#include "genactionbuy.h"
#include "agentbot.h"


GenActionBuy::GenActionBuy(double ammount) :
    m_ammount(ammount)
{
}

void GenActionBuy::operator()(AgentBot& parent)
{
    parent.buy(m_ammount);
}

void GenActionBuy::mutate()
{
    m_ammount = mutatecoeff(m_ammount);
}

QString GenActionBuy::toString() const
{
    return QString("buy ") + QString::number(m_ammount);
}
