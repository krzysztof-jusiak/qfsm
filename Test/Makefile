.PHONY: all
all: test

.PHONY: test
test:
	@cd UT && make test
	@cd MT && make test

.PHONY: clean_test
clean_test:
	@cd UT && make clean_test
	@cd MT && make clean_test

.PHONY: clean
clean: clean_test

