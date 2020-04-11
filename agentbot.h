#pragma once

#include <QList>

class Gen;

class AgentBot
{
public:
    AgentBot(const QList<Gen*> gens, double euros = 2000, double currency = 0);
    ~AgentBot();

    void buy (double ammount);
    void sell(double ammount);

    void nextTick();

    double getEuros() const;
    double getEurosEstimation() const;

private:
    double m_euros;
    double m_currency;

    QList<double> m_registers;
    QList<Gen*> m_gens;
};

