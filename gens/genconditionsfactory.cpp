#include <QRandomGenerator>

#include "genconditionsfactory.h"
#include "agentbot.h"
#include "market.h"

#include "gen.h"
#include "genconditionask.h"
#include "genconditionbid.h"
#include "genconditionnoop.h"
#include "genactionbuy.h"
#include "genactionsell.h"

GenFactory::GenFactory()
{

}

Gen *GenFactory::getRandomGen()
{
    Gen* gen = new Gen(getRandomGenCondition(), getRandomGenAction());
    return gen;
}

GenCondition *GenFactory::getRandomGenCondition()
{
    quint32 random = QRandomGenerator::global()->generate();
    const quint32 variants = 3;
    random %= variants;

    switch (random)
    {
    case 0: return new GenConditionNoop();
    case 1: return new GenConditionAsk();
    case 2: return new GenConditionBid();
    }
    Q_ASSERT(false);
    return nullptr;
}

GenAction *GenFactory::getRandomGenAction()
{
    quint32 random = QRandomGenerator::global()->generate();
    const quint32 variants = 2;
    random %= variants;

    switch (random)
    {
    case 0: return new GenActionBuy();
    case 1: return new GenActionSell();
    }
    Q_ASSERT(false);
    return nullptr;
}

GenCondition *GenFactory::getConditionByClassName(const QString &className)
{
    if(className == "GenConditionNoop")
        return new GenConditionNoop();
    if(className == "GenConditionAsk")
        return new GenConditionAsk();
    if(className == "GenConditionBid")
        return new GenConditionBid();
    return nullptr;
}

GenAction *GenFactory::getActionByClassName(const QString &className)
{
    if(className == "GenActionBuy")
        return new GenActionBuy();
    if(className == "GenActionSell")
        return new GenActionSell();
    return nullptr;
}

Mutatable* GenFactory::getMutatableByClassName(const QString &className)
{
    Mutatable* result = nullptr;
    result = getConditionByClassName(className);
    if(result)
        return result;
    result = getActionByClassName(className);
    return result;
}


