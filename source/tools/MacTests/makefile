##
## PIN tools
##

##############################################################
#
# Here are some things you might want to configure
#
##############################################################

TARGET_COMPILER?=gnu
ifdef OS
    ifeq (${OS},Windows_NT)
        TARGET_COMPILER=ms
    endif
endif

##############################################################
#
# include *.config files
#
##############################################################

ifeq ($(TARGET_COMPILER),gnu)
    include ../makefile.gnu.config
    CXXFLAGS ?= -I$(PIN_HOME)/InstLib -Wall -Werror -Wno-unknown-pragmas $(DBG) $(OPT) -MMD
endif

ifeq ($(TARGET_COMPILER),ms)
    include ../makefile.ms.config
    DBG?=
endif

##############################################################
#
# Tools sets
#
##############################################################

TOOL_ROOTS =

ifeq ($(TARGET_OS),m)
    TOOL_ROOTS = thcnt
    APPS = wqtimer libdep
endif

APPS_BINARY_FILES = $(APPS:%=$(OBJDIR)%)

ifeq ($(KIT),0)
  # not in kit, set pin shell definitions
  LIBDEP_DEFS = PIN_APP_DYLD_LIBRARY_PATH=. PIN_DYLD_RESTORE_REQUIRED=t
else
  LIBDEP_DEFS = DYLD_LIBRARY_PATH=. 
endif

##############################################################
#
# build rules
#
##############################################################

all: tools $(APPS_BINARY_FILES)

TOOLS = $(TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))

tools: $(OBJDIR) $(TOOLS)

test: $(OBJDIR) $(TOOL_ROOTS:%=%.test)


## build rules

$(OBJDIR):
	mkdir -p $(OBJDIR)


$(OBJDIR)%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(PIN_CXXFLAGS) ${OUTOPT}$@ $<

$(TOOLS): $(PIN_LIBNAMES)
$(TOOLS): $(OBJDIR)%$(PINTOOL_SUFFIX) : $(OBJDIR)%.o
	${PIN_LD} ${PIN_LDFLAGS} $(LINK_DEBUG) ${LINK_OUT}$@ $< ${PIN_LPATHS} ${PIN_LIBS} $(DBG)

# wqtimer is using __block, always use /usr/bin/gcc for it
$(OBJDIR)wqtimer: wqtimer.c
	/usr/bin/gcc $< -o $@ $(APP_CXXFLAGS)

$(OBJDIR)libmylib$(SHLIBEXT): mylib.c
	$(APP_CC) -shared $< -o $@ $(APP_CXXFLAGS)

$(OBJDIR)libdep: libdep.c $(OBJDIR)libmylib$(SHLIBEXT)
	$(APP_CC) $< -o $@ $(APP_CXXFLAGS) -L$(OBJDIR) -lmylib

thcnt.test: $(OBJDIR)thcnt$(PINTOOL_SUFFIX) thcnt.tested thcnt.failed $(OBJDIR)wqtimer
	$(PIN) -t $(OBJDIR)thcnt$(PINTOOL_SUFFIX) -- ./$(OBJDIR)wqtimer
	rm thcnt.out $(@:.test=.failed)

libdep.test: $(OBJDIR)libdep $(OBJDIR)libmylib$(SHLIBEXT) libdep.tested libdep.failed
	cd $(OBJDIR) ; env $(LIBDEP_DEFS) $(PIN) -- libdep
	rm $(@:.test=.failed)

## cleaning
clean:
	-rm -rf $(OBJDIR) *.out *.tested *.failed *.d pin.log

