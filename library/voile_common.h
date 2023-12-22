/**
 * @file voile_common.h
 * @author Jimmy Wang (wanghanyu2000@126.com)
 * @brief Common denpence for voile library
 * 
 */
#ifndef __VOILE_COMMON_H_
#define __VOILE_COMMON_H_


#include <stdint.h>
#include <stddef.h>

#define bool _Bool

/**
 * @brief Return value meaning
 * 
 */
typedef enum{
    success = 0,
    failure = 1,
    inputRangeError = 2,
    hardwareUnsupportedError = 3,
} voile_status_t;


#endif // !__VOILE_COMMON_H_