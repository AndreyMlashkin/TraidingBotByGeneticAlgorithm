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
