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
}

QString GenActionSell::toString() const
{
    return QString("sell ") + QString::number(m_ammount);
}

Mutatable *GenActionSell::copy() const
{
    return new GenActionSell(m_ammount);
}

