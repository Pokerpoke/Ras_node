/* an_core.i */

%module an_core

%{
#include "aeronode/system_info.h"
#include "aeronode/cam_capture.h"
%}

%include "../lib/system_info.cc"
%include "../lib/cam_capture.cc"