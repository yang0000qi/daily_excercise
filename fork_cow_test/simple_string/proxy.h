#ifndef _STRING_PROXY_H_
#define _STRING_PROXY_H_

class Proxy
{
	public:
		Proxy( const char *str = "");
		Proxy( const Proxy& );
		virtual ~Proxy();
		size_t length() const;
		size_t add_ref();
		size_t release();
		const char* data() const;
		char& operator [] ( int index ) ;
		int owner_count() const;

	private:
		void init( const char* str);

	private:
		size_t count;
		char *str;
		size_t size;
};

#endif
