#include "../SimpleNamedHttplib/SimpleNamedHttplib.h"
#include <iostream>
#include <thread>

void method(const char* req, const char*, char* res, char* type)
{
	sprintf(res, "hello!");
}

void on_close(bool success)
{
	std::cout << (success ? "yes" : "no");
}
int main()
{
	
	return 0;
}