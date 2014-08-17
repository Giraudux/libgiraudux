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

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

/*typedef giraudux_string_s giraudux_string_t;*/

struct giraudux_string_s
{
    char * content;
    size_t length;
};

/**
 * \fn int giraudux_netstring_check(const char * __netstring, size_t __max_len)
 * \param __netstring 
 * \param __max_len 
 * \return 
 * \brief 
 */
int giraudux_netstring_check(const char * __netstring, size_t __max_len);

/**
 * \fn int giraudux_netstring_decode_re(char ** __netstring, size_t * __max_len)
 * \param __netstring
 * \param __max_len 
 * \return 
 * \brief 
 */
#ifndef GIRAUDUX_NETSTRING_NO_ALLOC
int giraudux_netstring_decode_re(char ** __netstring, size_t * __max_len);
#endif /* GIRAUDUX_NETSTRING_NO_ALLOC */

/**
 * \fn int giraudux_netstring_encode_re(char ** __string, size_t * __len)
 * \param __string
 * \param __len 
 * \return 
 * \brief 
 */
#ifndef GIRAUDUX_NETSTRING_NO_ALLOC
int giraudux_netstring_encode_re(char ** __string, size_t * __len);
#endif /* GIRAUDUX_NETSTRING_NO_ALLOC */

/**
 * \fn struct giraudux_string_s giraudux_netstring_decode_ma(const char * __netstring, size_t __max_len)
 * \param __netstring
 * \param __max_len 
 * \return 
 * \brief 
 */
#ifndef GIRAUDUX_NETSTRING_NO_ALLOC
struct giraudux_string_s giraudux_netstring_decode_ma(const char * __netstring, size_t __max_len);
#endif /* GIRAUDUX_NETSTRING_NO_ALLOC */

/**
 * \fn struct giraudux_string_s giraudux_netstring_encode_ma(const char * __string, size_t __len)
 * \param __string
 * \param __len 
 * \return 
 * \brief 
 */
#ifndef GIRAUDUX_NETSTRING_NO_ALLOC
struct giraudux_string_s giraudux_netstring_encode_ma(const char * __string, size_t __len);
#endif /* GIRAUDUX_NETSTRING_NO_ALLOC */

/**
 * \fn struct giraudux_string_s giraudux_netstring_decode(const char * __netstring, size_t __max_len)
 * \param __netstring
 * \param __max_len 
 * \return 
 * \brief 
 */
#ifndef GIRAUDUX_NETSTRING_NO_ALLOC
struct giraudux_string_s giraudux_netstring_decode(const char * __netstring, size_t __max_len);
#endif /* GIRAUDUX_NETSTRING_NO_ALLOC */

#endif
