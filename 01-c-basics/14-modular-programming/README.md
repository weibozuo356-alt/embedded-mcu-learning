# 14 - Modular Programming

到目前为止，大多数练习都写在一个 `.c` 文件中。程序变大后，如果所有变量和函数都堆在同一个文件里，代码会越来越难阅读、修改和测试。

模块化编程的目标是按照职责拆分代码，并为每个模块提供清楚、有限的接口。这正是以后组织 STM32 GPIO、UART、传感器和应用逻辑的基础。

## 学习目标

完成本章后，你应该能够：

- 理解声明与定义的区别
- 使用 `.h` 声明模块对外接口
- 使用 `.c` 保存模块实现
- 编写头文件保护
- 正确使用 `#include`
- 使用 `static` 隐藏模块内部实现
- 使用宏和条件编译管理简单配置
- 编译由多个源文件组成的 C 程序

## 1. 为什么要拆分文件

一个简单的嵌入式项目可能包含：

```text
main.c           应用主流程
led.c / led.h    LED 驱动
button.c / .h    按键驱动
uart.c / .h      串口驱动
sensor.c / .h    传感器驱动
```

每个模块只处理一类职责。使用模块的人只需要阅读头文件中的接口，不必先理解内部所有细节。

## 2. 声明与定义

### 2.1 函数声明

```c
void led_on(void);
```

它告诉编译器函数的名字、返回类型和参数，但没有提供函数体。

### 2.2 函数定义

```c
void led_on(void)
{
    /* 实际操作 */
}
```

定义提供真正的实现。

同一个外部函数可以在多个地方被声明，但在整个程序中通常只能有一个定义。

### 2.3 变量声明与定义

```c
extern int system_state; /* 声明：定义在其他地方 */
int system_state = 0;    /* 定义：分配存储空间 */
```

初学阶段应尽量通过函数接口访问模块状态，而不是大量公开全局变量。

## 3. 头文件 .h

头文件可以理解成模块的“使用说明书”，它描述这个模块允许其他源文件使用哪些内容。

需要注意：**头文件不是把对应 `.c` 文件中的所有函数都声明一遍。** 它通常只包含其他文件确实需要使用的公开接口，例如：

- 类型定义
- 需要被其他 `.c` 文件调用的函数声明
- 必须公开的常量或宏

例如 `led.h`：

```c
#ifndef LED_H
#define LED_H

typedef enum
{
    LED_STATE_OFF,
    LED_STATE_ON
} LedState;

void led_init(void);
void led_on(void);
void led_off(void);
LedState led_get_state(void);

#endif
```

头文件只暴露使用模块所必需的内容。

例如，`main.c` 包含 `led.h` 后，编译器就能知道：

```text
led_init 是一个函数，不接收参数，也没有返回值
led_on 是一个函数，不接收参数，也没有返回值
led_get_state 会返回 LedState 类型的状态
```

但头文件中的声明并没有提供函数体。函数具体如何控制 LED，仍然写在 `led.c` 中。

### 3.1 哪些函数不应该写进头文件

如果一个辅助函数只在 `led.c` 内部使用，就不需要在 `led.h` 中声明：

```c
static void print_state(void)
{
    /* 只供 led.c 内部使用 */
}
```

这里使用 `static`，表示 `print_state` 是当前源文件的内部实现。其他源文件既不需要知道它，也不应该直接调用它。

可以按照下面的规则判断：

```text
需要给其他 .c 文件调用的函数 -> 在 .h 中声明
只在当前 .c 文件内部使用的函数 -> 留在 .c 中，通常添加 static
```

因此，头文件的重点不是“把所有东西都列出来”，而是为模块设计一个清楚、尽量精简的公开接口。

## 4. 头文件保护 include guard

```c
#ifndef LED_H
#define LED_H

/* 头文件内容 */

#endif
```

预处理器第一次包含头文件时，`LED_H` 尚未定义，于是处理内容并定义它。再次包含时，条件不成立，内容会被跳过。

这可以避免同一个头文件被重复展开后产生重复类型定义等错误。

保护宏应在项目中保持唯一，通常根据文件名命名。

## 5. 源文件 .c

`led.c` 包含模块实现：

```c
#include "led.h"

static LedState current_state = LED_STATE_OFF;

void led_on(void)
{
    current_state = LED_STATE_ON;
}
```

源文件首先包含自己的头文件，可以帮助编译器检查声明和定义是否一致。

`current_state` 使用 `static`，因此它属于模块内部状态，其他 `.c` 文件不能直接访问。

## 6. #include 的两种写法

标准库头文件通常使用尖括号：

```c
#include <stdio.h>
```

项目自己的头文件通常使用双引号：

```c
#include "led.h"
```

双引号通常会先从当前项目相关路径查找，再根据编译器设置继续查找。

不要这样做：

```c
#include "led.c"
```

`.c` 文件应该作为独立编译单元参与编译，而不是被另一个 `.c` 文件直接包含。

## 7. 编译多个源文件

本章程序由 `main.c` 和 `led.c` 共同组成：

```powershell
gcc main.c led.c -std=c11 -Wall -Wextra -Wpedantic -o modular_programming.exe
```

可以先把过程理解为：

1. 预处理器展开 `#include` 和宏
2. 每个 `.c` 文件分别编译
3. 链接器把各个目标文件和库连接成可执行程序

如果只编译 `main.c`，链接阶段会找不到 `led_init` 等函数的定义。

## 8. 宏定义

宏使用 `#define` 定义。可以先把宏理解成：**在正式编译之前，由预处理器按照规则替换源代码中的内容。**

### 8.1 宏是怎样替换的

```c
#define LED_BLINK_COUNT 3U
```

程序中写：

```c
led_blink(LED_BLINK_COUNT);
```

预处理器处理后，可以近似理解为：

```c
led_blink(3U);
```

也就是说：

```text
我们阅读源代码时看到：LED_BLINK_COUNT
预处理器替换后得到：  3U
编译器最终处理的是：  替换后的代码
```

宏名称本身通常不会作为运行时变量保存。对于这个常量宏，它最终表达的仍然是数值 `3U`。

### 8.2 使用名称比直接写数字清楚

下面的代码可以运行，但数字 `3U` 的用途不够明确：

```c
led_blink(3U);
```

换成有意义的宏名称：

```c
led_blink(LED_BLINK_COUNT);
```

读代码时可以直接理解为“按照设定的 LED 闪烁次数执行”，不需要猜测数字 `3` 的含义。这类没有说明的数字通常被称为“魔法数字”。

宏还便于统一修改。程序中无论使用多少次 `LED_BLINK_COUNT`，想改为闪烁 5 次时只需要修改定义：

```c
#define LED_BLINK_COUNT 5U
```

宏不仅可以代表数字，也可以代表字符串：

```c
#define APP_NAME "Modular LED Demo"
```

使用：

```c
printf("%s\n", APP_NAME);
```

预处理后近似为：

```c
printf("%s\n", "Modular LED Demo");
```

常量宏通常使用全部大写的名称，让读者容易认出它是宏。

### 8.3 宏与普通变量的区别

下面是宏：

```c
#define LED_BLINK_COUNT 3U
```

下面是一个只读对象：


```c
static const unsigned int blink_count = 3U;
```

可以先这样区分：

| 项目 | 常量宏 | `const` 对象 |
| --- | --- | --- |
| 发生阶段 | 正式编译前进行替换 | 作为 C 语言对象参与编译 |
| 类型 | 宏自身没有 C 数据类型 | 有明确的数据类型 |
| 调试观察 | 通常不能像变量一样观察 | 通常可以像变量一样观察 |
| 条件编译 | 可以用于 `#if` | 不能直接代替预处理宏 |

宏没有普通变量那样的类型检查。具体选择要结合是否需要条件编译、项目规范和工具链；现阶段先掌握宏的替换思想即可。

宏定义末尾通常不写分号：

```c
#define LED_BLINK_COUNT 3U   /* 正确 */
```

如果把分号也写进宏的替换内容，宏展开后可能出现在不合适的位置并产生语法问题。

### 8.4 函数式宏

```c
#define SQUARE(value) ((value) * (value))
```

函数式宏可以接收参数。例如：

```c
#define BIT(position) (1U << (position))
```

调用 `BIT(3)` 时，预处理器会把它展开成：

```c
(1U << 3)
```

函数式宏仍然是文本替换，并不等同于真正的函数。参数和整体表达式要加括号。但下面的调用仍有问题：

```c
SQUARE(index++)
```

因为参数可能被展开两次，产生多次自增。能用普通函数或 `inline` 函数清楚表达时，不要滥用复杂宏。

## 9. 条件编译

条件编译可以根据配置决定某段代码是否参与编译：

```c
#define DEBUG_OUTPUT 1

#if DEBUG_OUTPUT
printf("Debug message\n");
#endif
```

也可以判断一个宏是否已经定义：

```c
#ifdef DEBUG_OUTPUT
/* 调试代码 */
#endif
```

条件编译常用于：

- 开启或关闭调试输出
- 适配不同开发板
- 选择不同功能

不要用大量嵌套条件编译掩盖混乱的程序结构。

## 10. 本章项目结构

```text
14-modular-programming/
├── README.md
├── config.h
├── led.h
├── led.c
└── main.c
```

各文件职责：

| 文件 | 职责 |
| --- | --- |
| `config.h` | 应用名称、调试开关、循环次数 |
| `led.h` | LED 模块的公开类型和函数声明 |
| `led.c` | LED 状态和函数实现 |
| `main.c` | 组合配置与 LED 模块，形成程序流程 |

运行结果会模拟 LED 初始化、打开、关闭和闪烁。这里还没有真实硬件，所以 `led.c` 使用终端文字表示状态变化。

编译：

```powershell
gcc main.c led.c -std=c11 -Wall -Wextra -Wpedantic -o modular_programming.exe
```

运行：

```powershell
.\modular_programming.exe
```

## 11. 与 STM32 的联系

以后可以把模拟实现替换成真实 HAL 调用：

```c
void led_on(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}
```

对于 `main.c` 来说，接口仍然是 `led_on()`。硬件操作细节被封装在 LED 模块内部。

这种结构的好处是：

- 主流程更接近“初始化 LED、打开 LED”这样的业务语言
- 引脚变化时主要修改 LED 模块
- 可以把驱动和应用逻辑分开检查
- 更容易复用代码和定位错误

后续 STM32 项目可以逐步形成：

```text
Core/        CubeMX 或核心生成代码
Drivers/     芯片厂商底层驱动
BSP/         开发板上的 LED、按键、传感器驱动
App/         应用逻辑
```

具体目录不必现在照搬，先掌握“接口与实现分离”的思想。

## 12. 常见错误

1. 在头文件中直接定义普通全局变量，导致多个源文件出现重复定义。
2. 忘记头文件保护。
3. 直接 `#include` 一个 `.c` 文件。
4. 函数声明与定义的参数或返回类型不一致。
5. 编译时漏掉某个 `.c` 文件，链接器报告 `undefined reference`。
6. 把模块内部所有变量和函数都公开。
7. 宏表达式缺少括号，或给宏传入带副作用的表达式。
8. 头文件互相包含，形成不必要的循环依赖。

## 13. 练习

### 练习 1：添加 toggle

在 `led.h` 声明 `led_toggle`，在 `led.c` 实现它，并在 `main.c` 调用。

### 练习 2：创建按键模块

创建 `button.h` 和 `button.c`。先用一个普通变量模拟按键状态，并提供初始化和读取函数。

### 练习 3：关闭调试输出

把 `config.h` 中的 `DEBUG_OUTPUT` 改为 `0`，重新编译并观察输出差异。

### 练习 4：制造并修复链接错误

只编译 `main.c`，观察错误信息；再加入 `led.c`，说明为什么问题消失。

### 练习 5：封装计数器

在一个新的模块内创建 `static` 计数器，只通过 `counter_increment` 和 `counter_get` 对外提供操作。

## 本章检查

- 头文件和源文件分别负责什么？
- 声明与定义有什么区别？
- 头文件保护解决什么问题？
- 为什么模块内部状态适合使用文件作用域 `static`？
- 为什么不应该 `#include` 一个 `.c` 文件？
- 编译多文件程序时为什么必须列出所有实现文件？
