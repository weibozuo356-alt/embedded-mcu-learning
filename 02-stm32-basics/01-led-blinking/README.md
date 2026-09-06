# STM32 GPIO LED Control

## 学习目标

- 使用 STM32F103 标准外设库配置 GPIO 推挽输出。
- 理解 `GPIO_SetBits()` 与 `GPIO_ResetBits()` 的含义。
- 将 LED 驱动拆分为 `LED.c` 和 `LED.h`。
- 通过函数参数选择 LED 编号和开关状态。

## 核心知识

`GPIO_SetBits()` 表示让指定 GPIO 引脚输出高电平，`GPIO_ResetBits()` 表示输出低电平。LED 是否点亮还取决于硬件接法。

本实验采用低电平点亮方式：

```text
3.3V -> 限流电阻 -> LED 正极 -> LED 负极 -> GPIO
```

因此：

| GPIO 状态 | 调用方式 | LED 状态 |
| --- | --- | --- |
| 高电平 | `GPIO_SetBits()` | 熄灭 |
| 低电平 | `GPIO_ResetBits()` | 点亮 |

LED 必须串联限流电阻，建议使用 `220Ω` 至 `1kΩ`。

## 工程结构

```text
keil-project/
├── project.uvprojx   # Keil 工程文件
├── project.uvoptx    # Keil 工程选项
├── LED.c             # LED 驱动实现
├── USer/
│   ├── LED.h         # LED 函数声明
│   └── main.c        # 程序入口
├── Library/          # STM32 标准外设库
└── Startup/          # CMSIS、设备头文件和启动文件
```

编译生成的 `Objects/` 和 `Listings/` 没有上传，可在本地重新编译生成。

## 打开工程

使用 Keil 5 打开：

```text
keil-project/project.uvprojx
```

完成编译、下载并确认接线正确后，即可观察 LED 状态。
