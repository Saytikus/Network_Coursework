QT += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/const/FilePathConstants.cpp \
    common/logs/LogRecord.cpp \
    common/logs/Logger.cpp \
    core/Core.cpp \
    core/handlers/AccountRegistrationHandler.cpp \
    core/handlers/HandlerPool.cpp \
    core/serializers/AccountRegistrationSerializer.cpp \
    core/serializers/SerializerPool.cpp \
    core/storage/data/Account.cpp \
    core/storage/data/AccountBuffer.cpp \
    core/storage/data/AccountBufferPool.cpp \
    core/storage/database/Database.cpp \
    core/storage/database/DatabaseFileCreator.cpp \
    core/storage/database/DatabaseReader.cpp \
    core/storage/database/DatabaseWriter.cpp \
    core/storage/database/XMLElementReader.cpp \
    core/storage/database/XMLElementWriter.cpp \
    core/storage/database/XMLHelper.cpp \
    core/workers/Worker.cpp \
    core/workers/WorkerThreadPool.cpp \
    network/NetworkWorker.cpp \
    network\ApplicationServer.cpp \
    init\main.cpp \
    ui\MainWindow.cpp

HEADERS += \
    common/const/FilePathConstants.h \
    common/enums/EnumHandlerType.h \
    common/logs/LogRecord.h \
    common/logs/Logger.h \
    core/Core.h \
    core/handlers/AccountRegistrationHandler.h \
    core/handlers/BaseHandler.h \
    core/handlers/HandlerPool.h \
    core/serializers/AccountRegistrationSerializer.h \
    core/serializers/BaseSerializer.h \
    core/serializers/SerializerPool.h \
    core/storage/data/Account.h \
    core/storage/data/AccountBuffer.h \
    core/storage/data/AccountBufferPool.h \
    core/storage/database/Database.h \
    core/storage/database/DatabaseFileCreator.h \
    core/storage/database/DatabaseReader.h \
    core/storage/database/DatabaseWriter.h \
    core/storage/database/XMLElementReader.h \
    core/storage/database/XMLElementWriter.h \
    core/storage/database/XMLHelper.h \
    core/storage/innerPackets/AccountRegistrationPacket.h \
    core/storage/innerPackets/BasePacket.h \
    core/workers/Worker.h \
    core/workers/WorkerThreadPool.h \
    network/NetworkAddressData.h \
    network/NetworkWorker.h \
    network\ApplicationServer.h \
    ui\MainWindow.h

FORMS += \
    ui\forms\MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include($$PWD/../Qt-Secret/src/Qt-Secret.pri)
