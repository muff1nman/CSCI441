#ifndef __config_h__
#define __config_h__

#cmakedefine DEBUG
#cmakedefine LOGGING

// FOR logging stuffs
#define sep " "
#define list_sep ", "
#define nested_start "[ "
#define nested_finish  "]"

#define LOG_LEVEL @LOG_LEVEL@

#define PROGRESS

#define DEFAULT_OUTPUT_FILE "output.ppm"

#ifdef DEBUG
#include <iostream>
#endif

#endif
