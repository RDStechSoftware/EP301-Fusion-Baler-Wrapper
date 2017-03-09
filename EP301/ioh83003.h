/*       - IOH83003.H -

       WINDOWS simulation
*/

extern unsigned char h8_sfr[256];

/*    8 DMA channels
      --------------
*/
#define DMAC_MAR0AR  (*(unsigned char *)  (&h8_sfr[0x20]))
#define DMAC_MAR0AE  (*(unsigned char *)  (&h8_sfr[0x21]))
#define DMAC_MAR0AH  (*(unsigned char *)  (&h8_sfr[0x22]))
#define DMAC_MAR0AL  (*(unsigned char *)  (&h8_sfr[0x23]))
#define DMAC_ETCR0AH (*(unsigned char *)  (&h8_sfr[0x24]))
#define DMAC_ETCR0AL (*(unsigned char *)  (&h8_sfr[0x25]))
#define DMAC_ETCR0A  (*(unsigned short *) (&h8_sfr[0x24]))
#define DMAC_IOAR0A  (*(unsigned char *)  (&h8_sfr[0x26]))
#define DMAC_DTCR0A  (*(unsigned char *)  (&h8_sfr[0x27]))
#define DMAC_MAR0AW  (*(unsigned short *) (&h8_sfr[0x22]))
#define DMAC_MAR0A   (*(unsigned long *)  (&h8_sfr[0x20]))

#define DMAC_MAR0BR  (*(unsigned char *)  (&h8_sfr[0x28]))
#define DMAC_MAR0BE  (*(unsigned char *)  (&h8_sfr[0x29]))
#define DMAC_MAR0BH  (*(unsigned char *)  (&h8_sfr[0x2A]))
#define DMAC_MAR0BL  (*(unsigned char *)  (&h8_sfr[0x2B]))
#define DMAC_ETCR0BH (*(unsigned char *)  (&h8_sfr[0x2C]))
#define DMAC_ETCR0BL (*(unsigned char *)  (&h8_sfr[0x2D]))
#define DMAC_ETCR0B  (*(unsigned short *) (&h8_sfr[0x2C]))
#define DMAC_IOAR0B  (*(unsigned char *)  (&h8_sfr[0x2E]))
#define DMAC_DTCR0B  (*(unsigned char *)  (&h8_sfr[0x2F]))
#define DMAC_MAR0BW  (*(unsigned short *) (&h8_sfr[0x2A]))
#define DMAC_MAR0B   (*(unsigned long *)  (&h8_sfr[0x28]))

#define DMAC_MAR1AR  (*(unsigned char *)  (&h8_sfr[0x30]))
#define DMAC_MAR1AE  (*(unsigned char *)  (&h8_sfr[0x31]))
#define DMAC_MAR1AH  (*(unsigned char *)  (&h8_sfr[0x32]))
#define DMAC_MAR1AL  (*(unsigned char *)  (&h8_sfr[0x33]))
#define DMAC_ETCR1AH (*(unsigned char *)  (&h8_sfr[0x34]))
#define DMAC_ETCR1AL (*(unsigned char *)  (&h8_sfr[0x35]))
#define DMAC_ETCR1A  (*(unsigned short *) (&h8_sfr[0x34]))
#define DMAC_IOAR1A  (*(unsigned char *)  (&h8_sfr[0x36]))
#define DMAC_DTCR1A  (*(unsigned char *)  (&h8_sfr[0x37]))
#define DMAC_MAR1AW  (*(unsigned short *) (&h8_sfr[0x32]))
#define DMAC_MAR1A   (*(unsigned long *)  (&h8_sfr[0x30]))

#define DMAC_MAR1BR  (*(unsigned char *)  (&h8_sfr[0x38]))
#define DMAC_MAR1BE  (*(unsigned char *)  (&h8_sfr[0x39]))
#define DMAC_MAR1BH  (*(unsigned char *)  (&h8_sfr[0x3A]))
#define DMAC_MAR1BL  (*(unsigned char *)  (&h8_sfr[0x3B]))
#define DMAC_ETCR1BH (*(unsigned char *)  (&h8_sfr[0x3C]))
#define DMAC_ETCR1BL (*(unsigned char *)  (&h8_sfr[0x3D]))
#define DMAC_ETCR1B  (*(unsigned short *) (&h8_sfr[0x3C]))
#define DMAC_IOAR1B  (*(unsigned char *)  (&h8_sfr[0x3E]))
#define DMAC_DTCR1B  (*(unsigned char *)  (&h8_sfr[0x3F]))
#define DMAC_MAR1BW  (*(unsigned short *) (&h8_sfr[0x3A]))
#define DMAC_MAR1B   (*(unsigned long *)  (&h8_sfr[0x38]))

#define DMAC_MAR2AR  (*(unsigned char *)  (&h8_sfr[0x40]))
#define DMAC_MAR2AE  (*(unsigned char *)  (&h8_sfr[0x41]))
#define DMAC_MAR2AH  (*(unsigned char *)  (&h8_sfr[0x42]))
#define DMAC_MAR2AL  (*(unsigned char *)  (&h8_sfr[0x43]))
#define DMAC_ETCR2AH (*(unsigned char *)  (&h8_sfr[0x44]))
#define DMAC_ETCR2AL (*(unsigned char *)  (&h8_sfr[0x45]))
#define DMAC_ETCR2A  (*(unsigned short *) (&h8_sfr[0x44]))
#define DMAC_IOAR2A  (*(unsigned char *)  (&h8_sfr[0x46]))
#define DMAC_DTCR2A  (*(unsigned char *)  (&h8_sfr[0x47]))
#define DMAC_MAR2AW  (*(unsigned short *) (&h8_sfr[0x42]))
#define DMAC_MAR2A   (*(unsigned long *)  (&h8_sfr[0x40]))

#define DMAC_MAR2BR  (*(unsigned char *)  (&h8_sfr[0x48]))
#define DMAC_MAR2BE  (*(unsigned char *)  (&h8_sfr[0x49]))
#define DMAC_MAR2BH  (*(unsigned char *)  (&h8_sfr[0x4A]))
#define DMAC_MAR2BL  (*(unsigned char *)  (&h8_sfr[0x4B]))
#define DMAC_ETCR2BH (*(unsigned char *)  (&h8_sfr[0x4C]))
#define DMAC_ETCR2BL (*(unsigned char *)  (&h8_sfr[0x4D]))
#define DMAC_ETCR2B  (*(unsigned short *) (&h8_sfr[0x4C]))
#define DMAC_IOAR2B  (*(unsigned char *)  (&h8_sfr[0x4E]))
#define DMAC_DTCR2B  (*(unsigned char *)  (&h8_sfr[0x4F]))
#define DMAC_MAR2BW  (*(unsigned short *) (&h8_sfr[0x4A]))
#define DMAC_MAR2B   (*(unsigned long *)  (&h8_sfr[0x48]))

#define DMAC_MAR3AR  (*(unsigned char *)  (&h8_sfr[0x50]))
#define DMAC_MAR3AE  (*(unsigned char *)  (&h8_sfr[0x51]))
#define DMAC_MAR3AH  (*(unsigned char *)  (&h8_sfr[0x52]))
#define DMAC_MAR3AL  (*(unsigned char *)  (&h8_sfr[0x53]))
#define DMAC_ETCR3AH (*(unsigned char *)  (&h8_sfr[0x54]))
#define DMAC_ETCR3AL (*(unsigned char *)  (&h8_sfr[0x55]))
#define DMAC_ETCR3A  (*(unsigned short *) (&h8_sfr[0x54]))
#define DMAC_IOAR3A  (*(unsigned char *)  (&h8_sfr[0x56]))
#define DMAC_DTCR3A  (*(unsigned char *)  (&h8_sfr[0x57]))
#define DMAC_MAR3AW  (*(unsigned short *) (&h8_sfr[0x52]))
#define DMAC_MAR3A   (*(unsigned long *)  (&h8_sfr[0x50]))

#define DMAC_MAR3BR  (*(unsigned char *)  (&h8_sfr[0x58]))
#define DMAC_MAR3BE  (*(unsigned char *)  (&h8_sfr[0x59]))
#define DMAC_MAR3BH  (*(unsigned char *)  (&h8_sfr[0x5A]))
#define DMAC_MAR3BL  (*(unsigned char *)  (&h8_sfr[0x5B]))
#define DMAC_ETCR3BH (*(unsigned char *)  (&h8_sfr[0x5C]))
#define DMAC_ETCR3BL (*(unsigned char *)  (&h8_sfr[0x5D]))
#define DMAC_ETCR3B  (*(unsigned short *) (&h8_sfr[0x5C]))
#define DMAC_IOAR3B  (*(unsigned char *)  (&h8_sfr[0x5E]))
#define DMAC_DTCR3B  (*(unsigned char *)  (&h8_sfr[0x5F]))
#define DMAC_MAR3BW  (*(unsigned short *) (&h8_sfr[0x5A]))
#define DMAC_MAR3B  (*(unsigned long *)   (&h8_sfr[0x58]))


/*    The integrated timer-puls unit (5 channels)
      -------------------------------------------
*/
#define ITU_TSTR  (*(unsigned char *)  (&h8_sfr[0x60]))
#define ITU_TSNC  (*(unsigned char *)  (&h8_sfr[0x61]))
#define ITU_TMDR  (*(unsigned char *)  (&h8_sfr[0x62]))
#define ITU_TFCR  (*(unsigned char *)  (&h8_sfr[0x63]))
#define ITU_TOER  (*(unsigned char *)  (&h8_sfr[0x90]))
#define ITU_TOCR  (*(unsigned char *)  (&h8_sfr[0x91]))

#define ITU_TCR0  (*(unsigned char *)  (&h8_sfr[0x64]))
#define ITU_TIOR0 (*(unsigned char *)  (&h8_sfr[0x65]))
#define ITU_TIER0 (*(unsigned char *)  (&h8_sfr[0x66]))
#define ITU_TSR0  (*(unsigned char *)  (&h8_sfr[0x67]))
#define ITU_TCNT0 (*(unsigned short *) (&h8_sfr[0x68]))
#define ITU_GRA0  (*(unsigned short *) (&h8_sfr[0x6A]))
#define ITU_GRB0  (*(unsigned short *) (&h8_sfr[0x6C]))

#define ITU_TCR1  (*(unsigned char *)  (&h8_sfr[0x6e]))
#define ITU_TIOR1 (*(unsigned char *)  (&h8_sfr[0x6f]))
#define ITU_TIER1 (*(unsigned char *)  (&h8_sfr[0x70]))
#define ITU_TSR1  (*(unsigned char *)  (&h8_sfr[0x71]))
#define ITU_TCNT1 (*(unsigned short *) (&h8_sfr[0x72]))
#define ITU_GRA1  (*(unsigned short *) (&h8_sfr[0x74]))
#define ITU_GRB1  (*(unsigned short *) (&h8_sfr[0x76]))

#define ITU_TCR2  (*(unsigned char *)  (&h8_sfr[0x78]))
#define ITU_TIOR2 (*(unsigned char *)  (&h8_sfr[0x79]))
#define ITU_TIER2 (*(unsigned char *)  (&h8_sfr[0x7a]))
#define ITU_TSR2  (*(unsigned char *)  (&h8_sfr[0x7b]))
#define ITU_TCNT2 (*(unsigned short *) (&h8_sfr[0x7c]))
#define ITU_GRA2  (*(unsigned short *) (&h8_sfr[0x7e]))
#define ITU_GRB2  (*(unsigned short *) (&h8_sfr[0x80]))

#define ITU_TCR3  (*(unsigned char *)  (&h8_sfr[0x82]))
#define ITU_TIOR3 (*(unsigned char *)  (&h8_sfr[0x83]))
#define ITU_TIER3 (*(unsigned char *)  (&h8_sfr[0x84]))
#define ITU_TSR3  (*(unsigned char *)  (&h8_sfr[0x85]))
#define ITU_TCNT3 (*(unsigned short *) (&h8_sfr[0x86]))
#define ITU_GRA3  (*(unsigned short *) (&h8_sfr[0x88]))
#define ITU_GRB3  (*(unsigned short *) (&h8_sfr[0x8a]))
#define ITU_BRA3  (*(unsigned short *) (&h8_sfr[0x8c]))
#define ITU_BRB3  (*(unsigned short *) (&h8_sfr[0x8e]))

#define ITU_TCR4  (*(unsigned char *)  (&h8_sfr[0x92]))
#define ITU_TIOR4 (*(unsigned char *)  (&h8_sfr[0x93]))
#define ITU_TIER4 (*(unsigned char *)  (&h8_sfr[0x94]))
#define ITU_TSR4  (*(unsigned char *)  (&h8_sfr[0x95]))
#define ITU_TCNT4 (*(unsigned short *) (&h8_sfr[0x96]))
#define ITU_GRA4  (*(unsigned short *) (&h8_sfr[0x98]))
#define ITU_GRB4  (*(unsigned short *) (&h8_sfr[0x9a]))
#define ITU_BRA4  (*(unsigned short *) (&h8_sfr[0x9c]))
#define ITU_BRB4  (*(unsigned short *) (&h8_sfr[0x9e]))


/*    Programmable timing pattern controller
      --------------------------------------
*/
#define TPC_TPMR  (*(unsigned char *)  (&h8_sfr[0xa0]))
#define TPC_TPCR  (*(unsigned char *)  (&h8_sfr[0xa1]))
#define TPC_NDERB (*(unsigned char *)  (&h8_sfr[0xa2]))
#define TPC_NDERA (*(unsigned char *)  (&h8_sfr[0xa3]))
#define TPC_NDRB1 (*(unsigned char *)  (&h8_sfr[0xa4]))
#define TPC_NDRA1 (*(unsigned char *)  (&h8_sfr[0xa5]))
#define TPC_NDRB2 (*(unsigned char *)  (&h8_sfr[0xa6]))
#define TPC_NDRA2 (*(unsigned char *)  (&h8_sfr[0xa7]))


/*      Watchdog timer
        --------------
*/
#define WDT_TCSR   (*(unsigned char *)  (&h8_sfr[0xa8]))
#define WDT_TCNT   (*(unsigned char *)  (&h8_sfr[0xa9]))
#define WDT_RSTCSR (*(unsigned char *)  (&h8_sfr[0xab]))

#define WDT_WTCSR   (*(unsigned short *)  (&h8_sfr[0xa8]))
#define WDT_WTCNT   (*(unsigned short *)  (&h8_sfr[0xa8]))
#define WDT_WRSTCSR (*(unsigned short *)  (&h8_sfr[0xaa]))
#define WDT_WRSTOE  (*(unsigned short *)  (&h8_sfr[0xaa]))


/*      Refresh controller
        ------------------
*/
#define RFSHCR   (*(unsigned char *)  (&h8_sfr[0xac]))
#define RTMCSR   (*(unsigned char *)  (&h8_sfr[0xad]))
#define RTCNT    (*(unsigned char *)  (&h8_sfr[0xae]))
#define RTCOR    (*(unsigned char *)  (&h8_sfr[0xaf]))


/*        Serial communication interface
          ------------------------------
*/
#define SCI0_SMR  (*(unsigned char *)  (&h8_sfr[0xb0]))
#define SCI0_BRR  (*(unsigned char *)  (&h8_sfr[0xb1]))
#define SCI0_SCR  (*(unsigned char *)  (&h8_sfr[0xb2]))
#define SCI0_TDR  (*(unsigned char *)  (&h8_sfr[0xb3]))
#define SCI0_SSR  (*(unsigned char *)  (&h8_sfr[0xb4]))
#define SCI0_RDR  (*(unsigned char *)  (&h8_sfr[0xb5]))

#define SCI1_SMR  (*(unsigned char *)  (&h8_sfr[0xb8]))
#define SCI1_BRR  (*(unsigned char *)  (&h8_sfr[0xb9]))
#define SCI1_SCR  (*(unsigned char *)  (&h8_sfr[0xba]))
#define SCI1_TDR  (*(unsigned char *)  (&h8_sfr[0xbb]))
#define SCI1_SSR  (*(unsigned char *)  (&h8_sfr[0xbc]))
#define SCI1_RDR  (*(unsigned char *)  (&h8_sfr[0xbd]))


/*      Some 8-bit ports....
        --------------------
*/
#define P4CR    (*(unsigned char *)  (&h8_sfr[0xda]))
#define P4DR    (*(unsigned char *)  (&h8_sfr[0xc7]))
#define P4DDR   (*(unsigned char *)  (&h8_sfr[0xc5]))

#define P5CR    (*(unsigned char *)  (&h8_sfr[0xdb]))
#define P5DR    (*(unsigned char *)  (&h8_sfr[0xca]))
#define P5DDR   (*(unsigned char *)  (&h8_sfr[0xc8]))

#define P6DR    (*(unsigned char *)  (&h8_sfr[0xcb]))
#define P6DDR   (*(unsigned char *)  (&h8_sfr[0xc9]))

#define P7DR    (*(unsigned char *)  (&h8_sfr[0xce]))

#define P8DR    (*(unsigned char *)  (&h8_sfr[0xcf]))
#define P8DDR   (*(unsigned char *)  (&h8_sfr[0xcd]))

#define P9DR    (*(unsigned char *)  (&h8_sfr[0xd2]))
#define P9DDR   (*(unsigned char *)  (&h8_sfr[0xd0]))

#define PADR    (*(unsigned char *)  (&h8_sfr[0xd3]))
#define PADDR   (*(unsigned char *)  (&h8_sfr[0xd1]))

#define PBDR    (*(unsigned char *)  (&h8_sfr[0xd6]))
#define PBDDR   (*(unsigned char *)  (&h8_sfr[0xd4]))

#define PCDR    (*(unsigned char *)  (&h8_sfr[0xd7]))
#define PCDDR   (*(unsigned char *)  (&h8_sfr[0xd5]))


/*      A/D converters
        --------------
*/
#define ADDRA    (*(unsigned short *) (&h8_sfr[0xe0]))
#define ADDRAH   (*(unsigned char *)  (&h8_sfr[0xe0]))
#define ADDRAL   (*(unsigned char *)  (&h8_sfr[0xe1]))
#define ADDRB    (*(unsigned short *) (&h8_sfr[0xe2]))
#define ADDRBH   (*(unsigned char *)  (&h8_sfr[0xe2]))
#define ADDRBL   (*(unsigned char *)  (&h8_sfr[0xe3]))
#define ADDRC    (*(unsigned short *) (&h8_sfr[0xe4]))
#define ADDRCH   (*(unsigned char *)  (&h8_sfr[0xe4]))
#define ADDRCL   (*(unsigned char *)  (&h8_sfr[0xe5]))
#define ADDRD    (*(unsigned short *) (&h8_sfr[0xe6]))
#define ADDRDH   (*(unsigned char *)  (&h8_sfr[0xe6]))
#define ADDRDL   (*(unsigned char *)  (&h8_sfr[0xe7]))
#define ADCSR    (*(unsigned char *)  (&h8_sfr[0xe8]))
#define ADCR     (*(unsigned char *)  (&h8_sfr[0xe9]))


/*      Bus controller
        --------------
*/
#define ABWCR   (*(unsigned char *)  (&h8_sfr[0xec]))
#define ASTCR   (*(unsigned char *)  (&h8_sfr[0xed]))
#define WCR     (*(unsigned char *)  (&h8_sfr[0xee]))
#define WCER    (*(unsigned char *)  (&h8_sfr[0xef]))
#define BRCR    (*(unsigned char *)  (&h8_sfr[0xf3]))


/*      System control
        --------------
*/
#define MDCR    (*(unsigned char *)  (&h8_sfr[0xf1]))
#define SYSCR   (*(unsigned char *)  (&h8_sfr[0xf2]))


/*      Interrupt controller
        --------------------
*/
#define ISCR    (*(unsigned char *)  (&h8_sfr[0xf4]))
#define IER     (*(unsigned char *)  (&h8_sfr[0xf5]))
#define ISR     (*(unsigned char *)  (&h8_sfr[0xf6]))
#define IPRA    (*(unsigned char *)  (&h8_sfr[0xf8]))
#define IPRB    (*(unsigned char *)  (&h8_sfr[0xf9]))
