/**
 * \file netstring.c
 * \author Alexis Giraudet
 * \version 0.0
 * \date 
 * \brief 
 */

#include "netstring.h"

#ifndef GRDX_NETSTRING_NO_ALLOC
int grdx_netstring_decode_ab(char ** __netstring_block, size_t * __netstring_len)
{
    char _buffer[LEN_BUFFER_SIZE];
    size_t _cpy_count;
    char * _chr_ret;
    size_t _len;
    char * _end_ptr;
    size_t _buffer_len;
    char * _new_string;
    
    if((*__netstring_block)[(*__netstring_len)-1] != ',')
    {
        return 1;
    }
    _cpy_count = ((*__netstring_len) < LEN_BUFFER_SIZE) ? (*__netstring_len) : LEN_BUFFER_SIZE;
    memcpy(_buffer, *__netstring_block, sizeof(char)*_cpy_count);
    _chr_ret = memchr(_buffer, ':', sizeof(char)*_cpy_count);
    if(_chr_ret == NULL)
    {
        return 2;
    }
    *_chr_ret = '\0';
    _len = strtoul(_buffer, &_end_ptr, 10);
    if(_end_ptr == _buffer)
    {
        return 3;
    }
    if(((_len == 0) || (_len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    _buffer_len = strlen(_buffer);
    if(_len != ((*__netstring_len) - _buffer_len - 2))
    {
        return 5;
    }
    
    memmove(*__netstring_block, (*__netstring_block)+_buffer_len+1, sizeof(char)*_len);
    _new_string = realloc(*__netstring_block, sizeof(char)*_len);
    if(_new_string == NULL)
    {
        return 6;
    }
    *__netstring_len = _len;
    *__netstring_block = _new_string;
    
    return 0;
}
#endif /* GRDX_NETSTRING_NO_ALLOC */

#ifndef GRDX_NETSTRING_NO_ALLOC
int grdx_netstring_encode_ab(char ** __string_block, size_t * __string_len)
{
    char _buffer[LEN_BUFFER_SIZE];
    int _buffer_len;
    char * _new_netstring;
    size_t _new_netstring_len;
    size_t _old_string_len;
    
    _buffer_len = snprintf(_buffer, LEN_BUFFER_SIZE, "%lu", *__string_len);
    if(_buffer_len < 1)
    {
        return 1;
    }
    _new_netstring_len = (*__string_len)+_buffer_len+2;
    _new_netstring = realloc(*__string_block, sizeof(char)*_new_netstring_len);
    if(_new_netstring == NULL)
    {
        return 2;
    }
    _old_string_len = *__string_len;
    *__string_len = _new_netstring_len;
    *__string_block = _new_netstring;
    memmove((*__string_block)+_buffer_len+1, *__string_block, sizeof(char)*_old_string_len);
    memcpy(*__string_block, _buffer, sizeof(char)*_buffer_len);
    (*__string_block)[_buffer_len] = ':';
    (*__string_block)[(*__string_len)-1] = ',';
    
    return 0;
}
#endif /* GRDX_NETSTRING_NO_ALLOC */

#ifndef GRDX_NETSTRING_NO_ALLOC
int grdx_netstring_decode_wb(wchar_t ** __netstring_block, size_t * __netstring_len)
{
    wchar_t _buffer[LEN_BUFFER_SIZE];
    size_t _cpy_count;
    wchar_t * _chr_ret;
    size_t _len;
    wchar_t * _end_ptr;
    size_t _buffer_len;
    wchar_t * _new_string;
    
    if((*__netstring_block)[(*__netstring_len)-1] != L',')
    {
        return 1;
    }
    _cpy_count = ((*__netstring_len) < LEN_BUFFER_SIZE) ? (*__netstring_len) : LEN_BUFFER_SIZE;
    wmemcpy(_buffer, *__netstring_block, _cpy_count);
    _chr_ret = wmemchr(_buffer, L':', _cpy_count);
    if(_chr_ret == NULL)
    {
        return 2;
    }
    *_chr_ret = L'\0';
    _len = wcstoul(_buffer, &_end_ptr, 10);
    if(_end_ptr == _buffer)
    {
        return 3;
    }
    if(((_len == 0) || (_len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    _buffer_len = wcslen(_buffer);
    if(_len != ((*__netstring_len) - _buffer_len - 2))
    {
        return 5;
    }
    
    wmemmove(*__netstring_block, (*__netstring_block)+_buffer_len+1, _len);
    _new_string = realloc(*__netstring_block, sizeof(wchar_t)*_len);
    if(_new_string == NULL)
    {
        return 6;
    }
    *__netstring_len = _len;
    *__netstring_block = _new_string;
    
    return 0;
}
#endif /* GRDX_NETSTRING_NO_ALLOC */

int grdx_netstring_to_string_wb(const wchar_t * __netstring_block, size_t __netstring_len, wchar_t ** __string_block, size_t * __string_len)
{
    wchar_t _buffer[LEN_BUFFER_SIZE];
    size_t _cpy_count;
    wchar_t * _chr_ret;
    size_t _len;
    wchar_t * _end_ptr;
    size_t _buffer_len;
#ifndef GRDX_NETSTRING_NO_ALLOC
    wchar_t * _new_string;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    
    if(__netstring_block[__netstring_len-1] != L',')
    {
        return 1;
    }
    _cpy_count = (__netstring_len < LEN_BUFFER_SIZE) ? __netstring_len : LEN_BUFFER_SIZE;
    wmemcpy(_buffer, __netstring_block, _cpy_count);
    _chr_ret = wmemchr(_buffer, L':', _cpy_count);
    if(_chr_ret == NULL)
    {
        return 2;
    }
    *_chr_ret = L'\0';
    _len = wcstoul(_buffer, &_end_ptr, 10);
    if(_end_ptr == _buffer)
    {
        return 3;
    }
    if(((_len == 0) || (_len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    _buffer_len = wcslen(_buffer);
    if(_len != (__netstring_len - _buffer_len - 2))
    {
        return 5;
    }

    if(*__string_block == NULL)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 6;
#else /* GRDX_NETSTRING_NO_ALLOC */
        _new_string = malloc(sizeof(wchar_t)*_len);
        if(_new_string == NULL)
        {
            return 6;
        }
        *__string_block = _new_string;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    else if(*__string_len < _len)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 7;
#else /* GRDX_NETSTRING_NO_ALLOC */
        _new_string = realloc(*__string_block, sizeof(wchar_t)*_len);
        if(_new_string == NULL)
        {
            return 7;
        }
        *__string_block = _new_string;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    *__string_len = _len;
    wmemcpy(*__string_block, __netstring_block+_buffer_len+1, _len);
    
    return 0;
}

#ifndef GRDX_NETSTRING_NO_ALLOC
int grdx_netstring_encode_wb(wchar_t ** __string_block, size_t * __string_len)
{
    wchar_t _buffer[LEN_BUFFER_SIZE];
    int _buffer_len;
    wchar_t * _new_netstring;
    size_t _new_netstring_len;
    size_t _old_string_len;
    
    _buffer_len = swprintf(_buffer, LEN_BUFFER_SIZE, L"%lu", *__string_len);
    if(_buffer_len < 1)
    {
        return 1;
    }
    _new_netstring_len = (*__string_len)+_buffer_len+2;
    _new_netstring = realloc(*__string_block, sizeof(wchar_t)*_new_netstring_len);
    if(_new_netstring == NULL)
    {
        return 2;
    }
    _old_string_len = *__string_len;
    *__string_len = _new_netstring_len;
    *__string_block = _new_netstring;
    wmemmove((*__string_block)+_buffer_len+1, *__string_block, _old_string_len);
    wmemcpy(*__string_block, _buffer, _buffer_len);
    (*__string_block)[_buffer_len] = L':';
    (*__string_block)[(*__string_len)-1] = L',';
    
    return 0;
}
#endif /* GRDX_NETSTRING_NO_ALLOC */

int grdx_string_to_netstring_wb(const wchar_t * __string_block, size_t __string_len, wchar_t ** __netstring_block, size_t * __netstring_len)
{
    wchar_t _buffer[LEN_BUFFER_SIZE];
    int _buffer_len;
    #ifndef GRDX_NETSTRING_NO_ALLOC
    wchar_t * _new_netstring;
    #endif /* GRDX_NETSTRING_NO_ALLOC */
    size_t _new_netstring_len;
    
    _buffer_len = swprintf(_buffer, LEN_BUFFER_SIZE, L"%lu", __string_len);
    if(_buffer_len < 1)
    {
        return 1;
    }
    _new_netstring_len = __string_len+_buffer_len+2;
    
    if(*__netstring_block == NULL)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 2;
#else /* GRDX_NETSTRING_NO_ALLOC */
        _new_netstring = malloc(sizeof(wchar_t)*_new_netstring_len);
        if(_new_netstring == NULL)
        {
            return 2;
        }
        *__netstring_block = _new_netstring;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    else if(*__netstring_len < _new_netstring_len)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 3;
#else /* GRDX_NETSTRING_NO_ALLOC */
        _new_netstring = realloc(*__netstring_block, sizeof(wchar_t)*_new_netstring_len);
        if(_new_netstring == NULL)
        {
            return 3;
        }
        *__netstring_block = _new_netstring;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    *__netstring_len = _new_netstring_len;
    wmemcpy(*__netstring_block, _buffer, _buffer_len);
    (*__netstring_block)[_buffer_len] = L':';
    wmemcpy((*__netstring_block)+_buffer_len+1, __string_block, __string_len);
    (*__netstring_block)[_new_netstring_len-1] = L',';
    
    return 0;
}

int grdx_netstring_check_a(const char * __netstring)
{
    return grdx_netstring_check_ab(__netstring, strlen(__netstring));
}

int grdx_netstring_check_ab(const char * __netstring_block, size_t __netstring_len)
{
    char _buffer[LEN_BUFFER_SIZE];
    size_t _cpy_count;
    char * _chr_ret;
    size_t _len;
    char * _end_ptr;
    
    if(__netstring_block[__netstring_len-1] != ',')
    {
        return 1;
    }
    _cpy_count = (__netstring_len < LEN_BUFFER_SIZE) ? __netstring_len : LEN_BUFFER_SIZE;
    memcpy(_buffer, __netstring_block, _cpy_count*sizeof(char));
    _chr_ret = memchr(_buffer, ':', _cpy_count*sizeof(char));
    if(_chr_ret == NULL)
    {
        return 2;
    }
    *_chr_ret = '\0';
    _len = strtoul(_buffer, &_end_ptr, 10);
    if(_end_ptr == _buffer)
    {
        return 3;
    }
    if(((_len == 0) || (_len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    if(_len != (__netstring_len - strlen(_buffer) - 2))
    {
        return 5;
    }
    return 0;
}

int grdx_netstring_check_w(const wchar_t * __netstring)
{
    return grdx_netstring_check_wb(__netstring, wcslen(__netstring));
}

int grdx_netstring_check_wb(const wchar_t * __netstring_block, size_t __netstring_len)
{
    wchar_t _buffer[LEN_BUFFER_SIZE];
    size_t _cpy_count;
    wchar_t * _chr_ret;
    size_t _len;
    wchar_t * _end_ptr;
    
    if(__netstring_block[__netstring_len-1] != L',')
    {
        return 1;
    }
    _cpy_count = (__netstring_len < LEN_BUFFER_SIZE) ? __netstring_len : LEN_BUFFER_SIZE;
    wmemcpy(_buffer, __netstring_block, _cpy_count);
    _chr_ret = wmemchr(_buffer, L':', _cpy_count);
    if(_chr_ret == NULL)
    {
        return 2;
    }
    *_chr_ret = L'\0';
    _len = wcstoul(_buffer, &_end_ptr, 10);
    if(_end_ptr == _buffer)
    {
        return 3;
    }
    if(((_len == 0) || (_len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    if(_len != (__netstring_len - wcslen(_buffer) - 2))
    {
        return 5;
    }
    return 0;
}

int grdx_netstring_to_string_ab(const char * __netstring_block, size_t __netstring_len, char ** __string_block, size_t * __string_len)
{
    char _buffer[LEN_BUFFER_SIZE];
    size_t _cpy_count;
    char * _chr_ret;
    size_t _len;
    char * _end_ptr;
    size_t _buffer_len;
#ifndef GRDX_NETSTRING_NO_ALLOC
    char * _new_string;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    
    if(__netstring_block[__netstring_len-1] != ',')
    {
        return 1;
    }
    _cpy_count = (__netstring_len < LEN_BUFFER_SIZE) ? __netstring_len : LEN_BUFFER_SIZE;
    memcpy(_buffer, __netstring_block, sizeof(char)*_cpy_count);
    _chr_ret = memchr(_buffer, ':', sizeof(char)*_cpy_count);
    if(_chr_ret == NULL)
    {
        return 2;
    }
    *_chr_ret = '\0';
    _len = strtoul(_buffer, &_end_ptr, 10);
    if(_end_ptr == _buffer)
    {
        return 3;
    }
    if(((_len == 0) || (_len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    _buffer_len = strlen(_buffer);
    if(_len != (__netstring_len - _buffer_len - 2))
    {
        return 5;
    }

    if(*__string_block == NULL)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 6;
#else /* GRDX_NETSTRING_NO_ALLOC */
        _new_string = malloc(sizeof(char)*_len);
        if(_new_string == NULL)
        {
            return 6;
        }
        *__string_block = _new_string;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    else if(*__string_len < _len)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 7;
#else /* GRDX_NETSTRING_NO_ALLOC */
        _new_string = realloc(*__string_block, sizeof(char)*_len);
        if(_new_string == NULL)
        {
            return 7;
        }
        *__string_block = _new_string;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    *__string_len = _len;
    memcpy(*__string_block, __netstring_block+_buffer_len+1, sizeof(char)*_len);
    
    return 0;
}

int grdx_string_to_netstring_ab(const char * __string_block, size_t __string_len, char ** __netstring_block, size_t * __netstring_len)
{
    char _buffer[LEN_BUFFER_SIZE];
    int _buffer_len;
    #ifndef GRDX_NETSTRING_NO_ALLOC
    char * _new_netstring;
    #endif /* GRDX_NETSTRING_NO_ALLOC */
    size_t _new_netstring_len;
    
    _buffer_len = snprintf(_buffer, LEN_BUFFER_SIZE, "%lu", __string_len);
    if(_buffer_len < 1)
    {
        return 1;
    }
    _new_netstring_len = __string_len+_buffer_len+2;
    
    if(*__netstring_block == NULL)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 2;
#else /* GRDX_NETSTRING_NO_ALLOC */
        _new_netstring = malloc(sizeof(char)*_new_netstring_len);
        if(_new_netstring == NULL)
        {
            return 2;
        }
        *__netstring_block = _new_netstring;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    else if(*__netstring_len < _new_netstring_len)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 3;
#else /* GRDX_NETSTRING_NO_ALLOC */
        _new_netstring = realloc(*__netstring_block, sizeof(char)*_new_netstring_len);
        if(_new_netstring == NULL)
        {
            return 3;
        }
        *__netstring_block = _new_netstring;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    *__netstring_len = _new_netstring_len;
    memcpy(*__netstring_block, _buffer, sizeof(char)*_buffer_len);
    (*__netstring_block)[_buffer_len] = ':';
    memcpy((*__netstring_block)+_buffer_len+1, __string_block, sizeof(char)*__string_len);
    (*__netstring_block)[_new_netstring_len-1] = ',';
    
    return 0;
}
