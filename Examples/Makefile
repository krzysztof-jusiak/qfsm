INCLUDES:=-I.. -I.
CXXFLAGS:=$(INCLUDES) -O2 -std=c++98 -Wall -Wextra -Werror -pedantic -pedantic-errors -Wno-variadic-macros
#CXXFLAGS+=-DDEBUG_MODE
EXAMPLES:=$(patsubst %.cpp, %.o, $(shell find . -iname "*.cpp"))

.PHONY: all examples clean test

test all examples: clean $(EXAMPLES)

%.o:
	@echo
	@echo "Example: $*"
	@$(CXX) $(CXXFLAGS) -o $*.exe $*.cpp
	@./$*.exe
	@echo "-------------------------------------"

clean:
	@find . -iname "*.o" | xargs --no-run-if-empty rm -f
	@rm -f *.exe

