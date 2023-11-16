# voile-library
A collection of Object-oriented-likely MCU libraries based on C language

## About the voile library
The Voile library is a collection of object-oriented-likely MCU libraries in C that uses ```struct``` to implement ```class``` .

Two structures are used to implement a class, public struct ```voile_xxxx_t``` and internal struct ```voile_internal_xxxx(_yyyy)_t``` .

__public struct__ includes public members of the class, usually interface functions. For example: 
```C
/**
 * @brief Operations for ioPin
 * 
 */
typedef const struct{
    int (*Func1)(...);
    int (*Func2)(...);
    int (*Func3)(...);
} voile_ioPinOperations_t;
/**
 * @brief Single io
 * 
 */
typedef const struct{
    voile_ioPinOperations_t *Operations;    ///< Operations for ioPin
} voile_ioPin_t;
```

__internal struct__ includes all members of class, as well as some constants used to define hardware or constant pointers to cache areas, except for the public part. For example: 
```C
/**
 * @brief Single io for gpio in rp2040
 * 
 */
typedef const struct{
    voile_ioPinOperations_t *Operation;     ///< Functions of ioPin
    uint8_t pin;                            ///< Pin number
} voile_internal_ioPin_gpioRp2040_t;
```

We define devices use internal struct at _devicelist.c_. For example:
```C
voile_internal_ioPin_gpioRp2040_t led = {
        .Operation = &voile_ioPinOperations_gpio_rp2040,
        .pin = 25
};
```

__Notice:__ The specific internal struct definition format can be found in the readme of libraries.

And declare it as public struct at _devicelist.h_:
```C
extern voile_ioPin_t led;
```

Then we can include _devicelist.h_ and operate device like this:

```C
led.Operation->Func1(&MyDevice, i, j);
```

Different internal struct may have the same public interface, which can be treated as the same class, and the public struct can be shared. At this time, we take out public struct and put it in a separate header file. To indicate that this library does not contain specific implementations, it is named with interface.

## Library list

HAL for RP2040:
| Library name | Public struct/Internal struct | Description |
| --- | --- | --- |
| (alpha)[voile-gpio-rp2040](https://github.com/Jimmy39/voile-gpio-rp2040) | ```voile_ioPin_t```([voile-interface-iopin](https://github.com/Jimmy39/voile-interface-iopin)) / ```voile_internal_ioPin_gpioRp2040_t``` | For any single io in rp2040 |


## Todo list

| Library name | Public struct/Internal struct | Description |
| --- | --- | --- |
| voile-uart-rp2040 | ```voile_uart_t```(voile-interface-uart) / ```voile_internal_uart_rp2040_t``` | For hardware uart in rp2040 |
| voile-74gate | ```voile_74595_t``` / ```voile_internal_74595_t``` | For 74595 control |
| | ```voile_ioPin_t```([voile-interface-iopin](https://github.com/Jimmy39/voile-interface-iopin)) / ```voile_internal_ioPin_74595_t``` | Operate a 74595 pin as io |
| voile-gpio-ch552 | ```voile_ioPin_t```([voile-interface-iopin](https://github.com/Jimmy39/voile-interface-iopin)) / ```voile_internal_ioPin_gpioCh552_t``` | For any single io in rp2040 |

## Other

The name 'voile library' is inspired by the voile magic library in [Touhou Koumakyou (Scarlet Devil Land) ~ the Embodiment of Scarlet Devil](https://en.touhouwiki.net/wiki/Embodiment_of_Scarlet_Devil)
