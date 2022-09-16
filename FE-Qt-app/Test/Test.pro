QT += core gui network widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qsslnetaccessmanager.cpp \
    qsslnetrequest.cpp

HEADERS += \
    mainwindow.h \
    qsslnetaccessmanager.h \
    qsslnetrequest.h

FORMS += \
    mainwindow.ui

LIBS += -L$$PWD/lib
LIBS += -lssl-1_1-x64
LIBS += -lcrypto-1_1-x64
