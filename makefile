SUBDIRS=partitions

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):; $(MAKE) -C $@

clean:; for dir in $(SUBDIRS); do \
          $(MAKE) -C $$dir clean; \
        done

