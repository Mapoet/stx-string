#                                               -*- Autoconf -*-
# $Id$
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.60)
AC_INIT(stx-string, 0.6)
AC_CONFIG_SRCDIR(test.cc)
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

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# check whether cppunit is available
AM_PATH_CPPUNIT(1.10.0)

AM_CONDITIONAL(HAVE_CPPUNIT, test x$CPPUNIT_CONFIG != xno)

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
