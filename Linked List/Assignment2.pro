TEMPLATE = app
CONFIG += cmdline
CONFIG += c++17
CONFIG += strict_c++
CONFIG += no_include_pwd
CONFIG -= app_bundle
CONFIG -= qt
CONFIG -= debug_and_release

QMAKE_CXXFLAGS += -pedantic
QMAKE_CXXFLAGS += -pedantic-errors

QMAKE_CXXFLAGS += -Wmissing-include-dirs
QMAKE_CXXFLAGS += -Wfloat-equal
QMAKE_CXXFLAGS += -Wredundant-decls
QMAKE_CXXFLAGS += -Winit-self
QMAKE_CXXFLAGS += -Wshadow
QMAKE_CXXFLAGS += -Wconversion


#------------------------------

SOURCES += main.cpp \
    Address.cpp \
    AddressArrayList.cpp \
    AddressLinkedList.cpp \

HEADERS += \
    Address.h \
    AddressArrayList.h \
    AddressLinkedList.h \
    ArrayList.h \

DISTFILES += \
    25000AddressesA.txt \
    25000AddressesB.txt \

