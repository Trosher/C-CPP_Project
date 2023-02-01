QT       += core gui printsupport openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ima/giflib/dgif_lib.c \
    ima/giflib/egif_lib.c \
    ima/giflib/gif_err.c \
    ima/giflib/gif_font.c \
    ima/giflib/gif_hash.c \
    ima/giflib/gifalloc.c \
    ima/giflib/quantize.c \
    ima/qgifimage.cpp \
    main.cpp \
    mainwindow.cpp \
    C_file/pars_obj/pars_obj.c \
    C_file/struct.c \
    mywidget.cpp \
    C_file/Afina/afina.c

HEADERS += \
    C_file/struct.h \
    ima/giflib/gif_hash.h \
    ima/giflib/gif_lib.h \
    ima/giflib/gif_lib_private.h \
    ima/qgifglobal.h \
    ima/qgifimage.h \
    ima/qgifimage_p.h \
    mainwindow.h \
    C_file/pars_obj/pars_obj.h \
    mywidget.h \
    C_file/Afina/afina.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
  ima/gifimage.pro

DISTFILES += \
  ima/giflib/AUTHORS \
  ima/giflib/COPYING \
  ima/giflib/README
