#include <unistd.h>
#include <string.h>

#include "proxy.h"
#include "refstring.h"

String::String( const char* str )
	:proxy( new Proxy(str) )
{
	
}

String::String( const String& str)
{
	str.proxy->add_ref();
	proxy = str.proxy;
}

String::~String()
{
	proxy->release();
}

String& String::operator= ( const String& str )
{
	if ( &str == this )
		return *this;

	proxy->release();
	str.proxy->add_ref();
	proxy = str.proxy; 
	return *this;
}

const char* String::data() const
{
	return proxy->data();
}

const char String::operator [] ( int index ) const 
{
	const char res =  (*proxy)[index] ;
	return res;
}

char& String::operator [] ( int index )
{
	if ( proxy->owner_count() > 1 )
	{
		/*
		size_t length = proxy->length();
		char *new_str = new char[length];
		strncpy( new_str, proxy->data(), length );
		Proxy *new_proxy = new Proxy( new_str );
		*/
		Proxy *new_proxy = new Proxy(*proxy);
		proxy->release();
		proxy = new_proxy;
	}
	return (*proxy)[index];
}


