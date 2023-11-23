/**
 * @file voile_common.h
 * @author Jimmy Wang (wanghanyu2000@126.com)
 * @brief Common denpence for voile library
 * @version 0.0.0
 * @date 2023-10-25
 * @par History
 * Version|Auther|Date|Describe
 * ------|----|------|--------
 * 0.0.0|JimmyWang|2023-10-25|First update.
 * 
 */
#ifndef __VOILE_COMMON_H_
#define __VOILE_COMMON_H_


#include <stdint.h>

#define bool _Bool

/**
 * @enum voileFunctionReturn
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