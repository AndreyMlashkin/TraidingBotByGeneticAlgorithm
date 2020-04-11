#ifndef GENACTIONSELL_H
#define GENACTIONSELL_H

#include "genaction.h"

class GenActionSell : public GenAction
{
public:
    GenActionSell(double ammount = 1);
    void operator() (AgentBot& parent) override;

    void mutate() override;

    QString toString() const override;

private:
    double m_ammount;
};

#endif // GENACTIONSELL_H
