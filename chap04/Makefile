-include ../Makefile

lstat: ## run lstat
	$(call gcc,$(CURRENT_DIR)/lstat.c)
	$(call exec, /etc/passwd /etc /dev/tty /dev/fd)

access: ## run access
	$(call gcc,$(CURRENT_DIR)/access.c)
	$(call exec, /work/Makefile)
	$(call exec, /etc/shadow)

umask: ## run umask
	$(call gcc,$(CURRENT_DIR)/umask.c)
	$(call exec)

chmod: ## run chmod
	$(call gcc,$(CURRENT_DIR)/chmod.c)
	$(call exec)
