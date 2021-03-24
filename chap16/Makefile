-include ../Makefile

getaddrinfo: ## run getaddrinfo
	$(call gcc,$(CURRENT_DIR)/getaddrinfo.c)
	$(call exec,localhost ruptime)

server1: ## run server1
	docker run --rm -w /work -v $(PROJECT_ROOT):/work debian:gcc gcc -pthread -lrt -Wall -Og -o /work/bin/server1 /work/chap16/server1.c $(LIB_PATH)
	make run
