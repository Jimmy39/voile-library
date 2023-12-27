/**
 * @file voile_common.h
 * @author Jimmy Wang (wanghanyu2000@126.com)
 * @brief Common denpence for voile library
 *
 */
#ifndef __VOILE_COMMON_H_
#define __VOILE_COMMON_H_

#include <stddef.h>
#include <stdint.h>

#define bool _Bool

/**
 * @brief Return value meaning
 *
 */
typedef enum {
    success = 0,
    failure = 1,
    inputRangeError = 2,
    hardwareUnsupportedError = 3,
} voile_status_t;

static inline voile_status_t voile_ReturnHardwareUnsupportedError(const void*, ...) {
    return hardwareUnsupportedError;
}

#endif // !__VOILE_COMMON_H_
