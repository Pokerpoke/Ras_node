/* an_core.i */

%module an_core

%{
#include "an-core/system_info.h"
#include "an-core/cam_capture.h"
%}

%include "../lib/system_info.cc"
%include "../lib/cam_capture.cc"