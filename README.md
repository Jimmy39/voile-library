# voile-library
A collection of Object-oriented-likely MCU libraries based on C language

## About the voile library
The Voile library is an object-oriented-likely library.The voile library defines devices as structures and implements a universal interface by sharing a common public function. We can operate device like this:

```C
MyDevice.operation->Func1(&MyDevice, i, j);

```

The specific hardware definition format can be found in the readme of each hardware operation library.I prefer to put them in devicelist.h and devicelist.c.

The name 'voile library' is inspired by the voile magic library in [Touhou Koumakyou (Scarlet Devil Land) ~ the Embodiment of Scarlet Devil](https://en.touhouwiki.net/wiki/Embodiment_of_Scarlet_Devil)


## Library architecture
Voile library device to two parts: The top layer operations library voile-class-xxxx and hardware operations library voile-xxxx. 

### voile-class-xxxx
Library voile-class-xxxx defines the common public part of struct type. The design of the voile library is such that only public functions are available for classes, and variables are private. The devices shared public functions are referred to as a class. For example, ioPin is a class for single io.The devices of ioPin class include a pin in GPIO or io expansion chip even 54595 or 74164. 

One typical implementation of class is like this.

```C
/**
 * Public function in class Myclass
 */
struct voile_MyclassOperation_t{
    enum voileFunctionReturn const (*Func1)(void *, ...);
    enum voileFunctionReturn const (*Func2)(void *, ...);
    enum voileFunctionReturn const (*Func3)(void *, ...);
};

/**
 * Myclass is .....
 */
struct voile_Myclass_t
{
    const struct voile_MyclassOperation_t *operation;     ///< Public function
};

```

The enum voileFunctionReturn is a unified return value to indicate normal execution or errors such as passing incorrect parameters or using hardware-unsupported features on limited-function devices.

Library list:

|Library name|Description|Doxygen docs|
| --- | --- | --- |
|(developing)[voile-device-iopin](https://github.com/Jimmy39/voile-device-iopin)|For any single io|[Page](https://jimmy39.github.io/voile-class-iopin/index.html)|


### voile-xxxx
Library voile-xxxx defines struct type for specific device and performs operations function. One typical implementation of hardware struct type is like this.

```C
/**
 * Full defination of device, include common public part and specific private part.
 * ONLY INNER USE OR FOR INIT
 */
struct voile_Myclass_Mydeivce_inner_t{
    const struct voile_ioPinOperation_t *operation;     ///< Must first 
    const int someHavewareInformation;
    int someVariable;
};


/**
 * Umion the public function and full defination.
 */
union voile_Myclass_Mydeivce_t{
    const struct voile_ioPinOperation_t *operation;         
    const struct voile_ioPin_gpio_rp2040_inner_t Init;   
};

```

|Library name|Description|Doxygen docs|
| --- | --- | --- |
|Todo|||

## OTHER
