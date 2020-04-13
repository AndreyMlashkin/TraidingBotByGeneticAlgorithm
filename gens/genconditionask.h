#ifndef GENCONDITIONASK_H
#define GENCONDITIONASK_H

#include "gencondition.h"
#include "market.h"

class GenConditionAsk : public GenCondition
{
public:
    GenConditionAsk(double initialStrikeAsk);
    virtual bool operator() () override;

    void mutate() override;
    QString toString() const override;
    Mutatable* copy() const override;

private:
    double m_strikeAsk;
};

#endif // GENCONDITIONASK_H
