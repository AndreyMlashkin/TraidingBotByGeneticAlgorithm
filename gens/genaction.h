#pragma once

class AgentBot;

class GenAction
{
public:
    virtual ~GenAction() {}
    virtual void operator() (AgentBot&) = 0;
};

