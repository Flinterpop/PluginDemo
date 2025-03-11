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

    struct MyObject {
        unsigned int Length;
        const char* Id;
        void* Data;
    };

    /**
     * Gets the name of the PlugIn
     * @return a character array
     */
    API const char* get_PlugInName();

    /**
     * Initializes an object
     * @return a pointer to the object
     */
    API MyObject* MyObject_ctor();

    /**
     * Copies the object (very shallow)
     * @param ptr a pointer to the object
     * @param other a pointer another object
     * @return a MyObject
     */
    API void MyObject_CopyTo(MyObject* ptr, MyObject* other);

    /**
     * Disposes of the object
     * @param ptr a pointer to the object
     * @return void
     */
    API void MyObject_Dispose(MyObject* ptr);

    /**
     * Gets the object's ID
     * @param ptr a pointer to the object
     * @return a character array
     */
    API const char* MyObject_get_Id(MyObject* ptr);

    /**
     * Gets a pointer to the object data
     * @param ptr a pointer to the object
     * @return a byte array
     */
    API void* MyObject_get_Data(MyObject* ptr);

    /**
     * Gets the last error/debug message on the object
     * @param ptr a pointer to the object
     * @return a character array
     */
    API const char* MyObject_get_Message(MyObject* ptr);

#ifdef __cplusplus
}
#endif
#endif

