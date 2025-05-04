
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>


// SamplePlugIn.cpp
#include  "PlugInApi.h"
#include <stddef.h> /* provides NULL */


MapPlugin* MapPlugin_ctor() 
{
    MapPlugin *ptr = new MapPlugin("Id_01");
    return ptr;
}





