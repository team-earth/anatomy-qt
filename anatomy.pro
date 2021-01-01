QT += widgets uitools
#requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
    node.h \
    openglwidget.h
SOURCES       = main.cpp mainwindow.cpp \
    node.cpp \
    openglwidget.cpp
#! [0]
RESOURCES     = anatomy.qrc
#! [0]

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/anatomy
target.path = widgets/mainwindows/anatomy
INSTALLS += target

FORMS += \
    custommainwindow.ui
