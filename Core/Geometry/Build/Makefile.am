# $Id$
# Kassiopeia/Core/Configure Makefile definition

GEOMETRY_INCLUDES =  \
    -I@top_srcdir@\
    -I@top_srcdir@/Core/Geometry/Include\
    -I@top_srcdir@/Core/Utility/Include\
    -I@top_srcdir@/Core/Configuration/Include\
    -I@top_srcdir@/Core/Simulation/Include

GEOMETRY_HEADERFILES = \
	../Include/KSTransformation.h\
	../Include/KSGeometryToolbox.h\
	../Include/KSGeometry.h\
	../Include/KSShape.h\
	../Include/KSSurface.h\
	../Include/KSRectangle.h\
	../Include/KSVolume.h\
	../Include/KSBoxLikeVolume.h\
	../Include/KSBox.h\
	../Include/KSAssembly.h\
	../Include/KSPlacement.h\
	../Include/KSSurfacePlacement.h\
	../Include/KSVolumePlacement.h\
	../Include/KSAssemblyPlacement.h
	

GEOMETRY_SOURCEFILES = \
	../Source/KSTransformation.cxx\
	../Source/KSGeometryToolbox.cxx\
	../Source/KSGeometry.cxx\
    ../Source/KSShape.cxx\
    ../Source/KSSurface.cxx\
    ../Source/KSRectangle.cxx\
    ../Source/KSVolume.cxx\
    ../Source/KSBoxLikeVolume.cxx\
    ../Source/KSBox.cxx\
	../Source/KSAssembly.cxx\
	../Source/KSPlacement.cxx\
	../Source/KSSurfacePlacement.cxx\
	../Source/KSVolumePlacement.cxx\
	../Source/KSAssemblyPlacement.cxx
    
include_HEADERS = \
    $(GEOMETRY_HEADERFILES)
    
###########################################

noinst_LTLIBRARIES = libKassiopeiaGeometry.la

libKassiopeiaGeometry_la_CPPFLAGS = \
    $(AM_CPPFLAGS)\
    $(GEOMETRY_INCLUDES)

libKassiopeiaGeometry_la_SOURCES = \
    $(GEOMETRY_SOURCEFILES)

###########################################

CLEANFILES = 

MAINTAINERCLEANFILES = Makefile.in
