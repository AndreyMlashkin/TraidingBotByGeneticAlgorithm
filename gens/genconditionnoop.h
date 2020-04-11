#pragma once

#include "gencondition.h"

class GenConditionNoop : public GenCondition
{
public:
    GenConditionNoop() {}
    virtual bool operator() () override { return true; }
};
