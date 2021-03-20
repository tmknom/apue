-include ../Makefile

atexit: ## run atexit
	$(call gcc,$(CURRENT_DIR)/atexit.c)
	$(call exec)

echo: ## run echo
	$(call gcc,$(CURRENT_DIR)/echo.c)
	$(call exec, foo bar baz)

setjmp: ## run setjmp
	$(call gcc,$(CURRENT_DIR)/setjmp.c)
	$(call exec)
