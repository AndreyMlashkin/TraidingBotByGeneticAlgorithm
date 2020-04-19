#pragma once

#include <QList>
#include "gens/mutatable.h"

class Gen;

class AgentBot : public Mutatable
{
    Q_OBJECT

public:
    AgentBot(const QList<Gen*> gens = {}, double euros = 2000, double currency = 0);
    ~AgentBot();

    void buy (double ammount);
    void sell(double ammount);

    void nextTick();

    double getEuros() const;
    double getEurosEstimation() const;

    double getCurrency() const;
    double getCurrencyEstimation() const;

    void mutate() override;
    QString toString() const override;
    Mutatable* copy() const override;

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &object) override;

    AgentBot* crossover(AgentBot* partner) const;

    void setEuros(double ammount);
    void setCurrency(double ammount);

    int gensCount() const;
    const QList<Gen*> gens() const;

private:
    double m_euros;
    double m_currency;

    QList<double> m_registers;
    QList<Gen*> m_gens;
};

