QT += widgets uitools
#requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
    node.h \
    openglwidget.h \
    paintHelper.h
SOURCES       = main.cpp mainwindow.cpp \
    node.cpp \
    openglwidget.cpp \
    paintHelper.cpp
#! [0]
RESOURCES     = anatomy.qrc
#! [0]

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/anatomy
target.path = widgets/mainwindows/anatomy
INSTALLS += target

FORMS += \
    custommainwindow.ui
