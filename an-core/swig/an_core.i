/* an_core.i */

%module an_core

%{
#include "aero-node/system_info.h"
#include "aero-node/cam_capture.h"
%}

%include "../lib/system_info.cc"
%include "../lib/cam_capture.cc"