dnl Autoconf settings for MazeGame

AC_PREREQ(2.69)
AC_INIT(mini-kernel-64, 0.1)

AC_CANONICAL_HOST

AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

dnl
dnl  Check for tools
dnl

LDFLAGS="-nostdlib"

AX_PROG_NASM
AC_SUBST(NASM, ${nasm})
AC_PROG_CPP
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

dnl  Libtool
#LT_INIT

dnl
dnl  Check for compiler properties
dnl

AC_C_INLINE
AC_C_RESTRICT

dnl
dnl  Arch
dnl

case "${host_cpu}" in
  i?86)
    arch32="1"
    ;;
  amd64|x86_64)
    arch64="1"
    ;;
esac
AM_CONDITIONAL([HAVE_ARCH32], [test "${arch32}" = "1"])
AM_CONDITIONAL([HAVE_ARCH64], [test "${arch64}" = "1"])

dnl
dnl  Compiler flags
dnl

AM_COND_IF([HAVE_ARCH32], [NASMFLAGS="-felf32"], [NASMFLAGS="-felf64"])

AX_APPEND_COMPILE_FLAGS([-Wall -Wextra -Werror -masm=intel], [CFLAGS])
#AX_APPEND_COMPILE_FLAGS([-Wall -Wextra -Werror], [CXXFLAGS])

dnl  C/C++ preprocessor flags
#CPPFLAGS = '-isystem $(top_srcdir)/include ${CPPFLAGS}'

dnl
dnl  Command line args
dnl

AC_ARG_ENABLE([bootloader],
              [AS_HELP_STRING([--enable-bootloader], [The kernel has its own bootloader. (default enabled)])],
              [case "${enableval}" in
                yes)    have_bootloader=true ;;
                no)     have_bootloader=false ;;
                *)      AC_MSG_ERROR([bad value ${enableval} for --enable-bootloader]) ;;
              esac],
              [have_bootloader=true])
AM_CONDITIONAL(HAVE_BOOTLOADER, [test x$have_bootloader = xtrue])

AC_ARG_ENABLE([multiboot],
              [AS_HELP_STRING([--enable-multiboot], [The kernel is compliant to the MultiBoot specification. (default disabled)])],
              [case "${enableval}" in
                yes)    have_multiboot=true ;;
                no)     have_multiboot=false ;;
                *)      AC_MSG_ERROR([bad value ${enableval} for --enable-multiboot]) ;;
              esac],
              [have_multiboot=false])
AM_CONDITIONAL(HAVE_MULTIBOOT, [test x$have_multiboot = xtrue])

AC_ARG_ENABLE([multiboot2],
              [AS_HELP_STRING([--enable-multiboot2], [The kernel is compliant to the MultiBoot2 specification. (default disabled)])],
              [case "${enableval}" in
                yes)    have_multiboot2=true ;;
                no)     have_multiboot2=false ;;
                *)      AC_MSG_ERROR([bad value ${enableval} for --enable-multiboot2]) ;;
              esac],
              [have_multiboot2=false])
AM_CONDITIONAL(HAVE_MULTIBOOT2, [test x$have_multiboot2 = xtrue])

dnl
dnl  Configuration done
dnl

AC_SUBST([ARCH])
AC_SUBST([NASMFLAGS])

AC_CONFIG_FILES([
  Makefile
  kernel/Makefile
  kernel/boot/Makefile
])

dnl  Generate makefiles
AC_OUTPUT
