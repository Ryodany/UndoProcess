#include <iostream>

#include "Process.h"

int main()
{
	Process p;
	p.process1("install");
	p.process2("temp", "install");
	p.undoProcess();

	std::getchar();

	return 0;
}