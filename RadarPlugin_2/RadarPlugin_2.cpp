
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include "PlugInApi.h"
#include "ADSBPlugin.h"
#include <stddef.h> /* provides NULL */


MapPlugin* MapPlugin_ctor()
{
    ADSBPlugin* ptr2 = new ADSBPlugin("Id_02");
    return ptr2;
}

