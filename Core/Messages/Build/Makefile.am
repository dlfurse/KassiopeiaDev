# $Id$
# Kassiopeia/Core/Messaging/Build Makefile definition

MESSAGES_INCLUDES =  \
    -I@top_srcdir@\
	-I@top_srcdir@/Core/Utility/Include\
	-I@top_srcdir@/Core/Messages/Include

MESSAGES_HEADERFILES = \
    ../Include/KLMessage.h\
    ../Include/KLMessageBase.h\
    ../Include/KLMessageInitializer.h\
    ../Include/KLMessageManager.h\
    ../Include/KSMessage.h\
    ../Include/KSMessageHandler.h\
    ../Include/KSLog.h

MESSAGES_SOURCEFILES = \
    ../Source/KLMessage.cxx\
    ../Source/KLMessageBase.cxx\
    ../Source/KLMessageManager.cxx\
    ../Source/KSMessage.cxx\
    ../Source/KSMessageHandler.cxx\
    ../Source/KSLog.cxx

###########################################

noinst_LTLIBRARIES = libKassiopeiaMessages.la
    
include_HEADERS = \
    $(MESSAGES_HEADERFILES)

libKassiopeiaMessages_la_CPPFLAGS = \
    $(MESSAGES_INCLUDES)\
    $(AM_CPPFLAGS)

libKassiopeiaMessages_la_SOURCES = \
    $(MESSAGES_SOURCEFILES)

###########################################

CLEANFILES = \
   ../Source/*~\
   ../Include/*~

MAINTAINERCLEANFILES = Makefile.in
