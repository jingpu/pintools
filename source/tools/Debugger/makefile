##
## Tests to test the ability to debug the application while running with Pin.
##

TARGET_COMPILER?=gnu
ifdef OS
    ifeq (${OS},Windows_NT)
        TARGET_COMPILER=ms
    endif
endif

include ../makefile.$(TARGET_COMPILER).config
GDB = /usr/bin/gdb
GDB_MODERN = /usr/intel/pkgs/gdb/6.6/bin/gdb

# This is a time limit (in seconds) we use for some of the tests below.  It's intentionally high
# to avoid timeouts when the system load is very high, which can happen in our nightly tests.
#
TLIMIT=600


APPS_x86_lw     = simple-pindb simple
APPS_x86_l      = simple-static exec fork action-pending-app thread checkpoint-app watchpoint-app \
                  callerapp fibonacci sleep-unix intercept-app pc-change-bp pc-change-async \
                  mt-exit signal-catch reattach-loop pthread-bare-exit pthread-bare-exitgroup \
                  thread-posix
APPS_ia32_l     = bptest-ia32 xmm-ia32 debugger-shell-app-ia32 ymm-ia32
APPS_ia32e_l    = bptest-intel64 xmm-intel64 debugger-shell-app-intel64 ymm-intel64
APPS_x86_w      = win-unhandled-exception win-handled-exception win-continued-exception1 win-continued-exception2 \
                  win-software-exception win-cpp-exception win-load-library win-thread-stress thread-windows

SHLIBS_x86_w    = win-foo-library

TOOLS_x86_lw    = stack-debugger start-fini-callback simple-command-tool use-debugger-shell simultaneous-toolbreak
TOOLS_x86_l     = breaktool int3-count action-pending-tool checkpoint watchpoint launch-gdb-tool \
                  intercept-tool pc-change-async-tool interpreter-remove mt-exit-tool debugger-type set-mode-tool
TOOLS_ia32_l    = null-emulator-ia32
TOOLS_ia32e_l   = null-emulator-intel64

TESTS_x86_lw    = simple-pindb-launch pindb-start-fini pindb-noprompt-kill pindb-detach pindb-abrupt-disconnect \
                  pindb-kill-like-gdb pindb-simple-command pindb-step-custom-break pindb-simultaneous-toolbreak \
                  pindb-simultaneous-toolbreak-serialize pindb-simultaneous-toolbreak-squash \
                  pindb-simultaneous-toolbreak-change pindb-simultaneous-toolbreak-step pindb-simple-simultaneous-multi \
                  pindb-simple-simultaneous-multi-serialize
TESTS_x86_l     = simple execfail fork breaktool breaktool-wait breaktool-nodebugger bp-icount action-pending \
                  thread launch-gdb stack-debugger debugger-shell-breakpoints \
                  debugger-shell-tracepoints start-fini intercept-breakpoint emu-simple ymm pc-change-bp \
                  pc-change-async interpreter-remove mt-exit debugger-type signal-step siginfo \
                  pindb-attach-after-custom-stop allow-remote set-mode gdb-detach-reattach invalid-write \
                  pindb-pthread-step-exit gdb-pthread-step-exit pindb-pthread-cont-exitgroup simultaneous-toolbreak \
                  simultaneous-toolbreak-squash simultaneous-toolbreak-change simultaneous-toolbreak-attach \
                  pindb-simultaneous-multi pindb-simultaneous-multi-serialize pindb-simultaneous-toolbreak-attach
TESTS_ia32_l    = bptest-ia32 xmm-ia32
TESTS_ia32e_l   = bptest-intel64 xmm-intel64
TESTS_ia32_lw   = access-64-on-32
TESTS_x86_w     = pindb-win-unhandled-exception pindb-win-handled-exception pindb-win-continued-exception1 \
                  pindb-win-continued-exception2 pindb-win-software-exception pindb-win-cpp-exception \
                  pindb-win-squash-exception pindb-win-step-exception pindb-win-library-notifications \
                  pindb-win-step-library pindb-win-thread-stress


apps_ia32_l    = $(APPS) $(APPS_l) $(APPS_lw) $(APPS_x86) $(APPS_x86_l) $(APPS_x86_lw) $(APPS_ia32) $(APPS_ia32_l) $(APPS_ia32_lw)
apps_ia32e_l   = $(APPS) $(APPS_l) $(APPS_lw) $(APPS_x86) $(APPS_x86_l) $(APPS_x86_lw) $(APPS_ia32e) $(APPS_ia32e_l) $(APPS_ia32e_lw)
apps_ia32_w    = $(APPS) $(APPS_w) $(APPS_lw) $(APPS_x86) $(APPS_x86_w) $(APPS_x86_lw) $(APPS_ia32) $(APPS_ia32_w) $(APPS_ia32_lw)
apps_ia32e_w   = $(APPS) $(APPS_w) $(APPS_lw) $(APPS_x86) $(APPS_x86_w) $(APPS_x86_lw) $(APPS_ia32e) $(APPS_ia32e_w) $(APPS_ia32e_lw)
shlibs_ia32_l  = $(SHLIBS) $(SHLIBS_l) $(SHLIBS_lw) $(SHLIBS_x86) $(SHLIBS_x86_l) $(SHLIBS_x86_lw) $(SHLIBS_ia32) $(SHLIBS_ia32_l) $(SHLIBS_ia32_lw)
shlibs_ia32e_l = $(SHLIBS) $(SHLIBS_l) $(SHLIBS_lw) $(SHLIBS_x86) $(SHLIBS_x86_l) $(SHLIBS_x86_lw) $(SHLIBS_ia32e) $(SHLIBS_ia32e_l) $(SHLIBS_ia32e_lw)
shlibs_ia32_w  = $(SHLIBS) $(SHLIBS_w) $(SHLIBS_lw) $(SHLIBS_x86) $(SHLIBS_x86_w) $(SHLIBS_x86_lw) $(SHLIBS_ia32) $(SHLIBS_ia32_w) $(SHLIBS_ia32_lw)
shlibs_ia32e_w = $(SHLIBS) $(SHLIBS_w) $(SHLIBS_lw) $(SHLIBS_x86) $(SHLIBS_x86_w) $(SHLIBS_x86_lw) $(SHLIBS_ia32e) $(SHLIBS_ia32e_w) $(SHLIBS_ia32e_lw)
tools_ia32_l   = $(TOOLS) $(TOOLS_l) $(TOOLS_lw) $(TOOLS_x86) $(TOOLS_x86_l) $(TOOLS_x86_lw) $(TOOLS_ia32) $(TOOLS_ia32_l) $(TOOLS_ia32_lw)
tools_ia32e_l  = $(TOOLS) $(TOOLS_l) $(TOOLS_lw) $(TOOLS_x86) $(TOOLS_x86_l) $(TOOLS_x86_lw) $(TOOLS_ia32e) $(TOOLS_ia32e_l) $(TOOLS_ia32e_lw)
tools_ia32_w   = $(TOOLS) $(TOOLS_w) $(TOOLS_lw) $(TOOLS_x86) $(TOOLS_x86_w) $(TOOLS_x86_lw) $(TOOLS_ia32) $(TOOLS_ia32_w) $(TOOLS_ia32_lw)
tools_ia32e_w  = $(TOOLS) $(TOOLS_w) $(TOOLS_lw) $(TOOLS_x86) $(TOOLS_x86_w) $(TOOLS_x86_lw) $(TOOLS_ia32e) $(TOOLS_ia32e_w) $(TOOLS_ia32e_lw)
tests_ia32_l   = $(TESTS) $(TESTS_l) $(TESTS_lw) $(TESTS_x86) $(TESTS_x86_l) $(TESTS_x86_lw) $(TESTS_ia32) $(TESTS_ia32_l) $(TESTS_ia32_lw)
tests_ia32e_l  = $(TESTS) $(TESTS_l) $(TESTS_lw) $(TESTS_x86) $(TESTS_x86_l) $(TESTS_x86_lw) $(TESTS_ia32e) $(TESTS_ia32e_l) $(TESTS_ia32e_lw)
tests_ia32_w   = $(TESTS) $(TESTS_w) $(TESTS_lw) $(TESTS_x86) $(TESTS_x86_w) $(TESTS_x86_lw) $(TESTS_ia32) $(TESTS_ia32_w) $(TESTS_ia32_lw)
tests_ia32e_w  = $(TESTS) $(TESTS_w) $(TESTS_lw) $(TESTS_x86) $(TESTS_x86_w) $(TESTS_x86_lw) $(TESTS_ia32e) $(TESTS_ia32e_w) $(TESTS_ia32e_lw)

apps   = $(apps_$(TARGET)_$(TARGET_OS))
shlibs = $(shlibs_$(TARGET)_$(TARGET_OS))
tools  = $(tools_$(TARGET)_$(TARGET_OS))
tests  = $(tests_$(TARGET)_$(TARGET_OS)) dummy


# There is a bug in some 2.4 kernels that prevents Pin's debugger feature from
# working in cross-mode (32-bit application running on a 64-bit host).
# Disable testing in this case.  See Mantis #1414 for more details.
#
osrel = $(shell uname -r)
ifeq ($(findstring 2.4,$(osrel))-$(HOST_ARCH)-$(TARGET),2.4-ia32e-ia32)
  tests = 
endif

ifeq ($(findstring WR,$(osrel)),WR)
  tests =
endif

# There is a bug in the GDB installed on Redhat 9 (and probably previous versions too) which prevents debugging of MT
# programs with Pin.  Use a modern GDB version instead.
#
redhat = $(shell test -f /etc/redhat-release && cat /etc/redhat-release)
ifeq ($(findstring release 9,$(redhat)),release 9)
  GDB = $(GDB_MODERN)
endif

# The GDB on FC13 has a general problem with remote debugging.  See Mantis #2206 for details.  Use the /user/intel
# version until it is fixed.  We should remove this when there is a patch to FC13.
#
ifeq ($(findstring Fedora release 13,$(redhat)),Fedora release 13)
  GDB = $(GDB_MODERN)
endif

# These two tests trigger a compiler bug when building on 32-bit Windows with ICC versions 11.x.  It's difficult
# to disable the tests only for those compiler versions, so we disable them whenever we build with ICC.  These
# lines should be removed when we migrate to ICC 12.x.  See Mantis #2444.
#
ifeq ($(TARGET)-$(TARGET_OS),ia32-w)
  ifneq ($(ICC),)
    tests := $(tests:pindb-win-continued-exception1=)
    tests := $(tests:pindb-win-continued-exception2=)
  endif
endif

# There is a bug with PinADX when using early-injection (the default) on 32-bit applications when running
# on a 64-bit host and when using versions of Windows earlier than Vista.  That bug causes this test to
# fail, so we disable it in this case.  We can re-enable this test when Mantis #2385 is fixed.
#
osname = $(shell uname -s)
ifeq ($(findstring CYGWIN_NT-5,$(osname))-$(HOST_ARCH)-$(TARGET),CYGWIN_NT-5-ia32e-ia32)
  tests := $(tests:pindb-start-fini=)
endif

# Versions of gdb older than 6.6 do not understand the XMM registers, so disable the xmm tests.
#
GDB_VERSION_IF_BEFORE_66 = $(shell $(GDB) --version | head -1 | egrep -o "[6]\.[2-5]+")
ifneq ($(GDB_VERSION_IF_BEFORE_66),"")
  tests := $(tests:xmm-ia32=)
  tests := $(tests:xmm-intel64=)
endif


# These are the Pin flags needed to enable application debugging.
#
PINFLAGS_DEBUG = -appdebug
PINFLAGS_DEBUG_RUNFREE = -appdebug_enable

# A simple threaded application that we use for several tests.  Both Windows and Posix
# versions export the function "GlobalFunction()", which the tests rely on.
#
THREAD_APP = $(THREAD_APP_$(TARGET_OS))
THREAD_APP_l = $(OBJDIR)thread-posix
THREAD_APP_w = $(OBJDIR)thread-windows$(EXEEXT)


all: $(apps:%=$(OBJDIR)%$(EXEEXT)) $(shlibs:%=$(OBJDIR)%$(SHLIBEXT)) $(tools:%=$(OBJDIR)%$(PINTOOL_SUFFIX))
test: $(OBJDIR)
	-$(MAKE) run_test
run_test: $(tests:=.test)
tests-sanity: test

$(apps:%=$(OBJDIR)%$(EXEEXT)) $(shlibs:%=$(OBJDIR)%$(SHLIBEXT)) $(tools:%=$(OBJDIR)%$(PINTOOL_SUFFIX)): $(OBJDIR)make-directory

$(OBJDIR)make-directory:
	mkdir -p $(OBJDIR)
	touch  $(OBJDIR)make-directory
$(OBJDIR):
	mkdir -p $(OBJDIR)


#
# Rules to build the applications
#
$(OBJDIR)simple$(EXEEXT): $(OBJDIR)simple.$(OBJEXT)
	$(APP_CC) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)simple.$(OBJEXT)
$(OBJDIR)simple.$(OBJEXT): $(OBJDIR)make-directory simple.c
	$(APP_CC) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ simple.c

$(OBJDIR)simple-static: simple.c
	$(APP_CC) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) -static $(OUTOPT)$@ $<

$(OBJDIR)exec: exec.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $<

$(OBJDIR)fork: fork.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $<

$(OBJDIR)bptest-ia32: bptest.cpp bptest-asm-ia32.s
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ bptest.cpp bptest-asm-ia32.s

$(OBJDIR)bptest-intel64: bptest.cpp bptest-asm-intel64.s
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ bptest.cpp bptest-asm-intel64.s

$(OBJDIR)action-pending-app: action-pending-app.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $< $(APP_PTHREAD)

$(OBJDIR)xmm-ia32: xmm.c xmm-asm-ia32.s
	$(APP_CC) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ xmm.c xmm-asm-ia32.s

$(OBJDIR)xmm-intel64: xmm.c xmm-asm-intel64.s
	$(APP_CC) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ xmm.c xmm-asm-intel64.s

$(OBJDIR)thread: thread.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $< $(APP_PTHREAD)

$(OBJDIR)thread-static: thread.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) -static $(OUTOPT)$@ $< $(APP_PTHREAD)

$(OBJDIR)simple-pindb$(EXEEXT): $(OBJDIR)simple-pindb.$(OBJEXT) $(OBJDIR)simple-pindb-asm-$(TARGET_OS_LONG)-$(TARGET_LONG).$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)simple-pindb.$(OBJEXT) $(OBJDIR)simple-pindb-asm-$(TARGET_OS_LONG)-$(TARGET_LONG).$(OBJEXT) $(APP_CXXLINK_FLAGS_NORANDOM)
$(OBJDIR)simple-pindb.$(OBJEXT): $(OBJDIR)make-directory simple-pindb.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ simple-pindb.cpp
$(OBJDIR)simple-pindb-asm-windows-$(TARGET_LONG).$(OBJEXT): $(OBJDIR)make-directory simple-pindb-asm-windows-$(TARGET_LONG).asm
	$(MASM) /nologo /c /Fo$@ simple-pindb-asm-windows-$(TARGET_LONG).asm
$(OBJDIR)simple-pindb-asm-linux-$(TARGET_LONG).$(OBJEXT): $(OBJDIR)make-directory simple-pindb-asm-linux-$(TARGET_LONG).s
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ simple-pindb-asm-linux-$(TARGET_LONG).s

$(OBJDIR)checkpoint-app: checkpoint-app.c
	$(APP_CC) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $<

$(OBJDIR)watchpoint-app: watchpoint-app.c
	$(APP_CC) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $<

$(OBJDIR)callerapp: callerapp.c
	$(APP_CC) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $<

$(OBJDIR)fibonacci: ../ManualExamples/fibonacci.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $<

$(OBJDIR)sleep-unix: sleep-unix.c
	$(APP_CC) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $<

$(OBJDIR)debugger-shell-app-$(TARGET_LONG): debugger-shell-app.cpp debugger-shell-app-$(TARGET_LONG).s
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ debugger-shell-app.cpp debugger-shell-app-$(TARGET_LONG).s

$(OBJDIR)intercept-app: intercept-app.cpp intercept-app-asm-$(TARGET_LONG).s
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ intercept-app.cpp intercept-app-asm-$(TARGET_LONG).s

$(OBJDIR)ymm-$(TARGET_LONG): ymm.cpp ymm-asm-$(TARGET_LONG).s
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ ymm.cpp ymm-asm-$(TARGET_LONG).s

$(OBJDIR)pc-change-bp: pc-change-bp.cpp pc-change-bp-asm-$(TARGET_LONG).s
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ pc-change-bp.cpp pc-change-bp-asm-$(TARGET_LONG).s

$(OBJDIR)pc-change-async: pc-change-async.cpp pc-change-async-asm-$(TARGET_LONG).s
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ pc-change-async.cpp pc-change-async-asm-$(TARGET_LONG).s $(APP_PTHREAD)

$(OBJDIR)mt-exit: mt-exit.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $< $(APP_PTHREAD)

$(OBJDIR)signal-catch: signal-catch.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $<

$(OBJDIR)win-unhandled-exception$(EXEEXT): $(OBJDIR)win-unhandled-exception.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)win-unhandled-exception.$(OBJEXT)
$(OBJDIR)win-unhandled-exception.$(OBJEXT): $(OBJDIR)make-directory win-unhandled-exception.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ win-unhandled-exception.cpp

$(OBJDIR)win-handled-exception$(EXEEXT): $(OBJDIR)win-handled-exception.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)win-handled-exception.$(OBJEXT)
$(OBJDIR)win-handled-exception.$(OBJEXT): $(OBJDIR)make-directory win-handled-exception.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ win-handled-exception.cpp

$(OBJDIR)win-continued-exception1$(EXEEXT): $(OBJDIR)win-continued-exception1.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)win-continued-exception1.$(OBJEXT)
$(OBJDIR)win-continued-exception1.$(OBJEXT): $(OBJDIR)make-directory win-continued-exception1.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ win-continued-exception1.cpp

$(OBJDIR)win-continued-exception2$(EXEEXT): $(OBJDIR)win-continued-exception2.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)win-continued-exception2.$(OBJEXT)
$(OBJDIR)win-continued-exception2.$(OBJEXT): $(OBJDIR)make-directory win-continued-exception2.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ win-continued-exception2.cpp

$(OBJDIR)win-software-exception$(EXEEXT): $(OBJDIR)win-software-exception.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)win-software-exception.$(OBJEXT)
$(OBJDIR)win-software-exception.$(OBJEXT): $(OBJDIR)make-directory win-software-exception.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ win-software-exception.cpp

$(OBJDIR)win-cpp-exception$(EXEEXT): $(OBJDIR)win-cpp-exception.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)win-cpp-exception.$(OBJEXT)
$(OBJDIR)win-cpp-exception.$(OBJEXT): $(OBJDIR)make-directory win-cpp-exception.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ win-cpp-exception.cpp

$(OBJDIR)win-load-library$(EXEEXT): $(OBJDIR)win-load-library.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)win-load-library.$(OBJEXT)
$(OBJDIR)win-load-library.$(OBJEXT): $(OBJDIR)make-directory win-load-library.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ win-load-library.cpp

$(OBJDIR)win-foo-library$(SHLIBEXT): $(OBJDIR)win-foo-library.$(OBJEXT)
	$(SHLINK) $(APP_SHLINKFLAGS) $(APP_SHLINK_DBG_ALWAYS) $(LINK_OUT)$@ $(OBJDIR)win-foo-library.$(OBJEXT)
$(OBJDIR)win-foo-library.$(OBJEXT): $(OBJDIR)make-directory win-foo-library.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ win-foo-library.cpp

$(OBJDIR)reattach-loop: reattach-loop.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $<

$(OBJDIR)win-thread-stress$(EXEEXT): $(OBJDIR)win-thread-stress.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)win-thread-stress.$(OBJEXT)
$(OBJDIR)win-thread-stress.$(OBJEXT): $(OBJDIR)make-directory win-thread-stress.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ win-thread-stress.cpp

$(OBJDIR)pthread-bare-exit: pthread-bare-exit.cpp pthread-bare-exit-asm-$(TARGET_LONG).s
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ pthread-bare-exit.cpp pthread-bare-exit-asm-$(TARGET_LONG).s -lpthread

$(OBJDIR)pthread-bare-exitgroup: pthread-bare-exitgroup.cpp pthread-bare-exitgroup-asm-$(TARGET_LONG).s
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ pthread-bare-exitgroup.cpp pthread-bare-exitgroup-asm-$(TARGET_LONG).s -lpthread

$(OBJDIR)thread-posix$(EXEEXT): thread-posix.cpp
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ $< $(APP_PTHREAD)

$(OBJDIR)thread-windows$(EXEEXT): $(OBJDIR)thread-windows.$(OBJEXT)
	$(APP_CXX) $(DBG) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTEXE)$@ $(OBJDIR)thread-windows.$(OBJEXT) $(APP_CXXLINK_FLAGS_NORANDOM)
$(OBJDIR)thread-windows.$(OBJEXT): $(OBJDIR)make-directory thread-windows.cpp
	$(APP_CXX) $(DBG) $(COPT) $(APP_CXXFLAGS) $(DBG_INFO_ALWAYS) $(OUTOPT)$@ thread-windows.cpp

#
# Rules to build the object files
#
$(OBJDIR)%.$(OBJEXT): %.cpp $(OBJDIR)make-directory
	$(CXX) $(COPT) $(CXXFLAGS) $(PIN_CXXFLAGS) $(OUTOPT)$@ $<
$(OBJDIR)stack-debugger.$(OBJEXT): ../ManualExamples/stack-debugger.cpp $(OBJDIR)make-directory
	$(CXX) $(COPT) $(CXXFLAGS) $(PIN_CXXFLAGS) $(OUTOPT)$@ $<
$(OBJDIR)debugger-shell.$(OBJEXT): ../InstLib/debugger-shell.cpp $(OBJDIR)make-directory
	$(CXX) $(COPT) $(CXXFLAGS) $(PIN_CXXFLAGS) $(OUTOPT)$@ $<
$(OBJDIR)start-fini-callback.$(OBJEXT): start-fini-callback.cpp $(OBJDIR)make-directory
	$(CXX) $(COPT) $(CXXFLAGS) $(PIN_CXXFLAGS) $(OUTOPT)$@ $<

#
# Rules to build the tools
#
$(OBJDIR)breaktool$(PINTOOL_SUFFIX): $(OBJDIR)breaktool.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)int3-count$(PINTOOL_SUFFIX): $(OBJDIR)int3-count.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)action-pending-tool$(PINTOOL_SUFFIX): $(OBJDIR)action-pending-tool.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)checkpoint$(PINTOOL_SUFFIX): $(OBJDIR)checkpoint.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)watchpoint$(PINTOOL_SUFFIX): $(OBJDIR)watchpoint.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)launch-gdb-tool$(PINTOOL_SUFFIX): $(OBJDIR)launch-gdb-tool.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)stack-debugger$(PINTOOL_SUFFIX): $(OBJDIR)stack-debugger.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)use-debugger-shell$(PINTOOL_SUFFIX): $(OBJDIR)use-debugger-shell.$(OBJEXT) $(OBJDIR)debugger-shell.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $(OBJDIR)use-debugger-shell.$(OBJEXT) $(OBJDIR)debugger-shell.$(OBJEXT) $(PIN_LIBS)

$(OBJDIR)start-fini-callback$(PINTOOL_SUFFIX): $(OBJDIR)start-fini-callback.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $(OBJDIR)start-fini-callback.$(OBJEXT) $(PIN_LIBS)

$(OBJDIR)intercept-tool$(PINTOOL_SUFFIX): $(OBJDIR)intercept-tool.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $(OBJDIR)intercept-tool.$(OBJEXT) $(PIN_LIBS)

$(OBJDIR)null-emulator-$(TARGET_LONG)$(PINTOOL_SUFFIX): $(OBJDIR)null-emulator-$(TARGET_LONG).$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $(OBJDIR)null-emulator-$(TARGET_LONG).$(OBJEXT) $(PIN_LIBS)

$(OBJDIR)pc-change-async-tool$(PINTOOL_SUFFIX): $(OBJDIR)pc-change-async-tool.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $(OBJDIR)pc-change-async-tool.$(OBJEXT) $(PIN_LIBS)

$(OBJDIR)interpreter-remove$(PINTOOL_SUFFIX): $(OBJDIR)interpreter-remove.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)mt-exit-tool$(PINTOOL_SUFFIX): $(OBJDIR)mt-exit-tool.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)debugger-type$(PINTOOL_SUFFIX): $(OBJDIR)debugger-type.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)set-mode-tool$(PINTOOL_SUFFIX): $(OBJDIR)set-mode-tool.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)simple-command-tool$(PINTOOL_SUFFIX): $(OBJDIR)simple-command-tool.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)

$(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX): $(OBJDIR)simultaneous-toolbreak.$(OBJEXT)
	$(PIN_LD) $(PIN_LDFLAGS) $(DBG) ${LINK_OUT}$@ $< $(PIN_LIBS)


#
# Rules to run the tests.
#

# This is the example tool from the manual run such that you can attach the debugger after it triggers a stack
# breakpoint.
#
stack-debugger-late.test: $(OBJDIR)fibonacci $(OBJDIR)stack-debugger$(PINTOOL_SUFFIX) $(OBJDIR)stack-debugger-late.tested $(OBJDIR)stack-debugger-late.failed
	rm -f $(OBJDIR)$(@:.test=.toolout)
	$(PIN) $(PINFLAGS_DEBUG_RUNFREE) -appdebug_silent -t $(OBJDIR)stack-debugger$(PINTOOL_SUFFIX) \
	    -stackbreak 4000 -o $(OBJDIR)$(@:.test=.toolout) -timeout $(TLIMIT) -- \
	    $(OBJDIR)fibonacci 1000 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.toolout) > /dev/null 2>&1 || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.toolout) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)fibonacci > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Basic test of debugger features.
#
simple.test: $(OBJDIR)simple $(OBJDIR)simple.tested $(OBJDIR)simple.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Verify we can debug across a failed exec() call.
#
execfail.test: $(OBJDIR)exec $(OBJDIR)execfail.tested $(OBJDIR)execfail.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -follow_execv -- $(OBJDIR)exec ./does-not-exist > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)exec > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Verify we can debug across a parent call to fork().
#
fork.test: $(OBJDIR)fork $(OBJDIR)fork.tested $(OBJDIR)fork.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)fork > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)fork > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Basic test of PIN_ApplicationBreakpoint()
#
breaktool.test: $(OBJDIR)simple $(OBJDIR)breaktool$(PINTOOL_SUFFIX) $(OBJDIR)breaktool.tested $(OBJDIR)breaktool.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)breaktool$(PINTOOL_SUFFIX) -wait_for_debugger 0 -- $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Verify that PIN_ApplicationBreakpoint(.., TRUE, ..) will wait if there's no debugger.
#
breaktool-wait.test: $(OBJDIR)simple $(OBJDIR)breaktool$(PINTOOL_SUFFIX) $(OBJDIR)breaktool-wait.tested $(OBJDIR)breaktool-wait.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG_RUNFREE) -t $(OBJDIR)breaktool$(PINTOOL_SUFFIX) -wait_for_debugger 1 -port $(OBJDIR)$(@:.test=.out) -- $(OBJDIR)simple &
	count=0; \
	until test -s $(OBJDIR)$(@:.test=.out) -o $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	sleep 5
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	port=`cat $(OBJDIR)$(@:.test=.out)`; echo "target remote :$$port" >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Verify that PIN_ApplicationBreakpoint(.., FALSE, ..) does not wait if there's no debugger.
#
breaktool-nodebugger.test: $(OBJDIR)simple $(OBJDIR)breaktool$(PINTOOL_SUFFIX) $(OBJDIR)breaktool-nodebugger.tested $(OBJDIR)breaktool-nodebugger.failed
	$(PIN) $(PINFLAGS_DEBUG_RUNFREE) -t $(OBJDIR)breaktool$(PINTOOL_SUFFIX) -wait_for_debugger 0 -- $(OBJDIR)simple
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test breakpoints in various circumstances.
#
bptest-ia32.test: $(OBJDIR)bptest-ia32 $(OBJDIR)bptest-ia32.tested $(OBJDIR)bptest-ia32.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)bptest-ia32 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)bptest-ia32 > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.)$(COMPARE_EXT) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

bptest-intel64.test: $(OBJDIR)bptest-intel64 $(OBJDIR)bptest-intel64.tested $(OBJDIR)bptest-intel64.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)bptest-intel64 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)bptest-intel64 > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.)$(COMPARE_EXT) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that breakpoints do not cause the tool to see any extra instructions (e.g. INT3).
#
bp-icount.test: $(OBJDIR)simple-static $(OBJDIR)int3-count$(PINTOOL_SUFFIX) $(OBJDIR)bp-icount.tested $(OBJDIR)bp-icount.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) -t $(OBJDIR)int3-count$(PINTOOL_SUFFIX) -func main -o $(OBJDIR)bp-icount.reference -- $(OBJDIR)simple-static
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)int3-count$(PINTOOL_SUFFIX) -func main -o $(OBJDIR)bp-icount.count -- $(OBJDIR)simple-static > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple-static > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	$(PIN_CMP) $(OBJDIR)bp-icount.reference $(OBJDIR)bp-icount.count
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test the PIN_IsActionPending() API.
#
action-pending.test: $(OBJDIR)action-pending-app $(OBJDIR)action-pending-tool$(PINTOOL_SUFFIX) $(OBJDIR)action-pending.tested $(OBJDIR)action-pending.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)action-pending-tool$(PINTOOL_SUFFIX) -- $(OBJDIR)action-pending-app > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)action-pending-app > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that we can print out XMM registers.  Older GDB's don't know how to print XMM registers well,
# so use a modern GDB for this test.
#
# We first test that GDB itself will run.  If not, we just skip the body of this test.  The modern
# GDB won't run on some old test systems.
#
xmm-ia32.test: $(OBJDIR)xmm-ia32 $(OBJDIR)xmm-ia32.tested $(OBJDIR)xmm-ia32.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)xmm-ia32 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)xmm-ia32 > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

xmm-intel64.test: $(OBJDIR)xmm-intel64 $(OBJDIR)xmm-intel64.tested $(OBJDIR)xmm-intel64.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)xmm-intel64 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)xmm-intel64 > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Simple test of a threaded program.
#
thread.test: $(OBJDIR)thread $(OBJDIR)thread.tested $(OBJDIR)thread.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)thread > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat thread.gdb >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)thread > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p thread.compare -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Simple test of a threaded program built statically (uses non-nptl thread package on Linux).
# NOTE: This test is disabled, so it does not run automatically.  Modern versions of GDB do not
#   support non-nptl threads well.
#
thread-static.test: $(OBJDIR)thread-static $(OBJDIR)thread-static.tested $(OBJDIR)thread-static.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)thread-static > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat thread.gdb >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)thread-static > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p thread.compare -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Simple test of the 'pindb' debugger.  We launch Pin separatly and pindb attaches.
# TODO: This is disabled until Mantis #1839 is fixed.
#
simple-pindb-attach.test: $(OBJDIR)simple-pindb$(EXEEXT) $(OBJDIR)stack-debugger$(PINTOOL_SUFFIX) $(OBJDIR)simple-pindb-attach.tested $(OBJDIR)simple-pindb-attach.failed
	$(OBJDIR)simple-pindb$(EXEEXT) basic $(OBJDIR)$(@:.test=.pindbin) $(OBJDIR)$(@:.test=.compare)
	$(PYTHON) launch-pin-attach-debugger.py --pin=$(PIN_NOFLAGS) --pin-exe=$(PIN_EXE) \
	    --pindb=$(PINDB) --pindb-libpath=$(PINDB_LIBPATH) \
	    --tool=$(OBJDIR)stack-debugger$(PINTOOL_SUFFIX) --app=$(OBJDIR)simple-pindb$(EXEEXT) \
	    --cpu=$(TARGET_LONG) --timeout=$(TLIMIT) \
	    --pin-out=$(OBJDIR)$(@:.test=.out) --pindb-in=$(OBJDIR)$(@:.test=.pindbin) \
	    --pindb-out=$(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(OBJDIR)$(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Simple test of the 'pindb' debugger.  We use the pindb "run" command to launch and attach to pin.
#
simple-pindb-launch.test: $(OBJDIR)simple-pindb$(EXEEXT) $(OBJDIR)stack-debugger$(PINTOOL_SUFFIX) $(OBJDIR)simple-pindb-launch.tested $(OBJDIR)simple-pindb-launch.failed
	$(OBJDIR)simple-pindb$(EXEEXT) basic $(OBJDIR)$(@:.test=.pindbin.0) $(OBJDIR)$(@:.test=.compare)
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)stack-debugger$(PINTOOL_SUFFIX)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)simple-pindb$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(OBJDIR)$(@:.test=.pindbin.0) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(OBJDIR)$(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test the checkpoint tool.
#
checkpoint.test: $(OBJDIR)checkpoint-app $(OBJDIR)checkpoint$(PINTOOL_SUFFIX) $(OBJDIR)checkpoint.tested $(OBJDIR)checkpoint.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)checkpoint$(PINTOOL_SUFFIX) -- $(OBJDIR)checkpoint-app > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)checkpoint-app > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p checkpoint-gdb.compare -c $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p checkpoint-app.compare -c $(OBJDIR)$(@:.test=.out)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test the watchpoint tool.
#
watchpoint.test: $(OBJDIR)watchpoint-app $(OBJDIR)watchpoint$(PINTOOL_SUFFIX) $(OBJDIR)watchpoint.tested $(OBJDIR)watchpoint.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(OBJDIR)watchpoint-app 1 > $(OBJDIR)$(@:.test=.gdb)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)watchpoint$(PINTOOL_SUFFIX) -- $(OBJDIR)watchpoint-app > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(OBJDIR)$(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)watchpoint-app > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# This test starts Pin with debugger support enabled, but Pin does not stop at
# the first instruction waiting for a debugger to attach.  Instead, the
# application runs under Pin immediately.  Later, if the tool finds something
# interesting, it can ask the user (or a GUI shell) to start the debugger and
# attach at the interesting point.
#
launch-gdb.test: $(OBJDIR)callerapp $(OBJDIR)launch-gdb-tool$(PINTOOL_SUFFIX) $(OBJDIR)launch-gdb.tested $(OBJDIR)launch-gdb.failed
	rm -f $(OBJDIR)$(@:.test=.gdbin)
	$(PIN) $(PINFLAGS_DEBUG_RUNFREE) -t $(OBJDIR)launch-gdb-tool$(PINTOOL_SUFFIX) -timeout $(TLIMIT) \
	    -o $(OBJDIR)$(@:.test=.gdbin) -- $(OBJDIR)callerapp > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.gdbin) > /dev/null 2>&1 || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)callerapp > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# This is the example tool we describe in the manual, which demonstrates the major features
# of the application-level debugging API.  The tool tracks the application's stack usage
# and allows breakpoints to be set when the stack usage crosses a threshold.
#
stack-debugger.test: $(OBJDIR)fibonacci $(OBJDIR)stack-debugger$(PINTOOL_SUFFIX) $(OBJDIR)stack-debugger.tested $(OBJDIR)stack-debugger.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)stack-debugger$(PINTOOL_SUFFIX) -- $(OBJDIR)fibonacci 1000 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)fibonacci > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that we can asynchronously stop the target in PinDB by sending CTRL-C (SIGINT).
# TODO: This is disabled until Mantis #2055 is fixed.
#
pindb-async-stop.test: $(OBJDIR)sleep-unix $(OBJDIR)pindb-async-stop.tested $(OBJDIR)pindb-async-stop.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)sleep-unix" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout) & \
	    pid=$$!; \
	    sleep 2; \
	    while kill -INT $$pid > /dev/null 2>&1; \
	    do \
	        sleep 2; \
	    done; \
	    wait
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test of breakpoint commands in the "debugger-shell" instrumentation library.
#
debugger-shell-breakpoints.test: $(OBJDIR)debugger-shell-app-$(TARGET_LONG) $(OBJDIR)use-debugger-shell$(PINTOOL_SUFFIX) $(OBJDIR)debugger-shell-breakpoints.tested $(OBJDIR)debugger-shell-breakpoints.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(OBJDIR)debugger-shell-app-$(TARGET_LONG) breakpoints $(OBJDIR)$(@:.test=.gdbin.0) $(OBJDIR)$(@:.test=.compare)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)use-debugger-shell$(PINTOOL_SUFFIX) -- $(OBJDIR)debugger-shell-app-$(TARGET_LONG) > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(OBJDIR)$(@:.test=.gdbin.0) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)debugger-shell-app-$(TARGET_LONG) > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(OBJDIR)$(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test of tracepoint commands in the "debugger-shell" instrumentation library.
#
debugger-shell-tracepoints.test: $(OBJDIR)debugger-shell-app-$(TARGET_LONG) $(OBJDIR)use-debugger-shell$(PINTOOL_SUFFIX) $(OBJDIR)debugger-shell-tracepoints.tested $(OBJDIR)debugger-shell-tracepoints.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(OBJDIR)debugger-shell-app-$(TARGET_LONG) tracepoints $(OBJDIR)$(@:.test=.gdbin.0) $(OBJDIR)$(@:.test=.compare)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)use-debugger-shell$(PINTOOL_SUFFIX) -- $(OBJDIR)debugger-shell-app-$(TARGET_LONG) > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(OBJDIR)$(@:.test=.gdbin.0) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)debugger-shell-app-$(TARGET_LONG) > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(OBJDIR)$(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that the thread-start, thread-fini, and fini call-backs are correctly called even when GDB
# immediately terminates the application .
#
start-fini.test: $(OBJDIR)start-fini-callback$(PINTOOL_SUFFIX) $(OBJDIR)simple $(OBJDIR)start-fini.tested $(OBJDIR)start-fini.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)start-fini-callback$(PINTOOL_SUFFIX) -o $(OBJDIR)$(@:.test=.toolout) -- \
	    $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) & \
	    count=0; \
	    until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	        do sleep 1; count=`expr $$count + 1`; done; \
	    echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin); \
	    grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin); \
	    cat quit.gdb >> $(OBJDIR)$(@:.test=.gdbin); \
	    $(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > $(OBJDIR)$(@:.test=.gdbout) 2>&1; \
	wait
	$(PIN_CMP) start-fini.reference $(OBJDIR)$(@:.test=.toolout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that the thread-start, thread-fini, and fini call-backs are correctly called when PinDB
# immediately terminates the application (tested on both Linux and Windows).
#
pindb-start-fini.test: $(OBJDIR)start-fini-callback$(PINTOOL_SUFFIX) $(OBJDIR)simple$(EXEEXT) $(OBJDIR)pindb-start-fini.tested $(OBJDIR)pindb-start-fini.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)start-fini-callback$(PINTOOL_SUFFIX) \
	    -o $(OBJDIR)$(@:.test=.toolout)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)simple$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PIN_DIFF) start-fini.reference $(OBJDIR)$(@:.test=.toolout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Verify that PIN_InterceptDebuggingEvent() can intercept and squash breakpoints.
#
intercept-breakpoint.test: $(OBJDIR)intercept-app $(OBJDIR)intercept-tool$(PINTOOL_SUFFIX) $(OBJDIR)intercept-breakpoint.tested $(OBJDIR)intercept-breakpoint.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)intercept-tool$(PINTOOL_SUFFIX) -- $(OBJDIR)intercept-app > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)intercept-app > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=-gdb.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=-app.compare) -c $(OBJDIR)$(@:.test=.out)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test the PIN_AddDebuggerRegisterEmulator() API.  This test is legal to run with any version of GDB,
# but it only tests the API well when run with a GDB that supports register extensions in the XML
# "feature document".  This includes GDB 7.2 and later, and a few special earlier distributions.
#
emu-simple.test: $(OBJDIR)simple $(OBJDIR)null-emulator-$(TARGET_LONG)$(PINTOOL_SUFFIX) $(OBJDIR)emu-simple.tested $(OBJDIR)emu-simple.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)null-emulator-$(TARGET_LONG)$(PINTOOL_SUFFIX) -- $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat simple.gdb >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p simple.compare -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Verify that the debugger can print the value of a YMM register when running on native AVX hardware.
# This test will pass even when run on non-AVX hardware.  However, it's only effective when run on
# AVX hardware and when run with a GDB that supports AVX.
#
ymm.test: $(OBJDIR)ymm-$(TARGET_LONG) $(OBJDIR)ymm.tested $(OBJDIR)ymm.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)ymm-$(TARGET_LONG) > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)ymm-$(TARGET_LONG) > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Verify that the debugger change the the PC when stopped after an indirect JMP instruction.
#
pc-change-bp.test: $(OBJDIR)pc-change-bp $(OBJDIR)pc-change-bp.tested $(OBJDIR)pc-change-bp.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)pc-change-bp > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)pc-change-bp > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.out)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Verify that the tool can change the PC from an ASYNC_BREAK intercept function when the thread
# is stopped after an indirect JMP instruction.
#
pc-change-async.test: $(OBJDIR)pc-change-async $(OBJDIR)pc-change-async-tool$(PINTOOL_SUFFIX) $(OBJDIR)pc-change-async.tested $(OBJDIR)pc-change-async.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)pc-change-async-tool$(PINTOOL_SUFFIX) -- $(OBJDIR)pc-change-async > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)pc-change-async > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.out)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test the PIN_RemoveDebugInterpreter() API.
#
interpreter-remove.test: $(OBJDIR)interpreter-remove${PINTOOL_SUFFIX} $(OBJDIR)interpreter-remove.tested $(OBJDIR)interpreter-remove.failed $(OBJDIR)simple
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) -appdebug -t $< -- $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
		do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	echo 'monitor bdio' >> $(OBJDIR)$(@:.test=.gdbin)
	echo 'c' >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > /dev/null 2>&1
	! grep 'PIN_RemoveDebugInterpreter failed' $(OBJDIR)$(@:.test=.out) > /dev/null
	rm $(OBJDIR)$(@:.test=.failed)

# Verify that GDB can terminate an application where one thread is blocked in
# a system call.  Previously, the Pin process would sometimes hang when this
# happened, so the test checks that the process exits.  (Note, "kill -s 0 <pid>"
# just checks if a process exists, it doesn't send a signal.)
#
mt-exit.test: $(OBJDIR)mt-exit $(OBJDIR)mt-exit-tool$(PINTOOL_SUFFIX) $(OBJDIR)mt-exit.tested $(OBJDIR)mt-exit.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	rm -f $(OBJDIR)$(@:.test=.toolout)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)mt-exit-tool$(PINTOOL_SUFFIX) -o $(OBJDIR)$(@:.test=.toolout) -- $(OBJDIR)mt-exit > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)mt-exit > $(OBJDIR)$(@:.test=.gdbout)
	pid=`cat $(OBJDIR)$(@:.test=.toolout)`; \
	count=0; \
	until ! kill -s 0 $$pid > /dev/null 2>&1 || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done; \
	test $$count -le $(TLIMIT)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Simple test of the PIN_GetDebuggerType() API.
#
debugger-type.test: $(OBJDIR)simple $(OBJDIR)debugger-type$(PINTOOL_SUFFIX) $(OBJDIR)debugger-type.tested $(OBJDIR)debugger-type.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)debugger-type$(PINTOOL_SUFFIX) -- $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > $(OBJDIR)$(@:.test=.gdbout)
	grep 'Debugger Type is GDB' $(OBJDIR)$(@:.test=.out) > /dev/null
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that we can single-step into a signal handler.
#
signal-step.test: $(OBJDIR)signal-catch $(OBJDIR)signal-step.tested $(OBJDIR)signal-step.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)signal-catch > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)signal-catch > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that GDB can print $_siginfo and get the signal information structure from Pin.
#
siginfo.test: $(OBJDIR)signal-catch $(OBJDIR)siginfo.tested $(OBJDIR)siginfo.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)signal-catch > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)signal-catch > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that PinDB can attach after the Pin tool has stopped at a custom breakpoint and that PinDB
# can still get the tool's custom stop message (see Mantis #2357).
#
# This is disabled on Windows, but it could probably be enabled there when Mantis #1839 is fixed.
#
pindb-attach-after-custom-stop.test: $(OBJDIR)simple$(EXEEXT) $(OBJDIR)breaktool$(PINTOOL_SUFFIX) $(OBJDIR)pindb-attach-after-custom-stop.tested $(OBJDIR)pindb-attach-after-custom-stop.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG_RUNFREE) -t $(OBJDIR)breaktool$(PINTOOL_SUFFIX) -where main -wait_for_debugger 1 -port $(OBJDIR)$(@:.test=.port) -- $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'Tool stopping at breakpoint' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    --gdb-protocol=:`cat $(OBJDIR)$(@:.test=.port)` $(PINDB_USERFLAGS) < $(@:.test=.pindbin) > \
	    $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test Windows unhandled exception with PinDB.
#
pindb-win-unhandled-exception.test: $(OBJDIR)win-unhandled-exception$(EXEEXT) $(OBJDIR)pindb-win-unhandled-exception.tested $(OBJDIR)pindb-win-unhandled-exception.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-unhandled-exception$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test Windows handled exception with PinDB.
#
pindb-win-handled-exception.test: $(OBJDIR)win-handled-exception$(EXEEXT) $(OBJDIR)pindb-win-handled-exception.tested $(OBJDIR)pindb-win-handled-exception.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-handled-exception$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test Windows continued exception with PinDB.  The exception filter continues the search.  Note,
# this test is known to fail (due to a compiler bug) when compiled for IA32 with ICC version 11.x.
# (It passes with ICC versions 10.x and 12.x.)
#
pindb-win-continued-exception1.test: $(OBJDIR)win-continued-exception1$(EXEEXT) $(OBJDIR)pindb-win-continued-exception1.tested $(OBJDIR)pindb-win-continued-exception1.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-continued-exception1$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test Windows continued exception with PinDB.  The exception filter executes the handler.  Note,
# this test is known to fail (due to a compiler bug) when compiled for IA32 with ICC version 11.x.
# (It passes with ICC versions 10.x and 12.x.)
#
pindb-win-continued-exception2.test: $(OBJDIR)win-continued-exception2$(EXEEXT) $(OBJDIR)pindb-win-continued-exception2.tested $(OBJDIR)pindb-win-continued-exception2.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-continued-exception2$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test Windows software exception with PinDB.  The exception is raised via RaiseException() and is unhandled.
#
pindb-win-software-exception.test: $(OBJDIR)win-software-exception$(EXEEXT) $(OBJDIR)pindb-win-software-exception.tested $(OBJDIR)pindb-win-software-exception.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-software-exception$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test Windows C++ exception with PinDB.
#
pindb-win-cpp-exception.test: $(OBJDIR)win-cpp-exception$(EXEEXT) $(OBJDIR)pindb-win-cpp-exception.tested $(OBJDIR)pindb-win-cpp-exception.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-cpp-exception$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test ability to squash a Windows exception.  Squashing a first-chance exception re-executes
# the excepting instruction, which raises a new first-chance exception.  Squashing a last-chance
# exception also re-executes the excepting instruction, which raises a new first-chance exception.
#
pindb-win-squash-exception.test: $(OBJDIR)win-unhandled-exception$(EXEEXT) $(OBJDIR)pindb-win-squash-exception.tested $(OBJDIR)pindb-win-squash-exception.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-unhandled-exception$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test ability to single-step after receiving a Windows exception.  Stepping from a first-chance
# exception should go to the first instruction in the handler.  Stepping from a last-chance
# exception should cause the application to terminate.
#
pindb-win-step-exception.test: $(OBJDIR)win-unhandled-exception$(EXEEXT) $(OBJDIR)pindb-win-step-exception.tested $(OBJDIR)pindb-win-step-exception.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-unhandled-exception$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test DLL load / unload notifications with PinDB.
#
pindb-win-library-notifications.test: $(OBJDIR)win-load-library$(EXEEXT) $(OBJDIR)win-foo-library$(SHLIBEXT) $(OBJDIR)pindb-win-library-notifications.tested $(OBJDIR)pindb-win-library-notifications.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-load-library$(EXEEXT) $(OBJDIR)win-foo-library$(SHLIBEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test ability to single-step after receiving a Windows library load / unload notification.
#
pindb-win-step-library.test: $(OBJDIR)win-load-library$(EXEEXT) $(OBJDIR)win-foo-library$(SHLIBEXT) $(OBJDIR)pindb-win-step-library.tested $(OBJDIR)pindb-win-step-library.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-load-library$(EXEEXT) $(OBJDIR)win-foo-library$(SHLIBEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Make sure PinDB does not wait for confirmation when killing the target process when --noprompt is specified.
#
pindb-noprompt-kill.test: $(OBJDIR)simple$(EXEEXT) $(OBJDIR)pindb-noprompt-kill.tested $(OBJDIR)pindb-noprompt-kill.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)simple$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test the -appdebug_allow_remote knob, which allows GDB to run on a different machine than Pin.
# However, it's difficult to actually run GDB on a different machine as part of this test, so
# we still run them both on the same machine.
#
allow-remote.test: $(OBJDIR)simple $(OBJDIR)allow-remote.tested $(OBJDIR)allow-remote.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -appdebug_allow_remote -- $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat simple.gdb >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p simple.compare -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Verify that Pin doesn't crash if the debugger attempts to access a 64-bit address for a 32-bit Pin process.
#
access-64-on-32.test: $(OBJDIR)simple$(EXEEXT) $(OBJDIR)access-64-on-32.tested $(OBJDIR)access-64-on-32.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)simple$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Make sure we can ebable debugging via PIN_SetDebugMode() from the tool.  This test should
# be run without -appdebug.
#
set-mode.test: $(OBJDIR)simple$(EXEEXT) $(OBJDIR)set-mode-tool$(PINTOOL_SUFFIX) $(OBJDIR)set-mode.tested $(OBJDIR)set-mode.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) -t $(OBJDIR)set-mode-tool$(PINTOOL_SUFFIX) -- $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat simple.gdb >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > $(OBJDIR)$(@:.test=.gdbout)
	$(PYTHON) ../compare.py -p simple.compare -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that PinDB can detach from Pin.
#
pindb-detach.test: $(OBJDIR)simple-pindb$(EXEEXT) $(OBJDIR)pindb-detach.tested $(OBJDIR)pindb-detach.failed
	$(OBJDIR)simple-pindb$(EXEEXT) detach $(OBJDIR)$(@:.test=.pindbin.0) $(OBJDIR)$(@:.test=.compare)
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)simple-pindb$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(OBJDIR)$(@:.test=.pindbin.0) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(OBJDIR)$(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Abruptly disconnect PinDB from Pin.  This simulates the behavior when the debugger unexpectedly dies.
# We expect an error from Pin, but Pin shouldn't hang.
#
pindb-abrupt-disconnect.test: $(OBJDIR)simple$(EXEEXT) $(OBJDIR)pindb-abrupt-disconnect.tested $(OBJDIR)pindb-abrupt-disconnect.failed
	echo "set pinargs -logfile $(OBJDIR)$(@:.test=.pin.log) $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)simple$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test the "kill-like-gdb" command in PinDB.  This sends the same legacy "kill" command to PinADX that
# GDB uses.
#
pindb-kill-like-gdb.test: $(OBJDIR)simple$(EXEEXT) $(OBJDIR)pindb-kill-like-gdb.tested $(OBJDIR)pindb-kill-like-gdb.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)simple$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that GDB can detach from Pin and then re-attach later.
#
gdb-detach-reattach.test: $(OBJDIR)reattach-loop$(EXEEXT) $(OBJDIR)gdb-detach-reattach.tested $(OBJDIR)gdb-detach-reattach.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)reattach-loop > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	grep 'target remote' $(OBJDIR)$(@:.test=.out) > $(OBJDIR)$(@:.test=.port)
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=-1.gdbin)
	cat $(OBJDIR)$(@:.test=.port) >> $(OBJDIR)$(@:.test=-1.gdbin)
	cat $(@:.test=-1.gdb) >> $(OBJDIR)$(@:.test=-1.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=-1.gdbin) -n $(OBJDIR)reattach-loop > $(OBJDIR)$(@:.test=-1.gdbout)
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=-2.gdbin)
	cat $(OBJDIR)$(@:.test=.port) >> $(OBJDIR)$(@:.test=-2.gdbin)
	cat $(@:.test=-2.gdb) >> $(OBJDIR)$(@:.test=-2.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=-2.gdbin) -n $(OBJDIR)reattach-loop > $(OBJDIR)$(@:.test=-2.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=-gdb-1.compare) -c $(OBJDIR)$(@:.test=-1.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=-gdb-2.compare) -c $(OBJDIR)$(@:.test=-2.gdbout)
	$(PYTHON) ../compare.py -p $(@:.test=-app.compare) -c $(OBJDIR)$(@:.test=.out)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that extended commands work using PinDB.  This also checks that the tool does _not_ receive
# commands that start with the "pin " prefix.
#
pindb-simple-command.test: $(OBJDIR)simple$(EXEEXT) $(OBJDIR)simple-command-tool$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simple-command.tested $(OBJDIR)pindb-simple-command.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simple-command-tool$(PINTOOL_SUFFIX)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)simple$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that the debugger can write to an invalid address in the application.
#
invalid-write.test: $(OBJDIR)simple $(OBJDIR)invalid-write.tested $(OBJDIR)invalid-write.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)simple > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)simple > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Try debugging an application with lots of threads that exit at the same time.
#
pindb-win-thread-stress.test: $(OBJDIR)win-thread-stress$(EXEEXT) $(OBJDIR)pindb-win-thread-stress.tested $(OBJDIR)pindb-win-thread-stress.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)win-thread-stress$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that we can single-step over an instruction that exits the calling thread while another thread
# still exists.  We expect the debugger to stop after the thread exits, leaving the focus on
# the one remaining thread.
#
pindb-pthread-step-exit.test: $(OBJDIR)pthread-bare-exit$(EXEEXT) $(OBJDIR)pindb-pthread-step-exit.tested $(OBJDIR)pindb-pthread-step-exit.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)pthread-bare-exit$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Same test as above, but use GDB instead of PinDB.
#
gdb-pthread-step-exit.test: $(OBJDIR)pthread-bare-exit$(EXEEXT) $(OBJDIR)gdb-pthread-step-exit.tested $(OBJDIR)gdb-pthread-step-exit.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -- $(OBJDIR)pthread-bare-exit$(EXEEXT) > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(OBJDIR)pthread-bare-exit$(EXEEXT) > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that we can debug an application where one thread exits the entire process
# while another thread still exists.
#
pindb-pthread-cont-exitgroup.test: $(OBJDIR)pthread-bare-exitgroup$(EXEEXT) $(OBJDIR)pindb-pthread-cont-exitgroup.tested $(OBJDIR)pindb-pthread-cont-exitgroup.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)pthread-bare-exitgroup$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that we can single-step over an instruction that exits the entire process while
# another thread still exists.  We expect the debugger to stop after the exit call
# and indicate that the process is terminated.
#
pindb-pthread-step-exitgroup.test: $(OBJDIR)pthread-bare-exitgroup$(EXEEXT) $(OBJDIR)pindb-pthread-step-exitgroup.tested $(OBJDIR)pindb-pthread-step-exitgroup.failed
	echo "set pinargs $(PIN_USERFLAGS)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)pthread-bare-exitgroup$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that we can single-step over an instruction that triggers a custom breakpoint.
# This should stop due to the custom breakpoint, without stepping over the instruction.
# A subsequent step should skip the custom breakpoint and step over the instruction.
#
pindb-step-custom-break.test: $(OBJDIR)simple-pindb$(EXEEXT) $(OBJDIR)use-debugger-shell$(PINTOOL_SUFFIX) $(OBJDIR)pindb-step-custom-break.tested $(OBJDIR)pindb-step-custom-break.failed
	$(OBJDIR)simple-pindb$(EXEEXT) step-custom-break $(OBJDIR)$(@:.test=.pindbin.0) $(OBJDIR)$(@:.test=.compare)
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)use-debugger-shell$(PINTOOL_SUFFIX)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(OBJDIR)simple-pindb$(EXEEXT)" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(OBJDIR)$(@:.test=.pindbin.0) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(OBJDIR)$(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test the behavior when several threads stop at simultaneous tool breakpoints.
# After one breakpoint is delivered, the others are pending.  This test makes
# sure that the pending events are delivered one-at-a-time to GDB.  It also
# tests that the tool can list the pending breakpoints.
#
simultaneous-toolbreak.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)simultaneous-toolbreak.tested $(OBJDIR)simultaneous-toolbreak.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4 -- $(THREAD_APP) -threads 4 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(THREAD_APP) > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Another test when several threads stop at simultaneous tool breakpoints.
# After one breakpoint is delivered, the others are pending.  This test
# squashes the pending breakpoints and then makes sure they are not
# delivered to GDB.
#
simultaneous-toolbreak-squash.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)simultaneous-toolbreak-squash.tested $(OBJDIR)simultaneous-toolbreak-squash.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4 -- $(THREAD_APP) -threads 4 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(THREAD_APP) > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Another test when several threads stop at simultaneous tool breakpoints.
# After one breakpoint is delivered, the others are pending.  This test
# changes the message of the pending breakpoints and then makes sure they
# are delivered with the new message.
#
simultaneous-toolbreak-change.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)simultaneous-toolbreak-change.tested $(OBJDIR)simultaneous-toolbreak-change.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4 -- $(THREAD_APP) -threads 4 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'target remote' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(THREAD_APP) > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Test that we can attach GDB to the application after it has stopped
# at several simultaneous tool breakpoints.  We expect GDB to attach
# at the context of one of those breakpoints, and we expect the others
# to be pending.
#
simultaneous-toolbreak-attach.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)simultaneous-toolbreak-attach.tested $(OBJDIR)simultaneous-toolbreak-attach.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG_RUNFREE) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4 -wait_for_debugger -- $(THREAD_APP) -threads 4 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'Waiting for debugger to attach' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	echo 'set remotetimeout $(TLIMIT)' > $(OBJDIR)$(@:.test=.gdbin)
	grep 'target remote' $(OBJDIR)$(@:.test=.out) >> $(OBJDIR)$(@:.test=.gdbin)
	cat $(@:.test=.gdb) >> $(OBJDIR)$(@:.test=.gdbin)
	$(GDB) -batch -x $(OBJDIR)$(@:.test=.gdbin) -n $(THREAD_APP) > $(OBJDIR)$(@:.test=.gdbout) 2>&1
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.gdbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Another test when several threads stop at simultaneous tool breakpoints.
# This test runs with PinDB, which expects all breakpoints to be delivered
# simultaneously.  Make sure that all 4 breakpoints are delivered at once,
# and that none are pending.
#
pindb-simultaneous-toolbreak.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simultaneous-toolbreak.tested $(OBJDIR)pindb-simultaneous-toolbreak.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(THREAD_APP) -threads 4" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Another test when several threads stop at simultaneous tool breakpoints.
# This test runs PinDB in a mode where each breakpoint is delivered one-
# at-a-time (similar to GDB).  We make sure that there are pending breakpoints
# after the first is delivered, and we make sure that all breakpoints are
# delivered one-at-a-time.
#
pindb-simultaneous-toolbreak-serialize.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simultaneous-toolbreak-serialize.tested $(OBJDIR)pindb-simultaneous-toolbreak-serialize.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(THREAD_APP) -threads 4" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) \
	    --serialize-debugger-events --noprompt $(PINDB_USERFLAGS) \
	    < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Another test when several threads stop at simultaneous tool breakpoints.
# This test also runs PinDB in a mode where each breakpoint is delivered
# one-at-a-time.  In this test, we squash the remaining breakpoints after
# the first is delivered and then make sure that the squashed breakpoints
# are not delivered.
#
pindb-simultaneous-toolbreak-squash.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simultaneous-toolbreak-squash.tested $(OBJDIR)pindb-simultaneous-toolbreak-squash.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(THREAD_APP) -threads 4" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) \
	    --serialize-debugger-events --noprompt $(PINDB_USERFLAGS) \
	    < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Another test when several threads stop at simultaneous tool breakpoints.
# This test also runs PinDB in a mode where each breakpoint is delivered
# one-at-a-time.  In this test, we change the message of the remaining
# breakpoints after the first is delivered and then make sure that the
# breakpoints are delivered with the changed message.
#
pindb-simultaneous-toolbreak-change.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simultaneous-toolbreak-change.tested $(OBJDIR)pindb-simultaneous-toolbreak-change.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(THREAD_APP) -threads 4" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) \
	    --serialize-debugger-events --noprompt $(PINDB_USERFLAGS) \
	    < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# Another test when several threads stop at simultaneous tool breakpoints.
# When breakpoints are delivered one-at-a-time, try single-stepping one
# thread while there are pending breakpoints on the others.  The pending
# breakpoints should not be delivered because the single-step doesn't
# advance the execution of those threads.
#
pindb-simultaneous-toolbreak-step.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simultaneous-toolbreak-step.tested $(OBJDIR)pindb-simultaneous-toolbreak-step.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(THREAD_APP) -threads 4" >> $(OBJDIR)$(@:.test=.pindbin)
	cat $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) \
	    --serialize-debugger-events --noprompt $(PINDB_USERFLAGS) \
	    < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# This is a stress test for simultaneous debugger events.  Each thread stops when
# the thread is created, at a normal breakpoint, at a tool breakpoint, and stops
# when the thread exits.  There is no serialization in this variant of the test,
# so we expect that many events will be reported to the debugger simultaneously.
# The test verifies that we get all the events.
#
pindb-simultaneous-multi.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simultaneous-multi.tested $(OBJDIR)pindb-simultaneous-multi.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(THREAD_APP) -threads 8" >> $(OBJDIR)$(@:.test=.pindbin)
	$(THREAD_APP) -print-address > $(OBJDIR)$(@:.test=.address)
	sed "s/GLOBAL_FUNCTION/`cat $(OBJDIR)$(@:.test=.address)`/" $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
        $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare1) -c $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare2) -c $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare3) -c $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare4) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# This test is identical to the one above except that we don't stop when new
# threads are created or when they exit.  We use this test on Windows to avoid
# a problem with the virus scanner.  If a virus scan happens when this test runs,
# the scanner injects a new thread into the test application.  If the debugger
# stops when new threads are created, the scanner thread causes an extra stop in
# the debugger which causes the test to fail.  This variant of the test avoids
# the problem by not stopping in the debugger when new threads start or exit.
# We also run this test on Unix because it tests different code paths in Pin.
#
pindb-simple-simultaneous-multi.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simple-simultaneous-multi.tested $(OBJDIR)pindb-simple-simultaneous-multi.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(THREAD_APP) -threads 8" >> $(OBJDIR)$(@:.test=.pindbin)
	$(THREAD_APP) -print-address > $(OBJDIR)$(@:.test=.address)
	sed "s/GLOBAL_FUNCTION/`cat $(OBJDIR)$(@:.test=.address)`/" $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
        $(PINDB_USERFLAGS) < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare1) -c $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare2) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# This is another stress test for simultaneous debugger events, similar to the
# one above.  In this variant, Pin delivers the events one-at-a-time to the
# debugger.  Again, we verifiy that the debugger gets them all.
#
pindb-simultaneous-multi-serialize.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simultaneous-multi-serialize.tested $(OBJDIR)pindb-simultaneous-multi-serialize.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(THREAD_APP) -threads 8" >> $(OBJDIR)$(@:.test=.pindbin)
	$(THREAD_APP) -print-address > $(OBJDIR)$(@:.test=.address)
	sed "s/GLOBAL_FUNCTION/`cat $(OBJDIR)$(@:.test=.address)`/" $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) \
	    --serialize-debugger-events --noprompt $(PINDB_USERFLAGS) \
	    < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare1) -c $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare2) -c $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare3) -c $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare4) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# This test is identical to the one above except that we don't stop when new
# threads are created or when they exit.  We use this test on Windows to avoid
# a problem with the virus scanner.  See "pindb-simple-simultaneous-multi.test"
# for more information.  We also run it on Unix because it tests different code
# paths in Pin.
#
pindb-simple-simultaneous-multi-serialize.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simple-simultaneous-multi-serialize.tested $(OBJDIR)pindb-simple-simultaneous-multi-serialize.failed
	echo "set pinargs $(PIN_USERFLAGS) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX)" > $(OBJDIR)$(@:.test=.pindbin)
	echo "run $(THREAD_APP) -threads 8" >> $(OBJDIR)$(@:.test=.pindbin)
	$(THREAD_APP) -print-address > $(OBJDIR)$(@:.test=.address)
	sed "s/GLOBAL_FUNCTION/`cat $(OBJDIR)$(@:.test=.address)`/" $(@:.test=.pindb) >> $(OBJDIR)$(@:.test=.pindbin)
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) \
	    --serialize-debugger-events --noprompt $(PINDB_USERFLAGS) \
	    < $(OBJDIR)$(@:.test=.pindbin) > $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare1) -c $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare2) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)

# This is similar to "simultaneous-toolbreak-attach", but we use PinDB
# instead of GDB.  The application stops at several simultaneous breakpoints
# before PinDB attaches.  Since PinDB allows multiple simultaneous breakpoints,
# we expect all of them to be visible when PinDB attaches, and there will be
# no pending breakpoints.
#
# This is disabled on Windows, but it could probably be enabled there when Mantis #1839 is fixed.
#
pindb-simultaneous-toolbreak-attach.test: $(THREAD_APP) $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) $(OBJDIR)pindb-simultaneous-toolbreak-attach.tested $(OBJDIR)pindb-simultaneous-toolbreak-attach.failed
	rm -f $(OBJDIR)$(@:.test=.out)
	$(PIN) $(PINFLAGS_DEBUG_RUNFREE) -t $(OBJDIR)simultaneous-toolbreak$(PINTOOL_SUFFIX) -sync_for_threads 4 -wait_for_debugger -port $(OBJDIR)$(@:.test=.port) -- $(THREAD_APP) -threads 4 > $(OBJDIR)$(@:.test=.out) &
	count=0; \
	until grep 'Waiting for debugger to attach' $(OBJDIR)$(@:.test=.out) > /dev/null || test $$count -gt $(TLIMIT); \
	    do sleep 1; count=`expr $$count + 1`; done
	$(PINDB_WITH_LIBPATH) --pin=$(PIN_EXE) --timeout=$(TLIMIT) --cpu=$(TARGET_LONG) --noprompt \
	    --gdb-protocol=:`cat $(OBJDIR)$(@:.test=.port)` $(PINDB_USERFLAGS) < $(@:.test=.pindbin) > \
	    $(OBJDIR)$(@:.test=.pindbout)
	$(PYTHON) ../compare.py -p $(@:.test=.compare) -c $(OBJDIR)$(@:.test=.pindbout)
	rm -f $(OBJDIR)$(@:.test=.failed)


dummy.test:


clean:
	rm -rf $(OBJDIR)
	rm -f pin.log
