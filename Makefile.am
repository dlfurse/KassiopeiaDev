SUBDIRS = \
    Core/Utility/Build\
    Core/Math/Build\
    Core/Management/Build\
    Core/IO/Build\
    Core/Simulation/Build\
    Core/Geometry/Build\
    Core/Build\
    TransportModules/Build\
    Applications/Validation/Build


EXTRA_DIST = autogen.sh  README  Doc

ACLOCAL_AMFLAGS = -I AutoconfMacros

pkgconfigdir = @libdir@/pkgconfig
nodist_pkgconfig_DATA = Kassiopeia.pc


CLEANFILES = \
    bin/* \
    lib/* \
    include/*
    
CLEANDIRS = \
    bin \
    lib \
    include

MAINTAINERCLEANFILES = \
    Makefile.in \
    aclocal.m4 \
    config.guess \
    config.h.in \
    config.sub \
    configure \
	depcomp \
	install-sh \
	ltmain.sh \
	missing \
	compile \
	*~


