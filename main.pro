# define your application name here
TARGET = CurveApp

# add your source cpp files here
SOURCES += \
    main.cpp \
    mainWidget.cpp \
    toolsWidget.cpp \
    drawingWidgetItems.cpp \
    drawingWidget.cpp \
    animationWidgetItems.cpp \
    animationWidget.cpp \
    scene.cpp \
    curve_2D_lagrange.cpp \
    animatedPoint.cpp

# add your header files here
HEADERS += \
    mainWidget.h \
    toolsWidget.h \
    drawingWidgetItems.h \
    drawingWidget.h \
    animationWidgetItems.h \
    animationWidget.h \
    scene.h \
    curve1D.h \
    curve1DHermite.h \
    curve1DRessortHermite.h \
    curve1DRebondHermite.h \
    curve2DBsplines.h\
    curve2D.h \
    curve1DLinear.h \
    curve2DLinear.h \
    Curve1DLinearRessort.h \
    Curve1DLinearRebond.h \
    curve2DLinearclosed.h \
    curve1DBezier.h \
    curve2DBezier.h \
    Curve2DBezierClosed.h \
    curve_2D_lagrange.h \
    curve1DLagrange.h \
    curve2DBsplines.h \
    Curve2Dhermite.h\
    curve1DHermiteChange.h \
    curve1DHermite_random.h \
    curve2DBezierSin.h \
    curve2DBezierWeird.h \
    curve2DBsplinesChordal.h \
    animatedPoint.h

TEMPLATE = app

INCLUDEPATH += eigen

QMAKE_CXXFLAGS += -std=c++11 -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-misleading-indentation -Wno-deprecated-declarations

QT += core gui widgets
