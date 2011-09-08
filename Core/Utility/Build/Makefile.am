# $Id$
# Kassiopeia/Core/Utility/Build Makefile definition

UTILITY_INCLUDES =  \
    -I@top_srcdir@\
	-I@top_srcdir@/Core/Utility/Include

UTILITY_HEADERFILES =  \
	../Include/KSDimensions.h\
	../Include/KSUnits.h\
    ../Include/KSConst.h\
    ../Include/KSRandom.h\
    ../Include/KSQueue.h\
    ../Include/KSCommand.h\
    ../Include/KSCyclicIterator.h

UTILITY_SOURCEFILES = \
	../Source/KSDimensions.cxx\
	../Source/KSUnits.cxx\
    ../Source/KSConst.cxx\
    ../Source/KSRandom.cxx

###########################################

include_HEADERS = \
    $(UTILITY_HEADERFILES)

noinst_LTLIBRARIES = libUtility.la

libUtility_la_CPPFLAGS = \
    $(UTILITY_INCLUDES)\
    $(AM_CPPFLAGS)

libUtility_la_SOURCES = \
    $(UTILITY_SOURCEFILES)

###########################################

CLEANFILES =

MAINTAINERCLEANFILES = Makefile.in
