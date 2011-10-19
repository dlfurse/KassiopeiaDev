#$Id$
#  File: configure.ac
#  Author: S. Voecking, W. Kaefer, N. Oblath
#
#  Revision History
#  Date       Name          Brief description
#  -----------------------------------------------
#  09/12/09   N. Oblath     First version (based on KGSDUMMY version)
#  04/02/10   N. Oblath     KPAGE, SSC, and KESS added
#  23/02/10   N. Oblath     Loki check added; KTrack, KAFCA, KNAXS, KMath added
#  27/02/10   w. kaefer     commented LT_init(quickfix for compability with autmake 1.10. automake version should be checked and dependend on the outcome either LT_INIT (v.1.11 or later or AC_PROG_libtool for older versions called )
#  23/03/10   N. Oblath     KEMField added; modified install directories; Bumped version to 0.1.0
#  25/03/10   N. Oblath     Added KSCore Makefiles
#  26/03/10   wkaefer       set datadir and sysconfdir
#  09/06/10   wkaefer	    added cool features
#  11/18/10   N. Oblath     Added OpenMP, MPI, and Gmsh support


#autoconf version check and initialization
AC_PREREQ([2.50])
AC_INIT([Kassiopeia], [2.00.00], [https://savannah.fzk.de/projects/katrin/])

#automake version check and initialization
AM_INIT_AUTOMAKE([foreign 1.10 tar-ustar])
AC_CONFIG_MACRO_DIR([AutoconfMacros])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])], [AC_MSG_WARN([  "macro SILENT_RULES not found: upgrade autoconf to enjoy a less verbose build output!"])  ])

#libtool version check and initialization
LT_PREREQ(2.2)
AC_PROG_LIBTOOL

#shell tools and language settings
AC_LANG(C++)
AC_PROG_CXX
AC_PROG_SED
AC_PROG_LN_S
AC_CANONICAL_HOST
AM_PROG_CC_C_O

#check for root and required features
ROOT_CHECK([5.24])

#check for boost
AX_BOOST_BASE([1.34])
AX_BOOST_PROGRAM_OPTIONS

#check for gsl and its dependencies
AC_CHECK_LIB([m],[cos])
AX_PATH_GSL(1.0,[],[AC_MSG_ERROR(could not find required version of GSL)])
AC_CHECK_LIB([gslcblas],[cblas_dgemm])

#disable printing to the terminal
AC_ARG_ENABLE(
    [silent],
    [AS_HELP_STRING([--enable-silent],[turns off printing to the terminal; log file printing can still be used.])]
)
AS_IF(
    [test "x$enable_silent" = "xyes"],
    [DEBUG_FLAGS="$DEBUG_FLAGS -DSILENT_MODE"]
)

#enable full debug printing
AC_ARG_ENABLE(
    [debug],
    [AS_HELP_STRING([--enable-debug],[enables verbose debugging output; the modules for which debug messages are printed are controlled in the UserConfiguration])]
)
AS_IF(
    [test "x$enable_debug" = "xyes"],
    [DEBUG_FLAGS="$DEBUG_FLAGS -DDEBUG_VERBOSE"]
)

#set default prefix to build area
AC_PREFIX_DEFAULT([`pwd`])

#trick autotools into doing something sane and useful
PREFIX=`test "$prefix" = NONE && prefix=$ac_default_prefix; eval echo "${prefix}"`
AC_SUBST(PREFIX)

#define default directories
ksconfigdir=${PREFIX}/Config
AC_SUBST(ksconfigdir)

#define compiler and linker flags for automake
AM_CPPFLAGS="$DEFS -g $DEBUG_FLAGS $ROOT_CPPFLAGS $BOOST_CPPFLAGS -DKASSIOPEIA_CONFIG_DEFAULT_DIR=${PREFIX}/Config -DKASSIOPEIA_DATA_DEFAULT_DIR=${PREFIX}/Data -DKASSIOPEIA_SCRATCH_DEFAULT_DIR=${PREFIX}/Data -DKASSIOPEIA_OUTPUT_DEFAULT_DIR=. -DKASSIOPEIA_LOG_DEFAULT_DIR=." 
AM_CXXFLAGS="-W -Wall $ROOT_CXXFLAGS"
AM_LDFLAGS="-fPIC $ROOT_LDFLAGS"

AS_IF(
    [test "x$USE_MPI" = "xtrue"],
    [AM_CPPFLAGS="$AM_CPPFLAGS $MPI_CPPFLAGS"
     AM_CXXFLAGS="$AM_CXXFLAGS $MPI_CXXFLAGS"
     CC="$MPICC"
     CXX="$MPICXX"
     LIBS="$MPILIBS $LIBS"]
)

#allow the use of USE_MPI in conditional statements in Makefile.am's
AM_CONDITIONAL([USE_MPI], [test "x$USE_MPI" = "xtrue"])

AC_SUBST(AM_CPPFLAGS)
AC_SUBST(AM_CXXFLAGS)
AC_SUBST(AM_LDFLAGS)

AC_CONFIG_FILES([Makefile]
		[Kassiopeia.pc]
		[Core/Build/Makefile]
        [Core/Utility/Build/Makefile]
        [Core/Math/Build/Makefile]
        [Core/Management/Build/Makefile]
		[Core/IO/Build/Makefile]
		[Core/Simulation/Build/Makefile]
		[Core/Geometry/Build/Makefile]
		[TransportModules/Build/Makefile]
		[Applications/Validation/Build/Makefile]
		)

AC_OUTPUT
