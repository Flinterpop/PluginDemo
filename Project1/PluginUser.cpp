// main.cpp
#include <iostream>
#include <windows.h>

#include "PlugInApi.h"

#include <vector>

std::string ExePath() {
    wchar_t wcbuffer[MAX_PATH];
    GetModuleFileName(NULL, wcbuffer, MAX_PATH);
    std::wstring wbuffer(wcbuffer);
    std::string buffer(wbuffer.begin(), wbuffer.end());
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

class LoadedMapPlugin
{
public:

    LoadedMapPlugin(HINSTANCE _h_Plugin, MapPlugin* _p_Plugin) 
    {
        h_Plugin = _h_Plugin;  //handle to the plugin
        p_Plugin = _p_Plugin;  //pointer to the plugins base class
    };

    HINSTANCE h_Plugin;
    MapPlugin* p_Plugin;
};

std::vector<LoadedMapPlugin*> pluginList;


int LoadAllPlugins();
void UnLoadAllPlugins();



int main(int argc, char** argv) {

    int retVal = LoadAllPlugins();
    if (0 == retVal)
    {
        puts("No Plugins Loaded");
        return EXIT_FAILURE;
    }
    
    for (auto v : pluginList)
        v->p_Plugin->pme("Test");
   
    
    UnLoadAllPlugins();
    
    getchar();


    return EXIT_SUCCESS;
}


void UnLoadAllPlugins()
{

    for (auto v : pluginList)
    {
        delete v->p_Plugin;
        FreeLibrary(v->h_Plugin);
    }

}

int LoadAllPlugins()
{
    WIN32_FIND_DATA fileData;
    std::string path = ExePath() + "\\*.dll";
    std::wstring stemp = std::wstring(path.begin(), path.end());
    LPCWSTR sw = stemp.c_str();
    HANDLE fileHandle = FindFirstFile(sw, &fileData);

    if (fileHandle == (HANDLE)ERROR_INVALID_HANDLE || fileHandle == (HANDLE)ERROR_FILE_NOT_FOUND)
    {
        printf("No PlugIns found\n");
        printf("\n\nPress any key to exit...\n");
        return EXIT_FAILURE;
    }
    path = ExePath() + "\\";

    do {
        try {
            std::wstring wst(fileData.cFileName);
            std::string st(wst.begin(), wst.end());
            std::string fullPath = path + st;
            stemp = std::wstring(fullPath.begin(), fullPath.end());
            LPCWSTR swt = stemp.c_str();

            printf("Loading Plugin: %s\r\n", st.c_str());

            HINSTANCE h_Plugin = LoadLibrary(swt);

            if (!h_Plugin || h_Plugin == NULL) {
                continue; // could not load
            }

            FARPROC MyObject_ctor_process = GetProcAddress(h_Plugin, "MapPlugin_ctor");
            if (MyObject_ctor_process == NULL) {
                // could not get process
                FreeLibrary(h_Plugin);
                continue;
            }


            MapPlugin* ptr = ((MyObject_ctor_func)MyObject_ctor_process)();
            LoadedMapPlugin* plugin = new LoadedMapPlugin(h_Plugin, ptr);
            pluginList.push_back(plugin);
            //plugin->p_Plugin->pme("Fred");

        }
        catch (...) {
            continue;
        }
    } while (FindNextFile(fileHandle, &fileData));

    return (int)pluginList.size();
}
