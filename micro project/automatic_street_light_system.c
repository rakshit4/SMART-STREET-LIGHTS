#include<reg51.h>  
//sensors on street
sbit sensor1 = P1^0; //to check day or night
sbit sensor2 = P1^1; //for first street light
sbit sensor3 = P1^2; //for second street light
sbit sensor4 = P1^3; //for third street light
//lamps on street
sbit lamp1 = P1^4; //first street light
sbit lamp2 = P1^5; //second street light
sbit lamp3 = P1^6; //third street light
//ldrs to check lamps
sbit ldr1 = P0^0; //to check is street light 1 is working
sbit ldr2 = P0^1; //to check if second street light is working
sbit ldr3 = P0^2; //to check if third street light is working
//lcd interfacing
sfr lcd_data_port=0xA0;		/* P1 port as data port */
sbit rs=P3^0;			/* Register select pin */
sbit rw=P3^1;			/* Read/Write pin */
sbit en=P3^2;			/* Enable pin */


void delay(unsigned int count)  /* Function to provide delay Approx 1ms */
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<112;j++);
}

void LCD_Command (unsigned char cmd)  /* LCD16x2 command funtion */
{
	lcd_data_port= cmd;
	rs=0;			/* command reg. */
	rw=0;			/* Write operation */
	en=1; 
	delay(1);
	en=0;
	delay(5);
}

void LCD_Char (unsigned char char_data)  /* LCD data write function */
{
	lcd_data_port=char_data;
	rs=1;			/* Data reg.*/
	rw=0;			/* Write operation*/
	en=1;   				
	delay(1);
	en=0;
	delay(5);
}

void LCD_String (unsigned char *str) /* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)  /* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);  /* Call LCD data write */
	}
}

void LCD_String_xy (char row, char pos, char *str)  /* Send string to LCD function */
{
	if (row == 0)
	LCD_Command((pos & 0x0F)|0x80);
	else if (row == 1)
	LCD_Command((pos & 0x0F)|0xC0);
	LCD_String(str);	/* Call LCD string function */
}

void LCD_Init (void)		/* LCD Initialize function */
{	
	delay(20);		/* LCD Power ON Initialization time >15ms */
	LCD_Command (0x38);	/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);	/* Display ON Cursor OFF */
	LCD_Command (0x06);	/* Auto Increment cursor */
	LCD_Command (0x01);	/* clear display */
	LCD_Command (0x80);	/* cursor at home position */
}

void main ()
{
	LCD_Init();
	lamp1 = lamp2 = lamp3 = 0;
	sensor1 = sensor2 = sensor3 = sensor4 = 0;//optional logic based on input
	while(1){
			if(sensor1 == 0){
				lamp1 = lamp2 = lamp3 = 0;
				LCD_Command(0x01);
				LCD_String("DAY TIME");  
				LCD_Command(0xC0);
				LCD_String("ALL LIGHTS OFF");  
				delay(500);
			}
			if(ldr1== 0 && sensor2 == 1 && sensor1==1){
				LCD_Command(0x01);
				LCD_String("LAMP1        ");  
				LCD_Command(0xC0);
				LCD_String("WORKING       ");
				lamp1 = 1;
				lamp2 = 0;
				lamp3 = 0;
				delay(500);
			}
			if(ldr1!= 0 && sensor2 == 1 && sensor1==1){
				LCD_Command(0x01);
				LCD_String("LAMP1    ");  
				LCD_Command(0xC0);
				LCD_String("NOT WORKING     ");
				lamp1 = 1;
				lamp2 = 0;
				lamp3 = 0;
				delay(500);
			}
			if(ldr2== 0 && sensor3 == 1 && sensor1==1){
				LCD_Command(0x01);
				LCD_String("LAMP2   ");  
				LCD_Command(0xC0);
				LCD_String("WORKING   ");
				lamp1 = 0;
				lamp2 = 1;
				lamp3 = 0;
				delay(500);
			}if(ldr2!= 0 && sensor3 == 1 && sensor1==1){
				LCD_Command(0x01);
				LCD_String("LAMP2");  
				LCD_Command(0xC0);
				LCD_String("NOT WORKING    ");
				lamp1 = 0;
				lamp2 = 1;
				lamp3 = 0;
				delay(500);
			}if(ldr3== 0 && sensor4 == 1 && sensor1==1){
				LCD_Command(0x01);
				LCD_String("LAMP3");  
				LCD_Command(0xC0);
				LCD_String("WORKING           ");
				lamp1 = 0;
				lamp2 = 0;
				lamp3 = 1;
				delay(500);
			}if(ldr3!= 0 && sensor4 == 1 && sensor1==1){
				LCD_Command(0x01);
				LCD_String("LAMP3");  
				LCD_Command(0xC0);
				LCD_String("NOT WORKING  ");
				lamp1 = 0;
				lamp2 = 0;
				lamp3 = 1;
				delay(500);
			}
			if(sensor4 == 0){
			lamp3 = 0;}
			if(sensor3 == 0){
			lamp2 = 0;}
			if(sensor2 == 0){
			lamp1 = 0;}
			if(sensor1 == 1 && sensor2 == 0 && sensor3 == 0 && sensor4==0){
				LCD_Command(0x01);
				LCD_String("NO VEHICLE");  
				LCD_Command(0xC0);
				LCD_String("ALL LIGHTS OFF   ");
				delay(500);
				lamp1 = lamp2 = lamp3 = 0;
}
		
}
	}

