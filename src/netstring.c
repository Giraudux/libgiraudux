#include "netstring.h"

int grdx_netstring_decode_ab(char ** __netstring_block, size_t * __netstring_len)
{
    char buffer[LEN_BUFFER_SIZE];
    size_t cpy_count;
    char * chr_ret;
    size_t len;
    char * end_ptr;
    size_t buffer_len;
    char * new_string;
    
    if((*__netstring_block)[(*__netstring_len)-1] != ',')
    {
        return 1;
    }
    cpy_count = ((*__netstring_len) < LEN_BUFFER_SIZE) ? (*__netstring_len) : LEN_BUFFER_SIZE;
    memcpy(buffer, *__netstring_block, sizeof(char)*cpy_count);
    chr_ret = memchr(buffer, ':', sizeof(char)*cpy_count);
    if(chr_ret == NULL)
    {
        return 2;
    }
    *chr_ret = '\0';
    len = strtoul(buffer, &end_ptr, 10);
    if(end_ptr == buffer)
    {
        return 3;
    }
    if(((len == 0) || (len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    buffer_len = strlen(buffer);
    if(len != ((*__netstring_len) - buffer_len - 2))
    {
        return 5;
    }
    
    memmove(*__netstring_block, (*__netstring_block)+buffer_len+1, sizeof(char)*len);
    new_string = realloc(*__netstring_block, sizeof(char)*len);
    if(new_string == NULL)
    {
        return 6;
    }
    *__netstring_len = len;
    *__netstring_block = new_string;
    
    return 0;
}

int grdx_netstring_encode_ab(char ** __string_block, size_t * __string_len)
{
    char buffer[LEN_BUFFER_SIZE];
    int buffer_len;
    char * new_netstring;
    size_t new_netstring_len;
    size_t old_string_len;
    
    buffer_len = snprintf(buffer, LEN_BUFFER_SIZE, "%lu", *__string_len);
    if(buffer_len < 1)
    {
        return 1;
    }
    new_netstring_len = (*__string_len)+buffer_len+2;
    new_netstring = realloc(*__string_block, sizeof(char)*new_netstring_len);
    if(new_netstring == NULL)
    {
        return 2;
    }
    old_string_len = *__string_len;
    *__string_len = new_netstring_len;
    *__string_block = new_netstring;
    memmove((*__string_block)+buffer_len+1, *__string_block, sizeof(char)*old_string_len);
    memcpy(*__string_block, buffer, sizeof(char)*buffer_len);
    (*__string_block)[buffer_len] = ':';
    (*__string_block)[(*__string_len)-1] = ',';
    
    return 0;
}

int grdx_netstring_decode_wb(wchar_t ** __netstring_block, size_t * __netstring_len)
{
    wchar_t buffer[LEN_BUFFER_SIZE];
    size_t cpy_count;
    wchar_t * chr_ret;
    size_t len;
    wchar_t * end_ptr;
    size_t buffer_len;
    wchar_t * new_string;
    
    if((*__netstring_block)[(*__netstring_len)-1] != L',')
    {
        return 1;
    }
    cpy_count = ((*__netstring_len) < LEN_BUFFER_SIZE) ? (*__netstring_len) : LEN_BUFFER_SIZE;
    wmemcpy(buffer, *__netstring_block, cpy_count);
    chr_ret = wmemchr(buffer, L':', cpy_count);
    if(chr_ret == NULL)
    {
        return 2;
    }
    *chr_ret = L'\0';
    len = wcstoul(buffer, &end_ptr, 10);
    if(end_ptr == buffer)
    {
        return 3;
    }
    if(((len == 0) || (len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    buffer_len = wcslen(buffer);
    if(len != ((*__netstring_len) - buffer_len - 2))
    {
        return 5;
    }
    
    wmemmove(*__netstring_block, (*__netstring_block)+buffer_len+1, len);
    new_string = realloc(*__netstring_block, sizeof(wchar_t)*len);
    if(new_string == NULL)
    {
        return 6;
    }
    *__netstring_len = len;
    *__netstring_block = new_string;
    
    return 0;
}

int grdx_netstring_to_string_wb(const wchar_t * __netstring_block, size_t __netstring_len, wchar_t ** __string_block, size_t * __string_len)
{
    wchar_t buffer[LEN_BUFFER_SIZE];
    size_t cpy_count;
    wchar_t * chr_ret;
    size_t len;
    wchar_t * end_ptr;
    size_t buffer_len;
#ifndef GRDX_NETSTRING_NO_ALLOC
    wchar_t * new_string;
#endif /* GRDX_NETSTRING_NO_ALLOC */
    
    if(__netstring_block[__netstring_len-1] != L',')
    {
        return 1;
    }
    cpy_count = (__netstring_len < LEN_BUFFER_SIZE) ? __netstring_len : LEN_BUFFER_SIZE;
    wmemcpy(buffer, __netstring_block, cpy_count);
    chr_ret = wmemchr(buffer, L':', cpy_count);
    if(chr_ret == NULL)
    {
        return 2;
    }
    *chr_ret = L'\0';
    len = wcstoul(buffer, &end_ptr, 10);
    if(end_ptr == buffer)
    {
        return 3;
    }
    if(((len == 0) || (len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    buffer_len = wcslen(buffer);
    if(len != (__netstring_len - buffer_len - 2))
    {
        return 5;
    }
    
    if(*__string_block == NULL)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 6;
#else /* GRDX_NETSTRING_NO_ALLOC */
        new_string = malloc(sizeof(wchar_t)*len);
        if(new_string == NULL)
        {
            return 6;
        }
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    else if(*__string_len <len)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 7;
#else /* GRDX_NETSTRING_NO_ALLOC */
        new_string = realloc(*__string_block, sizeof(wchar_t)*len);
        if(new_string == NULL)
        {
            return 7;
        }
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    *__string_block = new_string;
    *__string_len = len;
    wmemcpy(*__string_block, __netstring_block+buffer_len+1, len);
    
    return 0;
}

int grdx_netstring_encode_wb(wchar_t ** __string_block, size_t * __string_len)
{
    wchar_t buffer[LEN_BUFFER_SIZE];
    int buffer_len;
    wchar_t * new_netstring;
    size_t new_netstring_len;
    size_t old_string_len;
    
    buffer_len = swprintf(buffer, LEN_BUFFER_SIZE, L"%lu", *__string_len);
    if(buffer_len < 1)
    {
        return 1;
    }
    new_netstring_len = (*__string_len)+buffer_len+2;
    new_netstring = realloc(*__string_block, sizeof(wchar_t)*new_netstring_len);
    if(new_netstring == NULL)
    {
        return 2;
    }
    old_string_len = *__string_len;
    *__string_len = new_netstring_len;
    *__string_block = new_netstring;
    wmemmove((*__string_block)+buffer_len+1, *__string_block, old_string_len);
    wmemcpy(*__string_block, buffer, buffer_len);
    (*__string_block)[buffer_len] = L':';
    (*__string_block)[(*__string_len)-1] = L',';
    
    return 0;
}

int grdx_string_to_netstring_wb(const wchar_t * __string_block, size_t __string_len, wchar_t ** __netstring_block, size_t * __netstring_len)
{
    wchar_t buffer[LEN_BUFFER_SIZE];
    int buffer_len;
    wchar_t * new_netstring;
    size_t new_netstring_len;
    
    buffer_len = swprintf(buffer, LEN_BUFFER_SIZE, L"%lu", __string_len);
    if(buffer_len < 1)
    {
        return 1;
    }
    new_netstring_len = __string_len+buffer_len+2;
    
    if(*__netstring_block == NULL)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 2;
#else /* GRDX_NETSTRING_NO_ALLOC */
        new_netstring = malloc(sizeof(wchar_t)*new_netstring_len);
        if(new_netstring == NULL)
        {
            return 2;
        }
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    else if(*__netstring_len <new_netstring_len)
    {
#ifdef GRDX_NETSTRING_NO_ALLOC
        return 3;
#else /* GRDX_NETSTRING_NO_ALLOC */
        new_netstring = realloc(*__netstring_block, sizeof(wchar_t)*new_netstring_len);
        if(new_netstring == NULL)
        {
            return 3;
        }
#endif /* GRDX_NETSTRING_NO_ALLOC */
    }
    
    *__netstring_block = new_netstring;
    *__netstring_len = new_netstring_len;
    wmemcpy(*__netstring_block, buffer, buffer_len);
    (*__netstring_block)[buffer_len] = L':';
    wmemcpy((*__netstring_block)+buffer_len+1, __string_block, __string_len);
    (*__netstring_block)[(*__netstring_len)-1] = L',';
    
    return 0;
}

int grdx_netstring_check_a(const char * __netstring)
{
    return grdx_netstring_check_ab(__netstring, strlen(__netstring));
}

int grdx_netstring_check_ab(const char * __netstring_block, size_t __netstring_len)
{
    char buffer[LEN_BUFFER_SIZE];
    size_t cpy_count;
    char * chr_ret;
    size_t len;
    char * end_ptr;
    
    if(__netstring_block[__netstring_len-1] != ',')
    {
        return 1;
    }
    cpy_count = (__netstring_len < LEN_BUFFER_SIZE) ? __netstring_len : LEN_BUFFER_SIZE;
    memcpy(buffer, __netstring_block, cpy_count*sizeof(char));
    chr_ret = memchr(buffer, ':', cpy_count*sizeof(char));
    if(chr_ret == NULL)
    {
        return 2;
    }
    *chr_ret = '\0';
    len = strtoul(buffer, &end_ptr, 10);
    if(end_ptr == buffer)
    {
        return 3;
    }
    if(((len == 0) || (len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    if(len != (__netstring_len - strlen(buffer) - 2))
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
    wchar_t buffer[LEN_BUFFER_SIZE];
    size_t cpy_count;
    wchar_t * chr_ret;
    size_t len;
    wchar_t * end_ptr;
    
    if(__netstring_block[__netstring_len-1] != L',')
    {
        return 1;
    }
    cpy_count = (__netstring_len < LEN_BUFFER_SIZE) ? __netstring_len : LEN_BUFFER_SIZE;
    wmemcpy(buffer, __netstring_block, cpy_count);
    chr_ret = wmemchr(buffer, L':', cpy_count);
    if(chr_ret == NULL)
    {
        return 2;
    }
    *chr_ret = L'\0';
    len = wcstoul(buffer, &end_ptr, 10);
    if(end_ptr == buffer)
    {
        return 3;
    }
    if(((len == 0) || (len == ULONG_MAX)) && (errno == ERANGE))
    {
        return 4;
    }
    if(len != (__netstring_len - wcslen(buffer) - 2))
    {
        return 5;
    }
    return 0;
}
