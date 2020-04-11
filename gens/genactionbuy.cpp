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
