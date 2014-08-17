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
        
    _cpy_count = (__max_len < LEN_BUFFER_SIZE) ? __max_len : LEN_BUFFER_SIZE;
    memcpy(_buffer, __netstring, _cpy_count*sizeof(char));
    _chr_ret = memchr(_buffer, ':', _cpy_count*sizeof(char));
    if(_chr_ret == NULL)
    {
        return 1;
    }
    *_chr_ret = '\0';
    _len = strtoul(_buffer, &_end_ptr, 10);
    if(_end_ptr == _buffer)
    {
        return 2;
    }
    if(((_len == 0) || (_len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 3;
    }
    _buffer_len = strlen(_buffer);
    if(__netstring[_buffer_len+1+_len] != ',')
    {
        return 4;
    }
    return 0;
}
