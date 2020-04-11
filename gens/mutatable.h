#pragma once

#include <QString>

class Mutatable
{
public:
    Mutatable();
    virtual ~Mutatable() {}

    virtual void mutate() = 0;
    virtual QString toString() const = 0;

    static double mutatecoeff(double original);
};
