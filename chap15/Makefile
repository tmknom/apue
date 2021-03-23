-include ../Makefile

pipe: ## run pipe
	$(call gcc,$(CURRENT_DIR)/pipe.c)
	make run

pager: ## run pager
	$(call gcc,$(CURRENT_DIR)/pager.c)
	make run

popen: ## run popen
	$(call gcc,$(CURRENT_DIR)/popen.c)
	make run

myuclc: ## run myuclc
	docker run --rm -w /work -v $(PROJECT_ROOT):/work debian:gcc gcc -pthread -lrt -Wall -Og -o /work/bin/myuclc /work/chap15/myuclc.c $(LIB_PATH)
	make run

prompt: ## run prompt
	$(call gcc,$(CURRENT_DIR)/prompt.c)
	make run
