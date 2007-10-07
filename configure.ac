# $Id$ -*- Autoconf -*-

AC_PREREQ(2.60)
AC_INIT(stx-string, 0.6)
AC_CONFIG_SRCDIR(include/stx-string.h)
AC_CONFIG_AUX_DIR(acscripts)

AM_INIT_AUTOMAKE(foreign)
# AM_MAINTAINER_MODE

if test "$CFLAGS" == ""; then
    CFLAGS="-g"
fi
if test "$CXXFLAGS" == ""; then
    CXXFLAGS="-g"
fi

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

AC_LANG([C++])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_HEADER_STDC
AC_CHECK_FUNCS([memset])

# Check whether to enable gcov coverage flags and macros

AC_ARG_ENABLE(gcov,
    AS_HELP_STRING([--enable-gcov],
                   [enable test coverage with gcov @<:@default=no@:>@]),
	[case "${enableval}" in
         yes) gcov=true ;;
         no)  gcov=false ;;
         *)   AC_MSG_ERROR([bad value ${enableval} for --enable-gcov]) ;;
         esac],
        [gcov=false])

AM_CONDITIONAL(GCOV, test x"$gcov" = "xtrue")

if test x"$gcov" = "xtrue"; then
    CFLAGS="$CFLAGS -fprofile-arcs -ftest-coverage"
    CXXFLAGS="$CXXFLAGS -fprofile-arcs -ftest-coverage"
fi

# check if zlib is available

AC_CHECK_LIB([z], [deflate],
	     [],
	     [AC_MSG_ERROR([*** zlib library not found!
Install zlib development package using your distribution's package manager.])]
            )

AC_CHECK_HEADER([zlib.h],
		[],
		[AC_MSG_ERROR([*** zlib.h include file not found!
Install zlib development package using your distribution's package manager.])])

# check if cppunit is available
AM_PATH_CPPUNIT(1.10.0)

AM_CONDITIONAL(HAVE_CPPUNIT, test x$CPPUNIT_CONFIG != xno)

# Checks for library functions.

AC_CONFIG_FILES([Makefile
		 testsuite/Makefile])
AC_OUTPUT
