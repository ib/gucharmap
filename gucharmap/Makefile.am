## Copyright © 2003  Noah Levitt
## Copyright © 2008  Christian Persch
##
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by the
## Free Software Foundation; either version 2 of the License, or (at your
## option) any later version.
##
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program; if not, write to the Free Software Foundation, Inc.,
## 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335 USA
##

NULL =

lib_LTLIBRARIES = libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@.la

BUILT_SOURCES = \
	gucharmap-marshal.c \
	gucharmap-marshal.h \
	gucharmap-type-builtins.c \
	gucharmap-type-builtins.h \
	$(NULL)

libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@_la_SOURCES = \
	gucharmap-block-chapters-model.c \
	gucharmap-block-chapters-model.h \
	gucharmap-block-codepoint-list.c \
	gucharmap-block-codepoint-list.h \
	gucharmap-chapters-model.c \
	gucharmap-chapters-model.h \
	gucharmap-chapters-view.c \
	gucharmap-chapters-view.h \
	gucharmap-charmap.c \
	gucharmap-charmap.h \
	gucharmap-chartable-accessible.c \
	gucharmap-chartable-accessible.h \
	gucharmap-chartable-cell-accessible.c \
	gucharmap-chartable-cell-accessible.h \
	gucharmap-chartable.c \
	gucharmap-chartable.h \
	gucharmap-codepoint-list.c \
	gucharmap-codepoint-list.h \
	gucharmap-init.c \
	gucharmap-macros.h \
	gucharmap-private.h \
	gucharmap-script-chapters-model.c \
	gucharmap-script-chapters-model.h \
	gucharmap-script-codepoint-list.c \
	gucharmap-script-codepoint-list.h \
	gucharmap-unicode-info.c \
	gucharmap-unicode-info.h \
	unicode-blocks.h \
	unicode-categories.h \
	unicode-names.h \
	unicode-nameslist.h \
	unicode-scripts.h \
	unicode-unihan.h \
	unicode-versions.h \
	$(NULL)

nodist_libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@_la_SOURCES = $(BUILT_SOURCES)

libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@_la_CPPFLAGS = \
	-I$(top_srcdir) \
	-DGUCHARMAP_COMPILATION \
	-DDATADIR=\"$(datadir)\" \
	-DLOCALEDIR=\"$(localedir)\" \
	-DHELPDIR=\"$(HELP_DIR)\" \
	-DGLIB_DISABLE_DEPRECATION_WARNINGS \
	-DPANGO_DISABLE_DEPRECATION_WARNINGS \
	-DATK_DISABLE_DEPRECATION_WARNINGS \
	-DGDK_DISABLE_DEPRECATION_WARNINGS \
	-DGDK_PIXBUF_DISABLE_DEPRECATION_WARNINGS \
	-DGTK_DISABLE_DEPRECATION_WARNINGS \
	$(DISABLE_DEPRECATED) \
	$(AM_CPPFLAGS)

libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@_la_CFLAGS = \
	$(GTK_CFLAGS)	\
	$(WARN_CFLAGS)	\
	$(AM_CFLAGS)

libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@_la_LDFLAGS = \
	-version-info $(LIBGUCHARMAP_LT_VERSION)	\
	-export-symbols-regex "^gucharmap_*"		\
	$(AM_LDFLAGS)

libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@_la_LIBADD = \
	$(GTK_LIBS)	\
	$(INTLLIBS)

libgucharmapincludedir = $(includedir)/gucharmap-$(GUCHARMAP_API_VERSION)/gucharmap
libgucharmapinclude_HEADERS = \
	gucharmap-block-chapters-model.h \
	gucharmap-block-codepoint-list.h \
	gucharmap-chapters-model.h \
	gucharmap-chapters-view.h \
	gucharmap-charmap.h \
	gucharmap-chartable.h \
	gucharmap-codepoint-list.h \
	gucharmap.h \
	gucharmap-macros.h \
	gucharmap-script-chapters-model.h \
	gucharmap-script-codepoint-list.h \
	gucharmap-unicode-info.h \
	gucharmap-version.h \
	$(NULL)

nodist_libgucharmapinclude_HEADERS = \
	gucharmap-type-builtins.h \
	$(NULL)

if ENABLE_CHARMAP
bin_PROGRAMS = gucharmap
else
noinst_PROGRAMS = gucharmap
endif

gucharmap_SOURCES = \
	gucharmap-mini-fontsel.c \
	gucharmap-mini-fontsel.h \
	gucharmap-print-operation.c \
	gucharmap-print-operation.h \
	gucharmap-search-dialog.c \
	gucharmap-search-dialog.h \
	gucharmap-settings.c \
	gucharmap-settings.h \
	gucharmap-window.c \
 	gucharmap-window.h \
	main.c \
	$(NULL)

gucharmap_CPPFLAGS = \
	-I$(top_srcdir) \
	-DDATADIR=\"$(datadir)\" \
	-DLOCALEDIR=\"$(localedir)\" \
	-DHELPDIR=\"$(HELP_DIR)\" \
	-DGLIB_DISABLE_DEPRECATION_WARNINGS \
	-DPANGO_DISABLE_DEPRECATION_WARNINGS \
	-DATK_DISABLE_DEPRECATION_WARNINGS \
	-DGDK_DISABLE_DEPRECATION_WARNINGS \
	-DGDK_PIXBUF_DISABLE_DEPRECATION_WARNINGS \
	-DGTK_DISABLE_DEPRECATION_WARNINGS \
	$(DISABLE_DEPRECATED) \
	$(AM_CPPFLAGS)

gucharmap_CFLAGS = \
	$(GTK_CFLAGS)	\
	$(GCONF_CFLAGS)	\
	$(WARN_CFLAGS)	\
	$(AM_CFLAGS)

gucharmap_LDFLAGS = \
	$(AM_LDFLAGS)

gucharmap_LDADD = \
	libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@.la	\
	$(GTK_LIBS)	\
	$(LIBDL) \
	$(GCONF_LIBS)	\
	$(INTL_LIBS)

if OS_WIN32
gucharmap_LDADD += gucharmaprc.o
gucharmaprc.o: gucharmaprc.rc
	$(AM_V_GEN) windres -i $< -o $@
endif

gucharmap-marshal.h: $(srcdir)/gucharmap-marshal.list
	$(AM_V_GEN) ( $(GLIB_GENMARSHAL) --prefix=_gucharmap_marshal $(srcdir)/gucharmap-marshal.list \
                            --header \
                            --internal > gucharmap-marshal.h.tmp \
	  && mv gucharmap-marshal.h.tmp gucharmap-marshal.h ) \
        || ( rm -f gucharmap-marshal.h.tmp && exit 1 )

gucharmap-marshal.c: $(srcdir)/gucharmap-marshal.list
	$(AM_V_GEN) ( $(GLIB_GENMARSHAL) --prefix=_gucharmap_marshal $(srcdir)/gucharmap-marshal.list \
			    --prototypes \
                            --body \
                            --internal > gucharmap-marshal.c.tmp \
          && mv gucharmap-marshal.c.tmp gucharmap-marshal.c ) \
        || ( rm -f gucharmap-marshal.c.tmp && exit 1 )


gucharmap-type-builtins.h: stamp-gucharmap-type-builtins.h
	@true

stamp-gucharmap-type-builtins.h: gucharmap-type-builtins.h.template $(libgucharmapinclude_HEADERS)
	$(AM_V_GEN) $(GLIB_MKENUMS) --template $< $(filter-out $<,$^) > xgen-gtbh \
	&& (cmp -s xgen-gtbh gucharmap-type-builtins.h || cp xgen-gtbh gucharmap-type-builtins.h ) \
	&& rm -f xgen-gtbh \
	&& echo timestamp > $(@F)

gucharmap-type-builtins.c: gucharmap-type-builtins.c.template $(libgucharmapinclude_HEADERS)
	$(AM_V_GEN) $(GLIB_MKENUMS) --template $< $(filter-out $<,$^) > xgen-gtbc \
	&& (cmp -s xgen-gtbc gucharmap-type-builtins.c || cp xgen-gtbc gucharmap-type-builtins.c ) \
	&& rm -f xgen-gtbc

# printoptions.h: print.glade
# 	$(AM_V_GEN) $(GTK_BUILDER_CONVERT) --root custom_tab_container $< - | \
# 		$(XMLLINT) --noblanks - | \
# 		$(HEXDUMP) -v -e '"" 1/1 "0x%02x,""\n"' > xgen-$(@F) \
# 	&& (cmp -s xgen-$(@F) $@ || cp -f xgen-$(@F) $@) \
# 	&& rm -f xgen-$(@F)

EXTRA_DIST = \
	gucharmap-marshal.list \
	gucharmap-type-builtins.c.template \
	gucharmap-type-builtins.h.template \
	gucharmaprc.rc \
	$(NULL)

CLEANFILES = \
	stamp-gucharmap-type-builtins.h \
	$(BUILT_SOURCES) \
	$(NULL)

# introspection

if HAVE_INTROSPECTION
-include $(INTROSPECTION_MAKEFILE)

INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

Gucharmap-@GUCHARMAP_API_VERSION@.gir: libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@.la
Gucharmap_@GUCHARMAP_API_VERSION_U@_gir_INCLUDES = Pango-1.0 Gdk-$(GTK_API_VERSION) Gtk-$(GTK_API_VERSION)
Gucharmap_@GUCHARMAP_API_VERSION_U@_gir_SCANNERFLAGS = --c-include "gucharmap/gucharmap.h"
Gucharmap_@GUCHARMAP_API_VERSION_U@_gir_EXPORT_PACKAGES = gucharmap-$(GUCHARMAP_API_PC_VERSION)
Gucharmap_@GUCHARMAP_API_VERSION_U@_gir_CFLAGS = $(GTK_CFLAGS) -DGUCHARMAP_COMPILATION -I$(top_srcdir)
Gucharmap_@GUCHARMAP_API_VERSION_U@_gir_LIBS = libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@.la
Gucharmap_@GUCHARMAP_API_VERSION_U@_gir_FILES = $(filter-out unicode-%.h,$(libgucharmap@GUCHARMAP_LIBRARY_SUFFIX_U@_la_SOURCES))

INTROSPECTION_GIRS = Gucharmap-$(GUCHARMAP_API_VERSION).gir

girdir = $(INTROSPECTION_GIRDIR)
nodist_gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(INTROSPECTION_TYPELIBDIR)
nodist_typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(nodist_gir_DATA) $(nodist_typelib_DATA)
endif

if ENABLE_CHARMAP

# don't do the symlink stuff if this is windows
if !OS_WIN32
# install a symlink to the binary called "charmap"
install-exec-hook:
	test -e "$(DESTDIR)$(bindir)/charmap" \
        || (cd "$(DESTDIR)$(bindir)" && $(LN_S) gucharmap charmap) ; \
	test -e "$(DESTDIR)$(bindir)/gnome-character-map" \
        || (cd "$(DESTDIR)$(bindir)" && $(LN_S) gucharmap gnome-character-map)

# remove bin/charmap if it's a symlink (it's a pain to test what it's
# a symlink to)
uninstall-local:
	test -h "$(DESTDIR)$(bindir)/charmap" \
	&& rm -f "$(DESTDIR)$(bindir)/charmap" ; \
	test -h "$(DESTDIR)$(bindir)/gnome-character-map" \
	&& rm -f "$(DESTDIR)$(bindir)/gnome-character-map"

endif # !OS_WIN32

endif # ENABLE_CHARMAP

-include $(top_srcdir)/git.mk
