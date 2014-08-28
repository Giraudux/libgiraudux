/**
 * \file netstring.h
 * \author Alexis Giraudet
 * \version 0.0
 * \date 
 * \brief 
 */

#ifndef NETSTRING_H
#define NETSTRING_H

#define LEN_BUFFER_SIZE 10

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \fn size_t giraudux_netstring_decode(const char * __netstring, size_t __max_len, const char ** __string)
 * \param __netstring
 * \param __max_len 
 * \param __string 
 * \return 
 * \brief 
 */
size_t giraudux_netstring_decode(const char * __netstring, size_t __max_len, const char ** __string);

#endif
