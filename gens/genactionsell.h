#ifndef GENACTIONSELL_H
#define GENACTIONSELL_H

#include "genaction.h"

class GenActionSell : public GenAction
{
    Q_OBJECT

public:
    GenActionSell(double ammount = 500);
    void operator() (AgentBot& parent) override;

    void mutate() override;
    QString toString() const override;
    Mutatable* copy() const override;

    QJsonObject serialize() const override;
    void deserialize(const QJsonObject &object) override;

private:
    double m_ammount;
};

#endif // GENACTIONSELL_H
