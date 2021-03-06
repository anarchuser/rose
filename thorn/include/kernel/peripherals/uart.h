#ifndef _ROSE_K_P_UART_H
#define _ROSE_K_P_UART_H

#include "base.h"

#define UART_CLOCK_FREQ 48000000// 48MHz

#define UART_BASE  PBASE + 0x00201000// 0xFE201000
#define UART_DR    (UART_BASE + 0x000)
#define UART_SR    (UART_BASE + 0x004)
#define UART_FR    (UART_BASE + 0x018)
#define UART_ILPR  (UART_BASE + 0x020)
#define UART_IBRD  (UART_BASE + 0x024)
#define UART_FBRD  (UART_BASE + 0x028)
#define UART_LCR_H (UART_BASE + 0x02C)
#define UART_CR    (UART_BASE + 0x030)
#define UART_IFLS  (UART_BASE + 0x034)
#define UART_IMSC  (UART_BASE + 0x038)
#define UART_RIS   (UART_BASE + 0x03C)
#define UART_MIS   (UART_BASE + 0x040)
#define UART_ICR   (UART_BASE + 0x044)
#define UART_MACR  (UART_BASE + 0x048)

#endif /*_ROSE_K_P_UART_H */
