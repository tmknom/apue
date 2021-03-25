-include ../Makefile

poll: ## run poll
	docker run --rm -w /work -v $(PROJECT_ROOT):/work debian:gcc gcc -pthread -lrt -Wall -Og -o /work/bin/poll /work/chap17/poll.c $(LIB_PATH)
	make run

msgsnd: ## run msgsnd
	$(call gcc,$(CURRENT_DIR)/msgsnd.c)
	make run
