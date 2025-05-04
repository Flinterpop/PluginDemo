#ifndef POIPlugIn_API_H_Include
#define POIPlugIn_API_H_Include

#include "stdio.h"
#include "PluginApi.h"


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



    class POIPlugin : public MapPlugin {
    public:

        int cost = 45;

        void pme(const char* str)
        {
            printf("ADSBPlugin (%s) pme\r\n%s\r\n", Id, str);
        };


        POIPlugin(const char* _Id) : MapPlugin{ _Id }
        {
            printf("In ADSBPlugin Constructor for %s\r\n", Id);
        };

        ~POIPlugin()
        {
            printf("In ADSBPlugin Destructor for %s\r\n", Id);
        };



        API POIPlugin* POI_MapPlugin_ctor();


        // Define the functions a PlugIn should have
        typedef POIPlugin* (WINAPIV* MapPlugin_ctor)();




    };


#ifdef __cplusplus
}
#endif
#endif


