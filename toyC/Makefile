CC := g++ # This is the main compiler provided by Dr. Resler

SRCDIR := src
INCDIR := include
TESTDIR := test
BUILDDIR := build
TARGET := bin/tc

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIB := -L lib
INC := -I include
_DEPS := *.h
DEPS := $(patsubst %,$(INCDIR)/%,$(_DEPS))
TESTFILES := $(wildcard $(TESTDIR)/*.tc)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(SCANNER): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(SCANNER) $(LIB)"; $(CC) $^ -o $(SCANNER) $(LIB)

$(PARSER): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(PARSER) $(LIB)"; $(CC) $^ -o $(PARSER) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(DEPS)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(SCANNER) $(PARSER)"; $(RM) -r $(BUILDDIR) $(TARGET) $(SCANNER) $(PARSER)

testrun:
	$(MAKE) $(TARGET)
	@echo " Testing"  $(TESTDIR)/$(TCFILE) "...";
	$(TARGET) $(TESTDIR)/$(TCFILE) -v
CC := g++ # This is the main compiler

SRCDIR := src
INCDIR := include
TESTDIR := test
BUILDDIR := build
JVMDIR := /JVM
JVMINSTRUCTDIR := /JVM/instruction
JVMLABELDIR := /JVM/label
JVMMETADIR := /JVM/meta
JVMDIRECTIVEDIR := /JVM/directive
TARGET := bin/tc

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIB := -L lib
INC := -Iinclude -Iinclude$(JVMDIR) -Iinclude$(JVMINSTRUCTDIR) -Iinclude$(JVMLABELDIR) -Iinclude$(JVMMETADIR) -Iinclude$(JVMDIRECTIVEDIR)
_DEPS := *.h
DEPS := $(patsubst %,$(INCDIR)/%,$(_DEPS))
TESTFILES := $(wildcard $(TESTDIR)/*.tc)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(DEPS)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)$(JVMINSTRUCTDIR)
	@mkdir -p $(BUILDDIR)$(JVMLABELDIR)
	@mkdir -p $(BUILDDIR)$(JVMMETADIR)
	@mkdir -p $(BUILDDIR)$(JVMDIRECTIVEDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(SCANNER) $(PARSER)"; $(RM) -r $(BUILDDIR) $(TARGET) $(SCANNER) $(PARSER)

testrun:
	$(MAKE) $(TARGET)
	@echo " Testing"  $(TESTDIR)/$(TCFILE) "...";
	$(TARGET) $(TESTDIR)/$(TCFILE) -v

alltests:
	$(MAKE) $(TARGET)
	for f in $(TESTFILES); \
	do \
	echo "File:" $$f; \
	$(TARGET) $$f -v; \
	done


.PHONY: clean

alltests:
	$(MAKE) $(TARGET)
	for f in $(TESTFILES); \
	do \
	echo "File:" $$f; \
	$(TARGET) $$f -v; \
	done


.PHONY: clean
