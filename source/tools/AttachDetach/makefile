## PIN tools
##

##############################################################
#
# Here are some	things you might want to configure
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
	include	../makefile.gnu.config
	STATIC=-static
endif

ifeq ($(TARGET_COMPILER),ms)
	include	../makefile.ms.config
	DBG?=
endif

ifneq ($(ENABLE_VS), 1)
	VS_FLAG	= -xyzzy -virtual_segments 1
else
	VS_FLAG	=
endif

SUF	= $(PINTOOL_SUFFIX)

###============================================================
##
## Set up the test tools
##

TEST_TOOLS = 
## linux only
## the tests run on ia32 and Intel64 
## Linux 2.4 is not supported
ifeq ($(TARGET_OS),l)
ifneq ($(TARGET),ipf)

ifeq ($(ATTACH_SUPPORTED),yes)
    TEST_TOOLS = jit_tool jit_detach_tool jit_instr_detach jit_anls_detach tls_check_tool simple_tool
    APPS = mt_attach verify_sigmask short_func_app mt_blocked mt_detach mt_thread tls_app_$(TARGET) \
                   reattach_probed_app reattach_verify_sigmask_app verify_fpstate_app \
                   attach_in_sighandler_app detach_in_sighandler_app mt_attach_and_execv threadOrder
	APPS += detach_probed_app read_write_app pause_msg_app hello_world detach_probed_wait_child_app

    TEST_ROOTS =  attach_jit verify_sigmask_jit attach_and_execv blocked_threads verify_fpstate attach_in_sighandler attach_in_sighandler1 pause_msg pause_msg1
    TEST_ROOTS += attach_twice attach_denied
    TEST_ROOTS += detach instr_detach anls_detach tls_check_detach
    TEST_ROOTS += detach_in_sighandler detach_in_sighandler1

ifeq ($(PROBE),1)
    TEST_TOOLS += imageLoad_tool probe_tool short_func_tool detach_probed_tool reattach_probed_tool threadOrder_tool
    TEST_ROOTS += l_imageLoad attach_probe short_func_instrumentation thread_order
    APPS += l_imageLoad_app
    ifeq ($(DETACH_SUPPORTED), yes)
        TEST_TOOLS += reattachImageLoadCallback_tool
        TEST_ROOTS += launchReattachImageLoadCallbacks attachReattachImageLoadCallbacks detach_probed reattach_probed reattach_verify_sigmask reattach_read_write detach_probed_wait_child
        APPS += launchReattachImageLoadCallbacks_app attachReattachImageLoadCallbacks_app
    endif
endif
endif
endif
endif

ifeq ($(TARGET_OS),l)
    DL_LIB = -ldl
else
    DL_LIB =
endif


# mac only
ifeq ($(TARGET_OS),m)
	TEST_TOOLS +=
endif

#windows only
ifeq ($(TARGET_OS),w)
	ifeq ($(TARGET_COMPILER),ms)
		TEST_TOOLS += w_attach_tool1 w_attach_tool2 w_attach_tool3 w_attach_tool4 w_attach_tool5
	endif
endif

###===========================================================

# windows only
ifeq ($(TARGET_OS),w)
	TEST_ROOTS +=	w_attach_tool1	w_attach_tool1_ror w_attach_tool1_detach_reattach w_attach_tool1_service
	TEST_ROOTS +=   w_attach_tool2 w_attach_tool2_detach_reattach_stress w_attach_tool3 w_attach_tool4 w_attach_tool5
	APPS = w_app1 w_app2 w_app3 w_app4 w_app_launcher
    ifeq ($(ATTACH_SUPPORTED),yes)
        ifeq ($(PROBE),1)
            TEST_TOOLS += imageLoad_tool
            APPS += w_imageLoad_app
            TEST_ROOTS += w_imageLoad
        endif
    endif
endif

APPS_BINARY_FILES = $(APPS:%=$(OBJDIR)%)
TOOLS =	$(TEST_TOOLS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))
TESTS_TO_RUN = $(TEST_ROOTS:%=%.test)



all: $(OBJDIR) $(TOOLS)	$(APPS_BINARY_FILES)

## sanity

SANITY_TESTS = $(TESTS_TO_RUN)


tests-sanity: $(OBJDIR)	$(SANITY_TESTS)


test: $(OBJDIR)	$(TESTS_TO_RUN)

$(OBJDIR):
	mkdir -p $(OBJDIR)

##======================================================
## Attach Windows tests
##======================================================

#Probes attach:

w_imageLoad.test: $(OBJDIR)imageLoad_tool$(PINTOOL_SUFFIX) $(OBJDIR)my_dll${PINTOOL_SUFFIX} $(OBJDIR)my_dll_1${PINTOOL_SUFFIX} $(OBJDIR)w_imageLoad_app $(OBJDIR)w_app_launcher w_imageLoad.tested w_imageLoad.failed
	rm -f pid1.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_imageLoad_app > pid_w_imageLoad_app.log
	$(PIN) -probe	-pid `cat pid_w_imageLoad_app.log` -t $(OBJDIR)imageLoad_tool$(PINTOOL_SUFFIX)
	cat imageLoad.out | grep "my_dll_1.dll" -o
	rm -f w_imageLoad.failed pid_w_imageLoad_app.log  imageLoad.out

w_attach_tool1.test	: $(OBJDIR)w_attach_tool1$(SUF)	w_attach_tool1.tested w_attach_tool1.failed	$(OBJDIR)w_app1	$(OBJDIR)w_app_launcher
	rm -f pid1.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app1	> pid1.log
	$(PIN) -probe -follow_execv	-pid `cat pid1.log` -t $<
	rm -f pid1.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app1	> pid1.log
	$(PIN) -probe -pid `cat pid1.log` -t $<
	rm -f w_attach_tool1.failed pid1.log

w_attach_tool1_ror.test	: $(OBJDIR)w_attach_tool1$(SUF)	w_attach_tool1_ror.tested w_attach_tool1_ror.failed	$(OBJDIR)w_app1	$(OBJDIR)w_app_launcher
	rm -f pid1_ror.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app1	> pid1_ror.log
	$(PIN) -probe -follow_execv -pid `cat pid1_ror.log` -t $<  -ror 1 -fc 2
	rm -f w_attach_tool1_ror.failed pid1_ror.log

w_attach_tool1_detach_reattach.test	: $(OBJDIR)w_attach_tool1$(SUF)	w_attach_tool1_detach_reattach.tested w_attach_tool1_detach_reattach.failed	$(OBJDIR)w_app1	$(OBJDIR)w_app_launcher
	rm -f detach_reattach.log
	$(PIN) -probe -detach_reattach 1 -follow_execv   -t $< -xyzzy  -attach_cycles 3 -fc 2	-- $(OBJDIR)w_app1 > detach_reattach.log
	rm -f detach_reattach.log pid1_detach_reattach
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app1	> pid1_detach_reattach.log
	$(PIN) -probe -detach_reattach 1 -follow_execv	-pid `cat pid1_detach_reattach.log` -t $< -attach_cycles 3 -fc 2
	rm -f w_attach_tool1_detach_reattach.failed pid1_detach_reattach.log

w_attach_tool1_service.test	: $(OBJDIR)w_attach_tool1$(SUF)	w_attach_tool1_service.tested w_attach_tool1_service.failed	$(OBJDIR)w_service_app1 $(OBJDIR)w_pin_service_launcher
	chmod 777 $(OBJDIR)
	rm -f pid1_service.log $(OBJDIR)w_service_app1.exe.service.log is_able_to_create_service.log
	$(OBJDIR)w_service_app1 -admin -create 2> is_able_to_create_service.log
	cat is_able_to_create_service.log
	$(OBJDIR)w_service_app1 -admin -start > pid1_service.log
	$(OBJDIR)w_pin_service_launcher -admin -create
	$(OBJDIR)w_pin_service_launcher -admin -start ../$(PIN) -probe -pid `cat pid1_service.log` -t ../$<
	$(OBJDIR)w_service_app1 -admin -stop
	$(OBJDIR)w_service_app1 -admin -delete
	$(OBJDIR)w_pin_service_launcher -admin -stop
	$(OBJDIR)w_pin_service_launcher -admin -delete
	grep "Failed to Create service" is_able_to_create_service.log || grep "Success! someone changed DoLoop on time" $(OBJDIR)w_service_app1.exe.service.log
	rm -f w_attach_tool1_service.failed pid1_service.log $(OBJDIR)w_service_app1.exe.service.log is_able_to_create_service.log

w_attach_tool2.test	: $(OBJDIR)w_attach_tool2$(SUF)	w_attach_tool2.tested w_attach_tool2.failed	$(OBJDIR)w_app1	$(OBJDIR)w_app_launcher
	rm -f pid2.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app1	> pid2.log
	$(PIN) -detach_reattach 1 -probe	-pid `cat pid2.log`	-t $<
	rm -f w_attach_tool2.failed pid2.log
	
w_attach_tool2_detach_reattach_stress.test	: $(OBJDIR)w_attach_tool2$(SUF)	w_attach_tool2_detach_reattach_stress.tested w_attach_tool2_detach_reattach_stress.failed	$(OBJDIR)w_app1	$(OBJDIR)w_app_launcher
	rm -f pid2_stress.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app1	> pid2_stress.log
	$(PIN) -detach_reattach 1 -probe	-pid `cat pid2_stress.log`	-t $< -stress_dr 10
	rm -f w_attach_tool2_detach_reattach_stress.failed pid2_stress.log
	
#Jit Attach	
	
w_attach_tool3.test	: $(OBJDIR)w_attach_tool3$(SUF)	w_attach_tool3.tested w_attach_tool3.failed	$(OBJDIR)w_app2	$(OBJDIR)w_app_launcher
	rm -f pid3.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app2	> pid3.log
	$(PIN) -pid `cat pid3.log` -t $<
	rm -f pid3.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app2	> pid3.log
	$(PIN) -follow_execv -pid `cat pid3.log` -t $<	-fc 1
	rm -f w_attach_tool3.failed pid3.log
	
w_attach_tool4.test	: $(OBJDIR)w_attach_tool4$(SUF)	w_attach_tool4.tested w_attach_tool4.failed	$(OBJDIR)w_app3	$(OBJDIR)w_app_launcher
	rm -f pid4.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app3	> pid4.log
	$(PIN) -pid `cat pid4.log` -t $<
	rm -f w_attach_tool4.failed pid4.log

w_attach_tool5.test	: $(OBJDIR)w_attach_tool5$(SUF)	w_attach_tool5.tested w_attach_tool5.failed	$(OBJDIR)w_app4	$(OBJDIR)w_app_launcher
	rm -f pid5.log w_app4.log
	$(OBJDIR)w_app_launcher	$(OBJDIR)w_app4	> pid5.log
	$(PIN) -pid `cat pid5.log` -t $<
	rm -f w_attach_tool5.failed pid5.log w_app4.log

##======================================================
## Attach Linux tests
##======================================================

launchReattachImageLoadCallbacks.test: %.test: $(OBJDIR)launchReattachImageLoadCallbacks_app $(OBJDIR)my_dll${PINTOOL_SUFFIX}  $(OBJDIR)my_dll_1${PINTOOL_SUFFIX} $(OBJDIR)reattachImageLoadCallback_tool${PINTOOL_SUFFIX} %.tested %.failed
	export LD_LIBRARY_PATH=`pwd`\/$(OBJDIR); $(PIN) -t $(OBJDIR)reattachImageLoadCallback_tool${PINTOOL_SUFFIX} -o launchReattachImageLoadCallbacks.out -- $<  $(OBJDIR)my_dll${PINTOOL_SUFFIX}  $(OBJDIR)my_dll_1${PINTOOL_SUFFIX}
	cat launchReattachImageLoadCallbacks.out | grep "$(OBJDIR)my_dll.so in iteration2" -o
	cat launchReattachImageLoadCallbacks.out | grep "$(OBJDIR)my_dll_1.so in iteration2" -o
	rm $*.failed $*.out


attachReattachImageLoadCallbacks.test: %.test: $(OBJDIR)attachReattachImageLoadCallbacks_app $(OBJDIR)my_dll${PINTOOL_SUFFIX} $(OBJDIR)my_dll_1${PINTOOL_SUFFIX}   $(OBJDIR)reattachImageLoadCallback_tool${PINTOOL_SUFFIX} %.tested %.failed
	export LD_LIBRARY_PATH=`pwd`\/$(OBJDIR);
	./$(OBJDIR)attachReattachImageLoadCallbacks_app $(OBJDIR)my_dll${PINTOOL_SUFFIX} $(OBJDIR)my_dll_1${PINTOOL_SUFFIX}  $(PIN) -probe  $(OBJDIR)reattachImageLoadCallback_tool${PINTOOL_SUFFIX} attachReattachImageLoadCallbacks.out
	cat attachReattachImageLoadCallbacks.out | grep "$(OBJDIR)my_dll.so in iteration2" -o
	cat attachReattachImageLoadCallbacks.out | grep "$(OBJDIR)my_dll_1.so in iteration2" -o
	rm $*.failed $*.out


l_imageLoad.test: $(OBJDIR)imageLoad_tool$(PINTOOL_SUFFIX) $(OBJDIR)my_dll${PINTOOL_SUFFIX} $(OBJDIR)my_dll_1${PINTOOL_SUFFIX} $(OBJDIR)l_imageLoad_app l_imageLoad.tested l_imageLoad.failed
	./$(OBJDIR)l_imageLoad_app $(OBJDIR)my_dll${PINTOOL_SUFFIX} $(OBJDIR)my_dll_1${PINTOOL_SUFFIX} $(PIN) -probe $(OBJDIR)imageLoad_tool${PINTOOL_SUFFIX}
	grep "in image callback of image: $(OBJDIR)my_dll_1.so"  imageLoad.out
	rm $(@:.test=.failed)  imageLoad.out

#change_mask.test: %.test: $(OBJDIR)change_mask$(PINTOOL_SUFFIX) $(OBJDIR)change_mask_app %.tested %.failed
#	./$(OBJDIR)change_mask_app $(PIN) $(OBJDIR)change_mask${PINTOOL_SUFFIX}
#	grep -e '^22*1*1' signal_list.txt
#	rm -f $*.failed signal_list.txt

attach_jit.test: %.test: $(OBJDIR)mt_attach $(OBJDIR)jit_tool${PINTOOL_SUFFIX} send_signals.sh %.tested %.failed
	./$< -th_num 6 -pin $(PIN) -pinarg  -t $(OBJDIR)jit_tool${PINTOOL_SUFFIX} -o $*.out
	#check that all 6 threads are attached
	grep "Thread counter" $*.out|grep -q 6
	rm -f $*.failed  $*.out pin.log
	
attach_twice.test: %.test: $(OBJDIR)mt_attach $(OBJDIR)jit_tool${PINTOOL_SUFFIX} send_signals.sh %.tested %.failed
	./$< -th_num 1  -attach_twice -pin $(PIN) -pinarg  -logfile $*.log -t $(OBJDIR)jit_tool${PINTOOL_SUFFIX} -o $*.out
	grep "Pin is already attached" $*.log
	rm -f $*.failed  $*.out pin.log $*.log

    
attach_probe.test: %.test: $(OBJDIR)mt_attach send_signals.sh $(OBJDIR)probe_tool${PINTOOL_SUFFIX} %.tested %.failed
	./$< -th_num 8 -pin $(PIN) -pinarg -t $(OBJDIR)probe_tool${PINTOOL_SUFFIX} -o $*.out
	grep "Thread counter" $*.out|grep -q 8
	grep -q "Application Start Callback" $*.out
	rm $*.failed  $*.out 
    
verify_sigmask_jit.test: %.test: $(OBJDIR)verify_sigmask $(OBJDIR)jit_tool${PINTOOL_SUFFIX} send_signals.sh %.tested %.failed        
	./$< -pin $(PIN) -pinarg -t $(OBJDIR)jit_tool${PINTOOL_SUFFIX} -o $*.out 
	rm $*.failed $*.out
    
short_func_instrumentation.test: %.test: $(OBJDIR)short_func_app $(OBJDIR)short_func_tool${PINTOOL_SUFFIX} %.tested %.failed
    #start 20 threads
	./$< -th_num 20 -pin $(PIN) -pinarg -t $(OBJDIR)short_func_tool${PINTOOL_SUFFIX} -o $*.out
	rm $*.failed $*.out
	
attach_and_execv.test: %.test: $(OBJDIR)mt_attach_and_execv $(OBJDIR)jit_tool${PINTOOL_SUFFIX} %.tested %.failed
	./$< -th_num 20 -pin $(PIN) -pinarg -follow_execv 1 -t $(OBJDIR)jit_tool${PINTOOL_SUFFIX} -o $*.out
	rm $*.failed $*.out
	
blocked_threads.test: %.test: $(OBJDIR)mt_blocked $(OBJDIR)jit_tool${PINTOOL_SUFFIX} %.tested %.failed
	./$< -pin $(PIN) -pinarg -xyzzy -mesgon log_fetch -logfile $(OBJDIR)$*.log -t $(OBJDIR)jit_tool${PINTOOL_SUFFIX} -o $*.out
	rm $*.failed $*.out


detach.test: %.test : $(OBJDIR)mt_detach $(OBJDIR)jit_detach_tool${PINTOOL_SUFFIX} %.tested %.failed
	./$< -th_num 7 -pin $(PIN) -pinarg -t $(OBJDIR)jit_detach_tool${PINTOOL_SUFFIX} -o $*.out
	rm $*.failed $*.out
	
instr_detach.test: %.test : $(OBJDIR)mt_thread $(OBJDIR)jit_instr_detach${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -t $(OBJDIR)jit_instr_detach${PINTOOL_SUFFIX} -- $(OBJDIR)mt_thread
	rm $*.failed

anls_detach.test: %.test : $(OBJDIR)mt_thread $(OBJDIR)jit_anls_detach${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -t $(OBJDIR)jit_anls_detach${PINTOOL_SUFFIX} -- $(OBJDIR)mt_thread
	rm $*.failed

tls_check_detach.test: %.test : $(OBJDIR)tls_app_$(TARGET) $(OBJDIR)tls_check_tool${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -t $(OBJDIR)tls_check_tool${PINTOOL_SUFFIX} -- $(OBJDIR)tls_app_$(TARGET) > $*.out 2>&1
	grep PASSED $*.out
	rm $*.failed $*.out
	
verify_fpstate.test: %.test : $(OBJDIR)verify_fpstate_app $(OBJDIR)jit_tool${PINTOOL_SUFFIX} %.tested %.failed
	./$< -pin $(PIN) -pinarg -t $(OBJDIR)jit_tool${PINTOOL_SUFFIX} -o $*.out
	rm $*.failed
	    
detach_probed.test: %.test: $(OBJDIR)detach_probed_app $(OBJDIR)detach_probed_tool${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -t $(OBJDIR)detach_probed_tool${PINTOOL_SUFFIX} -- $(OBJDIR)detach_probed_app > $*.out
	grep PASSED $*.out
	rm $*.failed $*.out
     
detach_probed_wait_child.test: %.test: $(OBJDIR)detach_probed_wait_child_app $(OBJDIR)detach_probed_tool${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -t $(OBJDIR)detach_probed_tool${PINTOOL_SUFFIX} -- $(OBJDIR)detach_probed_wait_child_app
	rm $*.failed

reattach_probed.test: %.test: $(OBJDIR)reattach_probed_app $(OBJDIR)reattach_probed_tool${PINTOOL_SUFFIX} %.tested %.failed
	export LD_LIBRARY_PATH=`pwd`\/$(OBJDIR); $(PIN) -t $(OBJDIR)reattach_probed_tool${PINTOOL_SUFFIX} -o reattach_probed_tool.out -- $<  	
	grep PASSED reattach_probed_tool.out
	rm $*.failed reattach_probed_tool.out
	
reattach_verify_sigmask.test: %.test: $(OBJDIR)reattach_verify_sigmask_app $(OBJDIR)reattach_probed_tool${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -t $(OBJDIR)reattach_probed_tool${PINTOOL_SUFFIX} -o $*.out -- $<
	grep PASSED $*.out
	rm $*.failed $*.out

reattach_read_write.test: %.test: $(OBJDIR)read_write_app $(OBJDIR)reattach_probed_tool${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -t $(OBJDIR)reattach_probed_tool${PINTOOL_SUFFIX} -o $*.out -- $<
	grep PASSED $*.out
	rm $*.failed $*.out
	
reattach_fork.test: %.test: $(OBJDIR)mt_fork_app $(OBJDIR)my_exe $(OBJDIR)reattach_probed_tool${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -follow_execv -t $(OBJDIR)reattach_probed_tool${PINTOOL_SUFFIX} -o $*.out -uniq -- $(OBJDIR)mt_fork_app $(OBJDIR)my_exe
	grep PASSED `grep -l mt_fork_app $*.out*`
	rm $*.failed $*.out*

attach_in_sighandler.test: %.test: $(OBJDIR)attach_in_sighandler_app $(OBJDIR)jit_tool${PINTOOL_SUFFIX} %.tested %.failed
	./$< -pin $(PIN) -pinarg  -t $(OBJDIR)jit_tool${PINTOOL_SUFFIX} -o $(OBJDIR)$*.log >$*.out  2>&1
	grep "xmm values are correct" $*.out
	rm $*.failed $*.out $(OBJDIR)$*.log

attach_in_sighandler1.test: %.test: $(OBJDIR)attach_in_sighandler_app $(OBJDIR)jit_tool${PINTOOL_SUFFIX} %.tested %.failed
	./$< -test 1 -pin $(PIN) -pinarg  -t $(OBJDIR)jit_tool${PINTOOL_SUFFIX} -o $(OBJDIR)$*.log >$*.out  2>&1
	grep "xmm values are correct" $*.out
	rm $*.failed $*.out $(OBJDIR)$*.log
                
detach_in_sighandler.test: %.test: $(OBJDIR)detach_in_sighandler_app $(OBJDIR)jit_detach_tool${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -t $(OBJDIR)jit_detach_tool${PINTOOL_SUFFIX} -o $(OBJDIR)$*.log -- $(OBJDIR)detach_in_sighandler_app >$*.out  2>&1
	grep "xmm values are correct" $*.out
	rm $*.failed $*.out $(OBJDIR)$*.log

detach_in_sighandler1.test: %.test: $(OBJDIR)detach_in_sighandler_app $(OBJDIR)jit_detach_tool${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -t $(OBJDIR)jit_detach_tool${PINTOOL_SUFFIX} -o $(OBJDIR)$*.log -- $(OBJDIR)detach_in_sighandler_app -test 1 >$*.out  2>&1
	grep "xmm values are correct" $*.out
	rm $*.failed $*.out $(OBJDIR)$*.log
    
pause_msg.test: %.test: $(OBJDIR)jit_tool${PINTOOL_SUFFIX} $(OBJDIR)pause_msg_app %.tested %.failed
	$(OBJDIR)pause_msg_app -pin $(PIN) -pinarg  -pause_tool 1 -t $(OBJDIR)jit_tool${PINTOOL_SUFFIX} -o $(OBJDIR)$*.log >$*.out  2>&1
	grep -q "Pausing to attach" $*.out
	grep -q "Resuming" $*.out
	rm $*.failed $*.out $(OBJDIR)$*.log

# use hello_world as simple application that writes somthing to standard output (the test makes sure pause msg is not overwritten)
pause_msg1.test: %.test: $(OBJDIR)hello_world $(OBJDIR)simple_tool${PINTOOL_SUFFIX} %.tested %.failed
	$(PIN) -pause_tool 1 -t $(OBJDIR)simple_tool${PINTOOL_SUFFIX} -- $(OBJDIR)hello_world >$*.out  2>&1
	grep -q "Pausing to attach" $*.out
	grep -q "Resuming" $*.out
	rm $*.failed $*.out
    
thread_order.test: %.test: $(OBJDIR)threadOrder $(OBJDIR)threadOrder_tool${PINTOOL_SUFFIX} thread_order.tested thread_order.failed
	$(OBJDIR)threadOrder $(PIN) $(OBJDIR)threadOrder_tool${PINTOOL_SUFFIX}
	$(PIN_CMP) threadOrder_master.out threadOrder_generated.out
	rm thread_order.failed threadOrder_master.out threadOrder_generated.out

attach_denied.test: %.test: %.tested %.failed
	-$(PIN) -pid 1 -error_file $*.out
	grep -q "<type>53</type>" $*.out
	rm $*.failed $*.out

##===================================================================================
## common and private build	rules for tools	and	applications
##==================================================================================

ifeq ($(TARGET_OS),w)
$(OBJDIR)my_dll_1.dll : my_dll.c
	$(CC) $(APP_CXXFLAGS) $(OUTEXE)$(OBJDIR)my_dll_1.dll  $< $(APP_CXXLINK_FLAGS) /DLL
$(OBJDIR)my_dll.dll : my_dll.c
	$(CC) $(APP_CXXFLAGS) $(OUTEXE)$(OBJDIR)my_dll.dll  $< $(APP_CXXLINK_FLAGS) /DLL
else
$(OBJDIR)my_dll_1.so : my_dll.c
	$(CC) $(APP_CXXFLAGS) ${OUTOPT}$@ -fpic -shared $< -g
$(OBJDIR)my_dll.so : my_dll.c
	$(CC) $(APP_CXXFLAGS) ${OUTOPT}$@ -fpic -shared $< -g
endif

$(OBJDIR)w_imageLoad_app: w_imageLoad_app.cpp
	$(CXX) ${NO_OPTIMIZE} ${APP_CXXFLAGS2} ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS)

$(OBJDIR)w_app1	: w_app1.cpp
	$(APP_CXX) ${NO_OPTIMIZE} ${APP_CXXFLAGS2} ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS)

$(OBJDIR)w_app2	: w_app2.cpp
	$(APP_CXX) ${NO_OPTIMIZE} ${APP_CXXFLAGS2} ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS)
	
$(OBJDIR)w_app3	: w_app3.cpp
	$(APP_CXX) ${NO_OPTIMIZE} ${APP_CXXFLAGS2} ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS)	

$(OBJDIR)w_app4	: w_app4.cpp
	$(APP_CXX) ${NO_OPTIMIZE} ${APP_CXXFLAGS2} ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS)
	
$(OBJDIR)w_service_app1	: w_service_app1.cpp
	$(APP_CXX) ${NO_OPTIMIZE} ${APP_CXXFLAGS2} ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) advapi32.lib

$(OBJDIR)w_app_launcher: w_app_launcher.cpp
	$(APP_CXX)	${APP_CXXFLAGS2} ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS)

$(OBJDIR)w_pin_service_launcher: w_pin_service_launcher.cpp
	$(APP_CXX)	${NO_OPTIMIZE} ${APP_CXXFLAGS2} ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) advapi32.lib

## Linux build rules

$(OBJDIR)launchReattachImageLoadCallbacks_app: launchReattachImageLoadCallbacks_app.cpp $(OBJDIR)my_dll.so
	$(CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread -ldl

$(OBJDIR)attachReattachImageLoadCallbacks_app: attachReattachImageLoadCallbacks_app.cpp $(OBJDIR)my_dll.so
	$(CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread -ldl

$(OBJDIR)l_imageLoad_app: l_imageLoad_app.cpp
	$(CXX) ${NO_OPTIMIZE} ${APP_CXXFLAGS2} ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) $(DL_LIB) -g

$(OBJDIR)verify_sigmask: verify_sigmask.cpp
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread

$(OBJDIR)mt_attach: mt_attach.cpp
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread

$(OBJDIR)mt_blocked: mt_blocked.cpp
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread

$(OBJDIR)mt_attach_and_execv: mt_attach_and_execv.cpp
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread

$(OBJDIR)short_func_app.o: short_func_app.cpp
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) $(COPT) ${NO_COMDAT_FLAG} $< -o $@
	
$(OBJDIR)short_func_app: $(OBJDIR)short_func_app.o short_func_$(TARGET).s
	$(APP_CXX) -O0 ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $^ $(APP_CXXLINK_FLAGS) -lpthread
	
$(OBJDIR)mt_detach: mt_detach.cpp
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread
	
$(OBJDIR)detach_probed_app: detach_probed_app.cpp
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread -ldl
	
$(OBJDIR)detach_probed_wait_child_app: detach_probed_wait_child_app.cpp
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread -ldl
        
$(OBJDIR)reattach_probed_app: reattach_probed_app.cpp $(OBJDIR)my_dll.so 
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread -ldl
	
$(OBJDIR)reattach_verify_sigmask_app: reattach_verify_sigmask_app.cpp
	$(APP_CXX) -O0 ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread 

#$(OBJDIR)change_mask_app: change_mask_app.c
#	$(APP_CC) -O0 ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread   
    
$(OBJDIR)read_write_app: read_write_app.cpp
	$(APP_CXX) -O0 ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) 
		
$(OBJDIR)my_dll.so : my_dll.c
	$(APP_CC) $(APP_CXXFLAGS) ${OUTOPT}$@ -fpic -shared $< -g

$(OBJDIR)my_exe : my_exe.c
	$(APP_CC) $(APP_CXXFLAGS) ${OUTOPT}$@ $< -g

$(OBJDIR)mt_fork_app: mt_fork_app.cpp
	$(CXX) ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread

$(OBJDIR)mt_thread: mt_thread.cpp
	$(APP_CXX) ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread

$(OBJDIR)tls_app_$(TARGET): tls_app_$(TARGET).cpp
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} ${OUTEXE}$@ $< $(APP_CXXLINK_FLAGS) -lpthread
	
$(OBJDIR)verify_fpstate_app: verify_fpstate_app.cpp $(OBJDIR)fp_save_restore.o
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} -c -o $(OBJDIR)verify_fpstate.o $<
	$(APP_CXX) ${APP_CXXFLAGS} $(DBG) $(OBJDIR)fp_save_restore.o $(OBJDIR)verify_fpstate.o $(APP_CXXLINK_FLAGS) -lpthread -o $@
        
$(OBJDIR)attach_in_sighandler_app: attach_in_sighandler_app.cpp $(OBJDIR)fp_save_restore.o
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} -c -o $(OBJDIR)attach_in_sighandler_app.o $<
	$(APP_CXX) ${APP_CXXFLAGS} $(DBG) $(OBJDIR)fp_save_restore.o $(OBJDIR)attach_in_sighandler_app.o $(APP_CXXLINK_FLAGS) -lpthread -o $@
        
$(OBJDIR)detach_in_sighandler_app: detach_in_sighandler_app.cpp $(OBJDIR)fp_save_restore.o
	$(APP_CXX) -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG} -c -o $(OBJDIR)detach_in_sighandler_app.o $<
	$(APP_CXX) ${APP_CXXFLAGS} $(DBG) $(OBJDIR)fp_save_restore.o $(OBJDIR)detach_in_sighandler_app.o $(APP_CXXLINK_FLAGS) -lpthread -o $@

$(OBJDIR)pause_msg_app: pause_msg_app.cpp 
	$(APP_CXX)  -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG}  -o $@ $< 

$(OBJDIR)hello_world: hello_world.cpp 
	$(APP_CXX)  -O0 --no-inline ${APP_CXXFLAGS} $(DBG) ${NO_COMDAT_FLAG}  -o $@ $< 

$(OBJDIR)threadOrder: threadOrder.cpp
	$(APP_CXX) ${APP_CXXFLAGS} -o $(OBJDIR)threadOrder $< -lpthread

$(OBJDIR)fp_save_restore.o: fp_save_restore_$(TARGET).s
	$(APP_CXX) ${APP_CXXFLAGS} -c fp_save_restore_$(TARGET).s -o $(OBJDIR)fp_save_restore.o
	
$(OBJDIR)%.o : %.cpp
	$(CXX) ${COPT} $(CXXFLAGS) $(PIN_CXXFLAGS) ${OUTOPT}$@ $<
    
$(TOOLS): $(OBJDIR)%$(PINTOOL_SUFFIX) :	$(OBJDIR)%.o $(PIN_LIBNAMES)
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) ${LINK_OUT}$@ $<	${PIN_LPATHS} $(PIN_LIBS) $(DBG)

## cleaning
clean:
	-rm	-rf	$(OBJDIR) *.tested *.failed	*.obj *.o *.out *.log* *.txt *.pdb


