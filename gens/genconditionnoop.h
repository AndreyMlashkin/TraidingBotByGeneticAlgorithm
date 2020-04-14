#pragma once

#include "gencondition.h"

class GenConditionNoop : public GenCondition
{
    Q_OBJECT

public:
    GenConditionNoop() {}
    virtual bool operator() () override;
    QString toString() const override;

    void mutate() override {}
    Mutatable* copy() const override;

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &object) override;
};
