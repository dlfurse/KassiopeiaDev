# $Id$
# Kassiopeia/Core/Configure Makefile definition

CONFIGURATION_INCLUDES =  \
    -I@top_srcdir@\
	-I@top_srcdir@/Core/Utility/Include\
	-I@top_srcdir@/Core/Messages/Include\
    -I@top_srcdir@/Core/Configuration/Include

CONFIGURATION_HEADERFILES = \
	../Include/KSIOMessage.h\
	../Include/KSConfigurationFile.h\
    ../Include/KSToken.h\
	../Include/KSBeginParsingToken.h\
	../Include/KSEndParsingToken.h\
	../Include/KSBeginFileToken.h\
	../Include/KSEndFileToken.h\
    ../Include/KSErrorToken.h\
    ../Include/KSXMLToken.h\
    ../Include/KSXMLStartElementToken.h\
    ../Include/KSXMLAttributeToken.h\
    ../Include/KSXMLEndElementToken.h\
    ../Include/KSXMLDataToken.h\
    ../Include/KSPseudoXMLToken.h\
    ../Include/KSPseudoBeginToken.h\
    ../Include/KSPseudoParameterToken.h\
    ../Include/KSPseudoEndToken.h\
    ../Include/KSPseudoKeywordToken.h\
    ../Include/KSPseudoErrorToken.h\
    ../Include/KSReceiver.h\
    ../Include/KSXMLReceiver.h\
    ../Include/KSPseudoXMLReceiver.h\
    ../Include/KSTokenizer.h\
    ../Include/KSXMLTokenizer.h\
    ../Include/KSPseudoXMLTokenizer.h\
    ../Include/KSBuilder.h\
    ../Include/KSBuilderSystem.h\
    ../Include/KSBuilderPrototype.h\
    ../Include/KSInitializer.h\
    ../Include/KSInitializerPrototype.h\
    ../Include/KSBuilderFactory.h\
    ../Include/KSBuilderFactoryPrototype.h\
    ../Include/KSBuilderFactoryTable.h

CONFIGURATION_SOURCEFILES = \
	../Source/KSIOMessage.cxx\
	../Source/KSConfigurationFile.cxx\
    ../Source/KSToken.cxx\
	../Source/KSBeginParsingToken.cxx\
	../Source/KSEndParsingToken.cxx\
	../Source/KSBeginFileToken.cxx\
	../Source/KSEndFileToken.cxx\
    ../Source/KSErrorToken.cxx\
    ../Source/KSXMLToken.cxx\
    ../Source/KSXMLStartElementToken.cxx\
    ../Source/KSXMLAttributeToken.cxx\
    ../Source/KSXMLDataToken.cxx\
    ../Source/KSXMLEndElementToken.cxx\
    ../Source/KSXMLErrorToken.cxx\
    ../Source/KSPseudoXMLToken.cxx\
    ../Source/KSPseudoBeginToken.cxx\
    ../Source/KSPseudoParameterToken.cxx\
    ../Source/KSPseudoEndToken.cxx\
    ../Source/KSPseudoKeywordToken.cxx\
    ../Source/KSPseudoErrorToken.cxx\
    ../Source/KSReceiver.cxx\
    ../Source/KSXMLReceiver.cxx\
    ../Source/KSPseudoXMLReceiver.cxx\
    ../Source/KSTokenizer.cxx\
    ../Source/KSXMLTokenizer.cxx\
    ../Source/KSPseudoXMLTokenizer.cxx\
    ../Source/KSBuilder.cxx\
    ../Source/KSInitializer.cxx\
    ../Source/KSBuilderFactory.cxx\
    ../Source/KSBuilderFactoryTable.cxx
    
include_HEADERS = \
    $(CONFIGURATION_HEADERFILES)
    
###########################################

noinst_LTLIBRARIES = libKassiopeiaConfiguration.la

libKassiopeiaConfiguration_la_CPPFLAGS = \
    $(AM_CPPFLAGS)\
    $(CONFIGURATION_INCLUDES)

libKassiopeiaConfiguration_la_SOURCES = \
    $(CONFIGURATION_SOURCEFILES)

###########################################

CLEANFILES = 

MAINTAINERCLEANFILES = Makefile.in
