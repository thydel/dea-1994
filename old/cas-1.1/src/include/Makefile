include $(CASDIR)/make/std-vars

HEADERS = \
	magic.h \
	local.h

top:

install:
	for i in $(HEADERS); do cp $$i $(CASDIR)/include; done

depends:
	true

clean:
	rm -f *~

clobber: clean

# DO NOT DELETE THIS LINE -- make depend depends on it.
