/* fichier pour commander l'envoi des trames */
#include <wiringPiSPI.h>
#include <wiringPi.h>


#define CLOCK_FREQ 	1000000

#define CHANNEL 	0


int main(void)
{
	//le channel n' aucune importance car les LED n'ont pas de chip_enable
	//ie prendront toujours le SPI !
	wiringPiSPISetup(CHANNEL, CLOCK_FREQ);


	char data[10];
	int T = 10;


	int i;
	for (i = 0; i < 4; i++) data[i] = 0;

    //LED1
    data[5] = 0xff; //on allume a fond, pas de pwm
    data[6] = 0xff;
    data[7] = 0;
    data[8] = 0;

    for (i = 9; i < 13; i++) data[i] = 0xff;



	wiringPiSPIDataRW(CHANNEL, data, 13);

	//il ne faut pas quitter tout de suite, car des fois ca fout la m*
	delay(1000);

	return 0;

