NULL =
CLEANFILES =
EXTRA_DIST =
ACLOCAL_AMFLAGS = -I m4
SUBDIRS = include data libmsi tests po .

makeflags_ = $(makeflags_$(AM_DEFAULT_VERBOSITY))
makeflags_0 = --no-print-directory -s
makeflags_1 =
AM_MAKEFLAGS = $(makeflags_$(V))

libmsiincludedir = $(includedir)/libmsi-1.0
dist_libmsiinclude_HEADERS =			\
	include/libmsi-database.h		\
	include/libmsi-enums.h			\
	include/libmsi-query.h			\
	include/libmsi-record.h			\
	include/libmsi-summary-info.h		\
	include/libmsi-types.h			\
	include/libmsi.h			\
	$(NULL)

AM_CFLAGS = $(WARN_CFLAGS)
AM_CPPFLAGS =						\
	-Iinclude -I$(srcdir)/include			\
	$(GLIB_CFLAGS) $(GSF_CFLAGS) $(UUID_CFLAGS)	\
	$(NULL)

AM_LDFLAGS = -Llibmsi -lgio-2.0 -lglib-2.0 -lgobject-2.0

# Low-level tools
bin_SCRIPTS = tools/msidump tools/msidiff
CLEANFILES += $(bin_SCRIPTS)

bin_PROGRAMS = msibuild msiinfo

msibuild_SOURCES = tools/msibuild.c tools/sqldelim.c tools/sqldelim.h
msibuild_LDADD = -lmsi $(GLIB_LIBS) $(GSF_LIBS) $(UUID_LIBS) -lgio-2.0 -lglib-2.0 -lgobject-2.0
msibuild_DEPENDENCIES = libmsi/libmsi.la

msiinfo_SOURCES = tools/msiinfo.c
msiinfo_LDADD = -lmsi $(GLIB_LIBS) $(GSF_LIBS) -lgio-2.0 -lglib-2.0 -lgobject-2.0
msiinfo_DEPENDENCIES = libmsi/libmsi.la

# msiextract

bin_PROGRAMS += msiextract

msiextract_CFLAGS = -w

# --vapidir paths are relative to the source directory!

msiextract_VALAFLAGS =				\
	--enable-experimental			\
	--pkg config				\
	--pkg gio-unix-2.0			\
	--pkg libgcab-1.0			\
	--pkg libmsi-1.0			\
	--pkg posix				\
	--vapidir=.				\
	--vapidir=$(abs_top_builddir)/libmsi	\
	$(NULL)

msiextract_SOURCES =				\
	tools/msiextract.vala			\
	$(NULL)

msiextract_CPPFLAGS = $(wixl_CPPFLAGS)
msiextract_LDADD = $(wixl_LDADD) -lgio-2.0 -lglib-2.0 -lgobject-2.0

# Wixl

noinst_LIBRARIES = libcommon.a
libcommon_a_SOURCES =				\
	tools/wixl/util.vala			\
	$(NULL)
libcommon_a_VALAFLAGS =				\
	--enable-experimental			\
	--pkg gio-2.0				\
	--pkg posix				\
	-H libcommon.h --library common		\
	$(NULL)
libcommon_a_CFLAGS = -w

common.vapi libcommon.h: libcommon.a

BUILT_SOURCES = common.vapi libcommon.h

bin_PROGRAMS += wixl

wixl_CFLAGS = -w

wixl_VALAFLAGS =				\
	-H wixl.h --use-header			\
	--vapidir=.				\
	--vapidir=vapi				\
	--vapidir=$(abs_top_builddir)/libmsi	\
	--pkg config				\
	--enable-experimental			\
	--pkg gio-2.0				\
	--pkg libmsi-1.0			\
	--pkg libgcab-1.0			\
	--pkg libxml-2.0			\
	--pkg posix				\
	--pkg common				\
	$(NULL)

wixl_SOURCES =					\
	tools/wixl/builder.vala			\
	tools/wixl/msi-default.vala		\
	tools/wixl/msi.vala			\
	tools/wixl/preprocessor.vala		\
	tools/wixl/wix.vala			\
	tools/wixl/wixl.vala			\
	$(NULL)

wixl_CPPFLAGS =					\
	-include config.h			\
	-Iinclude				\
	-I$(srcdir)/include			\
	$(WIXL_CFLAGS)				\
	-DG_LOG_DOMAIN=\""wixl"\"		\
	-DLOCALEDIR=\""$(localedir)"\"		\
	-DPKGDATADIR=\""$(datadir)/wixl-$(VERSION)/"\"	\
	-DPKGLIBDIR=\""$(pkglibdir)"\"		\
	$(NULL)

wixl_LDADD =					\
	libcommon.a				\
	libmsi/libmsi.la			\
	$(WIXL_LIBS)				\
	$(NULL)

# FIXME -j: automake valagen doesn't seem to wait deps:
wixl_DEPENDENCIES = libmsi/libmsi.la common.vapi

# FIXME: workaround for a vala bug 
BUILT_SOURCES += wixl.h

# Wixl-heat

bin_PROGRAMS += wixl-heat

wixl_heat_CFLAGS = -w

wixl_heat_VALAFLAGS =				\
	--vapidir=.				\
	--pkg config				\
	--pkg gio-2.0				\
	--pkg posix				\
	--pkg common				\
	--enable-experimental			\
	$(NULL)

wixl_heat_SOURCES =				\
	tools/wixl/wixl-heat.vala		\
	$(NULL)

wixl_heat_CPPFLAGS = $(wixl_CPPFLAGS)
wixl_heat_LDADD = $(wixl_LDADD) -lgio-2.0 -lglib-2.0 -lgobject-2.0

# bash completion

completiondir = $(datadir)/bash-completion/completions
completion_DATA = completion/msitools
EXTRA_DIST += $(completion_DATA)

# Autotest support

dist_noinst_DATA = tests/testsuite.at tests/wixl.at tests/package.m4 tests/testsuite
DISTCLEANFILES = atconfig atlocal
CLEANFILES += testsuite.log

check-local: $(srcdir)/tests/testsuite atconfig atlocal
	$(SHELL) $(srcdir)/tests/testsuite AUTOTEST_PATH=. $(TESTSUITEFLAGS)

installcheck-local: $(srcdir)/tests/testsuite atconfig atlocal
	$(SHELL) $(srcdir)/tests/testsuite AUTOTEST_PATH=$(bindir) $(TESTSUITEFLAGS)

clean-local:
	-$(SHELL) $(srcdir)/tests/testsuite --clean

dist-hook:
	@for file in `cd $(srcdir)/tests &&					    \
		$(AUTOM4TE) --language=autotest --trace='AT_MSIDATA:tests/data/$$1' \
			    testsuite.at`; do					    \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`;			    \
	    $(MKDIR_P) "$(distdir)$$dir" || exit 1;				    \
	    echo cp -fpR $(srcdir)/$$file "$(distdir)$$dir";			    \
	    cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1;		    \
	done
	@echo $(VERSION) > $(distdir)/.tarball-version


$(srcdir)/tests/testsuite: tests/testsuite.at tests/wixl.at tests/package.m4
	$(AM_V_GEN)cd $(srcdir)/tests &&					 \
		$(AUTOM4TE) --language=autotest -o testsuite.tmp testsuite.at && \
		mv testsuite.tmp testsuite

MAINTAINERCLEANFILES =				\
	$(srcdir)/tests/testsuite		\
	$(srcdir)/tests/package.m4		\
	$(NULL)

EXTRA_DIST +=					\
	$(top_srcdir)/.version			\
	NEWS					\
	autogen.sh				\
	build-aux/git-version-gen		\
	build-aux/move-if-change		\
	msitools.doap				\
	$(NULL)

BUILT_SOURCES += $(top_srcdir)/.version
$(top_srcdir)/.version:
	@echo $(VERSION) > $@-t && mv $@-t $@

MAINTAINERCLEANFILES +=					\
	$(GITIGNORE_MAINTAINERCLEANFILES_TOPLEVEL)	\
	$(GITIGNORE_MAINTAINERCLEANFILES_MAKEFILE_IN)	\
	$(GITIGNORE_MAINTAINERCLEANFILES_M4_LIBTOOL)	\
	m4/intltool.m4					\
	$(NULL)

-include $(top_srcdir)/git.mk
