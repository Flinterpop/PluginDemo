#ifndef ADSBPlugIn_API_H_Include
#define ADSBPlugIn_API_H_Include

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



    class ADSBPlugin :  public MapPlugin {
    public:
       
        int cost = 45;

        void pme(const char* str) 
        {
            printf("ADSBPlugin (%s) pme\r\n%s\r\n", Id, str);
        };


        ADSBPlugin(const char* _Id) : MapPlugin{ _Id }
        {
            printf("In ADSBPlugin Constructor for %s\r\n", Id);
        };

        ~ADSBPlugin()
        {
            printf("In ADSBPlugin Destructor for %s\r\n", Id);
        };
       
 

        API ADSBPlugin* ADSB_MapPlugin_ctor();


        // Define the functions a PlugIn should have
        typedef ADSBPlugin* (WINAPIV* MapPlugin_ctor)();




    };


#ifdef __cplusplus
}
#endif
#endif

