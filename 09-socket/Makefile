# Makefile (Raiz)

SUBDIRS = lib/basic lib/network cmd/server

.PHONY: all clean $(SUBDIRS)

all: $(SUBDIRS)

# Regra para entrar em cada diretório e rodar make
$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done