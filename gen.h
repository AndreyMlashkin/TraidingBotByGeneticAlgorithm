#ifndef GEN_H
#define GEN_H

#include "gens/genconditionsfactory.h"
#include "gens/mutatable.h"

class AgentBot;

class Gen : public Mutatable
{
public:
    Gen(GenCondition* condition, GenAction* action);
    ~Gen();

    bool condition();
    void action(AgentBot& parent);

    void mutate() override;
    QString toString() const override;

private:
    GenCondition* m_condition;
    GenAction*    m_action;

};

#endif // GEN_H
