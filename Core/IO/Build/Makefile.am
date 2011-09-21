# $Id$
# Kassiopeia/Core/IO Makefile definition

IO_INCLUDES =  \
    -I@top_srcdir@\
	-I@top_srcdir@/Core/Utility/Include\
	-I@top_srcdir@/Core/Management/Include\
	-I@top_srcdir@/Core/Messages/Include\
    -I@top_srcdir@/Core/IO/Include

IO_HEADERFILES = \
	../Include/KSMessage.h\
	../Include/KSFile.h\
	../Include/KSTextFile.h\
	../Include/KSRootFile.h\
	../Include/KSToken.h\
	../Include/KSTokenBeginParsing.h\
	../Include/KSTokenEndParsing.h\
	../Include/KSTokenBeginFile.h\
	../Include/KSTokenEndFile.h\
	../Include/KSTokenBeginElement.h\
	../Include/KSTokenEndElement.h\
	../Include/KSTokenAttribute.h\
	../Include/KSTokenData.h\
	../Include/KSTokenError.h\
	../Include/KSProcessor.h\
	../Include/KSTokenizer.h\
	../Include/KSVariableProcessor.h\
	../Include/KSLoopProcessor.h\
	../Include/KSIncludeProcessor.h\
	../Include/KSIOToolbox.h\
	../Include/KSIOMessage.h

IO_SOURCEFILES = \
	../Source/KSMessage.cxx\
	../Source/KSFile.cxx\
	../Source/KSTextFile.cxx\
	../Source/KSRootFile.cxx\
	../Source/KSToken.cxx\
	../Source/KSTokenBeginParsing.cxx\
	../Source/KSTokenEndParsing.cxx\
	../Source/KSTokenBeginFile.cxx\
	../Source/KSTokenEndFile.cxx\
	../Source/KSTokenBeginElement.cxx\
	../Source/KSTokenEndElement.cxx\
	../Source/KSTokenAttribute.cxx\
	../Source/KSTokenData.cxx\
	../Source/KSTokenError.cxx\
	../Source/KSProcessor.cxx\
	../Source/KSTokenizer.cxx\
	../Source/KSVariableProcessor.cxx\
	../Source/KSLoopProcessor.cxx\
	../Source/KSIncludeProcessor.cxx\
	../Source/KSIOToolbox.cxx\
	../Source/KSIOMessage.cxx
    
include_HEADERS = \
    $(IO_HEADERFILES)
    
###########################################

noinst_LTLIBRARIES = libKassiopeiaIO.la

libKassiopeiaIO_la_CPPFLAGS = \
    $(AM_CPPFLAGS)\
    $(IO_INCLUDES)

libKassiopeiaIO_la_SOURCES = \
    $(IO_SOURCEFILES)

###########################################

DISTCLEANFILES = ../Include/KSInstallDirectories.h
	
MAINTAINERCLEANFILES = Makefile.in
