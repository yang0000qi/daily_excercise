#include <unistd.h>

#include <iostream>

#include "proxy.h"
#include "refstring.h"

void foo( String c )
{
	std::cout<< c.data() << std::endl;
}

int main()
{
	/*
	 * String a("hello");
	String b(a);
	std::cout<< a.data() << std::endl;
	std::cout<< b.data() << std::endl;
	*/
	String b("hello");
	String c("world");
	std::cout<< b.data() << std::endl;
	std::cout<< c.data() << std::endl;
	b = c;
	std::cout<< b.data() << std::endl;

	//foo( c );

	std::cout<< c[1] << std::endl;
	c[1] = 'a';
	std::cout<< c[1] << std::endl;

	std::cout<< b.data() << std::endl;
	std::cout<< c.data() << std::endl;
	return 0;
}
