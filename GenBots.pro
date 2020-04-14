QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agentbot.cpp \
    gen.cpp \
    gens/genactionbuy.cpp \
    gens/genactionsell.cpp \
    gens/genconditionask.cpp \
    gens/genconditionbid.cpp \
    gens/genconditionnoop.cpp \
    gens/genconditionsfactory.cpp \
    gens/mutatable.cpp \
    main.cpp \
    mainwindow.cpp \
    market.cpp

HEADERS += \
    agentbot.h \
    gen.h \
    gens/genaction.h \
    gens/genactionbuy.h \
    gens/genactionsell.h \
    gens/gencondition.h \
    gens/genconditionask.h \
    gens/genconditionbid.h \
    gens/genconditionnoop.h \
    gens/genconditionsfactory.h \
    gens/mutatable.h \
    mainwindow.h \
    market.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
