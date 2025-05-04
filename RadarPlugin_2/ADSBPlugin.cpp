#ifndef PlugIn_API_H_Include
#define PlugIn_API_H_Include

//#include "stdio.h"
//#include "PluginApi.h"
#include "ADSBPlugin.h"


#ifdef WIN32 // declared when compiling with windows (if not, declare it)
#ifdef API_EXPORT // must be declared in Preprocessor Definitions
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif
#else
#define API
#endif

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif
#endif

