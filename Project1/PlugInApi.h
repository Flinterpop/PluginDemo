// PlugInApi.h
#ifndef PlugIn_API_H_Include
#define PlugIn_API_H_Include

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

    #include "stdio.h"
    
    class MapPlugin {
        public:
        const char* Id =0;

        virtual void pme(const char* str)
        {
            printf("MapPlugin (%s) pme\r\n%s\r\n", Id, str);
        };

        MapPlugin(const char * _Id)
        {
            Id = _Id;
            printf("In MapPlugin Constructor for %s\r\n",Id);
        };

        ~MapPlugin()
        {
            printf("In MapPlugin Destructor for %s\r\n", Id);
        };

    };
    

    /**
     * Initializes an object
     * @return a pointer to the object
     */
    API MapPlugin* MapPlugin_ctor();


    // Define the functions a PlugIn should have
    typedef MapPlugin* (WINAPIV* MyObject_ctor_func)();
    


#ifdef __cplusplus
}
#endif
#endif

