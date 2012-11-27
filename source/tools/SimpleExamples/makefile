##
## PIN tools makefile for Linux
##
## For Windows instructions, refer to source/tools/nmake.bat and
## source/tools/Nmakefile
## 
## To build the examples in this directory:
##
##   cd source/tools/SimpleExamples
##   make all
## 
## To build and run a specific example (e.g., opcodemix)
##   
##   cd source/tools/SimpleExamples
##   make dir opcodemix.test
##
## To build a specific example without running it (e.g., opcodemix)
##   
##   cd source/tools/SimpleExamples
##   make dir obj-intel64/opcodemix.so
##
## The example above applies to the Intel(R) 64 architecture.
## For the IA-32 architecture, use "obj-ia32" instead of 
## "obj-intel64".
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
    CXXFLAGS ?= -I$(PIN_HOME)/InstLib -fomit-frame-pointer -Wall -Werror -Wno-unknown-pragmas $(DBG) $(OPT) -MMD
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

TOOL_ROOTS = dcache edgcnt pinatrace trace icount inscount2_mt opcodemix malloctrace calltrace \
             jumpmix toprtn catmix regmix ilenmix coco get_source_location newtrace

APPS = get_source_app

ifneq ($(TARGET),ia32e)
    TOOL_ROOTS += topopcode 
else
    ifneq ($(TARGET_COMPILER),ms)
        TOOL_ROOTS += topopcode
    endif
endif

ifeq (${TARGET_OS},l)
    TOOL_ROOTS += fence
endif

ifeq (${TARGET_OS},m)
    TOOL_ROOTS += fence
endif

ifeq ($(TARGET),ia32)
    TOOL_ROOTS += emuload extmix xed-print xed-use ldstmix 
    ifeq (${TARGET_OS},l)
        TOOL_ROOTS +=  xed-cache	
    endif
endif

ifeq ($(TARGET),ia32e)
    TOOL_ROOTS += ldstmix extmix xed-use xed-print inscount2_vregs
    ifeq (${TARGET_OS},l)
        TOOL_ROOTS +=  xed-cache	
    endif
endif

SANITY_TOOLS = opcodemix$(PINTOOL_SUFFIX) 
# leave out fence, see comment at top of fence.cpp

TEST_TOOLS_ROOTS = dcache edgcnt pinatrace trace icount opcodemix  malloctrace calltrace \
                   jumpmix toprtn catmix regmix inscount2_mt coco get_source_location \
		newtrace
ifeq ($(TARGET),ia32)
    TEST_TOOLS_ROOTS +=  emuload extmix xed-use xed-print ldstmix 
    ifeq (${TARGET_OS},l)
        TEST_TOOL_ROOTS +=  xed-cache	
    endif
endif
ifeq ($(TARGET),ia32e)
    TEST_TOOLS_ROOTS +=  extmix xed-use xed-print ldstmix
    ifeq (${TARGET_OS},l)
        TEST_TOOL_ROOTS +=  xed-cache	
    endif
endif
ifneq ($(TARGET),ia32e)
    TEST_TOOLS_ROOTS += topopcode
else
    ifneq ($(TARGET_COMPILER),ms)
        TEST_TOOLS_ROOTS += topopcode
    endif
endif

TEST_TOOLS = $(TEST_TOOLS_ROOTS:%=%$(PINTOOL_SUFFIX))

TOOLS = $(TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))
APPS_BINARY_FILES = $(APPS:%=$(OBJDIR)%)

##############################################################
#
# build targets
#
##############################################################
all: tools apps
tools: $(OBJDIR) $(TOOLS)
test:  $(OBJDIR) $(TEST_TOOLS:%=%.test)
apps:  $(APPS_BINARY_FILES)
tests-sanity: $(SANITY_TOOLS:%=%.test)

##############################################################
#
# test rules
#
##############################################################
get_source_location.test : $(OBJDIR)get_source_location$(PINTOOL_SUFFIX) $(OBJDIR)get_source_app get_source_location.tested get_source_location.failed
	$(PIN) -t $< -- ./$(OBJDIR)get_source_app > $<.out 2>&1
	grep -q "get_source_app.cpp:2" $<.out 
	grep -q "get_source_app.cpp:3" $<.out 
	grep -q "get_source_app.cpp:4" $<.out 
	rm get_source_location.failed $<.out


##############################################################
#
# build rules
#
##############################################################
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : %.cpp
	${CXX} ${COPT} $(CXXFLAGS) ${PIN_CXXFLAGS} ${OUTOPT}$@ $< 

$(TOOLS): $(PIN_LIBNAMES)
$(TOOLS): $(OBJDIR)%$(PINTOOL_SUFFIX) : $(OBJDIR)%.o
	${PIN_LD} ${PIN_LDFLAGS} $(LINK_DEBUG) ${LINK_OUT}$@ $< ${PIN_LPATHS} ${PIN_LIBS} $(DBG)

##############################################################
#
# applications
#
##############################################################
$(OBJDIR)get_source_app: get_source_app.cpp
	$(APP_CXX) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $< -o $@

## cleaning
clean:
	-rm -rf $(OBJDIR) *.out *.log *.tested *.failed *.d *makefile.copy *.exp *.lib

-include *.d

