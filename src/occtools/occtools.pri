#############################################################################
##  FougTools
##  Copyright Fougue (30 Mar. 2015)
##  contact@fougue.pro
##
## This software is a computer program whose purpose is to provide utility
## tools for the C++ language, the Qt and OpenCascade toolkits.
##
## This software is governed by the CeCILL-C license under French law and
## abiding by the rules of distribution of free software.  You can  use,
## modify and/ or redistribute the software under the terms of the CeCILL-C
## license as circulated by CEA, CNRS and INRIA at the following URL
## "http://www.cecill.info".
#############################################################################

include(occ.pri)

HEADERS += \
    $$PWD/io.h \
    $$PWD/occtools.h \
    $$PWD/ais_text.h \
    $$PWD/handle_ais_text.h \
    $$PWD/brep_point_on_faces_projection.h \
    $$PWD/gcpnts_uniform_abscissa_const_iterator.h \
    $$PWD/point_on_faces_projector.h \
    $$PWD/qt_view.h \
    $$PWD/qt_view_controller.h \
    $$PWD/down_cast.h \
    $$PWD/ais_utils.h \
    $$PWD/geom_utils.h \
    $$PWD/kernel_utils.h \
    $$PWD/math_utils.h \
    $$PWD/topods_utils.h \
    $$PWD/qt_utils.h

SOURCES += \
    $$PWD/io.cpp \
    $$PWD/ais_text.cpp \
    $$PWD/brep_point_on_faces_projection.cpp \
    $$PWD/gcpnts_uniform_abscissa_const_iterator.cpp \
    $$PWD/point_on_faces_projector.cpp \
    $$PWD/qt_view.cpp \
    $$PWD/qt_view_controller.cpp \
    $$PWD/ais_utils.cpp \
    $$PWD/geom_utils.cpp \
    $$PWD/kernel_utils.cpp \
    $$PWD/math_utils.cpp \
    $$PWD/topods_utils.cpp \
    $$PWD/qt_utils.cpp

LIBS += -lTKBRep -lTKernel -lTKG2d -lTKG3d -lTKGeomAlgo -lTKGeomBase \
        -lTKIGES -lTKMath -lTKMesh -lTKOpenGl -lTKPrim -lTKService -lTKShHealing \
        -lTKSTEP -lTKSTEPAttr -lTKSTEPBase -lTKSTEP209 -lTKSTL -lTKTopAlgo \
        -lTKV3d -lTKXSBase
