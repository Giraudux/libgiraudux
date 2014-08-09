/**
 * \file netstring.h
 * \author Alexis Giraudet
 * \version 0.0
 * \date 
 * \brief 
 */

#ifndef NETSTRING_H
#define NETSTRING_H

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define LEN_BUFFER_SIZE 10

/**
 * \fn int grdx_netstring_decode_ab(char ** __netstring_block, size_t * __netstring_len)
 * \param __netstring_block 
 * \param __netstring_len 
 * \return 
 * \brief 
 */
int grdx_netstring_decode_ab(char ** __netstring_block, size_t * __netstring_len);

/**
 * \fn int grdx_netstring_encode_ab(char ** __string_block, size_t * __string_len)
 * \param __string_block 
 * \param __string_len 
 * \return 
 * \brief 
 */
int grdx_netstring_encode_ab(char ** __string_block, size_t * __string_len);

/**
 * \fn int grdx_netstring_decode_wb(wchar_t ** __netstring_block, size_t * __netstring_len)
 * \param __netstring_block 
 * \param __netstring_len 
 * \return 
 * \brief 
 */
int grdx_netstring_decode_wb(wchar_t ** __netstring_block, size_t * __netstring_len);

/**
 * \fn int grdx_netstring_encode_wb(wchar_t ** __string_block, size_t * __string_len)
 * \param __string_block 
 * \param __string_len 
 * \return 
 * \brief 
 */
int grdx_netstring_encode_wb(wchar_t ** __string_block, size_t * __string_len);

/*
int grdx_netstring_..._ab(const char * __netstring_block, size_t __netstring_len, char ** __string_block, size_t * __string_len);
int grdx_netstring_..._wb(const wchar_t * __netstring_block, size_t __netstring_len, wchar_t ** __string_block, size_t * __string_len);
*/

/**
 * \fn int grdx_netstring_check_a(const char * __netstring)
 * \param __netstring 
 * \return 
 * \brief 
 */
int grdx_netstring_check_a(const char * __netstring);

/**
 * \fn int grdx_netstring_check_ab(const char * __netstring_block, size_t __netstring_len)
 * \param __netstring_block 
 * \param __netstring_len 
 * \return 
 * \brief 
 */
int grdx_netstring_check_ab(const char * __netstring_block, size_t __netstring_len);

/**
 * \fn int grdx_netstring_check_w(const wchar_t * __netstring)
 * \param __netstring 
 * \return 
 * \brief 
 */
int grdx_netstring_check_w(const wchar_t * __netstring);

/**
 * \fn int grdx_netstring_check_wb(const wchar_t * __netstring_block, size_t __netstring_len)
 * \param __netstring_block 
 * \param __netstring_len 
 * \return 
 * \brief 
 */
int grdx_netstring_check_wb(const wchar_t * __netstring_block, size_t __netstring_len);

#endif
