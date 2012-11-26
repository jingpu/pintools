#!/bin/csh
# This script purpose is to check if the machine supports "/usr/bin/chfn" command.
# return 1 if it does, 0 otherwise.

set ALL_RELEASES=("SUSE Linux Enterprise Server 11" "SUSE Linux Enterprise Server 10" "openSUSE 11.1" "SUSE LINUX Enterprise Server 9" "Red Hat Enterprise Linux Server release 6.0"  "Ubuntu 11.10" "Ubuntu 8.10" "Ubuntu 9.10" "MeeGo release 1.1" "MeeGo release 1.1.99")
set OSREL=`cat /etc/*release`
set FIRST = 1
set LENGTH = $#ALL_RELEASES

while ($FIRST <= $LENGTH)  
    echo $OSREL | grep "$ALL_RELEASES[$FIRST]" > /dev/null 
    set ANS = $status    
    if ($ANS == 0) then     
        echo 1
        exit 0       
    endif
    @ FIRST++
end    

echo 0
exit 1
