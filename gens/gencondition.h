#ifndef GENCONDITION_H
#define GENCONDITION_H

#include "mutatable.h"

class GenCondition : public Mutatable
{
public:
    virtual ~GenCondition() {}
    virtual bool operator() () = 0;

    virtual void mutate() = 0;
};

#endif // GENCONDITION_H
