#include "spi_control.h"
#include "ccu_control.h"
#include "gpio_control.h"

//Probleem is twee ledig.

//A) de clock kan te hoog zijn, maar lijkt in de scope ook zo te staan

//B) voor het ontvangen na het zenden moet wellicht de rx fifo gewist worden. In de originele software
//   doen ze dat in de spi_transfer functie, waar ze na het schrijven de fifo lezen en de data negeren als er geen rx buffer is
//   mijns inziens kan je dat ook voor elkaar krijgen door voor het lezen te starten te zorgen dat de fifo gereset wordt

//   Dus nog eens goed hier naar kijken!!!!!!


void sys_spi_flash_init(void)
{
  //Configure PC0, PC1, PC2 and PC3 for SPI0
  *PORTC_CFG0_REG = PORTC_CFG0_PIN_3_SPI0_MOSI | PORTC_CFG0_PIN_2_SPI0_MISO | PORTC_CFG0_PIN_1_SPI0_CS | PORTC_CFG0_PIN_0_SPI0_CLK;

  //De-assert SPI0 reset
  *CCU_BUS_SOFT_RST0 |= CCU_BSRR0_SPI0_RST;

  //Open the SPI0 bus gate
  *CCU_BUS_CLK_GATE0 |= CCU_BCGR0_SPI0_EN;
  
  //Set SPI0 clock rate control register to AHB_CLK divided by 6 = (2 * (2 + 1))
  *SPI0_CCR = SPI_CCR_DRS_DIV_2 | SPI_CCR_CDR2(2);

  //Enable SPI0 in master mode with transmit pause enabled and do a soft reset
  *SPI0_GCR = SPI_GCR_SRST | SPI_GCR_TP_EN | SPI_GCR_MODE_MASTER | SPI_GCR_MODE_EN;

  //Wait for it to be reset  
  while(*SPI0_GCR & SPI_GCR_SRST);

  //Set slave select level high, and controlled by software with signal polarity active low
  *SPI0_TCR = SPI_TCR_SS_LEVEL_HIGH | SPI_TCR_SS_OWNER_SOFT | SPI_TCR_SPOL_ACTIVE_LOW;
  
  //Reset the FIFO's
  *SPI0_FCR = SPI_FCR_TX_FIFO_RST | SPI_FCR_TX_TRIG_LEV_64 | SPI_FCR_RX_FIFO_RST | SPI_FCR_RX_TRIG_LEV_1;
}

void sys_spi_flash_exit(void)
{
  //Disable the SPI0 controller and revert back to slave mode
  *SPI0_GCR &= ~(SPI_GCR_MODE_MASTER | SPI_GCR_MODE_EN);
}

void sys_spi_flash_read(int addr, unsigned char *rxbuffer, int length)
{
  unsigned char txbuffer[4];

  //Fill in the tx buffer with the read command and the address to read from
  txbuffer[0] = 0x03;
  txbuffer[1] = (unsigned char)(addr >> 16);
  txbuffer[2] = (unsigned char)(addr >> 8);
  txbuffer[3] = (unsigned char)(addr >> 0);
  
  //Assert the pre selected CS0 line
  *SPI0_TCR &= ~SPI_TCR_SS_LEVEL_HIGH;
  
  //Write the read command with the memory address to read from
  sys_spi_write(txbuffer, 4);

  //Read the data into the receive buffer
  sys_spi_read(rxbuffer, length);
  
  //De-assert the pre selected CS0 line
  *SPI0_TCR |= SPI_TCR_SS_LEVEL_HIGH;
}

//--------------------------------------------------------------------------------------
//Send a buffer full of data to the SPI, but do it in chunks of max 64 bytes (FIFO length)
void sys_spi_write(unsigned char *buffer, int length)
{
  int i;
  int cnt;
  
  //Send all the bytes in smaller chunks as needed
  while(length)
  {
    //Need to do it in chunks of max 64 bytes
    if(length <= 64)
      cnt = length;
    else
      cnt = 64;
    
    //Set the number of bytes to transfer in this burst
    *SPI0_MBC = cnt;

    //Set master transmit count with the number of bytes to transmit
    *SPI0_MTC = cnt;

    //Set the master single mode transmit counter to the same number of bytes to transmit
    *SPI0_BCC = cnt;

    //Load the bytes into the FIFO via the transmit byte register
    for(i=0;i<cnt;++i)
      *SPI0_TXD_BYTE = *buffer++;

    //Start the transfer
    *SPI0_TCR |= SPI_TCR_XCH_START;
    
    //Take of the chunk send
    length -= cnt;
    
    //When more bytes to send, wait until the bytes in the FIFO have been send
    if(length)
      while(*SPI0_TCR & SPI_TCR_XCH_START);
  }
}

//Read a buffer of bytes from the SPI, but do it in chunks of max 64 bytes (FIFO length)
void sys_spi_read(unsigned char *buffer, int length)
{
  int i;
  int cnt;

  //Make sure the SPI is ready to receive
  while(*SPI0_TCR & SPI_TCR_XCH_START);

  //Clear the receive FIFO to drop what ever is left in there
  *SPI0_FCR |= SPI_FCR_RX_FIFO_RST;
  
  //Make sure it is cleared
  while(*SPI0_FCR & SPI_FCR_RX_FIFO_RST);
  
  //No bytes to transmit
  *SPI0_MTC = 0;
  *SPI0_BCC = 0;
  
  //Receive all the bytes in smaller chunks as needed  
  while(length)
  {
    //Check if more then 64 bytes (FIFO size) to read
    if(length <= 64)
      cnt = length;
    else
      cnt = 64;
    
    //Set the number of bytes to read in this burst
    *SPI0_MBC = cnt;
    
    //Start the transfer
    *SPI0_TCR |= SPI_TCR_XCH_START;
    
    //Wait until all the bytes have been received
    while((*SPI0_FSR & 0xFF) < cnt);
    
    for(i=0;i<cnt;i++)
    {
      *buffer++ = *SPI0_RXD_BYTE;
    }

    length -= cnt;
  }
}


