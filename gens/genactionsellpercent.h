#pragma once

#include "genaction.h"

class GenActionSellPercent : public GenAction
{
    Q_OBJECT
public:
    GenActionSellPercent(double percent = 0.01);

    void mutate() override;
    QString toString() const override;
    Mutatable *copy() const override;
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &object) override;

    void operator ()(AgentBot & parent) override;

private:
    double m_percent;
};
