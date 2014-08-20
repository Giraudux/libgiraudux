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
    char _buffer[LEN_BUFFER_SIZE];
    size_t _cpy_count;
    char * _chr_ret;
    size_t _len;
    char * _end_ptr;
    size_t _buffer_len;
    unsigned short i;
        
    _cpy_count = (__max_len < LEN_BUFFER_SIZE) ? __max_len : LEN_BUFFER_SIZE;
    memcpy(_buffer, __netstring, _cpy_count*sizeof(char));
    _chr_ret = memchr(_buffer, ':', _cpy_count*sizeof(char));
    if(_chr_ret == NULL)
    {
        return 1;
    }
    *_chr_ret = '\0';
    for(i=0; i<_cpy_count; i++)
    {
		if(_buffer[i] == '\0')
		{
			break;
		}
		if(isdigit(_buffer[i]) == 0)
		{
			return 2;
		}
	}
    errno = 0;
    _len = strtoul(_buffer, &_end_ptr, 10);
    if((errno == ERANGE && (_len == ULONG_MAX || _len == 0)) || (errno != 0 && _len == 0))
    {
        return 3;
    }
    if(_end_ptr == _buffer)
    {
        return 4;
    }
    _buffer_len = strlen(_buffer);
    if((_buffer_len+1+_len+1) > __max_len)
    {
		return 5;
	}
    if(__netstring[_buffer_len+1+_len] != ',')
    {
        return 6;
    }
    return 0;
}
