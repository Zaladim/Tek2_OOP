#ifndef DLL_H
#define DLL_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <dlfcn.h>

template <typename T>
class DLLoader {
	public:
		T *getInstance(const char *lib)
		{
			void *_handle = dlopen(lib, RTLD_LAZY);
			T* (*start)();
			if (!_handle) {
				std::cout << dlerror() << std::endl;
				return NULL;
			}
			start = (T* (*)())dlsym(_handle, "start");
			if (!start) {
				std::cout << dlerror() << std::endl;
				return NULL;
			}
			return (T*)start();
		}
		int close(void)
		{
			if (_handle)
				return 0;
			return (dlclose(_handle));
		}
	
	private:
		void *_handle;
};

#endif