QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gui printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../main.cpp \
    mainwindow.cpp \
    loancalc_view.cpp \
    depositcalc_view.cpp \
    ../controller/depositcalc_controller.cpp \
    ../model/calc_model.cpp \
    ../model/loan_model.cpp \
    plot.cpp \
    qcustomplot.cpp \
    ../model/deposit_model.cpp

HEADERS += \
    mainwindow.h \
    ../controller/mainwindow_controller.h \
    loancalc_view.h \
    ../controller/loancalc_controller.h \
    depositcalc_view.h \
    ../controller/depositcalc_controller.h \
    ../model/calc_model.h \
    ../model/loan_model.h \
    ../model/deposit_model.h \
    plot.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui \
    loancalc.ui \
    depositcalc.ui \
    plot.ui

DESTDIR = ../../build/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
