dnl -*- mode: autoconf -*- 
dnl
dnl $Id$
dnl Author: N. Oblath
dnl
dnl Autoconf macro to check for existence of the Gmsh libraries and includes
dnl Synopsis:
dnl
dnl  GMSH_CHECK([])
dnl
dnl The macro defines the following substitution variables
dnl
dnl    GMSH_CPPFLAGS
dnl    GMSH_CXXFLAGS
dnl    GMSH_LDFLAGS


AC_DEFUN([GMSH_CHECK], [
    AC_ARG_WITH(
        [gmsh-inc-dir], 
        [AS_HELP_STRING([--with-gmsh-inc-dir=DIR],[Location of Gmsh headers (/usr/local/include])],    
        [user_gmshinc=$withval],
        [user_gmshinc="/usr/local/include"]
    )
    AC_ARG_WITH(
        [gmsh-lib-dir], 
        [AS_HELP_STRING([--with-gmsh-lib-dir=DIR],[Location of the Gmsh library (/usr/local/lib)])],
        [user_gmshlib=$withval],
        [user_gmshlib="/usr/local/lib"]
    )
    
    AC_CHECK_FILE(
    	[$user_gmshinc/gmsh/Gmsh.h],
    	[],
    	[AC_MSG_ERROR([Could not find \"Gmsh.h\" in $user_gmshinc. Provide PATH in PATH/gmsh/Gmsh.h with --with-gmsh-inc-dir=PATH])]
    )
   	
   	GMSH_CPPFLAGS="-DUSE_GMSH"
   	GMSH_CXXFLAGS="-I$user_gmshinc"
   	
    AC_CHECK_FILE(
    	[$user_gmshlib/libGmsh.a],
    	[],
    	[AC_MSG_ERROR([Could not find \"libGmsh\" in $user_gmshlib. Provide the path to this file with the option --with-gmsh-lib-dir=PATH])]
    )
   	
   	GMSH_LDFLAGS="-L$user_gmshlib -lGmsh -lblas -llapack"

    AC_SUBST(GMSH_CPPFLAGS)
    AC_SUBST(GMSH_CXXFLAGS)
    AC_SUBST(GMSH_LDFLAGS)
])
