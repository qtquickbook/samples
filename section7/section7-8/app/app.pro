include(../spectrum.pri)

TEMPLATE = app

QT += qml quick multimedia

CONFIG += c++11

HEADERS += \
    audio.h \
    devices.h \
    frequencyspectrum.h \
    spectrum.h \
    spectrumanalyser.h \
    spectrumimageprovider.h \
    utils.h

SOURCES += main.cpp \
    audio.cpp \
    devices.cpp \
    frequencyspectrum.cpp \
    spectrumanalyser.cpp \
    spectrumimageprovider.cpp \
    utils.cpp

fftreal_dir = ../3rdparty/fftreal

INCLUDEPATH += $${fftreal_dir}

RESOURCES += qml.qrc

# Dynamic linkage against FFTReal DLL
!contains(DEFINES, DISABLE_FFT) {
    LIBS += -L..$${spectrum_build_dir}
    LIBS += -lfftreal
}

DESTDIR = ..$${spectrum_build_dir}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

