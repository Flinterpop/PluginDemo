
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include "PlugInApi.h"
#include "POIPlugin.h"
#include <stddef.h> /* provides NULL */


MapPlugin* MapPlugin_ctor()
{
    POIPlugin* ptr2 = new POIPlugin("Id_03");
    return ptr2;
}


