#pragma once

#include "mutatable.h"

class AgentBot;

class GenAction : public Mutatable
{
public:
    virtual ~GenAction() {}
    virtual void operator() (AgentBot&) = 0;
    virtual void mutate() = 0;
};

