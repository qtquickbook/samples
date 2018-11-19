include(spectrum.pri)

TEMPLATE = subdirs

CONFIG  += ordered

!contains(DEFINES, DISABLE_FFT): SUBDIRS += 3rdparty/fftreal
SUBDIRS += app

TARGET = spectrum
