BUILD_DIR = build

valgrind:
	@true @$(eval DEBUGGER = valgrind --dsymutil=yes)
.PHONY : valgrind

lldb:
	@true @$(eval DEBUGGER = lldb -o "breakpoint set -n cereal::RapidJSONException" -o "r")
	@true @$(eval PARAMS = --nothrow)
.PHONY : lldb

default_target: all
.PHONY : default_target

all: build
.PHONY : all

mkdir:
	@mkdir -p $(BUILD_DIR)
.PHONY : mkdir

cmake: mkdir
	@cd $(BUILD_DIR) && cmake ..
.PHONY : cmake

compile:
	@cd $(BUILD_DIR) && make -j 5 -Wall -Wfatal-errors 2>&1 >$$(tty) | ifne less; test $${PIPESTATUS[0]} -eq 0
.PHONY : compile

build: cmake compile
.PHONY : build

rebuild: clean build
.PHONY : rebuild

test: compile
	@$(DEBUGGER) -- $(BUILD_DIR)/engine/test/SymmetryEngine_test $(PARAMS)
.PHONY : test

clean:
	@rm -rf $(BUILD_DIR)
.PHONY : clean
