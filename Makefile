CC=gcc
WARNINGS=-Wall
C_VERSION=-std=c99
DEBUG=-g
CFLAGS=$(DEBUG) $(WARNINGS)

GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
BLUE=\033[0;34m
RESET=\033[0m

CERVER_C_FILES=lib/data_utils/callback_queue.c\
			   lib/data_utils/hashmap.c\
			   lib/cerver.c\
			   lib/router/endpoint_tree.c\
			   lib/router/http_response.c\
			   lib/router/http_request.c\
			   lib/router/router.c\
			   lib/logger/logger.c\
			   lib/client/client.c

.PHONY: all clean test debug-test build start help

help: ## Show this help.
	@printf "${YELLOW} ============= Welcome to Cerver ============= ${RESET}\n"
	@echo " "
	@printf "Please use \`make ${BLUE}<target>${RESET}' where ${BLUE}<target>${RESET} is one of\n"
	@echo " "
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' ${MAKEFILE_LIST} | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "- ${BLUE}%-30s${RESET} %s\n", $$1, $$2}'


clean: ## Clean .o files generated during building
	@echo "$(RED)Cleaning$(RESET)"
	rm -f $(CERVER_C_FILES:.c=.o)
	rm -f src/*.o
	rm -f lib/tests/*.o
	rm -f src/a.out
	rm -f main
	rm -f test
	rm -f debug-test

%.o: %.c
	@echo "$(GREEN)Compiling $< into $@$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

src/main.o: src/main.c $(CERVER_C_FILES) $(CERVER_C_FILES:.c=.h) $(CERVER_C_FILES:.c=.o)
	@echo "$(GREEN)Compiling main.c into main.o$(RESET)"
	$(CC) src/main.c -c -o $@ $(CFLAGS)

main: src/main.o
	@echo "$(GREEN)Linking main.o into main$(RESET)"
	$(CC) $(CERVER_C_FILES:.c=.o) $< -o main $(CFLAGS)

lib/tests/main.o: lib/tests/main.c $(CERVER_C_FILES) $(CERVER_C_FILES:.c=.h) $(CERVER_C_FILES:.c=.o)
	@echo "$(GREEN)Creating main object$(RESET)"
	$(CC) $(CERVER_C_FILES:.c=.o) lib/tests/main.c -c -o $@ $(CFLAGS)

test: lib/tests/main.o ## Run tests
	@echo "$(GREEN)Creating tests executable...$(RESET)"
	$(CC) $(CFLAGS) $(CERVER_C_FILES:.c=.o) lib/tests/main.o -o $@
	@echo ""
	@echo "$(YELLOW)Running tests...$(RESET)"
	@echo ""
	@./test

debug-test: lib/tests/main.o ## Run tests with valgrind debugger
	@echo "$(GREEN)Creating tests executable...$(RESET)"
	$(CC) $(CFLAGS) $(CERVER_C_FILES:.c=.o) lib/tests/main.o -o $@
	@echo ""
	@echo "$(YELLOW)Running tests with valgrind debugger...$(RESET)"
	@echo ""
	valgrind --leak-check=full --show-leak-kinds=all ./$@


build: main ## Build application
	@echo "$(GREEN)Done!$(RESET)"

all: build

start: main ## Starts server
	./main



