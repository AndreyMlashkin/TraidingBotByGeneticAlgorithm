#pragma once

class Mutatable
{
public:
    Mutatable();

    virtual void mutate() = 0;

    static double mutatecoeff(double original);
};
