
LIBCINEON = $(top_builddir)/libcineon/libcineon.a

INCLUDES = -I$(top_builddir)/libcineon

bin_PROGRAMS = cineon2tiff

cineon2tiff_SOURCES = cineon2tiff.cpp
cineon2tiff_LDADD = $(LIBCINEON) -ltiff

