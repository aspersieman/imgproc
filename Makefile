CC						:= g++
BUILDDIR			:= build
TESTDIR				:= test
TARGET_NAME 	:= imgproc
TARGET				:= "$(BUILDDIR)/$(TARGET_NAME)"
SRCDIR				:= src
CFLAGS				:= -std=c++17 -g
SRCEXT				:= cpp
SOURCES_CPP 	:= $(wildcard $(SRCDIR)/*.$(SRCEXT))
SOURCES_H 		:= $(wildcard $(SRCDIR)/*.$(SRCEXT))
SOURCES_WASM	:= $(SRCDIR)/Image.cpp
OBJECTS				:= $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES_CPP:.$(SRCEXT)=.o))
CHEERP				:= /opt/cheerp/bin/clang++

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@printf "\e[33m\e[1mBuilding...\e[0m\n";
	@mkdir -p $(BUILDDIR)
	@echo "  $(notdir $@) from $(notdir $<)"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	@printf "\e[35m\e[1mLinking...\e[0m\n";
	@echo "  $(notdir $(OBJECTS))"
	@$(CC) $(CFLAGS) -o $@ $^


PHONY: clean
clean:
	@printf "\e[31m\e[1mCleaning...\e[0m\n"
	@echo "  /$(BUILDDIR)"
	@echo "  /$(TARGET)"
	@$(RM) -r $(BUILDDIR) $(OBJECTS)
	@$(RM) "./$(TARGET)"

PHONY: r
r:
	@printf "\e[33m\e[1mRunning $(TARGET)\e[0m\n"
	@./$(TARGET)

PHONY: run
run:
	@mkdir -p $(BUILDDIR)
	@for source in $(basename $(notdir $(SOURCES_CPP))); do\
		printf "\e[33m\e[1mBuilding...\e[0m\n";\
		echo "  $$source.o from $$source.$(SRCEXT)";\
		$(CC) $(CFLAGS) -c -o $(BUILDDIR)/$$source.o $(SRCDIR)/$$source.$(SRCEXT);\
	done
	@printf "\e[95m\e[1mLinking...\e[0m\n";
	@echo "  $(notdir $(OBJECTS))"
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@printf "\e[33m\e[1mRunning $(TARGET)\e[0m\n"
	@ ./$(TARGET)

PHONY: wasm
wasm:
	@printf "\e[33m\e[1mBuilding wasm...\e[0m\n";
	@mkdir -p $(BUILDDIR)
	$(CHEERP) \
		-target cheerp-wasm \
		-cheerp-linear-heap-size=128 \
		-o $(BUILDDIR)/$(TARGET_NAME).js \
		$(SOURCES_WASM)
	@cp $(TESTDIR)/js-test.html $(BUILDDIR)
