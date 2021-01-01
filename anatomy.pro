QT += widgets uitools
#requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
    node.h
SOURCES       = main.cpp mainwindow.cpp \
    node.cpp
#! [0]
RESOURCES     = anatomy.qrc
#! [0]

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/anatomy
INSTALLS += target

FORMS += \
    ui_mainwindow.ui
