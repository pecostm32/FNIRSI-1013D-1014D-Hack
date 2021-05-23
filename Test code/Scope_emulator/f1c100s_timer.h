//----------------------------------------------------------------------------------------------------------------------------------

#ifndef F1C100S_TIMER_H
#define F1C100S_TIMER_H

//----------------------------------------------------------------------------------------------------------------------------------

#define TMR_IRQ_EN                         0x00000000      //Timer interrupt enable register
#define TMR_IRQ_STA                        0x00000004      //Timer interrupt status register
#define TMR0_CTRL                          0x00000010      //Timer 0 control register
#define TMR0_INTV_VALUE                    0x00000014      //Timer 0 interval value register
#define TMR0_CUR_VALUE                     0x00000018      //Timer 0 current value register
#define TMR1_CTRL                          0x00000020      //Timer 1 control register
#define TMR1_INTV_VALUE                    0x00000024      //Timer 1 interval value register
#define TMR1_CUR_VALUE                     0x00000028      //Timer 1 current value register
#define TMR2_CTRL                          0x00000030      //Timer 2 control register
#define TMR2_INTV_VALUE                    0x00000034      //Timer 2 interval value register
#define TMR2_CUR_VALUE                     0x00000038      //Timer 2 current value register

#define AVS_CNT_CTL                        0x00000080      //AVS counter control register
#define AVS_CNT0                           0x00000084      //AVS counter 0 register
#define AVS_CNT1                           0x00000088      //AVS counter 1 register
#define AVS_CNT_DIV                        0x0000008C      //AVS counter divisor register

#define WDOG_IRQ_EN                        0x000000A0      //Watchdog irq enable register
#define WDOG_IRQ_STA                       0x000000A4      //Watchdog irq status register
#define WDOG_CTRL                          0x000000B0      //Watchdog control register
#define WDOG_CFG                           0x000000B4      //Watchdog configuration register
#define WDOG_MODE                          0x000000B8      //Watchdog mode register

//----------------------------------------------------------------------------------------------------------------------------------

#define TMR_CTRL_CLK_MASK                  0x0000000C
#define TMR_CTRL_PRS_MASK                  0x00000070

#define TMR_CTRL_ENABLE                    0x00000001
#define TMR_CTRL_RELOAD                    0x00000002
#define TMR_CTRL_CLOCK_24MHZ               0x00000004
#define TMR_CTRL_PRS_1                     0x00000000
#define TMR_CTRL_PRS_2                     0x00000010
#define TMR_CTRL_PRS_4                     0x00000020
#define TMR_CTRL_PRS_8                     0x00000030
#define TMR_CTRL_PRS_16                    0x00000040
#define TMR_CTRL_PRS_32                    0x00000050
#define TMR_CTRL_PRS_64                    0x00000060
#define TMR_CTRL_PRS_128                   0x00000070
#define TMR_CTRL_MODE_SINGLE               0x00000080

//----------------------------------------------------------------------------------------------------------------------------------

#define TMR_IRQ_EN_TMR0_EN                 0x00000001
#define TMR_IRQ_EN_TMR1_EN                 0x00000002
#define TMR_IRQ_EN_TMR2_EN                 0x00000004

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* F1C100S_TIMER_H */

