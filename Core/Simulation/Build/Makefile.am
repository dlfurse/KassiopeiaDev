# $Id$
# Kassiopeia/Core/Simulation/Build Makefile definition

SIMULATION_INCLUDES = \
    -I@top_srcdir@\
	-I@top_srcdir@/Core/Utility/Include\
	-I@top_srcdir@/Core/IO/Include\
	-I@top_srcdir@/Core/Math/Include\
	-I@top_srcdir@/Core/Simulation/Include

SIMULATION_HEADERFILES = \
	../Include/KSElectricField.h\
	../Include/KSRootElectricField.h\
	../Include/KSMagneticField.h\
	../Include/KSRootMagneticField.h\
	../Include/KSParticle.h\
	../Include/KSParticleFactory.h\
	../Include/KSParticleFactoryTable.h\
	../Include/KSProcess.h\
	../Include/KSTransportProcess.h\
	../Include/KSDiscreteProcess.h\
	../Include/KSRootProcess.h\
	../Include/KSStepSize.h\
	../Include/KSStepContainer.h\
	../Include/KSTrack.h\
	../Include/KSStep.h

SIMULATION_SOURCEFILES = \
	../Source/KSElectricField.cxx\
	../Source/KSRootElectricField.cxx\
	../Source/KSMagneticField.cxx\
	../Source/KSRootMagneticField.cxx\
    ../Source/KSParticle.cxx\
    ../Source/KSParticleFactory.cxx\
    ../Source/KSParticleFactoryList.cxx\
    ../Source/KSParticleFactoryTable.cxx\
    ../Source/KSProcess.cxx\
    ../Source/KSTransportProcess.cxx\
    ../Source/KSDiscreteProcess.cxx\
    ../Source/KSRootProcess.cxx\
    ../Source/KSStepSize.cxx\
    ../Source/KSStepContainer.cxx\
    ../Source/KSTrack.cxx\
    ../Source/KSStep.cxx

###########################################

noinst_LTLIBRARIES = libKassiopeiaSimulation.la

include_HEADERS = \
	$(SIMULATION_HEADERFILES)

libKassiopeiaSimulation_la_CPPFLAGS = \
	$(AM_CPPFLAGS)\
	$(SIMULATION_INCLUDES) 

libKassiopeiaSimulation_la_SOURCES = \
    $(SIMULATION_SOURCEFILES)

###########################################

CLEANFILES = \
   ../Source/*~\
   ../Include/*~

MAINTAINERCLEANFILES = Makefile.in
