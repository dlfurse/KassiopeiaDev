# $Id$
# Kassiopeia/Applications/Validation Makefile definition

VALIDATION_INCLUDES = \
    -I@top_srcdir@/Core/Math/Include\
    -I@top_srcdir@/Core/Messages/Include\
    -I@top_srcdir@/Core/Utility/Include\
    -I@top_srcdir@/Core/Configuration/Include\
    -I@top_srcdir@/Core/Simulation/Include\
    -I@top_srcdir@/TransportModules/Include

VALIDATION_LIBS = \
    @top_srcdir@/Core/Build/libKassiopeiaCore.la \
    @top_srcdir@/TransportModules/Build/libKassiopeiaTransportModules.la

###########################################

VALIDATION_COMPILER_FLAGS = \
    $(AM_CPPFLAGS)\
    $(GSL_CFLAGS)\
    $(VALIDATION_INCLUDES)
    
VALIDATION_LINKER_FLAGS = \
    $(AM_LDFLAGS)\
    $(GSL_LIBS)
    
###########################################

bin_PROGRAMS = TestExperiment
TestExperiment_SOURCES = ../Source/TestExperiment.cxx
TestExperiment_CPPFLAGS = $(VALIDATION_COMPILER_FLAGS)
TestExperiment_LDADD = $(VALIDATION_LIBS)
TestExperiment_LDFLAGS = $(VALIDATION_LINKER_FLAGS)

bin_PROGRAMS += TestAssert
TestAssert_SOURCES = ../Source/TestAssert.cxx
TestAssert_CPPFLAGS = $(VALIDATION_COMPILER_FLAGS)
TestAssert_LDADD = $(VALIDATION_LIBS)
TestAssert_LDFLAGS = $(VALIDATION_LINKER_FLAGS)

bin_PROGRAMS += TestTypeLists
TestTypeLists_SOURCES = ../Source/TestTypeLists.cxx
TestTypeLists_CPPFLAGS = $(VALIDATION_COMPILER_FLAGS)
TestTypeLists_LDADD = $(VALIDATION_LIBS)
TestTypeLists_LDFLAGS = $(VALIDATION_LINKER_FLAGS)
    
bin_PROGRAMS += TestMessages
TestMessages_SOURCES = ../Source/TestMessages.cxx
TestMessages_CPPFLAGS = $(VALIDATION_COMPILER_FLAGS)
TestMessages_LDADD = $(VALIDATION_LIBS)
TestMessages_LDFLAGS = $(VALIDATION_LINKER_FLAGS)

bin_PROGRAMS += TestXMLTokenizer
TestXMLTokenizer_SOURCES = ../Source/TestXMLTokenizer.cxx
TestXMLTokenizer_CPPFLAGS = $(VALIDATION_COMPILER_FLAGS)
TestXMLTokenizer_LDADD = $(VALIDATION_LIBS)
TestXMLTokenizer_LDFLAGS = $(VALIDATION_LINKER_FLAGS)

bin_PROGRAMS += TestODE
TestODE_SOURCES = ../Source/TestODE.cxx
TestODE_CPPFLAGS = $(VALIDATION_COMPILER_FLAGS)
TestODE_LDADD = $(VALIDATION_LIBS)
TestODE_LDFLAGS = $(VALIDATION_LINKER_FLAGS)

bin_PROGRAMS += TestStepComputer
TestStepComputer_SOURCES = ../Source/TestStepComputer.cxx
TestStepComputer_CPPFLAGS = $(VALIDATION_COMPILER_FLAGS)
TestStepComputer_LDADD = $(VALIDATION_LIBS)
TestStepComputer_LDFLAGS = $(VALIDATION_LINKER_FLAGS)

###########################################

CLEANFILES = 

MAINTAINERCLEANFILES = Makefile.in
