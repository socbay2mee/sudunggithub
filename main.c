
#include <16F887.h>  
#device ADC=10
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used FOR I/O
#use delay(crystal=20MHz)                          
#define DELAY 10                                                                                                                 
#define LCD_ENABLE_PIN PIN_D2             
#define LCD_RS_PIN PIN_D0                                                    
#define LCD_RW_PIN PIN_D1                          
#define LCD_DATA4 PIN_D4                                                          
#define LCD_DATA5 PIN_D5                                    
#define LCD_DATA6 PIN_D6                                                      
#define LCD_DATA7 PIN_D7                                    
#include <lcd.c>   
#define LED_R PIN_A0 
#define LED_B PIN_A1 
#define LED_G PIN_A2 
/*
SPI SS      RFID-RC522(SDA) - SlaveSelect (SS)                                   
SPI SDI     RFID-RC522(MOSI)                                                        
SPI SDO     RFID-RC522(MISO)
SPI SCK     RFID-RC522(SCK)   
 */
#define MFRC522_CS   PIN_B0                 
#define MFRC522_SCK  PIN_B1
#define MFRC522_SI   PIN_B2                           
#define MFRC522_SO   PIN_B3              
#define MFRC522_RST  PIN_B4    
#include<Built_in.h>                                                                        
char key[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
UNSIGNED INT8 I=0;
UNSIGNED INT tt=0;
//char writeData[] = "Mualinhkien.vn";  
char writeData[] = "12345";  
char RedData[6] ={0XBE,0XBD,0X02,0XC5,0XC4};

int1 red=false;    
int1 get_red(char Data[],char UID[] )
{
 FOR ( i = 0; i < 5; i++)                  
   {   
   if(UID[i]== Data[i] )
   {                                   
     red=true; 
   } 
   else                                             
   {
   red=false;
   break;
   }
   
           
   } 
   return red;

}


void main()
{

   CHAR UID[6];
   UNSIGNED int TagType;    
   CHAR size;                         
   CHAR i;                                        
   lcd_init ();                                                                    
   printf (LCD_PUTC, "\f MuaLinhKien.Vn\nPIC 16/18 Basic Kit");
   delay_ms (1000) ;
   // enable_interrupts (INT_EXT);              
   // enable_interrupts (INT_EXT_H2L);    
   //enable_interrupts (GLOBAL);
   printf (LCD_PUTC, "\fInitializing"); 
   MFRC522_Init ();
   printf (LCD_PUTC, "\nDone!");             
    
   
   WHILE (TRUE)
   {
/*IF (MFRC522_Auth (PICC_AUTHENT1A,63,&key, &UID) == 0) //authentication key A   
         {
            //Write data to block 1  
            lcd_gotoxy(13,1); 
            MFRC522_Write (63,&writeData1);
            printf (LCD_PUTC, "W-A!"); 
}*/
   
        
   
      IF (MFRC522_isCard (&TagType)) //Check any card
      {
           
       //  printf (LCD_PUTC, "\fTAG TYPE:");
        // printf (LCD_PUTC, "%X",TagType);
         
    
         //Read ID 
         IF (MFRC522_ReadCardSerial (&UID))             
         {
                
            printf (LCD_PUTC, "\nUID: ");
            FOR (i = 0; i < 5; i++)                  
            {
           printf (LCD_PUTC, "%X",UID[i]);
          }
          size = MFRC522_SelectTag (&UID);
       
     
      IF (MFRC522_Auth (PICC_AUTHENT1A,63,&writeData, &UID) == 0) //authentication key A   
     { 
       lcd_gotoxy(13,1);
       printf (LCD_PUTC, "W-A!");
     

            if(get_red(RedData,UID))
            {                    
                output_high(LED_R);
            } 
            else
            {
            output_low(LED_R);
            } 
            
     }     
             
                                           
         
       
        // }   
    
    }                                                               
                         
                                          
/*
         else IF (MFRC522_Auth (PICC_AUTHENT1B, 7, &KEY, &UID) == 0) //authentication key B 
         {
            //Write data to block 1 
            lcd_gotoxy(13,1); 
            MFRC522_Write (1,&writeData);
            printf (LCD_PUTC, "W-B!"); 
         }                                          
   */  
                     
         
 
     


MFRC522_Halt () ;
}
 
}

}

