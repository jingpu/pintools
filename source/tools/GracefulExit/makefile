
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
TEST_TOOL_ROOTS = applicationexit

# This defines the tools which will be run during the the tests, and were not already defined in
# TEST_TOOL_ROOTS.
TOOL_ROOTS = 

# This defines the tests to be run that were not already defined in TEST_TOOL_ROOTS.
TEST_ROOTS =

# This defines all the applications that will be run during the tests.
APPS = 

# This defines any additional object files that need to be compiled.
OBJECT_FILES =

## Place OS specific definitions here:

ifeq ($(TARGET_OS),w)
    TOOL_ROOTS += threadFini_tool exitFromFini_tool exitApplicationLocked_tool
    TEST_ROOTS += threadFini raceToEnterVm exitApplicationFromThreadFini exitApplicationFromFini \
                  exitProcessFromRunningThreadFini exitProcessFromBlockedThreadFini exitProcessFromFini \
                  exitApplicationLocked
    APPS += threadFini_app threadFini_exception_app raceToEnterVm_app exitFromFini_app exitApplicationLocked_app
    OBJECT_FILES += threadUtils.o
endif

ifeq ($(TARGET_OS),l)
    TOOL_ROOTS += threadFini_tool exitFromFini_tool exitApplicationLocked_tool
    TEST_ROOTS += threadFini threadFini_exception threadFini_sig raceToExit exitApplicationFromThreadFini \
                  exitApplicationFromFini exitProcessFromRunningThreadFini exitProcessFromBlockedThreadFini \
                  exitProcessFromFini exitApplicationLocked
    APPS += threadFini_app threadFini_exception_app threadFini_sig_app threadFini_sendsig raceToExit_app \
            exitFromFini_app exitApplicationLocked_app
    OBJECT_FILES += threadUtils.o
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

# Test PIN_ExitApplication from both an analysis routine and a callback.
applicationexit.test: $(OBJDIR)applicationexit$(PINTOOL_SUFFIX) $(TESTAPP) applicationexit.tested applicationexit.failed
	$(PIN) -t $< -o $(OBJDIR)applicationexit.out -- $(TESTAPP) 
	diff --strip-trailing-cr $(OBJDIR)applicationexit.out applicationexit.master
	$(PIN) -t $< -o $(OBJDIR)applicationexit_c.out -c -- $(TESTAPP) 
	diff --strip-trailing-cr $(OBJDIR)applicationexit_c.out applicationexit.master
	rm applicationexit.failed $(OBJDIR)applicationexit.out $(OBJDIR)applicationexit_c.out 

threadFini.test: $(OBJDIR)threadFini_tool$(PINTOOL_SUFFIX) $(OBJDIR)threadFini_app threadFini.tested threadFini.failed
	testFailed=0; \
	for trial in 0 1 2 3 4; do \
	  thisTest=0; \
	  $(PIN) -logfile $(OBJDIR)threadFini.log.$$trial \
	    -xyzzy -enable_vsm 1 -mesgon log_vsm -mesgon log_depot \
	    -t $(OBJDIR)threadFini_tool$(PINTOOL_SUFFIX) \
	    -startsfile $(OBJDIR)threadStarts.out.$$trial \
	    -finisfile $(OBJDIR)threadFinis.out.$$trial -- \
	        $(OBJDIR)threadFini_app $$trial > $(OBJDIR)threadFini.out.$$trial 2>&1; \
	  if ! grep -q "fini function 0 6" $(OBJDIR)threadFini.out.$$trial; then thisTest=1; fi; \
	  sort $(OBJDIR)threadStarts.out.$$trial > $(OBJDIR)threadStarts.sorted.$$trial; \
	  sort $(OBJDIR)threadFinis.out.$$trial > $(OBJDIR)threadFinis.sorted.$$trial; \
	  if ! $(PIN_DIFF) $(OBJDIR)threadStarts.sorted.$$trial $(OBJDIR)threadFinis.sorted.$$trial; then thisTest=1; fi; \
	  if test $$thisTest -eq 1; then echo threadFini scenario $$trial failed; testFailed=1; \
          else echo threadFini scenario $$trial passed; fi; \
	done; \
	test $$testFailed -eq 0
	rm threadFini.failed $(OBJDIR)threadFini.out.* $(OBJDIR)threadFini.log.* $(OBJDIR)threadStarts.* $(OBJDIR)threadFinis.*

threadFini_exception.test: $(OBJDIR)threadFini_tool$(PINTOOL_SUFFIX) $(OBJDIR)threadFini_exception_app threadFini_exception.tested threadFini_exception.failed
	-$(PIN) -logfile $(OBJDIR)threadFini_exception.log \
	  -xyzzy -mesgon log_vsm -mesgon log_depot \
	  -t $(OBJDIR)threadFini_tool$(PINTOOL_SUFFIX) \
	  -startsfile $(OBJDIR)threadStarts_exception.out \
	  -finisfile $(OBJDIR)threadFinis_exception.out -- \
	      $(OBJDIR)threadFini_exception_app > $(OBJDIR)threadFini_exception.out 2>&1
	grep -q "fini function 0 2" $(OBJDIR)threadFini_exception.out
	sort $(OBJDIR)threadStarts_exception.out > $(OBJDIR)threadStarts_exception.sorted
	sort $(OBJDIR)threadFinis_exception.out > $(OBJDIR)threadFinis_exception.sorted
	$(PIN_DIFF) $(OBJDIR)threadStarts_exception.sorted $(OBJDIR)threadFinis_exception.sorted
	rm threadFini_exception.failed $(OBJDIR)threadFini_exception.out $(OBJDIR)threadFini_exception.log
	rm $(OBJDIR)threadStarts_exception.* $(OBJDIR)threadFinis_exception.*

threadFini_sig.test: $(OBJDIR)threadFini_tool$(PINTOOL_SUFFIX) $(OBJDIR)threadFini_sig_app $(OBJDIR)threadFini_sendsig threadFini_sig.tested threadFini_sig.failed
	-$(PIN) -logfile $(OBJDIR)threadFini_sig.log \
	  -xyzzy -mesgon log_vsm -mesgon log_depot \
	  -t $(OBJDIR)threadFini_tool$(PINTOOL_SUFFIX) \
	  -startsfile $(OBJDIR)threadStarts_sig.out \
	  -finisfile $(OBJDIR)threadFinis_sig.out -- \
	      $(OBJDIR)threadFini_sig_app $(OBJDIR)threadFini_sendsig > $(OBJDIR)threadFini_sig.out 2>&1
	grep -q "fini function 0 2" $(OBJDIR)threadFini_sig.out
	sort $(OBJDIR)threadStarts_sig.out > $(OBJDIR)threadStarts_sig.sorted
	sort $(OBJDIR)threadFinis_sig.out > $(OBJDIR)threadFinis_sig.sorted
	$(PIN_DIFF) $(OBJDIR)threadStarts_sig.sorted $(OBJDIR)threadFinis_sig.sorted
	rm threadFini_sig.failed $(OBJDIR)threadFini_sig.out $(OBJDIR)threadFini_sig.log $(OBJDIR)threadStarts_sig.* $(OBJDIR)threadFinis_sig.*

raceToExit.test: $(OBJDIR)threadFini_tool$(PINTOOL_SUFFIX) $(OBJDIR)raceToExit_app raceToExit.tested raceToExit.failed
	$(PIN) -logfile $(OBJDIR)raceToExit.log \
	  -xyzzy -mesgon log_vsm -mesgon log_depot \
	  -t $(OBJDIR)threadFini_tool$(PINTOOL_SUFFIX) \
	  -startsfile $(OBJDIR)threadStarts_raceToExit.out \
	  -finisfile $(OBJDIR)threadFinis_raceToExit.out -- \
	      $(OBJDIR)raceToExit_app > $(OBJDIR)raceToExit.out 2>&1
	grep -q "fini function 0 `cat $(OBJDIR)threadStarts_raceToExit.out | wc -l`" $(OBJDIR)raceToExit.out
	sort $(OBJDIR)threadStarts_raceToExit.out > $(OBJDIR)threadStarts_raceToExit.sorted
	sort $(OBJDIR)threadFinis_raceToExit.out > $(OBJDIR)threadFinis_raceToExit.sorted
	$(PIN_DIFF) $(OBJDIR)threadStarts_raceToExit.sorted $(OBJDIR)threadFinis_raceToExit.sorted
	rm raceToExit.failed $(OBJDIR)raceToExit.out $(OBJDIR)raceToExit.log $(OBJDIR)threadStarts_raceToExit.* $(OBJDIR)threadFinis_raceToExit.*

raceToEnterVm.test: $(OBJDIR)raceToEnterVm_app raceToEnterVm.tested raceToEnterVm.failed
	$(PIN) -logfile $(OBJDIR)raceToEnterVm.log \
	  -xyzzy -enable_vsm 1 -mesgon log_vsm -mesgon log_depot -- \
	      $(OBJDIR)raceToEnterVm_app > $(OBJDIR)raceToEnterVm.out 2>&1
	rm raceToEnterVm.failed $(OBJDIR)raceToEnterVm.out $(OBJDIR)raceToEnterVm.log

exitApplicationFromThreadFini.test: $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) $(OBJDIR)exitFromFini_app exitApplicationFromThreadFini.tested exitApplicationFromThreadFini.failed
	testFailed=0; \
	for trial in 1 2; do \
	  thisTest=0; \
	  $(PIN) -logfile $(OBJDIR)exitApplicationFromThreadFini.log.$$trial \
	    -xyzzy -enable_vsm 1 -mesgon log_vsm -mesgon log_depot \
	    -t $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) -scenario $$trial \
	    -startsfile $(OBJDIR)threadStarts_exitApplicationFromThreadFini.out.$$trial \
	    -finisfile $(OBJDIR)threadFinis_exitApplicationFromThreadFini.out.$$trial \
	      -- $(OBJDIR)exitFromFini_app $$trial > $(OBJDIR)exitApplicationFromThreadFini.out.$$trial 2>&1; \
	  if ! grep -q "It is prohibited to call PIN_ExitApplication() from a thread-fini function" \
	    $(OBJDIR)exitApplicationFromThreadFini.out.$$trial; then thisTest=1; fi; \
	  if test $$thisTest -eq 1; then echo exitApplicationFromThreadFini scenario $$trial failed; testFailed=1; \
	    else echo exitApplicationFromThreadFini scenario $$trial passed; fi; \
	done; \
	test $$testFailed -eq 0
	rm exitApplicationFromThreadFini.failed $(OBJDIR)exitApplicationFromThreadFini.out.*
	rm $(OBJDIR)exitApplicationFromThreadFini.log.*
	rm $(OBJDIR)threadStarts_exitApplicationFromThreadFini.* $(OBJDIR)threadFinis_exitApplicationFromThreadFini.*
	
exitApplicationFromFini.test: $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) $(OBJDIR)exitFromFini_app exitApplicationFromFini.tested exitApplicationFromFini.failed
	-$(PIN) -logfile $(OBJDIR)exitApplicationFromFini.log \
	  -xyzzy -enable_vsm 1 -mesgon log_vsm -mesgon log_depot \
	  -t $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) -scenario 3 \
	  -startsfile $(OBJDIR)threadStarts_exitApplicationFromFini.out \
	  -finisfile $(OBJDIR)threadFinis_exitApplicationFromFini.out \
	    -- $(OBJDIR)exitFromFini_app 3 > $(OBJDIR)exitApplicationFromFini.out 2>&1;
	grep -q "It is prohibited to call PIN_ExitApplication() from an application-fini function" \
	  $(OBJDIR)exitApplicationFromFini.out
	rm exitApplicationFromFini.failed $(OBJDIR)exitApplicationFromFini.out $(OBJDIR)exitApplicationFromFini.log
	rm $(OBJDIR)threadStarts_exitApplicationFromFini.out $(OBJDIR)threadFinis_exitApplicationFromFini.out

exitProcessFromRunningThreadFini.test: $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) $(OBJDIR)exitFromFini_app exitProcessFromRunningThreadFini.tested exitProcessFromRunningThreadFini.failed
	$(PIN) -logfile $(OBJDIR)exitProcessFromRunningThreadFini.log \
	  -xyzzy -enable_vsm 1 -mesgon log_vsm -mesgon log_depot \
	  -t $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) -scenario 4 \
	  -startsfile $(OBJDIR)threadStarts_exitProcessFromRunningThreadFini.out \
	  -finisfile $(OBJDIR)threadFinis_exitProcessFromRunningThreadFini.out \
	    -- $(OBJDIR)exitFromFini_app 4 > $(OBJDIR)exitProcessFromRunningThreadFini.out 2>&1;
	test `cat $(OBJDIR)threadStarts_exitProcessFromRunningThreadFini.out | wc -l` -eq 2
	test `cat $(OBJDIR)threadFinis_exitProcessFromRunningThreadFini.out | wc -l` -eq 1
	rm exitProcessFromRunningThreadFini.failed $(OBJDIR)exitProcessFromRunningThreadFini.out
	rm $(OBJDIR)exitProcessFromRunningThreadFini.log
	rm $(OBJDIR)threadStarts_exitProcessFromRunningThreadFini.out $(OBJDIR)threadFinis_exitProcessFromRunningThreadFini.out

exitProcessFromBlockedThreadFini.test: $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) $(OBJDIR)exitFromFini_app exitProcessFromBlockedThreadFini.tested exitProcessFromBlockedThreadFini.failed
	$(PIN) -logfile $(OBJDIR)exitProcessFromBlockedThreadFini.log \
	  -xyzzy -enable_vsm 1 -mesgon log_vsm -mesgon log_depot \
	  -t $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) -scenario 5 \
	  -startsfile $(OBJDIR)threadStarts_exitProcessFromBlockedThreadFini.out \
	  -finisfile $(OBJDIR)threadFinis_exitProcessFromBlockedThreadFini.out \
	    -- $(OBJDIR)exitFromFini_app 5 > $(OBJDIR)exitProcessFromBlockedThreadFini.out 2>&1;
	sort $(OBJDIR)threadStarts_exitProcessFromBlockedThreadFini.out > \
	  $(OBJDIR)threadStarts_exitProcessFromBlockedThreadFini.sorted
	sort $(OBJDIR)threadFinis_exitProcessFromBlockedThreadFini.out > \
	  $(OBJDIR)threadFinis_exitProcessFromBlockedThreadFini.sorted
	$(PIN_DIFF) $(OBJDIR)threadStarts_exitProcessFromBlockedThreadFini.sorted \
	  $(OBJDIR)threadFinis_exitProcessFromBlockedThreadFini.sorted
	rm exitProcessFromBlockedThreadFini.failed $(OBJDIR)exitProcessFromBlockedThreadFini.out
	rm $(OBJDIR)exitProcessFromBlockedThreadFini.log
	rm $(OBJDIR)threadStarts_exitProcessFromBlockedThreadFini.* $(OBJDIR)threadFinis_exitProcessFromBlockedThreadFini.*

exitProcessFromFini.test: $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) $(OBJDIR)exitFromFini_app exitProcessFromFini.tested exitProcessFromFini.failed
	$(PIN) -logfile $(OBJDIR)exitProcessFromFini.log \
	  -xyzzy -enable_vsm 1 -mesgon log_vsm -mesgon log_depot \
	  -t $(OBJDIR)exitFromFini_tool$(PINTOOL_SUFFIX) -scenario 6 \
	  -startsfile $(OBJDIR)threadStarts_exitProcessFromFini.out \
	  -finisfile $(OBJDIR)threadFinis_exitProcessFromFini.out \
	    -- $(OBJDIR)exitFromFini_app 6 > $(OBJDIR)exitProcessFromFini.out 2>&1;
	sort $(OBJDIR)threadStarts_exitProcessFromFini.out > $(OBJDIR)threadStarts_exitProcessFromFini.sorted
	sort $(OBJDIR)threadFinis_exitProcessFromFini.out > $(OBJDIR)threadFinis_exitProcessFromFini.sorted
	$(PIN_DIFF) $(OBJDIR)threadStarts_exitProcessFromFini.sorted $(OBJDIR)threadFinis_exitProcessFromFini.sorted
	rm exitProcessFromFini.failed $(OBJDIR)exitProcessFromFini.out $(OBJDIR)exitProcessFromFini.log
	rm $(OBJDIR)threadStarts_exitProcessFromFini.* $(OBJDIR)threadFinis_exitProcessFromFini.*

exitApplicationLocked.test: $(OBJDIR)exitApplicationLocked_tool$(PINTOOL_SUFFIX) $(OBJDIR)exitApplicationLocked_app exitApplicationLocked.tested exitApplicationLocked.failed
	-$(PIN) -logfile $(OBJDIR)exitApplicationLocked.log \
	  -xyzzy -enable_vsm 1 -mesgon log_vsm -mesgon log_depot \
	  -t $(OBJDIR)exitApplicationLocked_tool$(PINTOOL_SUFFIX) \
	  -startsfile $(OBJDIR)threadStarts_exitApplicationLocked.out \
	  -finisfile $(OBJDIR)threadFinis_exitApplicationLocked.out \
	    -- $(OBJDIR)exitApplicationLocked_app > $(OBJDIR)exitApplicationLocked.out 2>&1
	grep -q "fini function 0 2" $(OBJDIR)exitApplicationLocked.out
	sort $(OBJDIR)threadStarts_exitApplicationLocked.out > $(OBJDIR)threadStarts_exitApplicationLocked.sorted
	sort $(OBJDIR)threadFinis_exitApplicationLocked.out > $(OBJDIR)threadFinis_exitApplicationLocked.sorted
	$(PIN_DIFF) $(OBJDIR)threadStarts_exitApplicationLocked.sorted $(OBJDIR)threadFinis_exitApplicationLocked.sorted
	rm exitApplicationLocked.failed $(OBJDIR)exitApplicationLocked.out $(OBJDIR)exitApplicationLocked.log
	rm $(OBJDIR)threadStarts_exitApplicationLocked.* $(OBJDIR)threadFinis_exitApplicationLocked.*


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
$(OBJDIR)threadFini_app: threadFini_app.cpp threadUtils.h $(OBJDIR)threadUtils.$(OBJEXT)
	${CXX} $(APP_CXXFLAGS) ${OUTEXE}$@ $< $(OBJDIR)threadUtils.$(OBJEXT) $(THREADLIB)

$(OBJDIR)threadFini_sig_app: threadFini_sig_app.cpp threadUtils.h $(OBJDIR)threadUtils.$(OBJEXT)
	${CXX} $(APP_CXXFLAGS) ${OUTOPT}$@ $< $(OBJDIR)threadUtils.$(OBJEXT) $(THREADLIB)

$(OBJDIR)threadFini_sendsig: threadFini_sendsig.cpp
	${CXX} $(APP_CXXFLAGS) ${OUTOPT}$@ $<

$(OBJDIR)threadFini_exception_app: threadFini_exception_app.cpp threadUtils.h $(OBJDIR)threadUtils.$(OBJEXT)
	${CXX} $(APP_CXXFLAGS) ${OUTEXE}$@ $< $(OBJDIR)threadUtils.$(OBJEXT) $(THREADLIB)

$(OBJDIR)raceToExit_app: raceToExit_app.cpp threadUtils.h $(OBJDIR)threadUtils.$(OBJEXT)
	${CXX} $(APP_CXXFLAGS) ${OUTEXE}$@ $< $(OBJDIR)threadUtils.$(OBJEXT) $(THREADLIB)

$(OBJDIR)raceToEnterVm_app: raceToEnterVm_app.cpp
	${CXX} $(APP_CXXFLAGS) ${OUTEXE}$@ $<

$(OBJDIR)exitFromFini_app: exitFromFini_app.cpp threadUtils.h $(OBJDIR)threadUtils.$(OBJEXT)
	${CXX} $(APP_CXXFLAGS) ${OUTEXE}$@ $< $(OBJDIR)threadUtils.$(OBJEXT) $(THREADLIB)

$(OBJDIR)exitApplicationLocked_app: exitApplicationLocked_app.cpp threadUtils.h $(OBJDIR)threadUtils.$(OBJEXT)
	${CXX} $(APP_CXXFLAGS) ${OUTEXE}$@ $< $(OBJDIR)threadUtils.$(OBJEXT) $(THREADLIB)

$(OBJDIR)threadUtils.$(OBJEXT): threadUtils_$(TARGET_OS).cpp threadUtils.h
	$(CXX) ${COPT} $(APP_CXXFLAGS) ${OUTOPT}$@ $<
