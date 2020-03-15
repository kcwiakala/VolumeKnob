#include <stdlib.h>

__extension__ typedef int __guard __attribute__((mode (__DI__)));

// void * operator new(size_t size)
// {
//   return malloc(size);
// }

// void operator delete(void * ptr)
// {
//   free(ptr);
// }

extern "C" {

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
void __cxa_pure_virtual(void) {};

}