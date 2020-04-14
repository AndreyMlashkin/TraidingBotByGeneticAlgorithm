#ifndef GENCONDITIONBID_H
#define GENCONDITIONBID_H

#include "gencondition.h"

class GenConditionBid : public GenCondition
{
    Q_OBJECT

public:
    GenConditionBid(double initialStrikeBid = 1);
    virtual bool operator() () override;

    void mutate() override;
    QString toString() const override;
    Mutatable* copy() const override;

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &object) override;

private:
    double m_strikeBid;
};

#endif // GENCONDITIONBID_H
