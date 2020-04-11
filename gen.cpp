#include <QRandomGenerator>

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

void Gen::mutate()
{
    quint32 randomOperation = QRandomGenerator::global()->generate();
    const quint32 variants = 4;
    randomOperation %= variants;

    if(randomOperation == 1 || randomOperation == 3)
        m_condition->mutate();
    if(randomOperation == 2 || randomOperation == 3)
        m_action->mutate();
}

QString Gen::toString() const
{
    return QString("Condition:[")
            + m_condition->toString() +
            "] Action:["
            + m_action->toString() + "]";
}
