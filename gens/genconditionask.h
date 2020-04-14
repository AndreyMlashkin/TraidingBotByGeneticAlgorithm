#ifndef GENCONDITIONASK_H
#define GENCONDITIONASK_H

#include "gencondition.h"
#include "market.h"

class GenConditionAsk : public GenCondition
{
    Q_OBJECT

public:
    GenConditionAsk(double initialStrikeAsk = 1);
    virtual bool operator() () override;

    void mutate() override;
    QString toString() const override;
    Mutatable* copy() const override;

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &object) override;

private:
    double m_strikeAsk;
};

#endif // GENCONDITIONASK_H
