#include <stdio.h>
// #include <stdlib.h>
#include <math.h>
#include <sys/random.h>


#define PI 3.14159265358979

double rand1(){
    int r;
    unsigned int max=4294967295;
    unsigned int tmp;
    r=getrandom(&tmp, sizeof(unsigned int), GRND_NONBLOCK);
    if(r!=4){
        printf("random returned something other than 4: %d\n",r);
    }
    return (double)tmp/max;
}

double rand(double a, double b){
    // b > a
    return (b-a)*rand1() + a;
}

void doubleArrToFile(double* arr, long arrlen, char* filename){
    FILE * fp=fopen(filename,"w");
    fwrite(arr, sizeof(double), arrlen, fp);
    fclose(fp);
}
