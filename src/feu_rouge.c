/* fichier pour commander l'envoi des trames */
#include <wiringPiSPI.h>
#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define CLOCK_FREQ 	1000000

#define CHANNEL 	0
#define MAX_INTENSITY 20


void set_color(char*, char*, char*, char*, int);
void chenillar(int, char*, int);



void set_color(char* r, char* g, char* b, char* intensity, int n){
/*
r, g, b : arrays which describes the color of each LED
intensity : array of intensity (0 <= intensity[i] < 2**5)
n : number of LED, ie length(r)
*/

    char * data = malloc(sizeof(char) * (n * 4 + 8)); //see datasheet
    int i, j;

    //start frame
    for (i = 0; i < 4; i++) data[i] = 0;

    for(i = 0; i < n; i++){
        j = 4 + 4 * i;
        data[j] = ((0b111) << 5);
        data[j] |= intensity[i];

        data[j + 1] = b[i];
        data[j + 2] = g[i];
        data[j + 3] = r[i];
    }

    //end frame
    for (j = 4 * n + 4; j < 4 * n + 8; j++){
        data[j] = 0xff;
    }

	wiringPiSPIDataRW(CHANNEL, data, 13);

	free(data);



}



void chenillar(int i, char* intensity, int N){
/*
i = iteration number
array  which will be modified by the function
N : length(intensity)
*/
    int j;

    for (j = 0; j < N; j++){

        int delta = abs(j - i);
        if (delta >= N / 2) delta = N - delta; //modulo ad hoc

        intensity[j] = (char) (pow(2.71, delta));

    }

}


int main(void)
{
	//le channel n' aucune importance car les LED n'ont pas de chip_enable
	//ie prendront toujours le SPI !
	wiringPiSPISetup(CHANNEL, CLOCK_FREQ);

    int N = 3; //number of LED
    int i;

    char* r = malloc(sizeof(char) * N);
    char* g = malloc(sizeof(char) * N);
    char* b = malloc(sizeof(char) * N);
    char* intensity = malloc(sizeof(char) * N);

    //define color
    r[0] = 255;
    g[0] = 0;
    b[0] = 0;
    intensity[0] = 0;

    r[1] = 255;
    g[1] = 50;
    b[1] = 50;
    intensity[1] = 0;

    r[2] = 0;
    g[2] = 255;
    b[2] = 0;

    intensity[2] = 0;

    i = 0;
    //main loop
    while (1){
        
	intensity[i]= 0;
    	i = (i + 1) % 3;
	intensity[i] = 25;
	set_color(r, g, b, intensity, N);

       delay(1000);
	printf("%d %d %d %d\n", i, intensity[0], intensity[1], intensity[2]);
    }







    free(r);
    free(g);
    free(b);
    free(intensity);


	//il ne faut pas quitter tout de suite, car des fois ca fout la m*
	delay(1000);

	return 0;

    }
