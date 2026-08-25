# 11 - Enums, typedef and Unions

这一章学习三个能够帮助我们组织数据的 C 语言工具：枚举 `enum`、类型别名 `typedef` 和联合体 `union`。

它们在 STM32 项目中很常见，例如表示 LED 状态、定义传感器数据类型，以及解释一块共享内存。

## 学习目标

完成本章后，你应该能够：

- 使用枚举表示一组有限的状态
- 使用 `typedef` 给已有类型起更清楚的名字
- 理解结构体和联合体在内存上的区别
- 根据实际需求选择 `enum`、`struct` 或 `union`
- 看懂嵌入式代码中常见的类型定义

## 1. 枚举 enum

当一个变量只允许出现有限的几种状态时，可以使用枚举。

```c
enum LedState
{
    LED_OFF,
    LED_ON,
    LED_BLINKING
};
```

如果没有手动指定数值，第一个成员从 `0` 开始，后面的成员依次加 `1`：

```text
LED_OFF      = 0
LED_ON       = 1
LED_BLINKING = 2
```

定义变量：

```c
enum LedState state = LED_ON;
```

枚举成员本质上是有名字的整数常量。与直接写 `0`、`1`、`2` 相比，`LED_ON` 的含义更加清楚。

### 1.1 手动指定枚举值

```c
enum ErrorCode
{
    ERROR_NONE = 0,
    ERROR_TIMEOUT = 10,
    ERROR_CHECKSUM = 20
};
```

只有确实需要与通信协议、硬件定义或已有数据对应时，才需要手动指定数值。

### 1.2 枚举与 switch

枚举经常和 `switch` 配合使用：

```c
switch (state)
{
    case LED_OFF:
        printf("LED is off\n");
        break;

    case LED_ON:
        printf("LED is on\n");
        break;

    case LED_BLINKING:
        printf("LED is blinking\n");
        break;

    default:
        printf("Unknown state\n");
        break;
}
```

## 2. 类型别名 typedef

`typedef` 不会创建一种全新的底层数据类型，它只是为已有类型提供一个新名字。

```c
typedef unsigned char Byte;

Byte value = 10;
```

这里的 `Byte` 仍然是 `unsigned char`，但名字更能表达用途。

### 2.1 typedef 与枚举

```c
typedef enum
{
    LED_OFF,
    LED_ON,
    LED_BLINKING
} LedState;

LedState state = LED_ON;
```

这样定义变量时不必重复写 `enum`。

### 2.2 typedef 与结构体

```c
typedef struct
{
    const char *name;
    int value;
    LedState state;
} Sensor;

Sensor temperature_sensor;
```

STM32 的 HAL 库中经常能看到类似 `GPIO_InitTypeDef`、`UART_HandleTypeDef` 的名字。这些通常就是使用 `typedef` 定义的结构体类型。

### 2.3 不要用 typedef 隐藏重要信息

下面的写法虽然合法，但初学阶段不建议：

```c
typedef int *IntPointer;
```

`IntPointer` 看起来不像指针，容易隐藏 `*`。在学习指针时，直接写 `int *` 通常更清楚。

## 3. 联合体 union

结构体中的每个成员通常拥有各自的存储空间，而联合体的所有成员共享同一块存储空间。

```c
typedef union
{
    unsigned int number;
    unsigned char bytes[4];
} SharedData;
```

联合体的大小至少能够容纳最大的成员，并可能因为内存对齐而更大。

### 3.1 结构体与联合体的区别

```c
struct ExampleStruct
{
    int number;
    char character;
};

union ExampleUnion
{
    int number;
    char character;
};
```

- `struct`：`number` 和 `character` 分别保存数据，可以同时有效
- `union`：两个成员共享内存，一般只把最近写入的那个成员看作当前有效成员

对联合体的一个成员赋值，可能覆盖另一个成员原来占用的字节。

### 3.2 联合体适合什么场景

- 同一时刻只需要保存多种数据中的一种
- 节省内存
- 按照不同形式描述同一块硬件或通信数据

不过，读取“不是最后一次写入的成员”可能涉及实现相关行为。初学时应先遵守：写入哪个成员，就读取哪个成员。

## 4. 三种工具如何选择

| 工具 | 主要用途 | 示例 |
| --- | --- | --- |
| `enum` | 表示有限状态 | 开、关、闪烁 |
| `typedef` | 简化或说明类型名称 | `LedState`、`Sensor` |
| `struct` | 同时组合多项数据 | 名称、数值、状态 |
| `union` | 多个成员共享一块内存 | 同一时刻保存整数或字节数组 |

## 5. 完整示例

本目录中的 [enums_typedef_unions.c](./enums_typedef_unions.c) 演示了：

- 用枚举表示 LED 状态
- 用 `typedef` 定义枚举、结构体和联合体
- 把枚举状态转换为可读文本
- 查看联合体不同成员是否共用同一个起始地址

编译：

```powershell
gcc enums_typedef_unions.c -std=c11 -Wall -Wextra -Wpedantic -o enums_typedef_unions.exe
```

运行：

```powershell
.\enums_typedef_unions.exe
```

## 6. 与 STM32 的联系

- GPIO、设备和任务的状态可以使用枚举表示
- HAL 库大量使用 `typedef struct` 定义配置和句柄类型
- 通信数据有时会使用联合体，但要注意字节序、内存对齐和可移植性
- 使用有意义的类型名，可以让驱动代码比一堆数字更容易检查

例如：

```c
typedef enum
{
    MOTOR_STOPPED,
    MOTOR_RUNNING,
    MOTOR_ERROR
} MotorState;
```

这比用 `0`、`1`、`2` 表示电机状态更清楚。

## 7. 常见错误

1. 把枚举当作字符串：`LED_ON` 是整数常量，不会自动输出 `"LED_ON"`。
2. 认为 `typedef` 创建了完全不同的新类型：它主要是别名。
3. 认为联合体所有成员都能同时保存各自的数据：它们共享内存。
4. 不检查枚举的非法值：函数接收枚举参数时，仍可以保留 `default` 分支。
5. 使用联合体解释通信字节却忽略大小端和编译器差异。

## 8. 练习

### 练习 1：交通灯状态

定义 `TrafficLight` 枚举，包括红灯、黄灯和绿灯。编写函数，根据状态输出相应提示。

### 练习 2：学生信息

使用 `typedef struct` 定义 `Student`，包含姓名、年龄和成绩，并在 `main` 中初始化和输出。

### 练习 3：设备工作模式

定义 `DeviceMode` 枚举，包括 `MODE_SLEEP`、`MODE_NORMAL` 和 `MODE_FAST`。使用 `switch` 输出不同模式。

### 练习 4：比较内存大小

定义具有相同成员的一个结构体和一个联合体，使用 `sizeof` 比较二者大小，并解释结果。

## 本章检查

如果你能够回答下面的问题，就可以进入下一章：

- 枚举为什么比直接使用数字更清楚？
- `typedef` 的作用是什么？
- 结构体和联合体在内存使用上有什么区别？
- 为什么联合体通常只把一个成员视为当前有效成员？
