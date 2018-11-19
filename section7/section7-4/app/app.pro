TEMPLATE = app

QT += qml quick multimedia

CONFIG += c++11

HEADERS += \
    audio.h \
    devices.h

SOURCES += \
    main.cpp \
    audio.cpp \
    devices.cpp

RESOURCES += qml.qrc
