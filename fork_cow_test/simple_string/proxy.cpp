#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "proxy.h"

Proxy::Proxy( const char *sour )
	:count(1)
{
	printf("%p count increase : %ld\n", this, count);
	size = strlen( sour ) ;		
	str = new char[ size + 1];
	if ( !str )
		return;

	strncpy( str, sour, size + 1 );
}

Proxy::Proxy( const Proxy& rhs )
	:count(1)
{
	size = rhs.length();
	str = new char[size];

	strncpy( str, rhs.str, size );
}

Proxy::~Proxy()
{
	delete[] str;
	str = NULL;
}

size_t Proxy::length() const
{
	return size;
}

size_t Proxy::add_ref()
{
	printf("%p count increase : %ld\n", this, count+1);
	return ++count;
}

size_t Proxy::release()
{
	if ( ! (--count) )
	{
		printf("one instance delete\n");
		delete this;
	}
	else
		printf("%p count = %ld\n", this, count);
	return count;
}

const char* Proxy::data() const
{
	return str;
}

char& Proxy::operator[] ( int index )
{
	return str[index];
}

int Proxy::owner_count() const
{
	return  count;
}

