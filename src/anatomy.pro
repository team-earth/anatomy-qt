QT += widgets uitools
#requires(qtConfig(filedialog))
#QMAKE_CXXFLAGS += -std=c++11 -s TOTAL_STACK=512MB -s TOTAL_MEMORY=1024MB
#QMAKE_LFLAGS += -s TOTAL_STACK=512MB -s TOTAL_MEMORY=1024MB
HEADERS       = mainwindow.h \
    myqgraphicstextitem.h \
    node.h \
    paintHelper.h \
    sample_data.h \
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