#ifndef _ROSE_K_P_ETHERNET_H
#define _ROSE_K_P_ETHERNET_H

#define ETHERNET_BASE	    0xFD580000
#define ETHERNET_MDIO	    (ETHERNET_BASE + 0x0E14)
#define ETHERNET_MDIO_END	(ETHERNET_BASE + 0x0E1B)
#define ETHERNET_END	    (ETHERNET_BASE + 0xFFFF)

// SYS registers
#define SYS             (ETHERNET_BASE + 0x0000)
#define SYS_REV_CTRL	(SYS + 0x0000)

// GR_BRIDGE registers
#define GR_BRIDGE       (ETHERNET_BASE + 0x0040)

// EXT registers
#define EXT             (ETHERNET_BASE + 0x0080)

// INTRL2_0 registers
#define INTRL2_0        (ETHERNET_BASE + 0x0200)

// INTRL2_1 registers
#define INTRL2_1        (ETHERNET_BASE + 0x0240)

// RBUF registers
#define RBUF            (ETHERNET_BASE + 0x0300)

// UMAC registers
#define UMAC            (ETHERNET_BASE + 0x0800)

#endif /*_ROSE_K_P_ETHERNET_H */
