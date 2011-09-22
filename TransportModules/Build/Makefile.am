# $Id$
# Kassiopeia/TransportModules Makefile definition

TRANSPORTMODULES_INCLUDES =  \
    -I@top_srcdir@\
	-I@top_srcdir@/Core/Utility/Include\
	-I@top_srcdir@/Core/Messages/Include\
	-I@top_srcdir@/Core/Management/Include\
	-I@top_srcdir@/Core/IO/Include\
    -I@top_srcdir@/Core/Math/Include\
    -I@top_srcdir@/Core/Simulation/Include\
    -I@top_srcdir@/Core/Configuration/Include\
    -I@top_srcdir@/TransportModules/Include

TRANSPORTMODULES_HEADERFILES = \
	../Include/KTrackODE.h\
	../Include/KTrackLorentzODE.h\
	../Include/KTrackParticle.h\
	../Include/KTrackExactParticle.h\
	../Include/KTrackError.h\
	../Include/KTrackExactError.h\
	../Include/KTrackStepComputer.h\
	../Include/KTrackExactStepComputer.h\
	../Include/KTrackProcess.h\
	../Include/KTrackProcessPropagation.h\
	../Include/KTrackStepSize.h\
	../Include/KTrackStepSizeCyclotron.h\
	../Include/KTrackStepSizeFix.h\
	../Include/KTrackStepSizeConst.h\
	../Include/KTrackStepSizeEnergy.h\
	../Include/KTrackStepSizeNumError.h\
	../Include/KScatteringStepSize.h\
	../Include/KScattering.h\
	../Include/KScatteringElastic.h\
	../Include/KScatteringExcitation.h\
	../Include/KScatteringIonisation.h\
	../Include/KScatteringCalculatorElastic.h\
	../Include/KScatteringCalculatorInelastic.h\
	../Include/DensityCalculator.h\
	../Include/ConstantDensityCalculator.h
	

TRANSPORTMODULES_SOURCEFILES = \
	../Source/KTrackODE.cxx\
	../Source/KTrackLorentzODE.cxx\
	../Source/KTrackParticle.cxx\
	../Source/KTrackExactParticle.cxx\
	../Source/KTrackError.cxx\
	../Source/KTrackExactError.cxx\
	../Source/KTrackStepComputer.cxx\
	../Source/KTrackExactStepComputer.cxx\
	../Source/KTrackProcess.cxx\
	../Source/KTrackProcessPropagation.cxx\
	../Source/KTrackStepSize.cxx\
	../Source/KTrackStepSizeCyclotron.cxx\
	../Source/KTrackStepSizeFix.cxx\
	../Source/KTrackStepSizeConst.cxx\
	../Source/KTrackStepSizeEnergy.cxx\
	../Source/KTrackStepSizeNumError.cxx\
	../Source/KScatteringStepSize.cxx\
	../Source/KScattering.cxx\
	../Source/KScatteringElastic.cxx\
	../Source/KScatteringExcitation.cxx\
	../Source/KScatteringIonisation.cxx\
	../Source/KScatteringCalculatorElastic.cxx\
	../Source/KScatteringCalculatorInelastic.cxx\
	../Source/DensityCalculator.cxx\
	../Source/ConstantDensityCalculator.cxx
    
include_HEADERS = \
    $(TRANSPORTMODULES_HEADERFILES)
    
###########################################

noinst_LTLIBRARIES = libKassiopeiaTransportModules.la

libKassiopeiaTransportModules_la_CPPFLAGS = \
    $(AM_CPPFLAGS)\
    $(TRANSPORTMODULES_INCLUDES)

libKassiopeiaTransportModules_la_SOURCES = \
    $(TRANSPORTMODULES_SOURCEFILES)

###########################################

CLEANFILES = 

MAINTAINERCLEANFILES = Makefile.in
