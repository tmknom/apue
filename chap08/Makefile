-include ../Makefile

fork: ## run fork
	$(call gcc,$(CURRENT_DIR)/fork.c)
	$(call exec)

wait: ## run wait
	$(call gcc,$(CURRENT_DIR)/wait.c)
	$(call exec)

waitpid: ## run waitpid
	$(call gcc,$(CURRENT_DIR)/waitpid.c)
	$(call exec)

race: ## run race
	$(call gcc,$(CURRENT_DIR)/race.c)
	$(call exec)

echoall: ## run echoall
	$(call gcc,$(CURRENT_DIR)/echoall.c)
	$(call exec)
