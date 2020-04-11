#ifndef GENCONDITIONASK_H
#define GENCONDITIONASK_H

#include "gencondition.h"

class GenConditionAsk : public GenCondition
{
public:
    GenConditionAsk(double initialStrikeAsk = 0);
    virtual bool operator() () override;

private:
    double m_strikeAsk;
};

#endif // GENCONDITIONASK_H
