GTEST=../../Externals/gtest
GTEST_LIBS=$(GTEST)/lib/.libs
BOOST=../../Externals/boost
CXXFLAGS=-I$(BOOST) -I$(BOOST)_ -I$(GTEST)/include -I../.. -I.. -g -Wall -Wextra -DDEBUG_MODE
OBJS=$(patsubst %.cpp,%.o,$(shell find . -iname "*.cpp")) ../Common/main.o
#OBJS=Front/Operations/IsFinishedTest.o ../Common/main.o

.PHONY: gtest
gtest:
	@[ -e $(GTEST_LIBS) ] || (cd $(GTEST) && ./configure && make)

.PHONY: test
test: gtest clean_test $(OBJS)
	@$(CXX) -o $(TEST_TARGET) $(OBJS) $(GTEST_LIBS)/libgtest.a -lpthread && LD_LIBRARY_PATH=$(GTEST_LIBS) ./$(TEST_TARGET)

.PHONY: clean_test
clean_test:
	@find . -iname "*.o" | xargs --no-run-if-empty rm -f
	@rm -f $(TEST_TARGET)

