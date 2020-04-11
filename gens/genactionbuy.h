#ifndef GENACTIONBUY_H
#define GENACTIONBUY_H

#include "genaction.h"

class GenActionBuy : public GenAction
{
public:
    GenActionBuy(double ammount = 1);
    void operator() (AgentBot& parent) override;
    void mutate() override;

    QString toString() const override;

private:
    double m_ammount;
};

#endif // GENACTIONBUY_H
