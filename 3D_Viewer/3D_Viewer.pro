QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_VERSION, 6): QT += openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    gifLibrary/QtGifImage/3rdParty/giflib/dgif_lib.c \
    gifLibrary/QtGifImage/3rdParty/giflib/egif_lib.c \
    gifLibrary/QtGifImage/3rdParty/giflib/gif_err.c \
    gifLibrary/QtGifImage/3rdParty/giflib/gif_font.c \
    gifLibrary/QtGifImage/3rdParty/giflib/gif_hash.c \
    gifLibrary/QtGifImage/3rdParty/giflib/gifalloc.c \
    gifLibrary/QtGifImage/3rdParty/giflib/quantize.c \
    gifLibrary/QtGifImage/gifimage/doc/snippets/doc_src_qtgifimage.cpp \
    gifLibrary/QtGifImage/gifimage/qgifimage.cpp \
    main.cc \
    model/figure.cc \
    model/model.cc \
    model/parser.cc \
    view/figurerenderer.cc \
    view/mainwindow.cc \

HEADERS += \
    controller/controller.h \
    gifLibrary/QtGifImage/3rdParty/giflib/gif_hash.h \
    gifLibrary/QtGifImage/3rdParty/giflib/gif_lib.h \
    gifLibrary/QtGifImage/3rdParty/giflib/gif_lib_private.h \
    gifLibrary/QtGifImage/gifimage/qgifglobal.h \
    gifLibrary/QtGifImage/gifimage/qgifimage.h \
    gifLibrary/QtGifImage/gifimage/qgifimage_p.h \
    model/figure.h \
    model/model.h \
    model/parser.h \
    model/renderoptions.h \
    view/figurerenderer.h \
    view/mainwindow.h

FORMS += \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    gifLibrary/QtGifImage/gifimage/doc/snippets/doc_src_qtgifimage.pro \
    gifLibrary/QtGifImage/gifimage/gifimage.pro \
    gifLibrary/QtGifImage/src.pro

DISTFILES += \
    gifLibrary/QtGifImage/3rdParty/giflib.pri \
    gifLibrary/QtGifImage/3rdParty/giflib/AUTHORS \
    gifLibrary/QtGifImage/3rdParty/giflib/COPYING \
    gifLibrary/QtGifImage/3rdParty/giflib/README \
    gifLibrary/QtGifImage/gifimage/doc/qtgifimage.qdocconf \
    gifLibrary/QtGifImage/gifimage/doc/src/examples.qdoc \
    gifLibrary/QtGifImage/gifimage/doc/src/index.qdoc \
    gifLibrary/QtGifImage/gifimage/doc/src/qtgifimage.qdoc \
    gifLibrary/QtGifImage/gifimage/doc/src/usage.qdoc \
    gifLibrary/QtGifImage/gifimage/qtgifimage.pri

RESOURCES += \
    icons.qrc
