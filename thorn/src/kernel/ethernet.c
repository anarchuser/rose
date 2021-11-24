#include "kernel/ethernet.h"

void handle_ethernet_irq() {
    printf ("ethernet interrupt received!\r\n");
}


// #define UMAC_CMD			0x008
// #define  CMD_SW_RESET			(1 << 13)
// #define  CMD_LCL_LOOP_EN		(1 << 15)
// #define SYS_RBUF_FLUSH_CTRL		0x08

// #define  MIB_RESET_RX			(1 << 0)
// #define  MIB_RESET_RUNT			(1 << 1)
// #define  MIB_RESET_TX			(1 << 2)

// #define UMAC_MIB_CTRL			0x580

// #define ENET_MAX_MTU_SIZE		1536	// with padding

// #define UMAC_MAX_FRAME_LEN		0x014
// #define RBUF_CTRL			0x00
// #define  RBUF_ALIGN_2B			(1 << 1)
// #define RBUF_TBUF_SIZE_CTRL		0xB4
// #define SYS_REV_CTRL			0x00

// // Register block offsets
// #define GENET_SYS_OFF			0x0000
// #define GENET_GR_BRIDGE_OFF		0x0040
// #define GENET_EXT_OFF			0x0080
// #define GENET_INTRL2_0_OFF		0x0200
// #define GENET_INTRL2_1_OFF		0x0240
// #define GENET_RBUF_OFF			0x0300
// #define GENET_UMAC_OFF			0x0800

// // intrl2 interrupts
// #define UMAC_IRQ_LINK_UP		(1 << 4)
// #define UMAC_IRQ_LINK_DOWN		(1 << 5)
// #define UMAC_IRQ_LINK_EVENT		(UMAC_IRQ_LINK_UP | UMAC_IRQ_LINK_DOWN)

// // uniMac intrl2 registers
// #define INTRL2_CPU_STAT			0x00
// #define INTRL2_CPU_SET			0x04
// #define INTRL2_CPU_CLEAR		0x08
// #define INTRL2_CPU_MASK_STATUS		0x0C
// #define INTRL2_CPU_MASK_SET		0x10
// #define INTRL2_CPU_MASK_CLEAR		0x14

// // Generate I/O inline functions
// #define GENET_IO_MACRO(name, offset)				\
// static inline unsigned int name##_readl(unsigned int off)				\
// {								\
// 	return get32 (ETHERNET_BASE + offset + off);	\
// }								\
// static inline void name##_writel(unsigned int val, unsigned int off)		\
// {								\
// 	put32 (ETHERNET_BASE + offset + off, val);	\
// }

// GENET_IO_MACRO(umac, GENET_UMAC_OFF);
// GENET_IO_MACRO(sys, GENET_SYS_OFF);
// GENET_IO_MACRO(intrl2_0, GENET_INTRL2_0_OFF);
// GENET_IO_MACRO(intrl2_1, GENET_INTRL2_1_OFF);
// GENET_IO_MACRO(rbuf, GENET_RBUF_OFF);

// #define rbuf_ctrl_set(val)		sys_writel(val, SYS_RBUF_FLUSH_CTRL)
// #define rbuf_ctrl_get()			sys_readl(SYS_RBUF_FLUSH_CTRL)

// #define BIT(n)		(1U << (n))

bool init_ethernet (void) {
    unsigned int revision = get32 (SYS_REV_CTRL);

    if (((revision >> 24) & 0x0F) != 6) { // major version
        ERROR ("Ethernet controller major version not supported");
        return false;
    } else if (((revision >> 16) & 0x0F) != 0) { // minor version
        ERROR ("Ethernet controller minor version not supported");
        return false;
    } else if ((revision & 0xFFFF) != 0) { // ephy version
        ERROR ("Ethernet controller ephy version not supported");
        return false;
    }

	return true;
}
