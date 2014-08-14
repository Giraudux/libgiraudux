/**
 * \file scgi.h
 * \author Alexis Giraudet
 * \version 0.0
 * \date 
 * \brief 
 */

#ifndef SCGI_H
#define SCGI_H

#include <search.h>

#include "netstring.h"

struct scgi_s;
typedef struct scgi_s scgi_t;

int grdx_scgi_init(scgi_t * __scgi);
int grdx_scgi_add_header(const char * __name, const char * __value, scgi_t * __scgi);
char * grdx_scgi_get_header(const char * __name, const scgi_t * __scgi);
int grdx_scgi_del_header(const char * __name, scgi_t * __scgi);
/*int grdx_scgi_set_body(char * __body, scgi_t * __scgi);
char * grdx_scgi_get_body(const scgi_t * __scgi);
int grdx_scgi_read(char * __request, scgi_t * __scgi);
char * grdx_scgi_write(const scgi_t * __scgi);*/

#endif
