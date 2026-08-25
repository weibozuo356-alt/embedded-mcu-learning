# 13 - Type Qualifiers and Storage

这一章学习 `const`、`static` 和 `volatile`。它们不会像循环或函数一样直接完成业务功能，却决定了数据是否允许修改、存在多久、能否被其他文件访问，以及编译器应如何读取它。

这些关键字在 STM32 驱动、寄存器定义和中断程序中非常常见。

## 学习目标

完成本章后，你应该能够：

- 使用 `const` 表示不应通过当前名称修改的数据
- 区分“指向常量的指针”和“常量指针”
- 理解局部 `static` 变量为什么能够保留上次的值
- 使用文件作用域 `static` 隐藏模块内部数据和函数
- 理解 `volatile` 为什么常用于寄存器和中断共享标志
- 知道 `volatile` 不能代替原子操作或线程同步

## 1. 先区分三个概念

### 1.1 作用域 scope

作用域回答：这个名字可以在代码的哪些位置使用？

- 块作用域：只在 `{}` 内可见
- 文件作用域：从声明处到当前源文件结尾可见

### 1.2 存储期 storage duration

存储期回答：这个对象在程序运行期间存在多久？

- 自动存储期：通常进入代码块时创建，离开时结束
- 静态存储期：从程序开始到程序结束一直存在
- 动态存储期：由 `malloc` 分配，到 `free` 释放

### 1.3 链接 linkage

链接回答：不同源文件中的同名声明是否表示同一个对象或函数？

初学阶段先记住：文件作用域的 `static` 名称只供当前 `.c` 文件使用。

## 2. const：不通过当前名称修改

```c
const int maximum = 100;
```

之后不能写：

```c
maximum = 200; /* 错误 */
```

`const` 能表达设计意图，也能让编译器帮助发现误修改。

### 2.1 const 参数

如果函数只读取数组，不应修改它，可以写：

```c
int sum_array(const int values[], int length);
```

在函数内部通过 `values` 修改数组元素会产生编译错误。

### 2.2 指向常量的指针

```c
const int *pointer = &value;
```

可以改变 `pointer` 指向哪里，但不能通过 `pointer` 修改目标：

```c
pointer = &another_value; /* 可以 */
*pointer = 10;            /* 不可以 */
```

读法：`pointer` 是一个指针，指向 `const int`。

### 2.3 常量指针

```c
int *const pointer = &value;
```

指针本身不能再指向其他地址，但可以通过它修改目标：

```c
*pointer = 10;             /* 可以 */
pointer = &another_value;  /* 不可以 */
```

### 2.4 指向常量的常量指针

```c
const int *const pointer = &value;
```

既不能改变指向，也不能通过该指针修改目标。

判断方法：从变量名 `pointer` 开始向两侧读；`const` 修饰它靠近的部分。

## 3. static 的三种常见用途

### 3.1 局部 static 变量保留值

```c
int next_number(void)
{
    static int number = 0;
    number++;
    return number;
}
```

普通局部变量每次调用函数都会重新创建，而这个 `number` 只初始化一次，并在后续调用中保留值。

它的名字仍然只有函数内部可见，但对象拥有静态存储期。

### 3.2 文件内部变量

```c
static int module_counter = 0;
```

当它写在所有函数之外时，这个名字只在当前 `.c` 文件内使用。其他文件不能直接引用它。

### 3.3 文件内部函数

```c
static void update_counter(void)
{
    module_counter++;
}
```

这表示函数只是当前模块的内部实现，不属于对外接口。

在模块化编程中，一个好习惯是：不需要被其他文件使用的文件作用域变量和函数，优先考虑 `static`。

## 4. volatile：每次都实际访问对象

```c
volatile unsigned int event_flag = 0U;
```

`volatile` 告诉编译器：这个对象可能在当前代码看不到的地方发生变化，因此每次读取和写入都要按程序表达式实际进行，不能仅使用之前缓存的结果。

常见来源包括：

- 硬件寄存器改变
- 中断服务程序改变共享标志
- 某些底层系统环境改变内存

例如主程序等待中断设置标志：

```c
volatile unsigned int data_ready = 0U;

while (data_ready == 0U)
{
    /* 等待中断更新 data_ready */
}
```

如果没有 `volatile`，编译器可能认为循环中没有代码会修改 `data_ready`，从而减少或合并读取。

### 4.1 volatile 不是什么

`volatile` 不保证：

- 多步操作不可被打断
- `counter++` 是原子操作
- 多线程访问没有竞争
- 多核之间自动同步
- 代码逻辑一定正确

如果主程序和中断会同时修改复杂数据，仍需根据 MCU 和场景使用临界区、关闭中断、原子操作或其他同步机制。

### 4.2 const volatile

硬件状态寄存器可能由硬件改变，而软件只应读取：

```c
const volatile uint32_t status_register;
```

- `const`：软件不应通过这个名称写入
- `volatile`：硬件可能随时改变，读取时要真正访问

## 5. auto 与 register

### 5.1 auto

块内普通局部变量默认就是自动存储期：

```c
auto int value = 10;
```

实际代码通常直接写 `int value = 10;`，很少显式写 `auto`。

### 5.2 register

`register` 是早期给编译器的优化建议：

```c
register int index;
```

现代编译器通常能自行决定如何优化，因此新代码很少需要它。不要把它当作学习重点。

## 6. 完整示例

本目录中的 [qualifiers_and_storage.c](./qualifiers_and_storage.c) 演示了：

- `const` 普通变量与指针
- 常量指针
- 局部 `static` 变量保存调用次数
- 文件内部 `static` 变量和函数
- 用 `volatile` 标志模拟外部事件

编译：

```powershell
gcc qualifiers_and_storage.c -std=c11 -Wall -Wextra -Wpedantic -o qualifiers_and_storage.exe
```

运行：

```powershell
.\qualifiers_and_storage.exe
```

## 7. 与 STM32 的联系

### const

- 只读查找表
- 不允许驱动函数修改的输入数据
- 固定配置参数

### static

- 驱动模块内部状态
- 不对外公开的辅助函数
- 函数调用之间需要保留的计数值

### volatile

- 外设寄存器
- 被中断服务程序修改、被主循环读取的简单标志
- DMA 或硬件可能更新的数据

例如：

```c
static volatile unsigned int uart_data_ready = 0U;
```

`static` 表示标志只供当前模块使用，`volatile` 表示它可能被中断等外部执行过程修改。

## 8. 常见错误

1. 认为 `const` 数据一定存放在 Flash：实际位置还取决于对象、链接脚本和工具链。
2. 强制转换去掉 `const` 后修改真正的只读对象：可能产生未定义行为。
3. 认为局部 `static` 每次调用都会重新初始化。
4. 把所有全局变量都写成普通外部变量，导致模块之间互相依赖。
5. 给普通变量随意添加 `volatile`，掩盖真正的同步或逻辑问题。
6. 认为 `volatile` 可以保证 `counter++` 不被中断。

## 9. 练习

### 练习 1：调用计数器

编写 `get_call_count` 函数，使用局部 `static` 变量记录自己被调用了多少次。

### 练习 2：只读数组

创建一个 `const int` 数组，并编写只读取数组的求和函数。给函数参数也添加正确的 `const`。

### 练习 3：指针辨析

分别声明：

- 指向常量整数的指针
- 指向整数的常量指针
- 指向常量整数的常量指针

尝试说明每一种情况下，指针和目标谁可以修改。

### 练习 4：事件标志

定义一个 `volatile` 标志。编写一个函数把它设为 `1`，主函数检测后输出信息并清零。

### 练习 5：模块私有状态

创建一个文件作用域 `static` 计数器，只允许通过两个函数增加和读取它。

## 本章检查

- `const int *p` 与 `int *const p` 有什么区别？
- 局部 `static` 变量的作用域和存储期分别是什么？
- 文件作用域 `static` 有什么价值？
- `volatile` 解决的是哪一类问题？
- 为什么 `volatile` 不能代替同步和原子操作？
