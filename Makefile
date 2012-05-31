PREFIX=/usr/include
QFSM=QFsm

.PHONY: install all

all:
	@cd Examples && make

install:
	@cp -r $(QFSM) $(PREFIX)

