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

GDB = /usr/bin/gdb

##############################################################
#
# include *.config files
#
##############################################################

ifeq ($(TARGET_COMPILER),gnu)
    include ../makefile.gnu.config
    OPT?=-O2 -fomit-frame-pointer
    CXXFLAGS ?= -Wall -Werror -Wno-unknown-pragmas $(DBG) $(OPT) -MMD
endif

ifeq ($(TARGET_COMPILER),ms)
    include ../makefile.ms.config
    DBG?=
endif

#uninit-new

APPS = memcpy_app
TOOL_ROOTS = removeinstrumentation segv probe after context-pc \
        hello icount1 icount2 icount3 icount4 icount5 icountcheck IARGList \
        sequence sequencecheck reg brtaken verify bblnull \
        imageLoad imageLoadBackward callargs traceusage \
        malloc new rtn_insert_call_probed \
        sec bblCache traceOriginal finiRemove rtnNumIns rtn_create_at_dup bblFallThrough \
        tracecount smc_check multipleinstrumentation win_cvapp_test_tool \
        inscount2_mt_debuginfo memory_addr_callback memory_callback_error



TEST_TOOLS_ROOTS = memory_addr_callback memory_callback_error

ifeq ($(DETACH_SUPPORTED), yes)
    TOOL_ROOTS += detach
endif


ifneq ($(TARGET_OS),w)
    TOOL_ROOTS += mtest
endif

ifeq ($(TARGET_OS),w)
  ifeq ($(TARGET_COMPILER),ms)
    TOOL_ROOTS += cflowcheck
  endif
  AVX_SUPPORT_ASM_OBJ = avx_support_$(TARGET).obj
else
  AVX_SUPPORT_ASM_OBJ = avx_support_$(TARGET).o
endif

ifeq ($(TARGET_OS),l)
  TOOL_ROOTS += cflowcheck launcher_tool
    APPS += launcher_app
    TEST_TOOLS_ROOTS += launcher
  ifeq ($(SOTOOL),1)
    TEST_TOOLS_ROOTS += toolwithoutso toolpathwithoutso imageLoader
  endif
endif

ifeq ($(TARGET_OS),b)
  TOOL_ROOTS += cflowcheck
endif

# cflowcheck doesn't run on Mac snow-leopard probably due to segment virtualization
ifeq ($(TARGET_OS),m)
  TOOL_ROOTS += cflowcheck
endif

# leave out probe because it causes an early exit
TEST_TOOLS_ROOTS += after hello icount1 icount2 icount3 icount4 icount5 context-pc \
    icountcheck sequence sequencecheck reg brtaken verify bblnull sec \
    callargs malloc new removeinstrumentation rtnNumIns rtn_create_at_dup \
    IARGList imageLoadBackward bblCache traceOriginal finiRemove bblFallThrough 

ifeq ($(DETACH_SUPPORTED), yes)
    TEST_TOOLS_ROOTS += detach
endif

ifneq ($(TARGET),ipf)
ifneq ($(TARGET_OS),m)
ifneq ($(ICC),1)
    TOOL_ROOTS += reg_ref_inlined
    TEST_TOOLS_ROOTS += reg_ref_inlined
endif
endif
endif



ifeq ($(TARGET),ia32e)
    TOOL_ROOTS += snprintf
    TEST_TOOLS_ROOTS += snprintf snprintf_non_inlined_bridge verify-nocmov 
    ifeq ($(TARGET_OS),l)
        TEST_TOOLS_ROOTS += checkaddress64 syntax_tst injectionStack ifunc_tst illegal_envp statdyn \
                            child_sig_while_execv sourceLocation #ifuncmemcpytrace
        TOOL_ROOTS += checkaddress ea_verifier syntax_tst ifunc_tst statdyn_tool sourceLocation_tool #ifuncmemcpytrace \
                      
    endif
    ifeq ($(TARGET_OS),w)
	    TEST_TOOLS_ROOTS += ifunc_win_tst
        TOOL_ROOTS += ea_verifier ifunc_tst
    endif
endif

ifeq ($(TARGET),ia32)
    TOOL_ROOTS += alah emu checkaddress operand syntax 
    TEST_TOOLS_ROOTS += alah emu emu-bridge checkaddress operand verify-nocmov syntax
    TEST_EBX_IN_EXCEPTIONS_SRC =  test_ebx_in_exceptions_l.cpp
    ifeq ($(TARGET_OS),l)
        TEST_TOOLS_ROOTS += verify-ia32 verify-ia32-nocmov limitedTraces thread \
                            symOutOfBound util prefix exitProcess insMix xedReg ifunc_tst \
                            illegal_envp statdyn sourceLocation #ifuncmemcpytrace
        TOOL_ROOTS += ea_verifier limitedTraces thread symOutOfBound util prefix exitProcess insMix \
                      xedReg ifunc_tst statdyn_tool sourceLocation_tool #ifuncmemcpytrace 
        APPS += loop threadApp prefixApp exitProcessApp insMixApp illegalEnvp_app statdyn_app sourceLocation_app \
                sourceLocation_img1.so sourceLocation_img2.so
    endif
    ifeq ($(TARGET_OS),w)
        TEST_EBX_IN_EXCEPTIONS_SRC =  test_ebx_in_exceptions_w.cpp
        TEST_TOOLS_ROOTS += win-emu-bridge ifunc_win_tst
        TOOL_ROOTS += set_df_flag_tool clear_df_flag_tool set_status_flags_tool ea_verifier ifunc_tst
    endif
	APPS += test_ebx_in_exceptions
endif

ifeq ($(TARGET),ipf)
    TEST_TOOLS_ROOTS += verify-ipf branch-ipf 
    TOOL_ROOTS += operand-ipf
else
ifneq ($(TARGET_OS),m)
ifneq ($(ICC),1)
    TOOL_ROOTS += context_stack_and_spill
endif
endif
endif

ifeq ($(TARGET_OS),w)
  ifeq ($(TARGET_COMPILER),gnu)
    CPPIN_FLAGS = -mno-cygwin
  else
    CPPIN_FLAGS = /nologo /EHsc /MD
  endif
  TEST_APPS  = $(OBJDIR)cp-pin
else
  ifeq (${HOST_ARCH},ia32e)
	ifeq (${TARGET},ia32)
	  CPPIN_FLAGS = -m32
	  TEST_APPS = $(OBJDIR)cp-pin
	endif
  endif
endif

ifndef TEST_APPS 
  TEST_APPS  = $(OBJDIR)cp-pin 
endif


TOOLS = $(TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))
TEST_TOOLS = $(TEST_TOOLS_ROOTS:%=%.test)
APPS_BINARY_FILES = $(APPS:%=$(OBJDIR)%)

TESTS_TO_RUN = $(TEST_TOOLS_ROOTS:%=%.test)
ifneq ($(TARGET),ipf)
ifneq ($(TARGET_OS),m)
ifneq ($(ICC),1)
TESTS_TO_RUN += context_stack_and_spill_noinline_bridge.test
endif
endif
endif

ifeq ($(TARGET_OS),w)
TESTS_TO_RUN += winapp_runs_pin.test
endif

ifeq ($(TARGET),ia32)
TESTS_TO_RUN += test_ebx_in_exceptions.test
endif

TESTS_TO_RUN += icount1_jit_recursion.test

all:  tools $(APPS_BINARY_FILES) 
tools: $(OBJDIR)
	-$(MAKE) run_tools
run_tools: $(TOOLS) $(OBJDIR)foobar
test-apps: $(OBJDIR)
	-$(MAKE) run_test-apps
run_test-apps: $(TEST_APPS)
tests: $(OBJDIR)
	-$(MAKE) run_tests
run_tests: $(TESTS_TO_RUN)

## sanity

SANITY_TOOLS_ROOTS =  icount2 verify after brtaken sequence
ifneq ($(TARGET_OS),w)
   #FIXME: image api
   SANITY_TOOLS_ROOTS += callargs
endif

SANITY_TOOLS = $(SANITY_TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))
SANITY_TESTS = $(SANITY_TOOL_ROOTS:%=%.test)

tools-sanity: $(OBJDIR) $(SANITY_TOOLS)
tests-sanity: $(OBJDIR) $(SANITY_TESTS)
test:         $(OBJDIR) $(TESTS_TO_RUN)

$(OBJDIR):
	mkdir -p $(OBJDIR)

winapp_runs_pin.test: winapp_runs_pin.tested winapp_runs_pin.failed $(OBJDIR)winapp_runs_pin  $(OBJDIR)correct_winapp_runs_pin_cmdline
ifeq (${KIT},1)
	echo ../../../ia32/bin/pin.exe -p64 ../../../intel64/bin/pin.exe > pin_invoke.txt
else
	echo $(PIN) > pin_invoke.txt
endif
	$(OBJDIR)correct_winapp_runs_pin_cmdline  -- ../Tests/$(OBJDIR)cp-pin.exe makefile makefile.winapp_runs_pin.copy > correct_winapp_runs_pin_cmdline.txt 
	$(OBJDIR)winapp_runs_pin `cat correct_winapp_runs_pin_cmdline.txt`
	$(PIN_CMP) makefile makefile.winapp_runs_pin.copy
	rm winapp_runs_pin.failed makefile.winapp_runs_pin.copy correct_winapp_runs_pin_cmdline.txt

child_sig_while_execv.test: $(OBJDIR)child_sig_while_execv_app $(OBJDIR)child_sig_while_execv_simple_app
	$(PIN) -follow_execv -- ./$(OBJDIR)child_sig_while_execv_app

#ifuncmemcpytrace.test : $(OBJDIR)ifuncmemcpytrace$(PINTOOL_SUFFIX) $(OBJDIR)memcpy_app ifuncmemcpytrace.tested ifuncmemcpytrace.failed
#	-$(PIN) -t $< -- ./$(OBJDIR)memcpy_app  $<.out 2>&1
#	if grep "Ifunc memcpy" ifuncmemcpytrace.out ; then \
#		grep "memcpy (ifunc)" ifuncmemcpytrace.out; \
#	else \
#		grep "memcpy (normal)" ifuncmemcpytrace.out; \
#	fi
#	rm ifuncmemcpytrace.failed ifuncmemcpytrace.out

launcher.test: $(OBJDIR)launcher_tool$(PINTOOL_SUFFIX) launcher.tested launcher.failed $(OBJDIR)launcher_app
	env LD_LIBRARY_PATH=TOKEN LD_ASSUME_KERNEL=TOKEN LD_BIND_NOW=TOKEN LD_PRELOAD=TOKEN	$(PIN) -t $(OBJDIR)launcher_tool$(PINTOOL_SUFFIX) -- ./$(OBJDIR)launcher_app
	rm $(@:.test=.failed)

statdyn.test: $(OBJDIR)statdyn_tool$(PINTOOL_SUFFIX) statdyn.tested statdyn.failed $(OBJDIR)statdyn_app
	$(PIN) -t $(OBJDIR)statdyn_tool$(PINTOOL_SUFFIX) -- ./$(OBJDIR)statdyn_app
	rm $(@:.test=.failed)

sourceLocation.test: $(OBJDIR)sourceLocation_tool$(PINTOOL_SUFFIX) sourceLocation.tested sourceLocation.failed $(OBJDIR)sourceLocation_app $(OBJDIR)sourceLocation_img1.so $(OBJDIR)sourceLocation_img2.so
	$(PIN) -t $(OBJDIR)sourceLocation_tool$(PINTOOL_SUFFIX) -- ./$(OBJDIR)sourceLocation_app ./$(OBJDIR)sourceLocation_img1.so ./$(OBJDIR)sourceLocation_img2.so
	rm $(@:.test=.failed)

icount1_jit_recursion.test: $(OBJDIR)icount1$(PINTOOL_SUFFIX) $(TESTAPP)  icount1_jit_recursion.tested icount1_jit_recursion.failed
	$(PIN) -xyzzy -max_jit_recursion_level 5 -jit_all_exits 1 -t $< -- $(TESTAPP) makefile icount1_jit_recursion.makefile.copy
	$(PIN_DIFF) makefile icount1_jit_recursion.makefile.copy
	rm icount1_jit_recursion.failed  icount1_jit_recursion.makefile.copy

illegal_envp.test: illegal_envp.tested illegal_envp.failed $(OBJDIR)illegalEnvp_app
	$(PIN) -follow_execv -- ./$(OBJDIR)illegalEnvp_app $(TESTAPP) makefile illegal_envp.makefile.copy
	$(PIN_CMP) makefile illegal_envp.makefile.copy
	$(PIN) -probe -follow_execv -- ./$(OBJDIR)illegalEnvp_app $(TESTAPP) makefile illegal_envp.probe.makefile.copy
	$(PIN_CMP) makefile illegal_envp.probe.makefile.copy
	rm illegal_envp.makefile.copy; rm illegal_envp.probe.makefile.copy; rm $(@:.test=.failed)

ifunc_tst.test: $(OBJDIR)ifunc_tst${PINTOOL_SUFFIX} ifunc_tst.tested ifunc_tst.failed $(OBJDIR)memcpy_app
	$(PIN) -t $(OBJDIR)ifunc_tst$(PINTOOL_SUFFIX) -- ./$(OBJDIR)memcpy_app > ifunc_tst.out
	# Use ldd to get the libc.so location
	ldd $(OBJDIR)memcpy_app | grep " /[a-z,/,\.,0-9,_,-]*/libc\.so[\.,0-9]*" -o > ifunc_tst_libc.out
	# Use nm -D to get the list of libc.so dynamic symbols
	nm -D `cat ifunc_tst_libc.out` > ifunc_tst_nm.out
	# if memcpy is IFUNC symbol make sure ifunc_tst tool recognize it and make sure the function is called only once
	if grep "i memcpy" ifunc_tst_nm.out ; then \
		grep "Found IFUNC memcpy" ifunc_tst.out; \
		grep "ifunc memcpy called" ifunc_tst.out -c > ifunc_tst_num_calls.out; \
		echo "1" > ifunc_tst_num_calls_ref.out; \
		$(PIN_CMP) ifunc_tst_num_calls.out ifunc_tst_num_calls_ref.out ; \
	else \
		grep "Found non IFUNC memcpy" ifunc_tst.out; \
	fi
	rm ifunc_tst*.out
	rm $(@:.test=.failed)

ifunc_win_tst.test: $(OBJDIR)ifunc_tst${PINTOOL_SUFFIX} ifunc_win_tst.tested ifunc_win_tst.failed $(OBJDIR)memcpy_app
	$(PIN) -t $(OBJDIR)ifunc_tst$(PINTOOL_SUFFIX) -- ./$(OBJDIR)memcpy_app > ifunc_win_tst.out
	grep "Found non IFUNC memcpy" ifunc_win_tst.out
	rm ifunc_win_tst*.out
	rm $(@:.test=.failed)
    
syntax_tst.test: $(OBJDIR)syntax_tst${PINTOOL_SUFFIX} syntax_tst.tested syntax_tst.failed $(OBJDIR)sampleApp
	$(PIN) -t $(OBJDIR)syntax_tst$(PINTOOL_SUFFIX) -setsyntax 0 -- ./$(OBJDIR)sampleApp > setsyntax_0.out
	grep "call " setsyntax_0.out
	$(PIN) -t $(OBJDIR)syntax_tst$(PINTOOL_SUFFIX) -setsyntax 1 -- ./$(OBJDIR)sampleApp > setsyntax_1.out
	grep "callq" setsyntax_1.out
	$(PIN) -t $(OBJDIR)syntax_tst$(PINTOOL_SUFFIX) -setsyntax 2 -- ./$(OBJDIR)sampleApp > setsyntax_2.out
	grep "CALL_NEAR" setsyntax_2.out
	rm setsyntax_0.out setsyntax_1.out setsyntax_2.out
	rm $(@:.test=.failed)

callargs.test: $(OBJDIR)callargs${PINTOOL_SUFFIX} callargs.tested callargs.failed $(OBJDIR)foobar
	$(PIN) -t $< -- ./$(OBJDIR)foobar
	rm callargs.failed
	
context_stack_and_spill.test: $(OBJDIR)context_stack_and_spill${PINTOOL_SUFFIX} context_stack_and_spill.tested context_stack_and_spill.failed
	$(PIN) -t $(OBJDIR)context_stack_and_spill$(PINTOOL_SUFFIX) -context_at_trace 1  -compare_contexts 1 -reverse_compare_contexts 1 -- $(TESTAPP) makefile context_stack_and_spill.makefile.copy
	$(PIN_CMP) makefile context_stack_and_spill.makefile.copy
	rm context_stack_and_spill.makefile.copy; rm $(@:.test=.failed)
	
context_stack_and_spill_noinline_bridge.test: $(OBJDIR)context_stack_and_spill${PINTOOL_SUFFIX} context_stack_and_spill_noinline_bridge.tested context_stack_and_spill_noinline_bridge.failed
	$(PIN) -xyzzy  -inline_bridge 0  -t $(OBJDIR)context_stack_and_spill$(PINTOOL_SUFFIX) -context_at_trace 1  -compare_contexts 1 -reverse_compare_contexts 1 -- $(TESTAPP) makefile context_stack_and_spill.makefile.copy
	$(PIN_CMP) makefile context_stack_and_spill.makefile.copy
	rm context_stack_and_spill.makefile.copy; rm $(@:.test=.failed)

context-pc.test: $(OBJDIR)context-pc${PINTOOL_SUFFIX} context-pc.tested context-pc.failed
	$(PIN)  -t $<  -- $(TESTAPP) makefile context-pc.makefile.copy
	$(PIN_CMP) makefile context-pc.makefile.copy
	rm context-pc.makefile.copy; rm  context-pc.out; rm $(@:.test=.failed)

memory_addr_callback.test: $(OBJDIR)memory_addr_callback${PINTOOL_SUFFIX} memory_addr_callback.tested memory_addr_callback.failed
	$(PIN)  -t $<  -- $(TESTAPP) makefile memory_addr_callback.makefile.copy
	$(PIN_CMP) makefile memory_addr_callback.makefile.copy
	rm memory_addr_callback.makefile.copy; rm $(@:.test=.failed)

memory_callback_error.test: $(OBJDIR)memory_callback_error${PINTOOL_SUFFIX} memory_callback_error.tested memory_callback_error.failed
	-$(PIN)  -t $<  -- $(TESTAPP) makefile memory_callback_error.makefile.copy > memory_callback_error.out 2>&1
	grep -q "Illegal use of memory address callback and register parameters" memory_callback_error.out
	rm  memory_callback_error.out; rm $(@:.test=.failed)

toolwithoutso.test: $(OBJDIR)callargs${PINTOOL_SUFFIX} toolwithoutso.tested toolwithoutso.failed $(OBJDIR)foobar
	$(PIN) -t $(subst ${PINTOOL_SUFFIX},,$<) -- ./$(OBJDIR)foobar
	rm toolwithoutso.failed

toolpathwithoutso.test: $(OBJDIR)callargs${PINTOOL_SUFFIX} toolpathwithoutso.tested toolpathwithoutso.failed $(OBJDIR)foobar
	$(PIN) -t ../Tests/$(subst ${PINTOOL_SUFFIX},,$<) -- ./$(OBJDIR)foobar
	rm toolpathwithoutso.failed

verify-ia32.test: $(OBJDIR)verify${PINTOOL_SUFFIX} verify-ia32.tested verify-ia32.failed $(OBJDIR)loop
	$(PIN) -t $< -- ./$(OBJDIR)loop
	rm verify-ia32.failed
	
snprintf_non_inlined_bridge.test: $(OBJDIR)snprintf${PINTOOL_SUFFIX} snprintf_non_inlined_bridge.tested snprintf_non_inlined_bridge.failed
	$(PIN) -xyzzy -inline_bridge 0 -t $(OBJDIR)snprintf$(PINTOOL_SUFFIX) -- $(TESTAPP) makefile snprintf_non_inlined_bridge.makefile.copy
	$(PIN_CMP) makefile snprintf_non_inlined_bridge.makefile.copy
	rm snprintf_non_inlined_bridge.makefile.copy; rm $(@:.test=.failed)
	
reg.test: $(OBJDIR)reg${PINTOOL_SUFFIX} reg.tested reg.failed
	$(PIN)  -t $(OBJDIR)reg$(PINTOOL_SUFFIX) -- $(TESTAPP) makefile reg.makefile.copy
	$(PIN_CMP) makefile reg.makefile.copy
	rm reg.makefile.copy; rm $(@:.test=.failed) 
	
reg_ref_inlined.test: $(OBJDIR)reg_ref_inlined${PINTOOL_SUFFIX} reg_ref_inlined.tested reg_ref_inlined.failed
	$(PIN) -log_inline -xyzzy -logfile reg_ref_inlined.log -t $(OBJDIR)reg_ref_inlined$(PINTOOL_SUFFIX) -- $(TESTAPP) makefile reg_ref_inlined.makefile.copy
	$(PIN_CMP) makefile reg_ref_inlined.makefile.copy
	test `grep -c "NOT INLINED" reg_ref_inlined.log ` -le "4" 
	grep "INLINED" reg_ref_inlined.log > reg_ref_inlined.txt 
	rm reg_ref_inlined.makefile.copy; rm $(@:.test=.failed) reg_ref_inlined.log reg_ref_inlined.txt

verify-ia32-nocmov.test: $(OBJDIR)verify${PINTOOL_SUFFIX} verify-ia32-nocmov.tested verify-ia32-nocmov.failed $(OBJDIR)loop
	$(PIN) -xyzzy -nocmov 1 -t $< -- ./$(OBJDIR)loop
	rm verify-ia32-nocmov.failed

verify-nocmov.test : $(OBJDIR)verify$(PINTOOL_SUFFIX) verify-nocmov.tested verify-nocmov.failed $(TESTAPP)
	touch $<.makefile.copy; rm $<.makefile.copy
	$(PIN) -xyzzy -nocmov 1 -t $(OBJDIR)verify$(PINTOOL_SUFFIX) -- $(TESTAPP) makefile $<.makefile.copy
	$(PIN_CMP) makefile $<.makefile.copy
	rm $<.makefile.copy; rm $(@:.test=.failed)

verify-ipf.test: $(OBJDIR)verify${PINTOOL_SUFFIX} verify-ipf.tested verify-ipf.failed $(OBJDIR)ipf_branch
	$(PIN) -t $< -- ./$(OBJDIR)ipf_branch
	rm verify-ipf.failed

branch-ipf.test: branch-ipf.tested branch-ipf.failed $(OBJDIR)ipf_branch
	$(PIN) -- ./$(OBJDIR)ipf_branch
	rm branch-ipf.failed

check_env.test: $(OBJDIR)hello${PINTOOL_SUFFIX} check_env.tested check_env.failed
	./check_env.sh > check_env.before
	$(PIN) -t $< -- ./check_env.sh > check_env.tool.after
	$(PIN) -- ./check_env.sh > check_env.notool.after
	$(PIN_CMP) check_env.before check_env.tool.after
	$(PIN_CMP) check_env.before check_env.notool.after
	rm check_env.before check_env.tool.after check_env.notool.after check_env.failed

emu-bridge.test: $(OBJDIR)emu${PINTOOL_SUFFIX} emu-bridge.tested emu-bridge.failed
	touch emu-bridge.makefile.copy; rm emu-bridge.makefile.copy
	$(PIN) -xyzzy -inline 0 -t $< -- $(TESTAPP) makefile emu-bridge.makefile.copy
	$(PIN_CMP) makefile emu-bridge.makefile.copy
	rm emu-bridge.makefile.copy; rm emu-bridge.failed

win-emu-bridge.test: $(OBJDIR)emu${PINTOOL_SUFFIX} win-emu-bridge.tested win-emu-bridge.failed $(OBJDIR)lasterror
	$(PIN) -xyzzy -inline 0 -t $< -- $(OBJDIR)lasterror
	rm win-emu-bridge.failed	

checkaddress64.test: $(OBJDIR)checkaddress${PINTOOL_SUFFIX} checkaddress64.tested checkaddress64.failed $(OBJDIR)checkaddressapp
	$(PIN) -t $< -- ./$(OBJDIR)checkaddressapp
	rm checkaddress64.failed

thread.test: $(OBJDIR)thread${PINTOOL_SUFFIX} thread.tested thread.failed $(OBJDIR)threadApp
	$(PIN) -t $< -- ./$(OBJDIR)threadApp
	rm thread.failed

util.test: $(OBJDIR)util${PINTOOL_SUFFIX} util.tested util.failed $(TESTAPP)
	$(PIN) -t $< -- $(TESTAPP) makefile $<.makefile.copy
	rm util.failed

injectionStack.test: injectionStack.tested injectionStack.failed $(OBJDIR)mysetenv $(TESTAPP)
	touch injectionStack.makefile.copy; rm injectionStack.makefile.copy
	$(OBJDIR)mysetenv $(PIN) -- $(TESTAPP) makefile injectionStack.makefile.copy
	$(PIN_CMP) makefile injectionStack.makefile.copy
	rm injectionStack.failed injectionStack.makefile.copy

prefix.test: $(OBJDIR)prefix${PINTOOL_SUFFIX} prefix.tested prefix.failed $(OBJDIR)prefixApp
	$(PIN) -t $< -- $(OBJDIR)prefixApp
	rm prefix.failed

insMix.test: $(OBJDIR)insMix${PINTOOL_SUFFIX} insMix.tested insMix.failed $(OBJDIR)insMixApp
	$(PIN) -t $< -- $(OBJDIR)insMixApp
	rm insMix.failed

exitProcess.test: $(OBJDIR)exitProcess${PINTOOL_SUFFIX} exitProcess.tested exitProcess.failed $(OBJDIR)exitProcessApp
	$(PIN) -t $< -- $(OBJDIR)exitProcessApp
	rm exitProcess.failed


test_ebx_in_exceptions.test:  test_ebx_in_exceptions.tested test_ebx_in_exceptions.failed $(OBJDIR)test_ebx_in_exceptions
	$(PIN) -- $(OBJDIR)test_ebx_in_exceptions
	rm test_ebx_in_exceptions.failed


imageLoader.test: $(OBJDIR)imageLoad${PINTOOL_SUFFIX} $(TESTAPP) imageLoader.tested imageLoader.failed
ifeq ($(TARGET),ia32e)
	$(PIN) -t $< -l -o imageLoader.out -- /lib64/ld-linux-x86-64.so.2 $(TESTAPP) makefile imageLoader.makefile.copy
else
	$(PIN) -t $< -l -o imageLoader.out -- /lib/ld-linux.so.2 $(TESTAPP) makefile imageLoader.makefile.copy
endif
	grep cp imageLoader.out
	grep libc.so.6 imageLoader.out 
	rm imageLoader.makefile.copy imageLoader.out imageLoader.failed
	
$(OBJDIR)winapp_runs_pin: winapp_runs_pin.cpp
ifeq ($(TARGET),ia32e)
	#devenv winapp_runs_pin.sln /Rebuild "Release|x64"
	#cp x64/Release/winapp_runs_pin.exe $(OBJDIR)winapp_runs_pin.exe
else
	#devenv winapp_runs_pin.sln /Rebuild "Release|ia32"
	#cp ia32/Release/winapp_runs_pin.exe $(OBJDIR)winapp_runs_pin.exe
endif
	cp winapp_runs_pin_$(TARGET).xex $(OBJDIR)winapp_runs_pin.exe
	
$(OBJDIR)checkaddressapp: checkaddressapp.s
	$(APP_CC) $(APP_CXXFLAGS) -o $(OBJDIR)checkaddressapp $<
$(OBJDIR)correct_winapp_runs_pin_cmdline: correct_winapp_runs_pin_cmdline.cpp
	$(CXX) $(APP_CXXFLAGS) -o $(OBJDIR)correct_winapp_runs_pin_cmdline $<

$(OBJDIR)prefixApp: prefixApp.s
	$(APP_CC) $(APP_CXXFLAGS) -o $(OBJDIR)prefixApp $< -g

$(OBJDIR)insMixApp: insMixApp.s
	$(APP_CC) $(APP_CXXFLAGS) -o $(OBJDIR)insMixApp $< -g

$(OBJDIR)child_sig_while_execv_app: child_sig_while_execv_app.c
	$(APP_CC) $(NO_OPTIMIZE) $(NO_LOGO) $(APP_CXXFLAGS) $(DBG) ${OUTEXE}$@ $<

$(OBJDIR)child_sig_while_execv_simple_app: child_sig_while_execv_simple_app.c
	$(APP_CC) $(NO_OPTIMIZE) $(NO_LOGO) $(APP_CXXFLAGS) $(DBG) ${OUTEXE}$@ $<

$(OBJDIR)mysetenv: mysetenv.c
	$(APP_CC) $(NO_OPTIMIZE) $(NO_LOGO) $(APP_CXXFLAGS) $(DBG) ${OUTEXE}$@ $<

$(OBJDIR)foobar: foobar.c
	$(APP_CC) $(NO_OPTIMIZE) $(NO_LOGO) $(APP_CXXFLAGS) $(DBG) ${OUTEXE}$@ $<

$(OBJDIR)memcpy_app: memcpy_app.c
	$(APP_CC) $(NO_OPTIMIZE) $(NO_LOGO) $(APP_CXXFLAGS) $(DBG) ${OUTEXE}$@ $<

ifeq ($(TARGET_OS),w)
$(OBJDIR)test_ebx_in_exceptions_asm.o: test_ebx_in_exceptions_ia32_w.asm
	ml /nologo /c /Fo$@ $<
else
$(OBJDIR)test_ebx_in_exceptions_asm.o: test_ebx_in_exceptions_ia32_l.s
	$(APP_CXX) ${COPT} $(PIN_CXXFLAGS) ${OUTOPT}$@ $<
endif

$(OBJDIR)test_ebx_in_exceptions.o: $(TEST_EBX_IN_EXCEPTIONS_SRC)
	$(CXX) ${COPT} $(PIN_CXXFLAGS)  ${OUTOPT}$@ $<

$(OBJDIR)test_ebx_in_exceptions_xed_interface.o: test_ebx_in_exceptions_xed_interface.cpp
	$(CXX) ${COPT} $(PIN_CXXFLAGS) ${OUTOPT}$@ $<

$(OBJDIR)test_ebx_in_exceptions: $(OBJDIR)test_ebx_in_exceptions.o $(OBJDIR)test_ebx_in_exceptions_xed_interface.o $(OBJDIR)test_ebx_in_exceptions_asm.o
	${PIN_LD} ${PIN_LD_MACHINE_FLAGS}  $(LINK_DEBUG) ${LINK_OUT}$@$(EXEEXT) $< $(OBJDIR)test_ebx_in_exceptions_asm.o $(OBJDIR)test_ebx_in_exceptions_xed_interface.o ${PIN_LPATHS} $(PIN_XED_LIBS) $(DBG)

$(OBJDIR)illegalEnvp_app: illegalEnvp_app.c
	$(APP_CC) $(NO_OPTIMIZE) $(NO_LOGO) $(APP_CXXFLAGS) $(DBG) ${OUTEXE}$@ $<

$(OBJDIR)cp-pin: cp-pin.cpp
	${APP_CXX} $(CPPIN_FLAGS) $(APP_CXXFLAGS) ${OUTEXE}$@ $<

$(OBJDIR)ipf_branch: ipf_branch.s
	$(APP_CC) $(APP_CXXFLAGS) -static -o $@ ipf_branch.s

$(OBJDIR)loop: loop.s
	$(APP_CC) $(APP_CXXFLAGS) -static -o $@ loop.s

$(OBJDIR)sampleApp: sampleApp.s
	$(APP_CC) $(DBG_INFO_ALWAYS) $(NO_OPTIMIZE) -static -o $@ sampleApp.s

$(OBJDIR)lasterror: lasterror.cpp
	$(APP_CXX) $(APP_CXXFLAGS) ${OUTEXE}$@ $< 

$(OBJDIR)threadApp: threadApp.cpp
	$(APP_CXX) $(APP_CXXFLAGS) -o $(OBJDIR)threadApp $< $(APP_PTHREAD)

$(OBJDIR)statdyn_app: statdyn_app.cpp
	$(APP_CXX) $(APP_CXXFLAGS) -Wl,--export-dynamic -o $(OBJDIR)statdyn_app $< 

$(OBJDIR)exitProcessApp: exitProcessApp.c
	$(APP_CXX) $(APP_CXXFLAGS) ${OUTEXE}$@ $<

$(OBJDIR)sourceLocation_app: sourceLocation_app.cpp
	$(APP_CXX) $(APP_CXXFLAGS) -o $(OBJDIR)sourceLocation_app $< -ldl

$(OBJDIR)launcher_app: launcher_app.cpp
	$(APP_CXX) $(APP_CXXFLAGS) -o $(OBJDIR)launcher_app $< -ldl

$(OBJDIR)sourceLocation_img1.so: sourceLocation_img1.cpp
	$(APP_CXX) $(APP_CXXFLAGS) -fPIC -shared -o $(OBJDIR)sourceLocation_img1.so $<

$(OBJDIR)sourceLocation_img2.so: sourceLocation_img2.cpp
	$(APP_CXX) $(APP_CXXFLAGS) -fPIC -shared -o $(OBJDIR)sourceLocation_img2.so $<

ifeq ($(TARGET_OS),w)		
$(OBJDIR)$(AVX_SUPPORT_ASM_OBJ): avx_support_$(TARGET).asm
	mkdir -p $(OBJDIR)
	$(MASM) /nologo /c /Fo$@ $<
else
$(OBJDIR)$(AVX_SUPPORT_ASM_OBJ): avx_support_$(TARGET).s
	mkdir -p $(OBJDIR)
	$(APP_CC) ${APP_CXXFLAGS} -c avx_support_$(TARGET).s -o $(OBJDIR)avx_support_$(TARGET).o
endif

## build rules

$(OBJDIR)%.o : %.cpp
	$(CXX) ${COPT} $(CXXFLAGS) $(PIN_CXXFLAGS) ${OUTOPT}$@ $<
$(TOOLS): $(PIN_LIBNAMES)


$(TOOLS): %$(PINTOOL_SUFFIX) : %.o
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) ${LINK_OUT}$@ $< ${PIN_LPATHS} $(PIN_LIBS) $(DBG)

$(OBJDIR)context_stack_and_spill$(PINTOOL_SUFFIX): $(OBJDIR)context_stack_and_spill.o $(OBJDIR)$(AVX_SUPPORT_ASM_OBJ)
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) ${LINK_OUT}$@ $<	 $(OBJDIR)$(AVX_SUPPORT_ASM_OBJ) ${PIN_LPATHS} $(PIN_LIBS) $(DBG)	
	
## cleaning
clean:
	-rm -rf $(OBJDIR) *.out *.log *.tested *.failed  $(TEST_APPS) *.manifest

-include *.d
