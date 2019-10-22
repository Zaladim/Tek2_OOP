#ifndef DLL_H
#define DLL_H

#include <string>
#include <stdlib.h>
#include <dlfcn.h>
#include "dyn.hpp"
#include "dyn2.hpp"

template <typename T>
class DLLoader {
	public:
		T *getInstance(const char *lib)
		{
			void *handle = dlopen(lib, RTLD_LAZY);
			T* (*entryPoint)();

			entryPoint = (T* (*)())dlsym(handle, "entryPoint");
			return (T*)entryPoint();
		}
};

#endif