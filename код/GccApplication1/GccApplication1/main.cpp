//подключенеи к порту D0 D1 D2 D3 D4 D5 D6 D7
//                    RS RW E     D4 D5 D6 D7

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DDR DDRA
#define PORT PORTA


void strob()                                               //строб
{
	PORT |= (1<<2);
	_delay_us(2);
	PORT &= ~(1<<2);
}
void writecomande(uint8_t cod,int fun)                     //отправка команды
{
	DDR=0xFF;
	PORT=0x00;
	uint8_t A=cod & 240;
	uint8_t B=(cod & 15)<<4;
	if (fun==0)
	{
		PORT=A|0x00;
		strob();
		_delay_us(40);
		PORT=B|0x00;
		strob();
		_delay_us(40);
	}
	else if (fun==1)
	{
		PORT=A|0x01;
		strob();
		_delay_us(40);
		PORT=B|0x01;
		strob();
		_delay_us(40);
	}
}
void initc ()                                              //инициализация дисплея
{
	_delay_ms(50);
	DDR=0xFF;
	PORT=0x00;
	PORT=0x20;
	strob();
	_delay_us(100);
	writecomande(0x2C,0);
	_delay_us(50);
	writecomande(0x0F,0);
	_delay_us(50);
	writecomande(0x01,0);
	_delay_us(50);
	writecomande(0x06,0);
	_delay_us(50);
}
void clearLCD()                                            //отчищаем дисплей
{
	writecomande(0x01,0);
}
void one_sdvig_option(int sc,int rl)                       //sc=1 сдвигаем экран иначе курсор rl=1сдвиг вправо иначе влево
{
	if (sc==1)
	{
		if (rl==1){writecomande(0x1C,0);}
		else{writecomande(0x18,0);}
	}
	else
	{
		if (rl==1){writecomande(0x14,0);}
		else{writecomande(0x10,0);}
	}
}
void setcusrsor(int x,int y)                               //установка курсора на позицию x y из 16*2
{
	switch (x)
	{
		case 1:
		{
			if (y==1) writecomande(0x80,0);
			else writecomande(0xC0,0);
			break;
		}
		case 2:
		{
			if (y==1) writecomande(0x81,0);
			else writecomande(0xC1,0);
			break;
		}
		case 3:
		{
			if (y==1) writecomande(0x82,0);
			else writecomande(0xC2,0);
			break;
		}
		case 4:
		{
			if (y==1) writecomande(0x83,0);
			else writecomande(0xC3,0);
			break;
		}
		case 5:
		{
			if (y==1) writecomande(0x84,0);
			else writecomande(0xC4,0);
			break;
		}
		case 6:
		{
			if (y==1) writecomande(0x85,0);
			else writecomande(0xC5,0);
			break;
		}
		case 7:
		{
			if (y==1) writecomande(0x86,0);
			else writecomande(0xC6,0);
			break;
		}
		case 8:
		{
			if (y==1) writecomande(0x87,0);
			else writecomande(0xC7,0);
			break;
		}
		case 9:
		{
			if (y==1) writecomande(0x88,0);
			else writecomande(0xC8,0);
			break;
		}
		case 10:
		{
			if (y==1) writecomande(0x89,0);
			else writecomande(0xC9,0);
			break;
		}
		case 11:
		{
			if (y==1) writecomande(0x8A,0);
			else writecomande(0xCA,0);
			break;
		}
		case 12:
		{
			if (y==1) writecomande(0x8B,0);
			else writecomande(0xCB,0);
			break;
		}
		case 13:
		{
			if (y==1) writecomande(0x8C,0);
			else writecomande(0xCC,0);
			break;
		}
		case 14:
		{
			if (y==1) writecomande(0x8D,0);
			else writecomande(0xCD,0);
			break;
		}
		case 15:
		{
			if (y==1) writecomande(0x8E,0);
			else writecomande(0xCE,0);
			break;
		}
		case 16:
		{
			if (y==1) writecomande(0x8F,0);
			else writecomande(0xCF,0);
			break;
		}
	}
	
}
void displaysettings(int D,int C,int B)                    //параметры экрана D=1 дисплей включен C=1 курсор виден в виде_ B=1 курсор мигает
{
	if (D==1)
	{
		if (C==1)
		{
			if (B==1)
			{writecomande(0x0F,0);}
			else
			{writecomande(0x0E,0);}
		}
		else
		{
			if (B==1)
			{writecomande(0x0D,0);}
			else
			{writecomande(0x0C,0);}
		}
	}
	else
	{
		if (C==1)
		{
			if (B==1)
			{writecomande(0x0B,0);}
			else
			{writecomande(0x0A,0);}
		}
		else
		{
			if (B==1)
			{writecomande(0x09,0);}
			else
			{writecomande(0x08,0);}
		}
	}
	
	_delay_us(50);
	
}
void letterssettings(int DL,int N,int F)                   //параметры символов и битности DL=1 8 разрядна линия иначе 4 разрядная N=1 используем 2 строки иначе 1 F=1 шрифт 5*7 иначе 5*10
{
	
	
	if (DL==1)
	{
		if (N==1)
		{
			if (F==1){writecomande(0x3C,0);}
			else{writecomande(0x38,0);}
		}
		else
		{
			if (F==1){writecomande(0x32,0);}
			else{writecomande(0x30,0);}
		}
	}
	else
	{
		if (N==1)
		{
			if (F==1){writecomande(0x2C,0);}
			else{writecomande(0x28,0);}
		}
			else
			{
				if (F==1){writecomande(0x22,0);}
				else{writecomande(0x20,0);}
			}
		}
		_delay_us(50);
	}
void cursorsettings(int ID,int S)                          //параметры курсора ID=1 сдвиг по умолчаню вправо иначе влево S=1 сдвиг экрана разрешен иначе запрещен
	{
		
		if (ID==1)
		{
			if (S==1)
			{writecomande(0x07,0);}
			else
			{writecomande(0x06,0);}
		}
		else
		{
			if (S==1)
			{writecomande(0x05,0);}
			else
			{writecomande(0x04,0);}
		}
		_delay_us(50);
		


	}
void writeletter(char simv)                                //отправка char
	{
		switch (simv)
		{
			case 'A':{writecomande(0x41,1);break;}
			case 'B':{writecomande(0x42,1);break;}
			case 'C':{writecomande(0x43,1);break;}
			case 'D':{writecomande(0x44,1);break;}
			case 'E':{writecomande(0x45,1);break;}
			case 'F':{writecomande(0x46,1);break;}
			case 'G':{writecomande(0x47,1);break;}
			case 'H':{writecomande(0x48,1);break;}
			case 'I':{writecomande(0x49,1);break;}
			case 'J':{writecomande(0x4A,1);break;}
			case 'K':{writecomande(0x4B,1);break;}
			case 'L':{writecomande(0x4C,1);break;}
			case 'M':{writecomande(0x4D,1);break;}
			case 'N':{writecomande(0x4E,1);break;}
			case 'O':{writecomande(0x4F,1);break;}
			case 'P':{writecomande(0x50,1);break;}
			case 'Q':{writecomande(0x51,1);break;}
			case 'R':{writecomande(0x52,1);break;}
			case 'S':{writecomande(0x53,1);break;}
			case 'T':{writecomande(0x54,1);break;}
			case 'U':{writecomande(0x55,1);break;}
			case 'V':{writecomande(0x56,1);break;}
			case 'W':{writecomande(0x57,1);break;}
			case 'X':{writecomande(0x58,1);break;}
			case 'Y':{writecomande(0x59,1);break;}
			case 'Z':{writecomande(0x5A,1);break;}
			case '0':{writecomande(0x30,1);break;}
			case '1':{writecomande(0x31,1);break;}
			case '2':{writecomande(0x32,1);break;}
			case '3':{writecomande(0x33,1);break;}
			case '4':{writecomande(0x34,1);break;}
			case '5':{writecomande(0x35,1);break;}
			case '6':{writecomande(0x36,1);break;}
			case '7':{writecomande(0x37,1);break;}
			case '8':{writecomande(0x38,1);break;}
			case '9':{writecomande(0x39,1);break;}
			case 'a':{writecomande(0x61,1);break;}
			case 'b':{writecomande(0x62,1);break;}
			case 'c':{writecomande(0x63,1);break;}
			case 'd':{writecomande(0x64,1);break;}
			case 'e':{writecomande(0x65,1);break;}
			case 'f':{writecomande(0x66,1);break;}
			case 'g':{writecomande(0x67,1);break;}
			case 'h':{writecomande(0x68,1);break;}
			case 'i':{writecomande(0x69,1);break;}
			case 'j':{writecomande(0x6A,1);break;}
			case 'k':{writecomande(0x6B,1);break;}
			case 'l':{writecomande(0x6C,1);break;}
			case 'm':{writecomande(0x6D,1);break;}
			case 'n':{writecomande(0x6E,1);break;}
			case 'o':{writecomande(0x6F,1);break;}
			case 'p':{writecomande(0x70,1);break;}
			case 'q':{writecomande(0x71,1);break;}
			case 'r':{writecomande(0x72,1);break;}
			case 's':{writecomande(0x73,1);break;}
			case 't':{writecomande(0x74,1);break;}
			case 'u':{writecomande(0x75,1);break;}
			case 'v':{writecomande(0x76,1);break;}
			case 'w':{writecomande(0x77,1);break;}
			case 'x':{writecomande(0x78,1);break;}
			case 'y':{writecomande(0x79,1);break;}
			case 'z':{writecomande(0x7A,1);break;}
			case ':':{writecomande(0x3A,1);break;}
			case '=':{writecomande(0x3D,1);break;}
			case '%':{writecomande(0x25,1);break;}
			case '$':{writecomande(0x24,1);break;}
			//ne vse simvoli
		}
	}
void cifralcd(int cifr)                                    //отправка двузначного числа
	{
		int a=cifr%10;
		int b= (cifr-cifr%10)/10;
		setcusrsor(1,1);
		if (b==1)  writeletter('1');
		if (b==2)  writeletter('2');
		if (b==3)  writeletter('3');
		if (b==4)  writeletter('4');
		if (b==5)  writeletter('5');
		if (b==6)  writeletter('6');
		if (b==7)  writeletter('7');
		if (b==8)  writeletter('8');
		if (b==9)  writeletter('9');
		if (b==0)  writeletter('0');
		setcusrsor(2,1);
		if (a==1)  writeletter('1');
		if (a==2)  writeletter('2');
		if (a==3)  writeletter('3');
		if (a==4)  writeletter('4');
		if (a==5)  writeletter('5');
		if (a==6)  writeletter('6');
		if (a==7)  writeletter('7');
		if (a==8)  writeletter('8');
		if (a==9)  writeletter('9');
		if (a==0)  writeletter('0');
		_delay_ms(20);
		
	}
int main(void)
{
	_delay_ms(1000);
	DDRB=0x00;
	DDRA = 0XFF;
	uint8_t last=PINB;
    initc();
	displaysettings(1,0,0);
    clearLCD();

		
    int count=50;
    while (1)
	{	
		
		
			if (PINB==0x00)
			{
				
				cifralcd(1);
				
			}
			else if (PINB==0x01)
			{
				
				cifralcd(2);
				
			}
			else if (PINB==0x05)
			{
				
				cifralcd(3);
				
			}
			else if (PINB==0x04)
			{
				
				cifralcd(4);
				
			}

		
			if (last==0x00)
			{
				if (PINB==0x01)
				{
					clearLCD();
					count++;
			
					last=0x01;
				}
				if (PINB==0x04)
				{
					clearLCD();
					count--;
			
					last=0x04;
				}
				
			}
			if (last==0x01)
			{
				if (PINB==0x05)
				{
					clearLCD();
					count++;
		
					last=0x01;
				}
				if (PINB==0x00)
				{
					clearLCD();
					count--;
				
					last=0x00;
				}
				
			}
			if (last==0x05)
			{
				if (PINB==0x04)
				{
					clearLCD();
					count++;
				
					last=0x04;
				}
				if (PINB==0x01)
				{
					clearLCD();
					count--;
				
					last=0x01;
				}
				
			}
			if (last==0x04)
			{
				if (PINB==0x00)
				{
					clearLCD();
					count++;
				
					last=0x00;
				}
				if (PINB==0x05)
				{
					clearLCD();
					count--;
			
					last=0x01;
				}
				
			}
			if((PINB==0x08)||(PINB==0x09)||(PINB==0x0D)||(PINB==0x0C))
			{
				setcusrsor(2,2);
				writeletter('@');
				_delay_ms(20);
		}
		last=PINB;
		cifralcd(count);
		
		if (count<100)
		{
			cifralcd(count);
			count++;
		}
		else
		{
			count=0;
			cifralcd(count);		
		}
	}
}

