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

    case 1: return new GenConditionAsk((Market::getMarketInstance().getMaxAsk() +
                                        Market::getMarketInstance().getMinAsk()) / 2);

    case 2: return new GenConditionBid((Market::getMarketInstance().getMaxBid() +
                                        Market::getMarketInstance().getMinBid()) / 2);
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


