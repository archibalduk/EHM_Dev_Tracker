QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++latest

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Enable as many compiler warnings as possible
CONFIG += warn_on

# Resources
RC_FILE = res/EHM_Dev_Tracker.rc
#RESOURCES = res/EHM_Dev_Tracker.qrc

# Application version
VERSION = 0.1.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# External project libraries
include($$PWD/lib/ehm_dal/ehm_dal.pri)
include($$PWD/lib/qxlsx/qxlsx.pri)

# Source files
SOURCES += \
    src/control_panel.cpp \
    src/individual_tools/research_spreadsheet_tool.cpp \
    src/main.cpp \
    src/main_window.cpp \
    src/tools/abstract_tool.cpp \
    src/tools/individual_tools_widget.cpp

HEADERS += \
    src/control_panel.h \
    src/individual_tools/research_spreadsheet_tool.h \
    src/main_window.h \
    src/tools/abstract_tool.h \
    src/tools/individual_tools_widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    res/EHM_Dev_Tracker.rc
