/**
 * \file netstring.c
 * \author Alexis Giraudet
 * \version 0.0
 * \date 
 * \brief 
 */

#include "netstring.h"

int giraudux_netstring_check(const char * __netstring, size_t __max_len)
{
	size_t _len;
	int _err;
	
	_err = 0;
	errno = 0;
	_len = giraudux_netstring_len(__netstring, __max_len);
	if((_len == 0) && (errno != 0))
	{
		_err = errno;
	}
	return _err;
}

size_t giraudux_netstring_len(const char * __netstring, size_t __max_len)
{
	int _err;
    char _buffer[LEN_BUFFER_SIZE];
    size_t _cpy_count;
    char * _chr_ret;
    size_t _len;
    char * _end_ptr;
    size_t _buffer_len;
    unsigned short _i;
    
    _err = 0;
    if((__netstring == NULL) || (__max_len < 3))
    {
		_err = 1;
	}
	else
	{
		_cpy_count = (__max_len < LEN_BUFFER_SIZE) ? __max_len : LEN_BUFFER_SIZE;
		memcpy(_buffer, __netstring, _cpy_count*sizeof(char));
		_chr_ret = memchr(_buffer, ':', _cpy_count*sizeof(char));
		if(_chr_ret == NULL)
		{
			_err = 2;
		}
		else
		{
			*_chr_ret = '\0';
			for(_i=0; _i<_cpy_count; _i++)
			{
				if((isdigit(_buffer[_i]) == 0) || (_buffer[_i] == '\0'))
				{
					break;
				}
			}
			if((_buffer+_i) != _chr_ret)
			{
				_err = 3;
			}
			else
			{
				errno = 0;
				_len = strtoul(_buffer, &_end_ptr, 10);
				if((errno == ERANGE && (_len == ULONG_MAX || _len == 0)) || (errno != 0 && _len == 0))
				{
					_err = 4;
				}
				else
				{
					if(_end_ptr == _buffer)
					{
						_err = 5;
					}
					else
					{
						_buffer_len = strlen(_buffer);
						if((_buffer_len+1+_len+1) > __max_len)
						{
							_err = 6;
						}
						else
						{
							if(__netstring[_buffer_len+1+_len] != ',')
							{
								_err = 7;
							}
						}
					}
				}
			}
		}
	}
	if(_err != 0)
	{
		_len = 0;
		errno = _err;
	}
    return _len;
}

#ifndef GIRAUDUX_NETSTRING_NO_ALLOC
struct giraudux_string_s giraudux_netstring_decode_ma(const char * __netstring, size_t __max_len)
{
	struct giraudux_string_s _string;
	struct giraudux_string_s _decode_ret;
	
	_string.content = NULL;
	_string.length = 0;
	_decode_ret = giraudux_netstring_decode(__netstring, __max_len);
	if((_decode_ret.content != NULL) && (_decode_ret.length > 0))
	{
		_string.content = malloc(sizeof(char)*_decode_ret.length);
		if(_string.content != NULL)
		{
			memcpy(_string.content, _decode_ret.content, _decode_ret.length);
			_string.length = _decode_ret.length;
		}
	}
	return _string;
}
#endif /* GIRAUDUX_NETSTRING_NO_ALLOC */

#ifndef GIRAUDUX_NETSTRING_NO_ALLOC
/*struct giraudux_string_s giraudux_netstring_encode_ma(const char * __string, size_t __len);*/
#endif /* GIRAUDUX_NETSTRING_NO_ALLOC */

struct giraudux_string_s giraudux_netstring_decode(const char * __netstring, size_t __max_len)
{
	struct giraudux_string_s _string;
	
	_string.content = NULL;
	errno = 0;
	_string.length = giraudux_netstring_len(__netstring, __max_len);
	if((_string.length > 0) && (errno == 0))
	{
		_string.content = ((char*)memchr(__netstring, ':', __max_len*sizeof(char)))+1;
	}
	return _string;
}
