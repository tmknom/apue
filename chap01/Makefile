-include ../Makefile

CURRENT_DIR := $(WORK_PATH)/chap01

ls: ## run ls
	$(call gcc,$(CURRENT_DIR)/ls.c)
	$(call exec,/dev)

io: ## run io
	$(call gcc,$(CURRENT_DIR)/io.c)
	$(call exec)

stdio: ## run stdio
	$(call gcc,$(CURRENT_DIR)/stdio.c)
	$(call exec)

process: ## run process
	$(call gcc,$(CURRENT_DIR)/process.c)
	$(call exec)
