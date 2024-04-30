//----------------------------------------------------------------------------------------------------------------------------------

#ifndef F1C100S_SPI_H
#define F1C100S_SPI_H

//----------------------------------------------------------------------------------------------------------------------------------
//SPI controller register low addresses
#define SPI_GCR                  0x00000004
#define SPI_TCR                  0x00000008
#define SPI_IER                  0x00000010
#define SPI_ISR                  0x00000014
#define SPI_FCR                  0x00000018
#define SPI_FSR                  0x0000001C
#define SPI_WCR                  0x00000020
#define SPI_CCR                  0x00000024
#define SPI_MBC                  0x00000030
#define SPI_MTC                  0x00000034
#define SPI_BCC                  0x00000038
#define SPI_TXD                  0x00000200
#define SPI_RXD                  0x00000300

//----------------------------------------------------------------------------------------------------------------------------------
//Global control settings
#define SPI_GCR_SRST                0x80000000       //Soft reset. Self clearing
#define SPI_GCR_TP_EN               0x00000080       //Transmit pause enable
#define SPI_GCR_MODE_MASTER         0x00000002       //Enable master mode
#define SPI_GCR_MODE_EN             0x00000001       //Enable SPI controller

//----------------------------------------------------------------------------------------------------------------------------------
//Transfer control settings
#define SPI_TCR_XCH_START           0x80000000       //Exchange burst start
#define SPI_TCR_SDM_NORMAL          0x00002000       //Set master sample data mode to normal
#define SPI_TCR_FBS_LSB             0x00001000       //Set first bit transmit to LSB
#define SPI_TCR_SDC_DELAY           0x00000800       //Set master sample data control to delay
#define SPI_TCR_RPSM_RAPID          0x00000400       //Set rapids mode to rapids write
#define SPI_TCR_DDB_ONE             0x00000200       //Set dummy burst type to bit value one
#define SPI_TCR_DHB_DISCARD         0x00000100       //Set discard hash burst to discarddummy burst type to bit value one
#define SPI_TCR_SS_LEVEL_HIGH       0x00000080       //Set ss level to high
#define SPI_TCR_SS_OWNER_SOFT       0x00000040       //Set ss owner to software
#define SPI_TCR_SS_SEL_SS0          0x00000000       //Set ss chip select line 0
#define SPI_TCR_SS_SEL_SS1          0x00000010       //Set ss chip select line 1
#define SPI_TCR_SS_SEL_SS2          0x00000020       //Set ss chip select line 2
#define SPI_TCR_SS_SEL_SS3          0x00000030       //Set ss chip select line 3
#define SPI_TCR_SS_CTL_NEGATE       0x00000008       //Set ss control to negate
#define SPI_TCR_SPOL_ACTIVE_LOW     0x00000004       //Set spol to active low
#define SPI_TCR_CPOL_ACTIVE_LOW     0x00000002       //Set spol to active low
#define SPI_TCR_CPHA_PHASE_1        0x00000001       //Set clock/data phase to leading edge for setup data 

//----------------------------------------------------------------------------------------------------------------------------------
//FIFO control settings
#define SPI_FCR_TX_FIFO_RST         0x80000000       //Transmit FIFO reset. Self clearing
#define SPI_FCR_TX_TRIG_LEV_64      0x00400000       //Trigger level for transmit FIFO

#define SPI_FCR_RX_FIFO_RST         0x00008000       //Receive FIFO reset. Self clearing
#define SPI_FCR_RX_TRIG_LEV_1       0x00000001       //Trigger level for receive FIFO

//----------------------------------------------------------------------------------------------------------------------------------
//Clock control settings
#define SPI_CCR_DRS_DIV_2           0x00001000       //Divide rate select. Clock divide rate 2

//SPI frequency is based on AHB_CLK.
//When CDR1 is used it is AHB_CLK / 2^(N + 1)
//Divide factor CDR1 (0 -- 15)
#define SPI_CCR_CDR1(x)             ((x & 0xF) << 8)

//When CDR2 is used it is AHB_CLK / 2*(N + 1)
//Divide factor CDR1 (0 -- 15)
#define SPI_CCR_CDR2(x)            (x & 0xF)

//----------------------------------------------------------------------------------------------------------------------------------
//Flash memory defines
#define FLASH_STATE_IDLE                 0
#define FLASH_STATE_RX_ADDRESS_H         1
#define FLASH_STATE_RX_ADDRESS_M         2
#define FLASH_STATE_RX_ADDRESS_L         3
#define FLASH_STATE_PROCESS              4

#define FLASH_MODE_IDLE                  0
#define FLASH_MODE_READ                  1

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* F1C100S_SPI_H */

