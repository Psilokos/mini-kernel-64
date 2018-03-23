include packages.mak

ifneq ($(shell curl -V >/dev/null 2>&1 || echo fail),fail)
DOWNLOAD_PKG = curl -f "$(1)"
else ifneq ($(shell wget -V >/dev/null 2>&1 || echo fail),fail)
DOWNLOAD_PKG = wget "$(1)"
else
DOWNLOAD_PKG = $(error need curl or wget)
endif

RM = rm -rf
EXTRACT = $(RM) $@ \
	  $(foreach tarball, $(filter %.tar.xz,$^), && tar -xJf $(tarball) -C $@)

#
# GNU binutils
#

$(BINUTILS_TARBALL):
	$(call DOWNLOAD_PKG,$(BINUTILS_URL))

binutils: $(BINUTILS_TARBALL)
	$(EXTRACT)

.build-binutils: binutils
	cd $< && \
	    ./configure --prefix="$(PREFIX)" --target=$(TARGET) --with-sysroot --disable-nls --disable-werror && \
	    make && \
	    make install
	touch $@

#
# GNU gcc
#

$(GCC_TARBALL):
	$(call DOWNLOAD_PKG,$(GCC_VERSION))

gcc: $(GCC_TARBALL)
	$(EXTRACT)

.build-gcc: .build-binutils gcc
	cd $< && \
	    ./configure --prefix="$(PREFIX)" --target=$(TARGET) --disable-nls --enable-languages=c,c++ --without-headers && \
	    make all-gcc && \
	    make all-target-libgcc && \
	    make install all-gcc && \
	    make install all-target-libgcc
	touch $@
