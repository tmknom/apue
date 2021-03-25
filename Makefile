SHELL=/bin/bash
.DEFAULT_GOAL := help

# https://gist.github.com/tadashi-aikawa/da73d277a3c1ec6767ed48d1335900f3
.PHONY: $(shell grep --no-filename -E '^[a-zA-Z0-9_-]+:' $(MAKEFILE_LIST) | sed 's/://')

WORK_PATH := /work
BINARY_PATH := $(WORK_PATH)/bin/main
OBJECT_PATH := $(WORK_PATH)/bin/main.o
LIB_PATH := $(WORK_PATH)/lib/libapue.a
PROJECT_ROOT := $$(git rev-parse --show-toplevel)
CURRENT_DIR := $(WORK_PATH)/$(notdir $(CURDIR))

define gcc
	docker run --rm -w /work -v $(PROJECT_ROOT):/work debian:gcc gcc -pthread -lrt -Wall -Og -o $(BINARY_PATH) ${1} $(LIB_PATH)
endef

define exec
	docker run -it --rm --cpuset-cpus 0 --cpu-quota 20000 -h localhost -w /work -v $(PROJECT_ROOT):/work debian:gcc $(BINARY_PATH) ${1}
endef

# Phony Targets

docker: ## docker build
	docker build -t debian:gcc docker/

clean: ## Clean
	rm -f $(PROJECT_ROOT)/bin/main
	rm -f $(PROJECT_ROOT)/bin/*.o
	rm -f $(PROJECT_ROOT)/lib/*.o
	rm -f $(PROJECT_ROOT)/lib/*.a

run: ## docker run
	docker run -it --rm --cpuset-cpus 0 --cpu-quota 20000 -h localhost --cap-add=SYS_PTRACE --security-opt="seccomp=unconfined" -w /work -v $(PROJECT_ROOT):/work debian:gcc /bin/bash || true

lib: clean ## compile lib
	docker run --rm -w /work -v $(PROJECT_ROOT)/lib:/work debian:gcc gcc -Wall -Og -c -o error.o error.c
	docker run --rm -w /work -v $(PROJECT_ROOT)/lib:/work debian:gcc gcc -Wall -Og -c -o io.o io.c
	docker run --rm -w /work -v $(PROJECT_ROOT)/lib:/work debian:gcc gcc -Wall -Og -c -o process.o process.c
	docker run --rm -w /work -v $(PROJECT_ROOT)/lib:/work debian:gcc gcc -Wall -Og -c -o daemon.o daemon.c
	docker run --rm -w /work -v $(PROJECT_ROOT)/lib:/work debian:gcc ar -r libapue.a error.o io.o process.o daemon.o

# https://postd.cc/auto-documented-makefile/
help: ## Show help
	@grep --no-filename -E '^[a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-40s\033[0m %s\n", $$1, $$2}'
