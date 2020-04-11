#ifndef GENCONDITIONBID_H
#define GENCONDITIONBID_H

#include "gencondition.h"

class GenConditionBid : public GenCondition
{
public:
    GenConditionBid(double initialStrikeBid = 0);
    virtual bool operator() () override;

private:
    double m_strikeBid;
};

#endif // GENCONDITIONBID_H
