#include "gen.h"
#include "gens/genaction.h"
#include "gens/gencondition.h"

Gen::Gen(GenCondition *condition, GenAction *action) :
    m_condition(condition),
    m_action(action)
{

}

Gen::~Gen()
{
    delete m_condition;
    delete m_action;
}

bool Gen::condition()
{
    return m_condition->operator()();
}

void Gen::action(AgentBot &parent)
{
    m_action->operator()(parent);
}
