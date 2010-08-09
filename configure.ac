# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([libcineon], 0.1)
AM_INIT_AUTOMAKE

AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

# libtool
AM_DISABLE_SHARED
AM_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB(tiff,_TIFFmalloc,have_libtiff='yes',have_libtiff='no')
AM_CONDITIONAL(HAVE_LIBTIFF, test "$have_libtiff" != "no")

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(ctime)

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_STRUCT_TM

# Checks for library functions.
AC_HEADER_STDC
AC_FUNC_STRFTIME
AC_CHECK_FUNCS([memset])

AC_OUTPUT([
Makefile
libcineon/Makefile
tools/Makefile
tools/cineonheader/Makefile
tools/cineon2tiff/Makefile
])


AC_MSG_RESULT([libcineon: build libtiff apps... "$have_libtiff"])


