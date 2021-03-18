-include ../Makefile

lseek: ## run lseek
	$(call gcc,$(CURRENT_DIR)/lseek.c)
	$(call exec)

hole: ## run hole
	$(call gcc,$(CURRENT_DIR)/hole.c)
	$(call exec)

fcntl: ## run fcntl
	$(call gcc,$(CURRENT_DIR)/fcntl.c)
	make run

setfl: ## run setfl
	$(call gcc,$(CURRENT_DIR)/setfl.c)
	make run
