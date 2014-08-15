/**
 * \file scgi.c
 * \author Alexis Giraudet
 * \version 0.0
 * \date 
 * \brief 
 */

#include "scgi.h"

struct header_s
{
    const char * name;
    char * value;
};

int free_header_s(struct header_s * __header);

int compare_header(const void * hs1, const void * hs2)
{
    return strcmp(((const struct header_s *)hs1)->name,((const struct header_s *)hs2)->name);
}

int grdx_scgi_init(scgi_t * __scgi)
{
    __scgi->tree_header = NULL;
    __scgi->body = NULL;
    __scgi->body_len = 0;
    return 0;
}

int grdx_scgi_add_header(const char * __name, const char * __value, scgi_t * __scgi)
{
    struct header_s * _header;
    void * _tsearch_ret;
    
    _header = malloc(sizeof(struct header_s));
    if(_header == NULL)
    {
        return 1;
    }
    _header->name = strdup(__name);
    _header->value = strdup(__value);
    _tsearch_ret = tsearch(_header , &(__scgi->tree_header), compare_header);
    if(_tsearch_ret == NULL)
    {
        free_header_s(_header);
        return 2;
    }
    return 0;
}

char * grdx_scgi_get_header(const char * __name, const scgi_t * __scgi)
{
    struct header_s _header_key;
    void * _tfind_ret;
    
    _header_key.name = __name;
    _header_key.value = NULL;
    _tfind_ret = tfind(&_header_key, &(__scgi->tree_header), compare_header);
    if(_tfind_ret == NULL)
    {
        return NULL;
    }
    return (*((struct header_s**)_tfind_ret))->value;
}

int grdx_scgi_del_header(const char * __name, scgi_t * __scgi)
{
    struct header_s _header_key;
    void * _tfind_ret;
    void * _tdelete_ret;
    struct header_s * _header_del;
    
    _header_key.name = __name;
    _header_key.value = NULL;
    _tfind_ret = tfind(&_header_key, &(__scgi->tree_header), compare_header);
    if(_tfind_ret == NULL)
    {
        return 1;
    }
    _header_del = *((struct header_s**)_tfind_ret);
    _tdelete_ret = tdelete(&_header_key, &(__scgi->tree_header), compare_header);
    if(_tdelete_ret == NULL)
    {
        return 2;
    }
    return free_header_s(_header_del);
}

int free_header_s(struct header_s * __header)
{
    int res = 0;
    
    if(__header == NULL)
    {
        res++;
    }
    else
    {
        if(__header->name == NULL)
        {
            res+=2;
        }
        else
        {
            free((char*)(__header->name));
        }
        if(__header->value == NULL)
        {
            res+=3;
        }
        else
        {
            free(__header->value);
        }
        free(__header);
    }
    return res;
}
