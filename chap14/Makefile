-include ../Makefile

nonblock: ## run nonblock
	$(call gcc,$(CURRENT_DIR)/nonblock.c)
	make run

aio: ## run aio
	$(call gcc,$(CURRENT_DIR)/aio.c)
	$(call exec,/work/chap14/aio.c /work/chap14/txt.o)

mmap: ## run mmap
	$(call gcc,$(CURRENT_DIR)/mmap.c)
	$(call exec,/work/chap14/mmap.c /work/chap14/txt.o)
