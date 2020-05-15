#include <stdio.h>

#include "KeLibTxtDl.h"          // TXT Lib
#include "FtShmem.h"             // TXT Transfer Area

static bool IsInit = false;

static double value_d;
static INT16 value_s;

extern "C" {

// Return value:
//  0: success, continue with waiting for pFinishVar becoming 1
//  1: not finished
//  2: busy (entity locked by other process)
// -1: error
// Other positive values can be used for other waiting codes
// Other negative values can be used for other error codes

int init(short* t)
{
    if(!IsInit)
    {
        // Do whatever inititialization is required
        value_d = 0.0;
        value_s = 0;
        IsInit = true;
    }
    return 0;
}

int setValueDouble(double v)
{
    if( !IsInit )
    {
        fprintf(stderr, "ExampleSLI:setValueDouble: Not initialized!\n");
        return -1;
    }
    value_d = v;
    printf( "ExampleSLI:setValueDouble: %lg\n", v);
    return 0;
}

int setValueShort(INT16 v)
{
    if( !IsInit )
    {
        fprintf(stderr, "ExampleSLI:setValueShort: Not initialized!\n");
        return -1;
    }
    value_s = v;
    printf( "ExampleSLI:setValueShort: %d\n", v);
    return 0;
}

int getValueDouble(double* v)
{
    if( !IsInit )
    {
        fprintf(stderr, "ExampleSLI:getValueDouble: Not initialized!\n");
        return -1;
    }
    *v = value_d;
    printf( "ExampleSLI:getValueDouble: %lg\n", *v);
    return 0;
}

int getValueShort(INT16* v)
{
    if( !IsInit )
    {
        fprintf(stderr, "ExampleSLI:getValueShort: Not initialized!\n");
        return -1;
    }
    *v = value_s;
    printf( "ExampleSLI:getValueShort: %d\n", *v);
    return 0;
}

} // extern "C"
