//Main function with lots of initialization and at the end the endless loop of calling some functions

//void FUN_80035320(void)
void main(void)
{
  int iVar1;
  undefined auStack568 [568];
  
  FUN_80028028(0);                           //Initialize the CPU clock on 600MHz
  FUN_80037484();                            //Initialize MMU
  FUN_8002809c(DAT_80035458);                //0x0001C200. Address of non existent (according to manual) SRAM. Initialize UART0
  FUN_80027fe8();                            //??
  FUN_8002510c();                            //Setup port C for communication with the flash
  FUN_800168a0();                            //Set up FPGA communication bus. This means that the UART0 is no longer connected to the PE pins
  FUN_8001c79c();
  FUN_8001d5d4();
  FUN_8001931c(); 
  FUN_8001794c();                            //Setup for the touch panel
  iVar1 = FUN_80033714(auStack568,&DAT_8003545c,1);  //Check if SD card present with a correct format

  if (iVar1 != 0)
  {
    *(undefined *)(DAT_80035460 + 2) = 100;
    FUN_800169f8(0x38);
    FUN_800168fc(0xea);
    FUN_800168fc(0x60);
    FUN_80019704(0);
    FUN_80018f6c(0,0,800,0x1e0);
    FUN_80019704(0xff0000);
    FUN_80019730(PTR_PTR_FUN_80035468);
    FUN_800197c8(0);
    FUN_80018bf8(s_SD_ERROR_8003546c,0x1e,0x32);  //Display text on the LCD
    do 
    {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }

  FUN_8001c138();                      //Check the hardware for correct operation
  FUN_8002a17c();
  FUN_80002b7c();
  FUN_800232e4();
  FUN_80016af4();
  FUN_8000690c();
  FUN_80009658();
  FUN_80001314();
  FUN_8000689c();
  FUN_800095e8();
  FUN_800068d4();
  FUN_80009620();
  FUN_80012a4c();
  FUN_80024e18();
  FUN_800266c4();
  FUN_800267e8();
  FUN_80002790();
  FUN_80026808();
  FUN_800267c4();
  FUN_80026828();
  FUN_8000696c();
  FUN_800096b8();
  FUN_80017ce0();
  FUN_80026918();
  FUN_8000a024();
  FUN_8000e8f0();
  FUN_8001d380();                         //Load display brightness from parameter storage and write it to the FPGA

  do                                      //Main program
  {
    FUN_8000a54c();
    FUN_800253e8();
    thunk_FUN_8002b124();
    FUN_8001a3b4();
  } while( true );
}

