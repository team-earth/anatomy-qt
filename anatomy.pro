QT += widgets uitools
#requires(qtConfig(filedialog))

HEADERS       =
SOURCES       = main.cpp
#! [0]
RESOURCES     = anatomy.qrc
#! [0]

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/anatomy
INSTALLS += target

FORMS += \
    mainwindow.ui
