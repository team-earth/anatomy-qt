QT += widgets uitools
#requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
    model.h \
    node.h \
    paintHelper.h \
    view.h
SOURCES       = main.cpp mainwindow.cpp \
    model.cpp \
    node.cpp \
    paintHelper.cpp \
    view.cpp
#! [0]
RESOURCES     = anatomy.qrc
#! [0]

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/anatomy
target.path = widgets/mainwindows/anatomy
INSTALLS += target

FORMS += \
    custommainwindow.ui
