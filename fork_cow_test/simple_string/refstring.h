#ifndef _STRING_STRING_H_
#define _STRING_STRING_H_

class String
{
	public:
		String( const char *str = "" );
		String( const String& );
		~String();
		String& operator= ( const String& );
		const char operator[] ( int index ) const;
		char& operator[] ( int index );
		const char* data() const;
	
	private:
		Proxy *proxy;
};

#endif
