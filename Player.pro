QT       += core gui multimedia multimediawidgets sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+=$$PWD surface
include(surface/surface.pri)

INCLUDEPATH+=$$PWD database
include(database/database.pri)

INCLUDEPATH+=$$PWD baseWidgets
include(baseWidgets/baseWidgets.pri)

SOURCES += \
    main.cpp

HEADERS += \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

