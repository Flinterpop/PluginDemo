// main.cpp
#include <iostream>
#include <windows.h>

// The header common to all PlugIns
#include "PlugInApi.h"

// Define the functions a PlugIn should have
typedef const char* (WINAPIV* get_PlugInName_func)();
typedef MyObject* (WINAPIV* MyObject_ctor_func)();
typedef void (WINAPIV* MyObject_Dispose_func)(MyObject*);
typedef void (WINAPIV* MyObject_CopyTo_func)(MyObject*, MyObject*);
typedef const char* (WINAPIV* MyObject_get_Id_func)(MyObject*);
typedef void* (WINAPIV* MyObject_get_Data_func)(MyObject*);

/// <summary>
///     Gets a human-readable copy of the data
/// </summary>
/// <param name="obj">A pointer a MyObject instance</param>
/// <returns>A character array (a string)</returns>
char* GetDataString(MyObject* obj) {
    char* str = (char*)malloc(sizeof(char) * (3 * obj->Length + 1));
    char* ret = str;
    char* data = (char*)obj->Data;
    *(str++) = '[';
    for (int i = 0; i < obj->Length - 1; i++) {
        *(str++) = data[i];
        *(str++) = ',';
        *(str++) = ' ';
    }
    *(str++) = data[obj->Length - 1];
    *(str++) = ']';
    *(str++) = '\0';
    return ret;
}

/// <summary>
///     Gets the current execution directory
/// </summary>
/// <returns>A std::string giving the path (no slash at the end)</returns>
std::string ExePath() {
    wchar_t wcbuffer[MAX_PATH];
    GetModuleFileName(NULL, wcbuffer, MAX_PATH);
    std::wstring wbuffer(wcbuffer);
    std::string buffer(wbuffer.begin(), wbuffer.end());
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

/// <summary>
///     The main function is called at program startup after
///     initialization of the non-local objects
/// </summary>
/// <param name="argc">
///     Non-negative value representing the number of arguments
///     passed to the program.
/// </param>
/// <param name="argv">
///     Pointer to the first element of an array of argc + 1 pointers,
///     of which the last one is null and the previous ones, if any,
///     point to null-terminated ('\0') multibyte strings
/// </param>
/// <returns>0 for success</returns>
int main(int argc, char** argv) {

    // The data for each file we find.
    WIN32_FIND_DATA fileData;

    // The number of PlugIns loaded
    int loaded = 0;

    std::string path = ExePath() + "\\*.dll";
    std::wstring stemp = std::wstring(path.begin(), path.end());
    LPCWSTR sw = stemp.c_str();
    HANDLE fileHandle = FindFirstFile(sw, &fileData);

    if (fileHandle == (HANDLE)ERROR_INVALID_HANDLE ||
        fileHandle == (HANDLE)ERROR_FILE_NOT_FOUND) {
        printf("No PlugIns found\n"); \
            printf("\n\nPress any key to exit...\n"); \
            getchar();
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
            HINSTANCE temp = LoadLibrary(swt);

            if (!temp || temp == NULL) {
                continue; // could not load
            }

            auto get_PlugInName_process = GetProcAddress(temp, "get_PlugInName");
            auto MyObject_ctor_process = GetProcAddress(temp, "MyObject_ctor");
            auto MyObject_Dispose_process = GetProcAddress(temp, "MyObject_Dispose");
            auto MyObject_CopyTo_process = GetProcAddress(temp, "MyObject_CopyTo");
            auto MyObject_get_Id_process = GetProcAddress(temp, "MyObject_get_Id");
            auto MyObject_get_Data_process = GetProcAddress(temp, "MyObject_get_Data");

            if (get_PlugInName_process == NULL ||
                MyObject_ctor_process == NULL ||
                MyObject_Dispose_process == NULL ||
                MyObject_CopyTo_process == NULL ||
                MyObject_get_Id_process == NULL ||
                MyObject_get_Data_process == NULL) {

                // could not get process
                FreeLibrary(temp);
                continue;
            }
            printf("Loaded %s\n", st.c_str());
            printf("PlugIn Name:      %s\n", ((get_PlugInName_func)get_PlugInName_process)());

            auto ptr = ((MyObject_ctor_func)MyObject_ctor_process)();
            printf("Object Id:        %s\n", ((MyObject_get_Id_func)MyObject_get_Id_process)(ptr));
            printf("   Length:        %d\n", ptr->Length);
            auto data = GetDataString(ptr);
            printf("     Data:        %s\n", data);
            free(data);
            ((MyObject_Dispose_func)MyObject_Dispose_process)(ptr);

            FreeLibrary(temp);

            loaded++;
        }
        catch (...) {
            continue;
        }
    } while (FindNextFile(fileHandle, &fileData));


    printf("\n\nPress any key to exit...\n");
    getchar();
    return loaded > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

