# $Id$
# Kassiopeia/Core/IO Makefile definition

IO_INCLUDES =  \
    -I@top_srcdir@\
	-I@top_srcdir@/Core/Utility/Include\
	-I@top_srcdir@/Core/Messages/Include\
    -I@top_srcdir@/Core/IO/Include

IO_HEADERFILES = \
	../Include/KSFile.h\
	../Include/KSTextFile.h\
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
	../Include/KSTokenizer.h

IO_SOURCEFILES = \
	../Source/KSFile.cxx\
	../Source/KSTextFile.cxx\
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
	../Source/KSTokenizer.cxx
    
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

CLEANFILES = 

MAINTAINERCLEANFILES = Makefile.in
