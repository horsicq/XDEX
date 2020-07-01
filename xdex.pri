INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD


HEADERS += \
    $$PWD/xdex.h \
    $$PWD/xdex_def.h

SOURCES += \
    $$PWD/xdex.cpp


!contains(XCONFIG, xbinary) {
    XCONFIG += xbinary
    include(../Formats/xbinary.pri)
}

