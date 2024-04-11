QT = core network

CONFIG += c++17 cmdline

SOURCES += \
        clientconnection.cpp \
        main.cpp \
        webserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    clientconnection.h \
    webserver.h
