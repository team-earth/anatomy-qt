QT += widgets uitools
#requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
    myqgraphicstextitem.h \
    node.h \
    paintHelper.h \
    textedit.h \
    view.h \
    xmlnode.h
SOURCES       = main.cpp mainwindow.cpp \
    myqgraphicstextitem.cpp \
    node.cpp \
    paintHelper.cpp \
    textedit.cpp \
    view.cpp \
    xmlnode.cpp
#! [0]
RESOURCES     = anatomy.qrc
#! [0]

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/anatomy
target.path = widgets/mainwindows/anatomy
INSTALLS += target

FORMS += \
    custommainwindow.ui
