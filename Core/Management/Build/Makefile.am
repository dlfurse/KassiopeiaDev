# $Id$
# Kassiopeia/Core/Management Makefile definition

MANAGEMENT_INCLUDES =  \
    -I@top_srcdir@\
	-I@top_srcdir@/Core/Utility/Include\
	-I@top_srcdir@/Core/Messages/Include\
    -I@top_srcdir@/Core/Management/Include

MANAGEMENT_HEADERFILES = \
	../Include/KSManager.h\
	../Include/KSManagerInstanceTable.h\
	../Include/KSManagerFactory.h\
	../Include/KSManagerFactoryTable.h
	
MANAGEMENT_SOURCEFILES = \
    ../Source/KSManager.cxx\
    ../Source/KSManagerInstanceTable.cxx\
    ../Source/KSManagerFactory.cxx\
    ../Source/KSManagerFactoryTable.cxx
    
include_HEADERS = \
    $(MANAGEMENT_HEADERFILES)
    
###########################################

noinst_LTLIBRARIES = libKassiopeiaManagement.la

libKassiopeiaManagement_la_CPPFLAGS = \
    $(AM_CPPFLAGS)\
    $(MANAGEMENT_INCLUDES)

libKassiopeiaManagement_la_SOURCES = \
    $(MANAGEMENT_SOURCEFILES)

###########################################

CLEANFILES = 

MAINTAINERCLEANFILES = Makefile.in
