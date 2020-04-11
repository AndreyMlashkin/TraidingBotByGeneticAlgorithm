#ifndef AGENTBOT_H
#define AGENTBOT_H

#include <QList>

class Gen;

class AgentBot
{
public:
    AgentBot(const QList<Gen*> gens);
    //~AgentBot();

    void buy (double ammount);
    void sell(double ammount);

    void nextTick();

private:
    double m_euros;
    double m_currency;

    QList<double> m_registers;
    QList<Gen*> m_gens;
};

#endif // AGENTBOT_H
