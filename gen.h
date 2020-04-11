#ifndef GEN_H
#define GEN_H

#include "gens/genconditionsfactory.h"
class AgentBot;

class Gen
{
public:
    Gen(GenCondition* condition, GenAction* action);
    ~Gen();

    bool condition();
    void action(AgentBot& parent);

private:
    GenCondition* m_condition;
    GenAction*    m_action;

};

#endif // GEN_H
