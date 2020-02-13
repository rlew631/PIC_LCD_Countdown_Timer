//this is actually part one of the exercises!!!
#include<P18F4580.h>
#include "lcd_fun.c" //put lcd_fun.c in the same folder
unsigned char secs=06, mins=00, x=0;
unsigned char str0[]={"Minute Second"};
unsigned char str1[]={"00:00"};
unsigned char str2[]={"Time is up!     "};

void Time_generate (void) //update the time in seconds
{
    TMR0H=11;
    TMR0L=220;
    secs--;
    //if(mins==00&&secs==00)
    //{mins=0;secs=0;}
    if(secs==00&&mins!=00){mins--; secs=59;}
    INTCONbits.TMR0IF=0;    //clear timer0 flag in INTCON register     
}
// ^^ CALL THE FUNCTION WHEN FLAG BIT IS 1
/*
 1 second delay:  Treq=1000000us,
 Fosc=8mhz, Fclk=2mhz, Tclk=1/(2*10^6)=0.5us
 no counts = Treq/(Tclkxprescaler<=65536
 prescaler>=Treq/(Tclk*65536)=10^us/(0.5us*65535)=30.5
 prescaler=32
 no.counts=Treq/(Tclk*prescaler)=10^6us/(0.5us*32)=62500
 TMRO=65536-62500=3036
 
 T0CON=0b10000100
 */        
void main(void)
{   OSCTUNEbits.PLLEN=1; //Choose internal oscillator
    OSCCON=0b01111100;      //8 pins in PortC as outputs
    TRISC=0x00;     //8 pins in PortC as outputs
    TMR0H=11; TMR0L=220;    //initializes timer0 register
    T0CON=0b10000100;
    init_lcd();
    lcdcmd(0x80);       //initializes the lcd for lcddata commands
    while(str0[i]!=0x00)
    {lcddata(str0[i]);  i++;}
    while(1)
    {   lcdcmd(0xC4);      //start writing on second row
        while(INTCONbits.TMR0IF==0){;} //if TMR0 rollover flag is zero, wait here
        Time_generate();
        str1[0]=mins/10+0x30;
        str1[1]=mins%10+0x30;
        str1[3]=secs/10+0x30;
        str1[4]=secs%10+0x30;
        i=0;
        while(str1[i]!=0x00)
            {lcddata(str1[i]);  i++;}
        if(mins==00 && secs==00)
        {
            lcdcmd(0xC9);//last digit of seconds
            lcddata(30); //write "0"
            lcdcmd(0x80); //first line first char
            i=0;
            while(str2[i]!=0x00)
                {
                lcddata(str2[i]);
                i++;}
            break;
        }

    }
}




