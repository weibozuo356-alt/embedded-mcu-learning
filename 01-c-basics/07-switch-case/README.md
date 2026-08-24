# `switch...case` 选择语句

`switch...case` 是一种选择结构。它会根据一个表达式的值，从多个 `case` 分支中选择相匹配的分支执行。在判断多个固定值时，它通常比连续的 `if...else if` 更清晰。

## 1. 基本格式

```c
switch (表达式)
{
    case 常量值一:
        程序语句;
        break;
    case 常量值二:
        程序语句;
        break;
    default:
        程序语句;
        break;
}
```

执行过程如下：

1. 计算 `switch` 圆括号中表达式的值。
2. 从上到下寻找值相同的 `case`。
3. 从匹配位置开始执行程序。
4. 遇到 `break` 时退出整个 `switch`。

`case` 后面使用英文冒号 `:`，不是分号 `;`。

## 2. `break` 的作用

`break` 会结束当前的 `switch`，程序继续执行 `switch` 后面的语句。

`break` 并非语法上强制要求，但多数独立分支都应该写。如果省略，程序会继续执行后面的 `case`，这种现象称为贯穿（fall-through）。

```c
switch (number)
{
    case 1:
        printf("one\n");
        /* 没有 break，会继续执行 case 2。 */
    case 2:
        printf("two\n");
        break;
}
```

只有明确需要多个分支共用逻辑时，才应有意省略 `break`，并写下注释说明。

## 3. `default` 标签

当所有 `case` 都不匹配时，会执行 `default` 分支：

```c
default:
    printf("Invalid input\n");
    break;
```

`default` 不是必须的，但它可以处理意料之外的输入，因此通常建议保留。

## 4. 使用注意事项

### 4.1 表达式类型

`switch` 表达式需要使用整数类型或枚举类型，例如：

- `char`
- `short`
- `int`
- `long`
- `enum`

不能直接使用 `float`、`double` 或字符串进行 `switch` 判断。

### 4.2 `case` 必须是常量

每个 `case` 后面必须是编译时可确定的整数常量，并且同一个 `switch` 中不能出现重复的 `case` 值。

```c
case 1:
case 'A':
```

### 4.3 `switch` 与 `if` 的选择

- 判断一个变量是否等于多个固定值：适合使用 `switch`。
- 判断范围或复杂条件，例如 `score >= 60 && score < 80`：适合使用 `if...else`。

## 5. 本课程序

源代码：[`number_to_chinese.c`](number_to_chinese.c)

程序接收一个 `1–10` 的整数，并使用 `switch...case` 输出对应的中文数字。输入不在这个范围内时，由 `default` 分支显示提示信息。

## 学习小结

- [x] 理解 `switch...case` 的基本结构
- [x] 能够正确使用 `case` 和 `break`
- [x] 理解省略 `break` 后的贯穿现象
- [x] 能够使用 `default` 处理其他输入
- [x] 知道何时选择 `switch` 或 `if...else`
