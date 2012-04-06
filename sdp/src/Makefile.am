## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(datadir)/sdp/ui
ui_DATA = sdp.ui \
	story.ui \
	status.ui \
	title.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(SDP_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = sdp

sdp_SOURCES = \
	main.c \
	sdp.h \
	sdp.c \
	crappy_soil.jpg	

sdp_LDFLAGS = \
	-Wl,--export-dynamic

sdp_LDADD = $(SDP_LIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/sdp

