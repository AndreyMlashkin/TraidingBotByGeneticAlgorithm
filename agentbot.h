#pragma once

#include <QList>
#include "gens/mutatable.h"

class Gen;

class AgentBot : public Mutatable
{
public:
    AgentBot(const QList<Gen*> gens, double euros = 2000, double currency = 0);
    ~AgentBot();

    void buy (double ammount);
    void sell(double ammount);

    void nextTick();

    double getEuros() const;
    double getEurosEstimation() const;

    void mutate() override;
    QString toString() const override;
    Mutatable* copy() const override;

    void setEuros(double ammount);
    void setCurrency(double ammount);

private:
    double m_euros;
    double m_currency;

    QList<double> m_registers;
    QList<Gen*> m_gens;

};

