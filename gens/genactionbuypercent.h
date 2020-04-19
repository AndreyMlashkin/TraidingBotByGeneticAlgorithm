#pragma once

#include "genaction.h"

class GenActionBuyPercent : public GenAction
{
    Q_OBJECT
public:
    GenActionBuyPercent(double percent = 0.05);

    void mutate() override;
    QString toString() const override;
    Mutatable *copy() const override;
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &object) override;

    void operator ()(AgentBot & parent) override;

private:
    double m_percent;
};
