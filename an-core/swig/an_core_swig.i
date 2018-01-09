/* system_info_swig.i */

%module an-core

%{
#include "system_info.h"
#include "tcp_client.h"
%}

%include "system_info.h"
%include "tcp_client.h"