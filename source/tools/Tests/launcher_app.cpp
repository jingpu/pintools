/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2012 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */
/*
 * runpin_app.cpp
 *
 *  Created on: Feb 2, 2012
 *      Author: bkemper
 */
#include <stdlib.h>
#include <iostream>
#include <string>

bool check_token(const char* var) {
    // Check that LD_LIBRARY_PATH contains the required libraries to the VM.
    //
    char* raw_var = getenv(var);
    if (raw_var) {
        std::string var_value(raw_var);
        size_t pos_found = var_value.find("TOKEN");
        bool not_found_token = pos_found == std::string::npos;
        bool not_only_token = pos_found > 0;
        if (not_found_token || not_only_token)
            return false;
    } else {
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    // Check that LD_LIBRARY_PATH contains the required libraries to the VM.
    //
    if (!check_token("LD_LIBRARY_PATH") || !check_token("LD_ASSUME_KERNEL") ||
        !check_token("LD_BIND_NOW") || !check_token("LD_PRELOAD")) {
        std::cout << "Failed!" << std::endl;
        exit(1);
    }
    std::cout << "Success!" << std::endl;
    return 0;
}
