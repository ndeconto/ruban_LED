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


	

	wiringPiSPIDataRW(CHANNEL, data, T);

	//il ne faut pas quitter tout de suite, car des fois ca fout la m*
	delay(1000);

	return 0;

