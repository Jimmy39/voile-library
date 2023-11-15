# voile-library
A collection of Object-oriented-likely MCU libraries based on C language

## About the voile library
The Voile library is an object-oriented-likely library.The voile library defines devices as structures and implements a universal interface by sharing a common public function.

Voile library device to two parts: The top layer operations library voile-class-xxxx and hardware operations library voile-xxxx. 


__Library voile-xxxx__ is hardware operation library. It defines struct type for specific device and performs operations function.Such as: 
```C
/**
 * @brief Single io for gpio in rp2040
 * 
 */
struct voile_hardware_ioPin_gpioRp2040_t{
    const struct voile_ioPinOperations_t *Operation;    ///< Functions of ioPin
    const uint8_t pin;                                  ///< Pin number
};
```
We define these struct at _devicelist.c_:
```C
#include "voile_gpio_rp2040.h"

struct voile_hardware_ioPin_gpioRp2040_t led = {
        .Operation = &voile_ioPinOperations_gpio_rp2040,
        .pin = 25
};
```
```voile_ioPinOperations_gpio_rp2040``` is a struct(```struct voile_ioPinOperations_t``` type) of functions for gpio in rp2040. __The specific hardware definition format can be found in the readme of each hardware operation library.__


__Library voile-class-xxxx__ defines the common public interface part of struct and function struct.Such as:
```C
/**
 * @brief Operations of ioPin
 * 
 */
struct voile_ioPinOperations_t{
    int (*Func1)(...);
    int (*Func2)(...);
    int (*Func3)(...);
};
/**
 * @brief Single io
 * 
 */
struct voile_ioPin_t{
    const struct voile_ioPinOperations_t *Operations;   ///< Operations of ioPin
};
```

```struct voile_ioPin_t``` is the public part of struct voile_hardware_ioPin_gpioRp2040_t, so we declare ```struct voile_hardware_ioPin_gpioRp2040_t led``` as ```struct voile_ioPin_t``` at _devicelist.h_:
```C
#include "voile_class_iopin.h"

extern struct voile_ioPin_t led;
```
Then we can include _devicelist.h_ and operate device like this:

```C
led.Operation->Func1(&led, i, j);
```


The name 'voile library' is inspired by the voile magic library in [Touhou Koumakyou (Scarlet Devil Land) ~ the Embodiment of Scarlet Devil](https://en.touhouwiki.net/wiki/Embodiment_of_Scarlet_Devil)


## Library list

|Class|Class Library|Hardware operation library|Description|
| --- | --- | --- | --- |
|```struct voile_ioPin_t```|(developing)[voile-class-iopin](https://github.com/Jimmy39/voile-device-iopin)|(developing)[voile-gpio-rp2040](https://github.com/Jimmy39/voile-gpio-rp2040)|For any single io in rp2040|

