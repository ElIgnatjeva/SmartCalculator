QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/testProject/calc.c \
    ../src/testProject/credit_calc.c \
    ../src/testProject/creditcalc.cpp \
    ../src/testProject/deposit_calc.c \
    ../src/testProject/main.cpp \
    ../src/testProject/mainwindow.cpp \
    ../src/testProject/qcustomplot.cpp \
    ../src/testProject/support.c \
    ../src/testProject/validator.c

HEADERS += \
    ../src/testProject/calc.h \
    ../src/testProject/creditcalc.h \
   ../src/testProject/mainwindow.h \
   ../src/testProject/qcustomplot.h

FORMS += \
   ../src/testProject/creditcalc.ui \
   ../src/testProject/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
