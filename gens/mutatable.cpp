#include <QtGlobal>
#include <QRandomGenerator>

#include "mutatable.h"

Mutatable::Mutatable()
{

}

double Mutatable::mutatecoeff(double original)
{

    quint32 randomOperation = QRandomGenerator::global()->generate();
    const quint32 variants = 4;
    randomOperation %= variants;

    double randomKoeff = QRandomGenerator::global()->generateDouble();
    switch (randomOperation)
    {
    case 0: original += randomKoeff; break;
    case 1: original -= randomKoeff; break;
    case 2: original *= randomKoeff; break;
    case 3: original /= randomKoeff; break;
    }
    return original;
}

double Mutatable::mutatecoeffNoNegative(double original)
{
    double result = mutatecoeff(original);
    if(result < 0)
        result *= -1;
    return result;
}
