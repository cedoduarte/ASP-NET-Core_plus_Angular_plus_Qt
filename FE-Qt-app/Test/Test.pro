QT += core gui network widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qflexiblejsonobject.cpp \
    qsslnetaccessmanager.cpp \
    qsslnetrequest.cpp

HEADERS += \
    mainwindow.h \
    qflexiblejsonobject.h \
    qsslnetaccessmanager.h \
    qsslnetrequest.h

FORMS += \
    mainwindow.ui

LIBS += -L$$PWD/lib
LIBS += -lssl-1_1-x64
LIBS += -lcrypto-1_1-x64

RESOURCES += \
    res.qrc
