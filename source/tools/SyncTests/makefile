##
## Tests for the synchronization primitives.
##

TARGET_COMPILER?=gnu
ifdef OS
    ifeq (${OS},Windows_NT)
        TARGET_COMPILER=ms
    endif
endif

include ../makefile.$(TARGET_COMPILER).config



APPS_u          = mt-worker-posix
APPS_l          = rt-locks-app
APPS_w          = mt-worker-windows
APPS_x86_lw     = 
APPS_x86_l      = 
APPS_ia32_l     = 
APPS_ia32e_l    = 
APPS_x86_w      = 

TOOLS           = lock-tester
TOOLS_l         = rt-locks-tool
TOOLS_x86_lw    = 
TOOLS_x86_l     = 
TOOLS_ia32_l    = 
TOOLS_ia32e_l   = 

TESTS           = lock-integrity lock-stress mutex-integrity mutex-stress mutex-trystress \
                  writer-integrity writer-stress writer-trystress reader-stress reader-trystress \
                  rw-integrity rw-stress rw-trystress semaphore trylocks
TESTS_l         = rt-locks
TESTS_x86_lw    = 
TESTS_x86_l     = 
TESTS_ia32_l    = 
TESTS_ia32e_l   = 
TESTS_ia32_lw   = 
TESTS_x86_w     = 


apps_ia32_l    = $(APPS) $(APPS_u) $(APPS_l) $(APPS_lw) $(APPS_x86) $(APPS_x86_l) $(APPS_x86_lw) $(APPS_ia32) $(APPS_ia32_l) $(APPS_ia32_lw)
apps_ia32e_l   = $(APPS) $(APPS_u) $(APPS_l) $(APPS_lw) $(APPS_x86) $(APPS_x86_l) $(APPS_x86_lw) $(APPS_ia32e) $(APPS_ia32e_l) $(APPS_ia32e_lw)
apps_ipf_l     = $(APPS) $(APPS_u) $(APPS_l) $(APPS_ipf) $(APPS_ipf_l)
apps_ia32_w    = $(APPS) $(APPS_w) $(APPS_lw) $(APPS_x86) $(APPS_x86_w) $(APPS_x86_lw) $(APPS_ia32) $(APPS_ia32_w) $(APPS_ia32_lw)
apps_ia32e_w   = $(APPS) $(APPS_w) $(APPS_lw) $(APPS_x86) $(APPS_x86_w) $(APPS_x86_lw) $(APPS_ia32e) $(APPS_ia32e_w) $(APPS_ia32e_lw)
apps_ia32_m    = $(APPS) $(APPS_u) $(APPS_m) $(APPS_x86) $(APPS_x86_m) $(APPS_ia32) $(APPS_ia32_m)
apps_ia32e_m   = $(APPS) $(APPS_u) $(APPS_m) $(APPS_x86) $(APPS_x86_m) $(APPS_ia32e) $(APPS_ia32e_m)
apps_ia32_b    = $(APPS) $(APPS_u) $(APPS_b) $(APPS_x86) $(APPS_x86_b) $(APPS_ia32) $(APPS_ia32_b)
apps_ia32e_b   = $(APPS) $(APPS_u) $(APPS_b) $(APPS_x86) $(APPS_x86_b) $(APPS_ia32e) $(APPS_ia32e_b)
tools_ia32_l   = $(TOOLS) $(TOOLS_u) $(TOOLS_l) $(TOOLS_lw) $(TOOLS_x86) $(TOOLS_x86_l) $(TOOLS_x86_lw) $(TOOLS_ia32) $(TOOLS_ia32_l) $(TOOLS_ia32_lw)
tools_ia32e_l  = $(TOOLS) $(TOOLS_u) $(TOOLS_l) $(TOOLS_lw) $(TOOLS_x86) $(TOOLS_x86_l) $(TOOLS_x86_lw) $(TOOLS_ia32e) $(TOOLS_ia32e_l) $(TOOLS_ia32e_lw)
tools_ipf_l    = $(TOOLS) $(TOOLS_u) $(TOOLS_l) $(TOOLS_ipf) $(TOOLS_ipf_l)
tools_ia32_w   = $(TOOLS) $(TOOLS_w) $(TOOLS_lw) $(TOOLS_x86) $(TOOLS_x86_w) $(TOOLS_x86_lw) $(TOOLS_ia32) $(TOOLS_ia32_w) $(TOOLS_ia32_lw)
tools_ia32e_w  = $(TOOLS) $(TOOLS_w) $(TOOLS_lw) $(TOOLS_x86) $(TOOLS_x86_w) $(TOOLS_x86_lw) $(TOOLS_ia32e) $(TOOLS_ia32e_w) $(TOOLS_ia32e_lw)
tools_ia32_m   = $(TOOLS) $(TOOLS_u) $(TOOLS_m) $(TOOLS_x86) $(TOOLS_x86_m) $(TOOLS_ia32) $(TOOLS_ia32_m)
tools_ia32e_m  = $(TOOLS) $(TOOLS_u) $(TOOLS_m) $(TOOLS_x86) $(TOOLS_x86_m) $(TOOLS_ia32e) $(TOOLS_ia32e_m)
tools_ia32_b   = $(TOOLS) $(TOOLS_u) $(TOOLS_b) $(TOOLS_x86) $(TOOLS_x86_b) $(TOOLS_ia32) $(TOOLS_ia32_b)
tools_ia32e_b  = $(TOOLS) $(TOOLS_u) $(TOOLS_b) $(TOOLS_x86) $(TOOLS_x86_b) $(TOOLS_ia32e) $(TOOLS_ia32e_b)
tests_ia32_l   = $(TESTS) $(TESTS_u) $(TESTS_l) $(TESTS_lw) $(TESTS_x86) $(TESTS_x86_l) $(TESTS_x86_lw) $(TESTS_ia32) $(TESTS_ia32_l) $(TESTS_ia32_lw)
tests_ia32e_l  = $(TESTS) $(TESTS_u) $(TESTS_l) $(TESTS_lw) $(TESTS_x86) $(TESTS_x86_l) $(TESTS_x86_lw) $(TESTS_ia32e) $(TESTS_ia32e_l) $(TESTS_ia32e_lw)
tests_ipf_l    = $(TESTS) $(TESTS_u) $(TESTS_l) $(TESTS_ipf) $(TESTS_ipf_l)
tests_ia32_w   = $(TESTS) $(TESTS_w) $(TESTS_lw) $(TESTS_x86) $(TESTS_x86_w) $(TESTS_x86_lw) $(TESTS_ia32) $(TESTS_ia32_w) $(TESTS_ia32_lw)
tests_ia32e_w  = $(TESTS) $(TESTS_w) $(TESTS_lw) $(TESTS_x86) $(TESTS_x86_w) $(TESTS_x86_lw) $(TESTS_ia32e) $(TESTS_ia32e_w) $(TESTS_ia32e_lw)
tests_ia32_m   = $(TESTS) $(TESTS_u) $(TESTS_m) $(TESTS_x86) $(TESTS_x86_m) $(TESTS_ia32) $(TESTS_ia32_m)
tests_ia32e_m  = $(TESTS) $(TESTS_u) $(TESTS_m) $(TESTS_x86) $(TESTS_x86_m) $(TESTS_ia32e) $(TESTS_ia32e_m)
tests_ia32_b   = $(TESTS) $(TESTS_u) $(TESTS_b) $(TESTS_x86) $(TESTS_x86_b) $(TESTS_ia32) $(TESTS_ia32_b)
tests_ia32e_b  = $(TESTS) $(TESTS_u) $(TESTS_b) $(TESTS_x86) $(TESTS_x86_b) $(TESTS_ia32e) $(TESTS_ia32e_b)

apps   = $(apps_$(TARGET)_$(TARGET_OS))
tools  = $(tools_$(TARGET)_$(TARGET_OS))
tests  = $(tests_$(TARGET)_$(TARGET_OS)) dummy


# An application that calls the function "InstrumentedWithPin()" in a loop simultaneously
# by many threads.  This is shared by several tests.
#
MT_WORKER_APP = $(MT_WORKER_APP_$(TARGET_OS))
MT_WORKER_APP_l = $(OBJDIR)mt-worker-posix
MT_WORKER_APP_m = $(OBJDIR)mt-worker-posix
MT_WORKER_APP_b = $(OBJDIR)mt-worker-posix
MT_WORKER_APP_w = $(OBJDIR)mt-worker-windows$(EXEEXT)



all: $(apps:%=$(OBJDIR)%$(EXEEXT)) $(tools:%=$(OBJDIR)%$(PINTOOL_SUFFIX))
test: $(OBJDIR)
	-$(MAKE) run_test
run_test: $(tests:=.test)

ifeq ($(TARGET_OS),b)
tests-sanity:
else
tests-sanity: test
endif

$(apps:%=$(OBJDIR)%$(EXEEXT)) $(tools:%=$(OBJDIR)%$(PINTOOL_SUFFIX)): $(OBJDIR)make-directory

$(OBJDIR)make-directory:
	mkdir -p $(OBJDIR)
	touch  $(OBJDIR)make-directory
$(OBJDIR):
	mkdir -p $(OBJDIR)


#
# Rules to build the applications
#
$(OBJDIR)mt-worker-posix: mt-worker-posix.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(OUTOPT)$@ $< $(APP_PTHREAD) -latomic

$(OBJDIR)mt-worker-windows$(EXEEXT): $(OBJDIR)mt-worker-windows.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(OUTEXE)$@ $< $(APP_LIB_ATOMIC)
$(OBJDIR)mt-worker-windows.$(OBJEXT): $(OBJDIR)make-directory mt-worker-windows.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(OUTOPT)$@ mt-worker-windows.cpp

$(OBJDIR)rt-locks-app: rt-locks-app.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(OUTOPT)$@ $< $(APP_PTHREAD)

#
# Rules to build the tool object files
#
$(OBJDIR)%.$(OBJEXT): %.cpp $(OBJDIR)make-directory
	$(CXX) $(COPT) $(CXXFLAGS) $(PIN_CXXFLAGS) $(OUTOPT)$@ $<

#
# Rules to build the tools
#
$(OBJDIR)rt-locks-tool$(PINTOOL_SUFFIX): $(OBJDIR)rt-locks-tool.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)lock-tester$(PINTOOL_SUFFIX): $(OBJDIR)lock-tester.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)


#
# Rules to run the tests.
#

# Test that PIN_LOCK works when using real-time scheduling on Linux.
#
rt-locks.test: $(OBJDIR)rt-locks-app $(OBJDIR)rt-locks-tool$(PINTOOL_SUFFIX) $(OBJDIR)rt-locks.tested $(OBJDIR)rt-locks.failed
	$(PIN) -t $(OBJDIR)rt-locks-tool$(PINTOOL_SUFFIX) -- $(OBJDIR)rt-locks-app
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_LOCK to see if two threads can be in the mutex simultaneously.
#
lock-integrity.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)lock-integrity.tested $(OBJDIR)lock-integrity.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_LOCK to see if we miss a wakeup and cause a deadlock.
#
lock-stress.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)lock-stress.tested $(OBJDIR)lock-stress.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_MUTEX to see if two threads can be in the mutex simultaneously.
#
mutex-integrity.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)mutex-integrity.tested $(OBJDIR)mutex-integrity.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_MUTEX to see if we miss a wakeup and cause a deadlock.
#
mutex-stress.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)mutex-stress.tested $(OBJDIR)mutex-stress.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_MUTEX when acquiring via "try".
#
mutex-trystress.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)mutex-trystress.tested $(OBJDIR)mutex-trystress.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_RWMUTEX to see if two writer threads can be in the rwmutex simultaneously.
#
writer-integrity.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)writer-integrity.tested $(OBJDIR)writer-integrity.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_RWMUTEX to see if we miss a wakeup and cause a deadlock when
# there are multiple writer threads contending on the lock.
#
writer-stress.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)writer-stress.tested $(OBJDIR)writer-stress.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_RWMUTEX when acquiring via "try".
#
writer-trystress.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)writer-trystress.tested $(OBJDIR)writer-trystress.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_RWMUTEX when readers acquire the lock as fast as possible.
#
reader-stress.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)reader-stress.tested $(OBJDIR)reader-stress.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_RWMUTEX when there are only readers trying to acquire with "try".
#
reader-trystress.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)reader-trystress.tested $(OBJDIR)reader-trystress.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_RWMUTEX to see if a writer can hold the lock simultaneously with a reader.
#
rw-integrity.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)rw-integrity.tested $(OBJDIR)rw-integrity.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_RWMUTEX with many readers and writers contending on the lock.
#
rw-stress.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)rw-stress.tested $(OBJDIR)rw-stress.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_RWMUTEX with many readers and writers trying to acquire the lock via "try".
#
rw-trystress.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)rw-trystress.tested $(OBJDIR)rw-trystress.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Stress test for PIN_SEMAPHORE.
#
semaphore.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)semaphore.tested $(OBJDIR)semaphore.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP) -t 2
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test the various "try" operations on locks.
#
trylocks.test: $(MT_WORKER_APP) $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) $(OBJDIR)trylocks.tested $(OBJDIR)trylocks.failed
	$(PIN) -t $(OBJDIR)lock-tester$(PINTOOL_SUFFIX) -test $(@:.test=) -- $(MT_WORKER_APP) -t 1
	rm -f $(OBJDIR)$(@:.test=.failed)


dummy.test:


clean:
	rm -rf $(OBJDIR)
	rm -f pin.log
