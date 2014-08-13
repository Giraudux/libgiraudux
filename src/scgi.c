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
    char * name;
    char * value;
};

struct scgi_s
{
    void * tree_header;
    char * body;
    size_t body_len;
};

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
    void * _tsearch_res;
    
    _header = malloc(sizeof(struct header_s));
    if(_header == NULL)
    {
        return 1;
    }
    _header->name = strdup(__name);
    _header->value = strdup(__value);
    _tsearch_res = tsearch(_header , &(__scgi->tree_header), compare_header);
    if(_tsearch_res == NULL)
    {
        free(_header);
        return 2;
    }
    return 0;
}

char * grdx_scgi_get_header(char * __name, const scgi_t * __scgi)
{
    return 0;
}
