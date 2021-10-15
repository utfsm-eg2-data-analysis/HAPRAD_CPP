.DELETE_ON_ERROR:

ifndef ROOTSYS
    $(error "ERROR: please, set the variable ROOTSYS")
endif

MKDIR_P := mkdir -p

BINDIR := ./bin
SRCDIR := ./src

ROOTCONFIG := root-config
ROOTCFLAGS := $(shell $(ROOTCONFIG) --cxx --cflags)
ROOTLDFLAGS := $(shell $(ROOTCONFIG) --cxx --ldflags)
ROOTGLIBS := $(shell $(ROOTCONFIG) --glibs)

CERNLIBS := -L$(CERN_LIB) -lpdflib804 -lmathlib -lphtools -lpacklib -lkernlib -lpawlib

LDFLAGS := -lgfortran -Wl,-rpath,$(HAPRAD_CPP)/slib

INCLUDES := -I./include -I$(HAPRAD_CPP)
LIBS := -L$(HAPRAD_CPP)/slib -lTRadCor $(ROOTGLIBS) $(CERNLIBS)

PROG := GetRC
LIST := $(addprefix $(BINDIR)/, $(PROG))

.PHONY: all clean

all: $(LIST)

$(BINDIR)/%: $(BINDIR)/%.o
	@echo "Linking" $<
	$(ROOTLDFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.cxx
	@echo "Compiling" $<
	$(MKDIR_P) $(BINDIR)
	$(ROOTCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(LIST:%=%.o) $(LIST)
