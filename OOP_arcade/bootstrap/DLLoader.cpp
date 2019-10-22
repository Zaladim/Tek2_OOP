#include "DLLoader.hpp"
#include "IDisplayModule.hpp"

template <typename T>
T* DLLoader<T>::getInstance(const char *lib)
{
	void *handle = dlopen(lib, RTLD_LAZY);
	T* (*entryPoint)();

	entryPoint = (T* (*)())dlsym(handle, "entryPoint");
	return (T*)entryPoint();
}