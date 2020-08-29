QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Emulator.cpp \
    EmulatorView.cpp \
    Obstacle.cpp \
    UserProcess.cpp \
    Wheelbase.cpp \
    helper.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Emulator.h \
    EmulatorView.h \
    Obstacle.h \
    UserProcess.h \
    Wheelbase.h \
    helper.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/Resourses.qrc

# QCodeEditor includes.
HEADERS += \
    include/third-party/QCodeEditor/internal/QCodeEditor.hpp \
    include/third-party/QCodeEditor/internal/QCXXHighlighter.hpp \
    include/third-party/QCodeEditor/internal/QFramedTextAttribute.hpp \
    include/third-party/QCodeEditor/internal/QGLSLCompleter.hpp \
    include/third-party/QCodeEditor/internal/QLanguage.hpp \
    include/third-party/QCodeEditor/internal/QLineNumberArea.hpp \
    include/third-party/QCodeEditor/internal/QStyleSyntaxHighlighter.hpp \
    include/third-party/QCodeEditor/internal/QSyntaxStyle.hpp \
    include/third-party/QCodeEditor/internal/QXMLHighlighter.hpp \

SOURCES += \
    src/third-party/QCodeEditor/QCodeEditor.cpp \
    src/third-party/QCodeEditor/QCXXHighlighter.cpp \
    src/third-party/QCodeEditor/QFramedTextAttribute.cpp \
    src/third-party/QCodeEditor/QGLSLCompleter.cpp \
    src/third-party/QCodeEditor/QLanguage.cpp \
    src/third-party/QCodeEditor/QLineNumberArea.cpp \
    src/third-party/QCodeEditor/QStyleSyntaxHighlighter.cpp \
    src/third-party/QCodeEditor/QSyntaxStyle.cpp \
    src/third-party/QCodeEditor/QXMLHighlighter.cpp \

INCLUDEPATH += \
    $$PWD/include/third-party/QCodeEditor \
    $$PWD/include/third-party/QCodeEditor/internal

RESOURCES += resources/qcodeeditor_resources.qrc
