#include <QtGlobal>
#include <QRandomGenerator>

#include "mutatable.h"

Mutatable::Mutatable()
{

}

double Mutatable::mutatecoeff(double original)
{
    double randomKoeff = QRandomGenerator::global()->generateDouble();

    quint32 randomOperation = QRandomGenerator::global()->generate();
    const quint32 variants = 4;
    randomOperation %= variants;

    switch (randomOperation)
    {
    case 0: original += randomKoeff; break;
    case 1: original -= randomKoeff; break;
    case 2: original *= randomKoeff; break;
    case 3: original /= randomKoeff; break;
    }
    return original;
}
