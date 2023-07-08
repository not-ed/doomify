#include "platform.h"

bool Platform::IsWindows() {
    #ifdef WINDOWS
    return true;
    #endif
    return false;
}

bool Platform::IsLinux() {
    #ifdef LINUX
    return true;
    #endif
    return false;
}