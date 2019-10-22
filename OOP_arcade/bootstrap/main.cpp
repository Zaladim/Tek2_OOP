#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <iostream>
#include "IDisplayModule.hpp"
#include "DLLoader.hpp"

int main(void)
{
	IDisplayModule* dyn;
	DLLoader<IDisplayModule> loader;

	dyn = loader.getInstance("./libdyn.so");
	dyn->init();
	dyn->stop();
	dyn = loader.getInstance("./libdyn2.so");
	dyn->init();
	dyn->stop();

	/*void *handle = dlopen("./libdyn.so", RTLD_LAZY);
	void *handle2 = dlopen("./libdyn2.so", RTLD_LAZY);
	IDisplayModule* (*entryPoint)();

	entryPoint = (IDisplayModule* (*)())dlsym(handle, "entryPoint");
	IDisplayModule* dyn = (IDisplayModule*)entryPoint();
	dyn->init();
	dyn->stop();
	entryPoint = (IDisplayModule* (*)())dlsym(handle2, "entryPoint");
	IDisplayModule* dyn2 = (IDisplayModule*)entryPoint();
	dyn2->init();
	dyn2->stop();*/
}