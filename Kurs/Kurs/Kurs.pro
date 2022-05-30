QT       += core gui network script qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api.cpp \
    arrow.cpp \
    basedblocksetting.cpp \
    basedblockwindow.cpp \
    compositeblocksetting.cpp \
    compositeblockwindow.cpp \
    diagramitem.cpp \
    diagramitembased.cpp \
    diagramitemcomposite.cpp \
    diagramitemsparql.cpp \
    diagramscene.cpp \
    diagramsparqlatom.cpp \
    diagramtextitem.cpp \
    diagramview.cpp \
    main.cpp \
    mainwindow.cpp \
    mynetwork.cpp \
    outputwidget.cpp \
    sparqlblocksetting.cpp \
    sparqlblockwindow.cpp \
    virtualsetting.cpp

HEADERS += \
    api.h \
    arrow.h \
    basedblocksetting.h \
    basedblockwindow.h \
    compositeblocksetting.h \
    compositeblockwindow.h \
    diagramitem.h \
    diagramitembased.h \
    diagramitemcomposite.h \
    diagramitemsparql.h \
    diagramscene.h \
    diagramsparqlatom.h \
    diagramtextitem.h \
    diagramview.h \
    mainwindow.h \
    mynetwork.h \
    outputwidget.h \
    sparqlblocksetting.h \
    sparqlblockwindow.h \
    virtualsetting.h

FORMS += \
    basedblockwindow.ui \
    diagramview.ui \
    mainwindow.ui \
    outputwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    diagramscene.qrc
