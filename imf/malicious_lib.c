// malicious_lib.c
#include <stdio.h>
#include <string.h>


// Override strcmp function to always return that the strings are equla
// this way no matter what we pass as token when comparing it with de access token it will return success
int strcmp(const char *str1, const char *str2) {
    return 0;
}