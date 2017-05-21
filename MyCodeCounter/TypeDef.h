#pragma once
#include<new>

#define MY_DELETE(pValue) \
    if(pValue != NULL) \
    { \
        delete pValue; \
        pValue = NULL; \
    } 

#define MY_DELETE_A(pValue) \
    if(pValue != NULL) \
    { \
        delete [] pValue; \
        pValue = NULL; \
    } 

#define MY_NEW(Type, pValue) \
    try \
    { \
        pValue = new Type(); \
    } \
    catch( std::bad_alloc &) \
    { \
        MY_DELETE(pValue); \
        pValue = NULL; \
    } 

#define MY_NEW_A(Type, pValue, size) \
    try \
    { \
        pValue = new Type[size]; \
    } \
    catch( std::bad_alloc &ba) \
    { \
        MY_DELETE_A(pValue); \
        pValue = NULL; \
    } 


