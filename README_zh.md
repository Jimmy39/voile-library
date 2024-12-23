# 伏瓦鲁库
一组基于C语言的面向对象风格的微处理器库

## 伏瓦鲁库的设计方式
伏瓦鲁库的设计遵循以下方式：

1. 本库应当是具有高度的通用性的，适配多重处理器以及开发环境。 并尽可能避免与各种sdk或者其他第三方库的冲突。

1. 使用多重的按照一定规律设计的结构体来模拟类的行为，包括公有私有、部分继承和复用的特性，来在C语言中实现面向对象风格。

1. 对常用硬件（如IO、ADC等）抽象成统一的类和函数，具有统一的命名规则。

1. 类似设备树，所有硬件相关内容，统一在 deviceslist.c 和 deviceslist.h 中定义。

1. 版本号规则为 a.b.c。其中升级a版本时不保持兼容；升级b版本只增加新功能新函数，不改变现有函数；升级c版本仅进行bug修复。

1. 本库是我在开发项目时顺便开发的，具体具有什么功能、实现什么接口、适配了哪些处理器和开发环境主要取决于我用到了哪些。也欢迎有同样需求的朋友一起参与开发。

## 关于“多重的按照一定规律设计的结构体”
伏瓦鲁库通过如下方式来模拟类（以串口为例）：

考虑到微处理器内存有限，以及硬件设备是固定不变的，所以使用常量结构体。为了实现公有私有、部分继承和复用的特性，这里对于一个硬件设施使用公有私有两个结构体进行定义。公有结构体使用函数指针保存了所有作为公开操作接口的函数：

```C
/**
 * @brief xxx硬件的公有结构体
 * 
 */
 typedef const struct{

    voile_status_t (*Init)(voile_const_xxx_t **, ...);
    voile_status_t (*Fun1)(voile_const_xxx_t **，uint8_t *);
    uint8_t (*Fun1_get)(voile_const_xxx_t **);

    // And other
    // ...

} voile_const_xxx_t;
```
所有函数的第一个参数是self,类型为(voile_const_xxx_t **)，用于在调用类中的函数时时引用类自己。对于一般的函数，返回值为枚举类型voile_status_t，用于返回函数状态。如果需要返回其他数据则通过函数指针。对于以_get结尾的函数，直接通过返回值获得数据。

私有结构体以公有结构体的指针为首元素，增加了其他硬件所需的部分：
```C

/**
 * @brief aaa型号的xxx硬件的私有结构体
 * 
 */
typedef const struct{

    // 公开接口
    voile_const_xxx_t *op;
    
    // 一些硬件所需的描述信息，比如串口号，外部芯片连接的引脚
    uint8_t id;

    // 因为结构体是常量，所以私有变量需要用指针指向外部另创建的变量
    void *data；

    // And others
    // ...
    
} voile_const_internal_xxx_aaa_t;
```

这里我们利用结构体首元素的地址与结构体的地址相同的特性。在 *deviceslist.c* 中建立并初始化私有结构体，并在 *deviceslist.h* 中声明为公有结构体：
```C
// deviceslist.c

uint8_t mydevice1_data[4]
voile_const_internal_xxx_aaa_t mydevice1 = {
    // op需要手动初始化
    op = xxx_aaa_op;

    // 例如xxx是串口，串口号为1
    id = 1;

    // 如果需要私有变量
    data = (void*)mydevice1_data

    // And others
    // ...
}


// deviceslist.h

extern voile_const_xxx_t *mydevice1；
```
调用方式如下：
```C
mydeivce1->Init(&mydevice1);
```
对于同一种硬件外设，使用同一个类型的公有结构体```voile_const_xxx_t```比如```voile_const_ADC_t```。不同厂家不同型号aaa、bbb，使用不同私有结构体，比如```voile_const_internal_ADC_stm32hal_t```或者```voile_const_internal_ADC_ads1263_t```。这样即可隐藏不同型号的设备的细节，暴露出完全相同的公有接口。