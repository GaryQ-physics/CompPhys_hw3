#include "helpfuncs.c"

double Pi_semicirc_UN(double x, double a){
    if(fabs(x) < a){
        return sqrt(a*a - x*x);
    }else{
        return 0.;
    }
}
double Pi_semicirc(double x, double a){
    return ( 2./(PI*a*a) )*Pi_semicirc_UN(x,a);
}

double Pi_gaussian_UN(double x, double sig){
    return exp(-x*x/(2*sig*sig));
}
double Pi_gaussian(double x, double sig){
    return ( 1./sqrt(2*PI*sig*sig) )*Pi_gaussian_UN(x, sig);
}
/////////////////////////////////////////////////////

double sample_semicirc(double a){
    // rejection method
    double maxpi = 2./(PI*a);
    double x0,y0;

    while(1){
        x0 = MYrand(-a,a);
        y0 = MYrand(0.,maxpi);
        if(Pi_semicirc(x0,a)>y0) return x0;
    }
}

double sample_gaussian(double sigma){
    // box muller method
    double x,y,sign,R2;
    while(1){
        x = MYrand1();
        y = MYrand1();
        sign = MYrand1();
        R2 = x*x + y*y;
        if(R2<=1.){
            if(sign>0.5){
                return sqrt(-2.*log(R2)/R2)*x;
            }else{
                return -sqrt(-2.*log(R2)/R2)*x;
            }
        }
    }
}

# define NHIST 1000000
void forhistograms(){
    double arr[NHIST];

    for(long i=0; i<NHIST; i++){
        arr[i] = sample_semicirc(1.);
    }
    doubleArrToFile(arr, NHIST, "data/semicirc.data");

    for(long i=0; i<NHIST; i++){
        arr[i] = sample_gaussian(1.);
    }
    doubleArrToFile(arr, NHIST, "data/gaussian.data");
}

#define NWALKERS 1000000
#define TMAX 100
#define IDX(r,c) r*(TMAX+1)+c
// IDX macro allows us to mimik X[nrows, TMAX+1] multidim array allocation (only for ncols=TMAX+1)
void random_walkers(){
    double choose;
    long dummy;

    // long X[NWALKERS,TMAX+1]
    long * X = malloc(sizeof(long)*NWALKERS*(TMAX+1));

    for(long i=0; i<NWALKERS; i++){
        X[IDX(i,0)] = 0; // all walkers start at origin
        for(long t=1; t<TMAX+1; t++){
            choose=MYrand1();
            dummy = t-1;
            // printf("%f ; %ld ; %ld ; %ld\n", choose, i, t, dummy);
            if(choose < 0.5){
                X[IDX(i,t)] = X[IDX(i,dummy)]+1;
            }else
                X[IDX(i,t)] = X[IDX(i,dummy)]-1;
        }
    }

    // long Pi_UN[2*TMAX+1,TMAX+1]
    long * Pi_UN = malloc(sizeof(long)*(2*TMAX+1)*(TMAX+1));

    long xx;
    for(long t=0; t<TMAX+1; t++){
        for(long x=0; x<2*TMAX+1; x++){
            Pi_UN[IDX(x,t)]=0;
        }
        for(long i=0; i<NWALKERS; i++){
            //printf("t=%ld ; i=%ld ; [i,t]=%ld\n", t, i, IDX(i,t));
            //printf("t=%ld ; i=%ld ; [i,t]=%ld\n", t, i, IDX(i,t));
            xx = X[IDX(i,t)] + TMAX;
            Pi_UN[IDX(xx,t)]++;
        }
    }

    // double Pi[2*TMAX+1,TMAX+1]
    double * Pi  = malloc(sizeof(double)*(2*TMAX+1)*(TMAX+1));

    for(long t=0; t<TMAX+1; t++){
        for(long x=0; x<2*TMAX+1; x++){
            Pi[IDX(x,t)] = (double)Pi_UN[IDX(x,t)]/NWALKERS;
        }
    }
    doubleArrToFile(Pi, (2*TMAX+1)*(TMAX+1), "data/walker_Pi.data");
}


int main(){
    forhistograms();
    random_walkers();
    return 0;
}
