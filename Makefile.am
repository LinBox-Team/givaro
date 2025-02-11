# Copyright(c)'1994-2009 by The Givaro group
# This file is part of Givaro.
# Givaro is governed by the CeCILL-B license under French law
# and abiding by the rules of distribution of free software.
# see the COPYRIGHT file for more details.

ACLOCAL_AMFLAGS = -I macros

SUBDIRS=src macros tests docs examples benchmarks

include_HEADERS=givaro-config.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = givaro.pc

docs:docs/givaro-html/index.html

docs/givaro-html/index.html:
	(cd docs; ${MAKE} docs)

.PHONY:examples benchmarks

examples:
	(cd examples; ${MAKE} examples)

benchmarks:
	(cd benchmarks; ${MAKE} benchmarks)

perfpublisher: benchmarks/perfpublisher tests/perfpublisher

benchmarks/perfpublisher:
	(cd benchmarks; ${MAKE} perfpublisher)

tests/perfpublisher:
	(cd tests; ${MAKE} perfpublisher)

bin_SCRIPTS=givaro-config
pkgdata_DATA = givaro-makefile

EXTRA_DIST=COPYRIGHT Licence_CeCILL-B_V1-en.txt Licence_CeCILL-B_V1-fr.txt \
	   givaro.doxy \
	README.md

DIST_SUBDIRS=${SUBDIRS}

DISTCLEANFILES = src/kernel/system/givaro   \
		 src/kernel/bstruct/givaro  \
		 src/kernel/integer/givaro  \
		 src/kernel/memory/givaro   \
		 src/kernel/rational/givaro \
		 src/kernel/recint/recint   \
		 src/kernel/field/givaro    \
		 src/kernel/ring/givaro     \
		 src/kernel/gmp++/gmp++     \
		 src/library/matrix/givaro  \
		 src/library/poly1/givaro   \
		 src/library/tools/givaro   \
		 src/library/vector/givaro  \
		 givaro-config.h            \
		 docs/DoxyfileDev	    \
		 docs/Doxyfile

uninstall-hook:
	(test -d "$(includedir)/givaro" && rmdir "$(includedir)/givaro") || true
	(test -d "$(includedir)/gmp++" && rmdir "$(includedir)/gmp++") || true
	(test -d "$(includedir)/recint" && rmdir "$(includedir)/recint") || true


docs_dev:docs/givaro-dev-html/index.html

docs/givaro-dev-html/index.html:
	(cd docs; ${MAKE} docs_dev)

git:
	git commit -a; git pull; git push
