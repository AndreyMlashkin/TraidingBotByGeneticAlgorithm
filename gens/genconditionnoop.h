#pragma once

#include "gencondition.h"

class GenConditionNoop : public GenCondition
{
public:
    GenConditionNoop() {}
    virtual bool operator() () override { return true; }
    QString toString() const override { return "no condition"; }

    void mutate() override {}
    Mutatable* copy() const override { return new GenConditionNoop(); }
};
