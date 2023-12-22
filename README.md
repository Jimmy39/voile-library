# voile-library
A collection of Object-oriented-likely MCU libraries based on C language

## About the voile library
The Voile library is a collection of object-oriented-likely MCU libraries in C that uses ```struct``` to implement ```class``` .

To save memory, voile library uses const struct. Two struct are used to implement a class, public struct ```voile_const_xxxx_t``` and internal struct ```voile_internal_const_xxxx(_yyyy)_t``` .

__public struct__ includes public members of the class, usually interface functions. For example: 
```C
/**
 * @brief Operations of uart
 * 
 */
typedef const struct{

    voile_status_t (*Init)(void *, uint32_t);

    // And other
    // ...

} voile_const_uartOperate_t;

/**
 * @brief Get something from uart
 * 
 */
typedef const struct{

    uint8_t (*Receive)(void *);

    // And others
    // ...

} voile_const_uartGet_t;

/**
 * @brief Class for UART
 * 
 */
typedef const struct{

    // Operate the uart
    voile_const_uartOperate_t *Operate;

    ///< Get date or status from uart
    voile_const_uartGet_t *Get;

} voile_const_uart_t;
```

__internal struct__ includes all members of class, as well as some constants used to define hardware or constant pointers to cache areas, except for the public part. For example: 
```C

/**
 * @brief Class for hardware UART in rp2040
 * 
 */
typedef const struct{
    // Operate the uart
    voile_const_uartOperate_t *Operate;

    ///< Get date or status from uart
    voile_const_uartGet_t *Get;
    
    // UART0 or UART1
    uint8_t uartId;

    // And others
    // ...
    
} voile_const_internal_uart_rp2040_t;
```

We define devices use internal struct at _devicelist.c_. For example:
```C
#include "voile_uart_rp2040.h"
voile_const_internal_uart_rp2040_t myuart = {
    
    // A micro to init all function pointer
    FUNCINIT,

    .uartId = UART0,

    //And others
    // ...

};

// Other voile_const_internal_uart_rp2040_t defination
// ...

#include "voile_uart_rp2040_end.h"
```

__Notice:__ The specific internal struct definition format can be found in the readme of libraries.

And declare it as public struct at _devicelist.h_:
```C
#include "voile_uart.h"
extern voile_const_uart_t myuart;
```

Then we can include _devicelist.h_ and operate device like this:

```C
myuart.Operate->Transmit(&myuart, ...);
```

Different internal struct may have the same public interface, which can be treated as the same class, and the public struct can be shared. At this time, we take out public struct and put it in a separate header file. To indicate that this library does not contain specific implementations, it is named with interface.

## Library list

HAL for RP2040:
| Public struct(Library name) | Internal struct(Library name) | Description |
| --- | --- | --- |
| (alpha)```voile_const_ioPin_t```([voile-interface-iopin](https://github.com/Jimmy39/voile-interface-iopin)) | (alpha)```voile_const_internal_ioPin_gpioRp2040_t```([voile-iopin-rp2040](https://github.com/Jimmy39/voile-iopin-rp2040)) | For any single io in rp2040 |
| (alpha)```voile_const_uart_t```([voile-interface-uart](https://github.com/Jimmy39/voile-interface-uart)) | (alpha)```voile_const_internal_uart_rp2040_t```([voile-uart-rp2040](https://github.com/Jimmy39/voile-uart-rp2040)) | For hardware uart in rp2040 |
| (alpha)```voile_const_74595_t```([voile-74595](https://github.com/Jimmy39/voile-74595)) | (alpha)```voile_const_internal_74595_t```([voile-74595](https://github.com/Jimmy39/voile-74595)) | For 74595 control |


## Todo list

| Library name | Public struct/Internal struct | Description |
| voile-iopin-74595 | ```voile_const_ioPin_t```([voile-interface-iopin](https://github.com/Jimmy39/voile-interface-iopin)) / ```voile_const_internal_ioPin_74595_t``` | Operate a 74595 pin as io |
|voile-potentiometer-3wire | ```voile_const_potentiometer_t```/```voile_const_internal_potentiometer_3wire_t``` | Opearte 3 wire potentiometer |
| voile-gpio-ch552 | ```voile_ioPin_t```([voile-interface-iopin](https://github.com/Jimmy39/voile-interface-iopin)) / ```voile_internal_ioPin_gpioCh552_t``` | For any single io in rp2040 |

## Other

The name 'voile library' is inspired by the voile magic library in [Touhou Koumakyou (Scarlet Devil Land) ~ the Embodiment of Scarlet Devil](https://en.touhouwiki.net/wiki/Embodiment_of_Scarlet_Devil)
