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
	docker run --rm -w /work -v $(PROJECT_ROOT):/work debian:gcc gcc -Wall -Og -o $(WORK_PATH)/bin/echoall $(CURRENT_DIR)/echoall.c $(LIB_PATH)
	docker run -it --rm -w /work -v $(PROJECT_ROOT):/work debian:gcc $(WORK_PATH)/bin/echoall

exec: echoall ## run exec
	$(call gcc,$(CURRENT_DIR)/exec.c)
	$(call exec)

system: ## run system
	$(call gcc,$(CURRENT_DIR)/system.c)
	$(call exec,$(WORK_PATH)/bin/uid)

uid: ## run uid
	docker run --rm -w /work -v $(PROJECT_ROOT):/work debian:gcc gcc -Wall -Og -o $(WORK_PATH)/bin/uid $(CURRENT_DIR)/uid.c $(LIB_PATH)
	docker run -it --rm -w /work -v $(PROJECT_ROOT):/work debian:gcc $(WORK_PATH)/bin/uid
