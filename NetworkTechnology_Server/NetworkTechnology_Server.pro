QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/storage/data/Account.cpp \
    core/storage/data/AccountBuffer.cpp \
    core/storage/data/AccountBufferPool.cpp \
    network\ApplicationServer.cpp \
    init\main.cpp \
    ui\MainWindow.cpp

HEADERS += \
    core/storage/data/Account.h \
    core/storage/data/AccountBuffer.h \
    core/storage/data/AccountBufferPool.h \
    network/NetworkAddressData.h \
    network\ApplicationServer.h \
    ui\MainWindow.h

FORMS += \
    ui\forms\MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include($$PWD/../Qt-Secret/src/Qt-Secret.pri)