//SAVE AS lcd_fun.c!!!!!!!!!!!!!!!!!!!!!!!
#pragma config OSC = IRCIO67
#pragma config BOREN = OFF
#pragma config WDT   = OFF
#pragma config LVP   = OFF

#define ldata PORTC
#define rs PORTCbits.RC4
#define en PORTCbits.RC5
#include <P18F4580.h>


void init_lcd(void);
void lcdcmd(unsigned char value);
void lcddata(unsigned char value);
void delay_ms(unsigned int value);

unsigned char lcd_msg[]={"Hello, PIC! This is long"}, i = 0;
unsigned char lcd_msg2[]={"line two goes on too"}, j = 0;
unsigned int shift = 0;

void delay_ms(unsigned int itime)
{ unsigned int i, j;
for(i=0;i<itime;i++)
    for(j=0;j<107;j++);
}

void lcdcmd(unsigned char value) //send command to the lcd module
{
    ldata = value >> 4;
    rs=0;
    en=1; delay_ms(1); en=0;
    ldata = value &0x0F;
    rs=0;
    en=1; delay_ms(1); en=0;    
}

void lcddata(unsigned char value)
{
    ldata = value >> 4;
    rs=1;
    en=1; delay_ms(1); en=0;
    ldata = value &0x0F;
    rs=1;
    en=1; delay_ms(1); en=0;    
}

void init_lcd(void)
{
    delay_ms(100);
    lcdcmd(0x22);
    ldata=0x0C; rs=0; en=1; delay_ms(1); en=0;
    delay_ms(1);
    lcdcmd(0x0f); //display on, cursor on, cursor flash
    delay_ms(1);
    lcdcmd(0x01); //clear display
    delay_ms(2); 
    lcdcmd(0x06); //cursor is in  increment mode, no shift screen
    delay_ms(1);
}






