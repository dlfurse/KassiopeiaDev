# $Id$
# Kassiopeia/KSCore/build Makefile definition
# Author: Noah Oblath

MATH_INCLUDES =  \
	-I@top_srcdir@/Core/Math/Include\
	-I@top_srcdir@/Core/Utility/Include\
	-I@top_srcdir@/Core/Messages/Include

MATH_HEADERFILES =  \
    ../Include/KMathODE.h\
    ../Include/KMathCompositeODE.h\
    ../Include/KMathODESolver.h\
	../Include/KMathRK8.h\
    ../Include/KMathRK86.h\
    #../include/KMathPredictorCorrector.h\
    #../include/Legendre.h\
    #../include/KMathRK65.h\
    #../include/KMathRK87.h\
    #../include/KMathRK54.h

MATH_SOURCEFILES =  \
    ../Source/KMathODE.cxx\
    ../Source/KMathCompositeODE.cxx\
    ../Source/KMathODESolver.cxx\
    ../Source/KMathRK8.cxx\
    ../Source/KMathRK86.cxx
    
###########################################

noinst_LTLIBRARIES = libKassiopeiaMath.la

libKassiopeiaMath_la_CPPFLAGS = $(MATH_INCLUDES) $(AM_CPPFLAGS)

libKassiopeiaMath_la_SOURCES = \
    $(MATH_SOURCEFILES)
    
include_HEADERS = \
    $(MATH_HEADERFILES)

###########################################

CLEANFILES = 

MAINTAINERCLEANFILES = Makefile.in