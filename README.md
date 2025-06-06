# spe-stm32-adin1110-modbus-framework

This is a **STM32CubeIDE** project that includes a modular framework supporting:

- **STM32L4S5VITX** microcontroller  
- **FreeRTOS** real-time operating system  
- **ADIN1110** Ethernet transceiver (using the no-OS driver)  
- **Modbus TCP/IP server** (via [micro-modbus](https://github.com/landas/micro-modbus))

> The framework requires approximately 160 kB of flash memory.  
> It should be relatively straightforward to adapt the project to other STM32 microcontrollers.

## ADIN1110 Device Driver

This project uses a **generic SPI interface** to communicate with the **ADIN1110** transceiver.

### SPI Pin Configuration

| Signal | Pin |
|--------|-----|
| MISO   | PA6 |
| MOSI   | PA7 |
| SCLK   | PA5 |
| CS     | PA3 |
| RESET  | PD7 |

> These pin assignments may need to be updated in both the source code (`config.h`) and the STM32CubeIDE **Pinout & Configuration** tool.

### Driver Notes

A small "hack" has been applied to the no-OS driver to enable **SPI DMA** transfers for improved performance.

You can find the original driver here:  
[Analog Devices no-OS ADIN1110 Driver](https://github.com/analogdevicesinc/no-OS/tree/main/drivers/net/adin1110)

## Modbus TCP/IP Server

The project uses the lightweight and efficient **[micro-modbus](https://github.com/landas/micro-modbus)** library to implement a Modbus TCP/IP server.

## Background & Support

This project originated as part of a **bachelor thesis in electrical automation** at **USN Vestfold**, Spring 2025.

> **Note:** I am unable to provide support for this project, but I hope it serves as a helpful reference for others working on similar applications.
