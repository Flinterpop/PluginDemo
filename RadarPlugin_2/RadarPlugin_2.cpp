
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>


// SamplePlugIn.cpp
#include  "PlugInApi.h"
#include <stddef.h> /* provides NULL */
#include <string> /* provides malloc and free */

const char* get_PlugInName() {
    return "SamplePlugIn_02";
}

MyObject* MyObject_ctor() {
    auto ptr = new MyObject();
    ptr->Id = "Id_02";
    ptr->Length = 10;
    ptr->Data = malloc(ptr->Length * sizeof(unsigned char));
    unsigned char* data = (unsigned char*)ptr->Data;
    for (unsigned int i = 0; i < ptr->Length; i++) {
        data[i] = 65 + i;
    }
    return ptr;
}

void MyObject_CopyTo(MyObject* ptr, MyObject* other) {
    other->Length = ptr->Length;
    other->Id = ptr->Id;
    other->Data = ptr->Data;
}

void MyObject_Dispose(MyObject* ptr) {
    if (ptr == NULL) { return; }
    if (ptr->Data != NULL) {
        free(ptr->Data);
        ptr->Data = NULL;
        ptr->Length = 0;
        ptr->Id = NULL;
    }
    delete ptr;
    ptr = NULL;
}

const char* MyObject_get_Id(MyObject* ptr) {
    if (ptr == NULL) { return NULL; }
    return ptr->Id;
}

void* MyObject_get_Data(MyObject* ptr) {
    if (ptr == NULL) { return NULL; }
    return ptr->Data;
}

const char* MyObject_get_Message(MyObject* ptr) {
    if (ptr == NULL || ptr->Data == NULL || ptr->Length < 1 || ptr->Id == NULL)
    {
        return "Object has been disposed";
    }
    return "Valid";
}

