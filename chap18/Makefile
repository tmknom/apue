-include ../Makefile

tcsetattr: ## run tcsetattr
	$(call gcc,$(CURRENT_DIR)/tcsetattr.c)
	make run

isatty: ## run isatty
	$(call gcc,$(CURRENT_DIR)/isatty.c)
	$(call exec)

ttyname: ## run ttyname
	$(call gcc,$(CURRENT_DIR)/ttyname.c)
	$(call exec)

getpass: ## run getpass
	$(call gcc,$(CURRENT_DIR)/getpass.c)
	$(call exec)

winsize: ## run winsize
	$(call gcc,$(CURRENT_DIR)/winsize.c)
	$(call exec)
