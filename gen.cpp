#include <QRandomGenerator>

#include "gen.h"
#include "gens/genaction.h"
#include "gens/gencondition.h"
#include "gens/genconditionsfactory.h"

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

Gen &Gen::operator=(const Gen &other)
{
    m_action = other.m_action;
    m_condition = other.m_condition;
    return *this;
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
    const quint32 variants = 5;
    randomOperation %= variants;

    if(randomOperation == 0)
    {
        delete m_condition;
        m_condition = GenFactory::getRandomGenCondition();
    }
    if(randomOperation == 1)
    {
        delete m_action;
        m_action = GenFactory::getRandomGenAction();
    }

    if(randomOperation == 2 || randomOperation == 4)
        m_condition->mutate();
    if(randomOperation == 3 || randomOperation == 4)
        m_action->mutate();

}

QString Gen::toString() const
{
    return QString("Condition:[")
            + m_condition->toString() +
            "] Action:["
            + m_action->toString() + "]";
}

Mutatable *Gen::copy() const
{
    return new Gen(
                dynamic_cast<GenCondition*>(m_condition->copy()),
                dynamic_cast<GenAction*>   (m_action->copy()));
}

QJsonObject Gen::serialize() const
{
    QJsonObject result;
    result["name"]      = metaObject()->className();
    result["condition"] = m_condition->serialize();
    result["action"]    = m_action->serialize();
    return result;
}

void Gen::deserialize(const QJsonObject &object)
{
    Q_ASSERT(object.contains("condition"));
    Q_ASSERT(object.contains("action"));

    delete m_condition;
    QString conditionType = object.value("condition").toObject().value("name").toString();
    m_condition = GenFactory::getConditionByClassName(conditionType);

    delete m_action;
    QString actionType = object.value("action").toObject().value("name").toString();
    m_action = GenFactory::getActionByClassName(actionType);
}
