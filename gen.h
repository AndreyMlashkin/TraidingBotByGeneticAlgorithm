#ifndef GEN_H
#define GEN_H

#include "gens/genconditionsfactory.h"
#include "gens/mutatable.h"

class AgentBot;

class Gen : public Mutatable
{
    Q_OBJECT
public:
    Gen(GenCondition* condition, GenAction* action);
    ~Gen();

    Gen& operator=(const Gen& other);

    bool condition();
    void action(AgentBot& parent);

    void mutate() override;
    QString toString() const override;
    Mutatable* copy() const override;

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &object) override;

private:
    GenCondition* m_condition;
    GenAction*    m_action;
};

#endif // GEN_H
