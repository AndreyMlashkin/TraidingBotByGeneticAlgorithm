QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app
INCLUDEPATH += ../../
INCLUDEPATH += ../../gens

#original project's files:
SOURCES +=     \
    ../../gen.cpp \
    ../../gens/genactionbuy.cpp         \
    ../../gens/genactionsell.cpp        \
    ../../gens/genconditionask.cpp      \
    ../../gens/genconditionbid.cpp      \
    ../../gens/genconditionnoop.cpp     \
    ../../gens/genconditionsfactory.cpp \
    ../../gens/mutatable.cpp            \
    ../../agentbot.cpp                  \
    ../../market.cpp                    \

HEADERS +=                            \
    ../../gen.h                       \
    ../../gens/genaction.h            \
    ../../gens/genactionbuy.h         \
    ../../gens/genactionsell.h        \
    ../../gens/gencondition.h         \
    ../../gens/genconditionask.h      \
    ../../gens/genconditionbid.h      \
    ../../gens/genconditionnoop.h     \
    ../../gens/genconditionsfactory.h \
    ../../gens/mutatable.h            \
    ../../agentbot.h                  \
    ../../market.h                    \


SOURCES +=  tst_agentbottest.cpp
