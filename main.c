#include <reg51.h>

#define lcd P2

sbit rs = P3^0;
sbit rw = P3^1;
sbit en = P3^2;

sbit entry = P1^0;
sbit exit1 = P1^1;

int slots = 5;

void delay()
{
    int i,j;

    for(i=0;i<20;i++)
    for(j=0;j<100;j++);
}

void lcd_cmd(unsigned char cmd)
{
    lcd = cmd;

    rs = 0;
    rw = 0;
    en = 1;

    delay();

    en = 0;
}

void lcd_data(unsigned char dat)
{
    lcd = dat;

    rs = 1;
    rw = 0;
    en = 1;

    delay();

    en = 0;
}

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str);
        str++;
    }
}

void lcd_init()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

void display_slots()
{
    lcd_cmd(0x80);

    if(slots == 0)
    {
        lcd_string("PARKING FULL ");
    }
    else
    {
        lcd_string("SLOTS LEFT: ");

        lcd_data(slots + '0');
        lcd_string(" ");
    }
}

void main()
{
    lcd_init();

    while(1)
    {
        display_slots();

        if(entry == 0)
        {
            delay();

            if(entry == 0)
            {
                if(slots > 0)
                {
                    slots--;
                }

                while(entry == 0);
            }
        }

        if(exit1 == 0)
        {
            delay();

            if(exit1 == 0)
            {
                if(slots < 5)
                {
                    slots++;
                }

                while(exit1 == 0);
            }
        }
    }
}