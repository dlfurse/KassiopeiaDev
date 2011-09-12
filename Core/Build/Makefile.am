# $Id$
# Kassiopeia/Core/build Makefile definition

###########################################

lib_LTLIBRARIES = libKassiopeiaCore.la

libKassiopeiaCore_la_CPPFLAGS = \
	$(AM_CPPFLAGS)

libKassiopeiaCore_la_LIBADD = \
    ../Utility/Build/libUtility.la\
    ../Math/Build/libKassiopeiaMath.la\
    ../Management/Build/libKassiopeiaManagement.la\
    ../IO/Build/libKassiopeiaIO.la\
    ../Simulation/Build/libKassiopeiaSimulation.la\
    ../Geometry/Build/libKassiopeiaGeometry.la


libKassiopeiaCore_la_SOURCES = 
#A dummy source is required to induce linking, because autotools sucks.
#Autotools sucks, big-time...
nodist_EXTRA_libKassiopeiaCore_la_SOURCES = dummy.cxx

###########################################

CLEANFILES = 

MAINTAINERCLEANFILES = Makefile.in
