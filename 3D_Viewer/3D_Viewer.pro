QT       += core gui

QT += openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    glwidget.cpp \
    ../parsing_file.c \
    ../normalization.c \
    ../min_max.c \
    ../turn_matrix.c \
    ../move_matrix.c \
    ../scale_matrix.c

HEADERS += \
    glwidget.h \
    mainwindow.h \
    ../s21_3DViewer.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
