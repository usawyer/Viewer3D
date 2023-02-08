QT       += core gui widgets opengl openglwidgets
include (../QtGifImage/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affine_transformation.cpp \
    controller.cc \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp \
    model.cc \
    matrix_oop.cpp \
    settings_data.cc

HEADERS += \
    affine_transformation.h \
    controller.h \
    mainwidget.h \
    mainwindow.h \
    model.h \
    matrix_oop.h \
    settings_data.h

FORMS += \
    mainwindow.ui

DEFINES += HOME_DIR=\\\"$(HOME)\\\"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    button_image.qrc \
    sett.qrc \
    shaders.qrc

DISTFILES += \
    fshader.glsl \
    gif.png \
    images.png \
    vshader.glsl
