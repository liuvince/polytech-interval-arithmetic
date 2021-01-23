all clean:
	(cd lib; $(MAKE) $@)
	(cd src; $(MAKE) $@)

.PHONY: all clean
