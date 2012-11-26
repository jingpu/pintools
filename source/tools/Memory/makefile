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
    CXXFLAGS ?= -Wall -Werror -Wno-unknown-pragmas $(DBG) $(OPT)
endif

ifeq ($(TARGET_COMPILER),ms)
    include ../makefile.ms.config
    DBG?=
endif

##############################################################
#
# build rules
#
##############################################################

TOOL_ROOTS = icache dcache allcache dcache_xscale_config footprint new_delete_tool

ifeq ($(TARGET),ia32e)
    TOOL_ROOTS += big_malloc
endif

ifneq ($(TARGET_OS),m)
    TOOL_ROOTS += memalloc memalloc2
endif

THREAD_LIB=$(OBJDIR)threadlib.$(OBJEXT)
APPS = new_delete_app

ifeq ($(TARGET_OS),w)
    OS_API=windows
else
    OS_API=unix
endif

all: tools

TOOLS = $(TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))

tools: $(OBJDIR) $(TOOLS)
test: $(OBJDIR) $(TOOL_ROOTS:%=%.test)


## build rules

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(PIN_CXXFLAGS) ${OUTOPT}$@ $<
$(TOOLS): $(PIN_LIBNAMES)
$(TOOLS): %$(PINTOOL_SUFFIX) : %.o
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) ${LINK_OUT}$@ $< ${PIN_LPATHS} $(PIN_LIBS) $(DBG)

##
## In this test the tool does repeated mallocs in it's Fini function until it gets a NULL return value
## It tests that PIN's malloc supplied to the tool correctly returns NULL when out of memory
## A separate test is still needed to get PIN to internally exhaust memory and see that PIN
## outputs the "Out of memory" message to the pin logfile before exiting.

memalloc.test: $(OBJDIR)memalloc$(PINTOOL_SUFFIX) memalloc.tested memalloc.failed
	touch memalloc.out; rm memalloc.out
	$(PIN) -t $< -o memalloc.out -- $(TESTAPP) makefile $<.makefile.copy
	grep -q NULL memalloc.out
	rm memalloc.failed memalloc.out
	
memalloc2.test: $(OBJDIR)memalloc2$(PINTOOL_SUFFIX) memalloc2.tested memalloc2.failed
	touch memalloc2.out; rm memalloc2.out
	$(PIN) -t $< -o  memalloc2.out -- $(TESTAPP) makefile $<.makefile.copy
	grep -q OutOfMem memalloc2.out
	rm memalloc2.out memalloc2.failed


new_delete_tool.test: $(OBJDIR)new_delete_tool$(PINTOOL_SUFFIX) new_delete.tested new_delete.failed $(OBJDIR)new_delete_app
	$(PIN) -xyzzy -statistic -logfile ./$(OBJDIR)new_delete_tool_test.log -t $< -- ./$(OBJDIR)new_delete_app
	numToolBytes=`grep 'mem::bytes::RawMmap/tool ' ./$(OBJDIR)new_delete_tool_test.log | sed -e 's/.*norm: *[0-9\.]*//' | sed -e 's/\/.*//' | sed -e 's/,//g'`; \
		test `expr $$numToolBytes \< 1000000` -eq "1"
	rm new_delete.failed

big_malloc.test: $(OBJDIR)big_malloc$(PINTOOL_SUFFIX) big_malloc.tested big_malloc.failed
	$(PIN) -separate_memory -t $< -- $(TESTAPP) makefile big_malloc.makefile.copy
	$(PIN_DIFF) makefile big_malloc.makefile.copy
	rm big_malloc.failed big_malloc.makefile.copy

$(OBJDIR)threadlib.$(OBJEXT): ../threadlib/threadlib_$(OS_API).c ../threadlib/threadlib.h
	$(CC) $(APP_CXXFLAGS) ${COPT} ${OUTOPT}$@ $< 

$(OBJDIR)new_delete_app: new_delete_app.cpp ../threadlib/threadlib.h $(THREAD_LIB)
	$(CXX) ${APP_CXXFLAGS} $(NO_OPTIMIZE) ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) $(THREAD_LIB) $(APP_PTHREAD) $(APP_LIB_ATOMIC)

## cleaning
clean:
	-rm -rf $(OBJDIR) *.out *.log *.tested *.failed
