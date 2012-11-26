
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

SUF = $(PINTOOLS_SUFFIX)


##############################################################
#
# include *.config files
#
##############################################################

ifeq ($(TARGET_COMPILER),gnu)
    include ../makefile.gnu.config
    STATIC=-static
endif

ifeq ($(TARGET_COMPILER),ms)
    include ../makefile.ms.config
    DBG?=
endif

ifeq ($(TARGET_OS),w)
    OS_API=windows
else
    OS_API=unix
endif


##############################################################
#
# Tests, tools and apps definitions
#
##############################################################

## Place all generic definitions here:

# This defines tests which run tools of the same name.  This is simply for convenience to avoid
# defining the test name twice (once in TOOL_ROOTS and again in TEST_ROOTS).
# Tests defined here should not be defined in TOOL_ROOTS and TEST_ROOTS.
TEST_TOOL_ROOTS =  instrumentation_order1 instrumentation_order2 instrumentation_order3 instrumentation_order4 instrumentation_order5
TEST_TOOL_ROOTS += instrumentation_order6 instrumentation_order7 instrumentation_order8 instrumentation_order9 instrumentation_order11 instrumentation_order10
TEST_TOOL_ROOTS += instrumentation_order16 instrumentation_order17 instrumentation_order18 instrumentation_order20
TEST_TOOL_ROOTS += instrumentation_order11 instrumentation_order12 instrumentation_order13 instrumentation_order14 instrumentation_order15
TEST_TOOL_ROOTS += instrumentation_order20 instrumentation_order21 instrumentation_order22 instrumentation_order23 instrumentation_order  

# This defines the tools which will be run during the the tests, and were not already defined in
# TEST_TOOL_ROOTS.
TOOL_ROOTS = 

# This defines the tests to be run that were not already defined in TEST_TOOL_ROOTS.
TEST_ROOTS =

# This defines all the applications that will be run during the tests.
APPS = special_case_app instrumentation_order_app

# This defines any additional object files that need to be compiled.
OBJECT_FILES =

## Place OS specific definitions here:

ifeq ($(TARGET_OS),w)
    TEST_TOOL_ROOTS += special special_case special_case1 special_case2 special_case3 special_case_aoti special_case_aoti1
endif
ifeq ($(TARGET_OS),l)
    TEST_TOOL_ROOTS += special special_case special_case1 special_case2 special_case3 special_case_aoti special_case_aoti1
endif

## Finalize definitions - add prefixes and suffixes
TOOLS = $(TEST_TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX)) $(TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))
APPS_BINARY_FILES = $(APPS:%=$(OBJDIR)%)
TESTS = $(TEST_TOOL_ROOTS:%=%.test) $(TEST_ROOTS:%=%.test)


##############################################################
#
# make targets
#
##############################################################

ifeq ($(TARGET_OS),w)
all: tools 
else
all: tools $(APPS_BINARY_FILES)
endif

tools: $(OBJDIR) $(TOOLS)

tests-sanity: $(OBJDIR) test

test: $(OBJDIR) $(TESTS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

## Cleanup
clean:
	-rm -rf $(OBJDIR) *.output  *.out *.tested *.failed *.xml *.makefile.copy
	-rm -rf pin.log pintool.log core.* *.core *.obj

##############################################################
#
# Test rules
#
##############################################################


special.test: $(OBJDIR)special$(PINTOOL_SUFFIX) special.tested special.failed $(OBJDIR)redblue
	$(PIN) -t $< -- ./$(OBJDIR)redblue
	$(PIN_DIFF) special.out special.ref
	rm special.failed

special_case.test: $(OBJDIR)special_case$(PINTOOL_SUFFIX) special_case.tested special_case.failed $(OBJDIR)special_case_app
	$(PIN) -t $< -- ./$(OBJDIR)special_case_app
	$(PIN_DIFF) special_case.out special_case.ref
	rm special_case.failed special_case.out

special_case1.test: $(OBJDIR)special_case1$(PINTOOL_SUFFIX) special_case1.tested special_case1.failed $(OBJDIR)special_case_app
	$(PIN) -t $< -- ./$(OBJDIR)special_case_app
	$(PIN_DIFF) special_case1.out special_case1.ref
	rm special_case1.failed special_case1.out

special_case2.test: $(OBJDIR)special_case2$(PINTOOL_SUFFIX) special_case2.tested special_case2.failed $(OBJDIR)special_case_app
	$(PIN) -t $< -- ./$(OBJDIR)special_case_app
	$(PIN_DIFF) special_case2.out special_case.ref
	rm special_case2.failed special_case2.out

special_case3.test: $(OBJDIR)special_case3$(PINTOOL_SUFFIX) special_case3.tested special_case3.failed $(OBJDIR)special_case_app
	$(PIN) -t $< -- ./$(OBJDIR)special_case_app
	$(PIN_DIFF) special_case3.out special_case1.ref
	rm special_case3.failed special_case3.out

special_case_aoti.test: $(OBJDIR)special_case_aoti$(PINTOOL_SUFFIX) special_case_aoti.tested special_case_aoti.failed $(OBJDIR)special_case_app
	$(PIN) -t $< -- ./$(OBJDIR)special_case_app
	$(PIN_DIFF) special_case_aoti.out special_case_aoti.ref
	rm special_case_aoti.failed special_case_aoti.out

special_case_aoti1.test: $(OBJDIR)special_case_aoti1$(PINTOOL_SUFFIX) special_case_aoti1.tested special_case_aoti1.failed $(OBJDIR)special_case_app
	$(PIN) -t $< -- ./$(OBJDIR)special_case_app
	$(PIN_DIFF) special_case_aoti1.out special_case_aoti1.ref
	rm special_case_aoti1.failed special_case_aoti1.out

instrumentation_order.test: $(OBJDIR)instrumentation_order$(PINTOOL_SUFFIX) instrumentation_order.tested instrumentation_order.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order_tool.out
	$(PIN_DIFF) instrumentation_order.out instrumentation_order.ref
	rm instrumentation_order.failed instrumentation_order.out instrumentation_order_tool.out

instrumentation_order1.test: $(OBJDIR)instrumentation_order1$(PINTOOL_SUFFIX) instrumentation_order1.tested instrumentation_order1.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order1_tool.out
	$(PIN_DIFF) instrumentation_order1.out instrumentation_order1.ref
	rm instrumentation_order1.failed instrumentation_order1.out instrumentation_order1_tool.out

instrumentation_order2.test: $(OBJDIR)instrumentation_order2$(PINTOOL_SUFFIX) instrumentation_order2.tested instrumentation_order2.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order2_tool.out
	$(PIN_DIFF) instrumentation_order2.out instrumentation_order2.ref
	rm instrumentation_order2.failed instrumentation_order2.out instrumentation_order2_tool.out

instrumentation_order3.test: $(OBJDIR)instrumentation_order3$(PINTOOL_SUFFIX) instrumentation_order3.tested instrumentation_order3.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order3_tool.out
	$(PIN_DIFF) instrumentation_order3.out instrumentation_order3.ref
	rm instrumentation_order3.failed instrumentation_order3.out instrumentation_order3_tool.out

instrumentation_order4.test: $(OBJDIR)instrumentation_order4$(PINTOOL_SUFFIX) instrumentation_order4.tested instrumentation_order4.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order4_tool.out
	$(PIN_DIFF) instrumentation_order4.out instrumentation_order4.ref
	rm instrumentation_order4.failed instrumentation_order4.out instrumentation_order4_tool.out

instrumentation_order5.test: $(OBJDIR)instrumentation_order5$(PINTOOL_SUFFIX) instrumentation_order5.tested instrumentation_order5.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order5_tool.out
	$(PIN_DIFF) instrumentation_order5.out instrumentation_order5.ref
	rm instrumentation_order5.failed instrumentation_order5.out instrumentation_order5_tool.out

instrumentation_order6.test: $(OBJDIR)instrumentation_order6$(PINTOOL_SUFFIX) instrumentation_order6.tested instrumentation_order6.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order6_tool.out
	$(PIN_DIFF) instrumentation_order6.out instrumentation_order6.ref
	rm instrumentation_order6.failed instrumentation_order6.out instrumentation_order6_tool.out

instrumentation_order7.test: $(OBJDIR)instrumentation_order7$(PINTOOL_SUFFIX) instrumentation_order7.tested instrumentation_order7.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order7_tool.out
	$(PIN_DIFF) instrumentation_order7.out instrumentation_order7.ref
	rm instrumentation_order7.failed instrumentation_order7.out instrumentation_order7_tool.out

instrumentation_order8.test: $(OBJDIR)instrumentation_order8$(PINTOOL_SUFFIX) instrumentation_order8.tested instrumentation_order8.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order8_tool.out
	$(PIN_DIFF) instrumentation_order8.out instrumentation_order8.ref
	rm instrumentation_order8.failed instrumentation_order8.out instrumentation_order8_tool.out

instrumentation_order9.test: $(OBJDIR)instrumentation_order9$(PINTOOL_SUFFIX) instrumentation_order9.tested instrumentation_order9.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order9_tool.out
	$(PIN_DIFF) instrumentation_order9.out instrumentation_order9.ref
	rm instrumentation_order9.failed instrumentation_order9.out instrumentation_order9_tool.out

instrumentation_order10.test: $(OBJDIR)instrumentation_order10$(PINTOOL_SUFFIX) instrumentation_order10.tested instrumentation_order10.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order10_tool.out
	$(PIN_DIFF) instrumentation_order10.out instrumentation_order10.ref
	rm instrumentation_order10.failed instrumentation_order10.out instrumentation_order10_tool.out

instrumentation_order11.test: $(OBJDIR)instrumentation_order11$(PINTOOL_SUFFIX) instrumentation_order11.tested instrumentation_order11.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order11_tool.out
	$(PIN_DIFF) instrumentation_order11.out instrumentation_order11.ref
	rm instrumentation_order11.failed instrumentation_order11.out instrumentation_order11_tool.out

instrumentation_order12.test: $(OBJDIR)instrumentation_order12$(PINTOOL_SUFFIX) instrumentation_order12.tested instrumentation_order12.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order12_tool.out
	$(PIN_DIFF) instrumentation_order12.out instrumentation_order12.ref
	rm instrumentation_order12.failed instrumentation_order12.out instrumentation_order12_tool.out

instrumentation_order13.test: $(OBJDIR)instrumentation_order13$(PINTOOL_SUFFIX) instrumentation_order13.tested instrumentation_order13.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order13_tool.out
	$(PIN_DIFF) instrumentation_order13.out instrumentation_order13.ref
	rm instrumentation_order13.failed instrumentation_order13.out instrumentation_order13_tool.out

instrumentation_order14.test: $(OBJDIR)instrumentation_order14$(PINTOOL_SUFFIX) instrumentation_order14.tested instrumentation_order14.failed $(OBJDIR)instrumentation_order_app
	-$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order14_tool.out
	echo "instrumentation_order14.test pin execution should fail.  Ignore the error (above, but not one below!)."
	grep "RTN_InsertCall is NOT supported from the tool's TRACE or INS instrumentation callback" instrumentation_order14_tool.out
	rm instrumentation_order14.failed instrumentation_order14.out instrumentation_order14_tool.out

instrumentation_order15.test: $(OBJDIR)instrumentation_order15$(PINTOOL_SUFFIX) instrumentation_order15.tested instrumentation_order15.failed $(OBJDIR)instrumentation_order_app
	-$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order15_tool.out
	echo "instrumentation_order15.test pin execution should fail.  Ignore the error (above, but not one below!)."
	grep "RTN_InsertCall is NOT supported from the tool's TRACE or INS instrumentation callback" instrumentation_order15_tool.out
	rm instrumentation_order15.failed instrumentation_order15.out instrumentation_order15_tool.out

instrumentation_order16.test: $(OBJDIR)instrumentation_order16$(PINTOOL_SUFFIX) instrumentation_order16.tested instrumentation_order16.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order16_tool.out
	$(PIN_DIFF) instrumentation_order16.out instrumentation_order16.ref
	rm instrumentation_order16.failed instrumentation_order16.out instrumentation_order16_tool.out

instrumentation_order17.test: $(OBJDIR)instrumentation_order17$(PINTOOL_SUFFIX) instrumentation_order17.tested instrumentation_order17.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order17_tool.out
	$(PIN_DIFF) instrumentation_order17.out instrumentation_order17.ref
	rm instrumentation_order17.failed instrumentation_order17.out instrumentation_order17_tool.out

instrumentation_order18.test: $(OBJDIR)instrumentation_order18$(PINTOOL_SUFFIX) instrumentation_order18.tested instrumentation_order18.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order18_tool.out
	$(PIN_DIFF) instrumentation_order18.out instrumentation_order18.ref
	rm instrumentation_order18.failed instrumentation_order18.out instrumentation_order18_tool.out

instrumentation_order19.test: $(OBJDIR)instrumentation_order19$(PINTOOL_SUFFIX) instrumentation_order19.tested instrumentation_order19.failed $(OBJDIR)instrumentation_order_app
	$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order19_tool.out
	$(PIN_DIFF) instrumentation_order19.out instrumentation_order19.ref
	rm instrumentation_order19.failed instrumentation_order19.out instrumentation_order19_tool.out

instrumentation_order20.test: $(OBJDIR)instrumentation_order20$(PINTOOL_SUFFIX) instrumentation_order20.tested instrumentation_order20.failed $(OBJDIR)instrumentation_order_app
	-$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order20_tool.out
	echo "instrumentation_order20.test pin execution should fail.  Ignore the error (above, but not one below!)."
	grep "RTN_ReplaceSignature is NOT supported from the tool's TRACE or INS instrumentation callback" instrumentation_order20_tool.out
	rm instrumentation_order20.failed instrumentation_order20.out instrumentation_order20_tool.out

instrumentation_order21.test: $(OBJDIR)instrumentation_order21$(PINTOOL_SUFFIX) instrumentation_order21.tested instrumentation_order21.failed $(OBJDIR)instrumentation_order_app
	-$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order21_tool.out
	echo "instrumentation_order21.test pin execution should fail.  Ignore the error (above, but not one below!)."
	grep "RTN_ReplaceSignature is NOT supported from the tool's TRACE or INS instrumentation callback" instrumentation_order21_tool.out
	rm instrumentation_order21.failed instrumentation_order21.out instrumentation_order21_tool.out

instrumentation_order22.test: $(OBJDIR)instrumentation_order22$(PINTOOL_SUFFIX) instrumentation_order22.tested instrumentation_order22.failed $(OBJDIR)instrumentation_order_app
	-$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order22_tool.out
	echo "instrumentation_order22.test pin execution should fail.  Ignore the error (above, but not one below!)."
	grep "RTN_Replace is NOT supported from the tool's TRACE or INS instrumentation callback" instrumentation_order22_tool.out
	rm instrumentation_order22.failed instrumentation_order22.out instrumentation_order22_tool.out

instrumentation_order23.test: $(OBJDIR)instrumentation_order23$(PINTOOL_SUFFIX) instrumentation_order23.tested instrumentation_order23.failed $(OBJDIR)instrumentation_order_app
	-$(PIN) -t $< -- ./$(OBJDIR)instrumentation_order_app > instrumentation_order23_tool.out
	echo "instrumentation_order23.test pin execution should fail.  Ignore the error (above, but not one below!)."
	grep "RTN_Replace is NOT supported from the tool's TRACE or INS instrumentation callback" instrumentation_order23_tool.out
	rm instrumentation_order23.failed instrumentation_order23.out instrumentation_order23_tool.out

##############################################################
#
# Build rules
#
##############################################################

## defines

ifeq ($(TARGET_OS),l)
    THREADLIB = -lpthread
else
    THREADLIB =
endif

## Default build rules
$(OBJDIR)%.o: %.cpp
	$(CXX) ${COPT} $(CXXFLAGS) $(PIN_CXXFLAGS) ${OUTOPT}$@ $<

$(OBJDIR)%$(PINTOOL_SUFFIX): $(OBJDIR)%.o $(PIN_LIBNAMES)
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) ${LINK_OUT}$@ $< ${PIN_LPATHS} $(PIN_LIBS) $(DBG)

## Special build rules

$(OBJDIR)special_case_app: special_case_app.cpp
	$(CXX) $(APP_CXXFLAGS) $(NO_OPTIMIZE) $(OUTEXE)$@ $(DBG) special_case_app.cpp

$(OBJDIR)instrumentation_order_app: instrumentation_order_app.cpp
	$(CXX) $(APP_CXXFLAGS) $(NO_OPTIMIZE) $(OUTEXE)$@ $(DBG) instrumentation_order_app.cpp

ifeq ($(TARGET_OS),l)
$(OBJDIR)redblue: redblue.s
	$(CC) $(APP_CXXFLAGS) -o $@ $(DBG) redblue.s
endif
ifeq ($(TARGET_OS),w)
$(OBJDIR)redblue_$(TARGET).obj: redblue_$(TARGET).asm
	$(MASM) /nologo /c /Fo$@ $<

$(OBJDIR)redblue: $(OBJDIR)redblue_$(TARGET).obj redblue.cpp
	$(CC) $(APP_CXXFLAGS) $(OUTEXE)$@  $(OBJDIR)redblue_$(TARGET).obj redblue.cpp /link /EXPORT:red /EXPORT:blue /EXPORT:common
endif
