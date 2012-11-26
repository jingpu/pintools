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
# build rules
#
##############################################################

ifeq ($(TARGET_COMPILER),ms)
   EXTRA_LIBS =
else
   EXTRA_LIBS =
endif

IA32_TEST_TOOLS = alignchk

ifeq ($(TARGET),ia32)
    TOOL_ROOTS += $(IA32_TEST_TOOLS)
    APP_ROOTS = misaligned
ifneq ($(TARGET_OS),w)
ifneq ($(TARGET_OS),m)
    TOOL_ROOTS += movdqa_test2
endif
endif
endif
ifeq ($(TARGET),ia32e)
    TOOL_ROOTS += $(IA32_TEST_TOOLS)
    APP_ROOTS = misaligned
endif

SANITY_TOOLS = 
# every tool should be tested
TEST_TOOLS_ROOTS = $(TOOL_ROOTS)

TOOLS = $(TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))

APPS = $(APP_ROOTS:%=$(OBJDIR)%)

TEST_TOOLS = $(TEST_TOOLS_ROOTS:%=%$(PINTOOL_SUFFIX))
TESTS_TO_RUN = $(TEST_TOOLS:%=%.test)
ifeq ($(TARGET),ia32)
ifneq ($(TARGET_OS),w)
ifneq ($(TARGET_OS),m)
    TESTS_TO_RUN += movdqa_test3.test movdqa_test4.test 
endif
endif
endif

all: $(OBJDIR)
	-$(MAKE) make_all
tools: $(OBJDIR)
	-$(MAKE) make_tools
test: $(OBJDIR)
	-$(MAKE) make_test
tests-sanity: $(OBJDIR)
	-$(MAKE) make_tests-sanity

make_all: $(APPS) $(TOOLS)
make_tools: $(TOOLS)
make_test: $(TESTS_TO_RUN)
make_tests-sanity: $(SANITY_TOOLS:%=%.test)

## build rules

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(PIN_CXXFLAGS) ${OUTOPT}$@ $<

$(TOOLS): $(PIN_LIBNAMES)

$(TOOLS): $(OBJDIR)%$(PINTOOL_SUFFIX) : $(OBJDIR)%.o
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) ${LINK_OUT}$@ $< ${PIN_LPATHS} $(PIN_LIBS) $(EXTRA_LIBS) $(DBG)

ifeq ($(TARGET),ia32e)
    ifeq ($(TARGET_COMPILER),ms)
        SSE_ASM_OBJ     = $(OBJDIR)movdqa_test_ia32e.obj
        LINK_OPTION     = /link
    endif
endif

ifeq ($(TARGET),ia32)
    ifeq ($(TARGET_COMPILER),ms)
        SSE_ASM_OBJ     = $(OBJDIR)movdqa_test_ia32.obj
        LINK_OPTION     = /link
    endif
endif

$(OBJDIR)movdqa_test2_ia32.o: movdqa_test2_ia32.s
	$(APP_CC) $(APP_CXXFLAGS) -x assembler-with-cpp -c $< -o $@

$(OBJDIR)movdqa_test2$(PINTOOL_SUFFIX): $(OBJDIR)movdqa_test2.o $(OBJDIR)movdqa_test2_ia32.o
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) ${LINK_OUT}$@ $< ${PIN_LPATHS} $(PIN_LIBS) $(DBG) $(OBJDIR)movdqa_test2_ia32.o

$(OBJDIR)misaligned: misaligned.c $(SSE_ASM_OBJ)
	${APP_CC} $(APP_CXXFLAGS) $(NO_LOGO) $(DBG) $(NO_OPTIMIZE) $(SSE2) ${OUTEXE}$@ $< $(LINK_OPTION) $(SSE_ASM_OBJ)


$(OBJDIR)movdqa_test_ia32.obj: movdqa_test_ia32.asm
	ml /nologo $(OUTOPT) $@ /c $< 

$(OBJDIR)movdqa_test_ia32e.obj: movdqa_test_ia32e.asm
	ml64 /nologo $(OUTOPT) $@ /c $< 

## cleaning
clean:
	-rm -rf $(OBJDIR) *.out *.tested *.failed *.exp *.lib 

alignchk.test : $(OBJDIR)alignchk$(PINTOOL_SUFFIX) $(OBJDIR)misaligned alignchk.tested alignchk.failed 
	-rm -f alignchk.out
	@echo This is supposed to fail and report a problem about an unaligned MOVDQA
	-$(PIN) -t $(OBJDIR)alignchk$(PINTOOL_SUFFIX)  -- ./$(OBJDIR)misaligned  >  alignchk.out 2>&1
	grep "Misaligned MOVDQA at instruction" alignchk.out
	rm alignchk.failed  alignchk.out

movdqa_test3.test: $(OBJDIR)movdqa_test2$(PINTOOL_SUFFIX) movdqa_test3.tested movdqa_test3.failed 
	touch movdqa_test3.makefile.copy; rm movdqa_test3.makefile.copy
	$(PIN) -xyzzy -inline_maxlen 1 -t $<  -- $(TESTAPP) makefile movdqa_test3.makefile.copy
	$(PIN_CMP) makefile movdqa_test3.makefile.copy
	rm movdqa_test3.makefile.copy $(@:.test=.failed) 

movdqa_test4.test: $(OBJDIR)movdqa_test2$(PINTOOL_SUFFIX) movdqa_test4.tested movdqa_test4.failed 
	touch movdqa_test4.makefile.copy; rm movdqa_test4.makefile.copy
	$(PIN) -xyzzy -inline 0 -t $<  -- $(TESTAPP) makefile movdqa_test4.makefile.copy
	$(PIN_CMP) makefile movdqa_test4.makefile.copy
	rm movdqa_test4.makefile.copy $(@:.test=.failed) 

-include $(OBJDIR)*.d
