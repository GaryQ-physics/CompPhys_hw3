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

double sample_semicirc(double a){
    // rejection method
    double maxpi = 2./(PI*a);
    double x0,y0;

    while(1){
        x0 = rand(-a,a);
        y0 = rand(0.,maxpi);
        if(Pi_semicirc(x0)>y0) return x0;
    }
}

double sample_gaussian(double sigma){
    // box muller method
    return 0.;
}

random_walker(long start, long tmax){
    long X[tmax+1];
    double choose;

    X[0] = start;
    for(i=0, i<tmax, i++){
        choose=rand1();
        if(choose < 0.5){
            X[i+1] = x[i]+1
        }else
            X[i+1] = x[i]-1
        }
    }

}

#define NWALKERS
#define TMAX
multiple_random_walkers(){}
    long X[NWALKERS,TMAX+1];
    double choose;

    for(i=0; i<NWALKERS; i++){
        X[i,0] = start;
        for(t=1, t<tmax+1, i++){
            choose=rand1();
            if(choose < 0.5){
                X[i,t] = x[i,t-1]+1
            }else
                X[i,t] = x[i,t-1]-1
        }
    }

    long Pi_UN[TMAX,TMAX+1];

    // Order TMAX*TMAX*NWALKERS
//    for(x=0, x<TMAX, x++){
//    for(t=0, t<TMAX+1, t++){
//        Pi_UN[x,t]=0;
//        for(i=0; i<NWALKERS; i++){
//            if(X[i,t] == x) Pi_UN[x,t]++;
//        }
//    }
//    }

    // Order TMAX*NWALKERS + TMAX*TMAX
    for(t=0, t<TMAX+1, t++){
        for(x=0, x<TMAX, x++){
            Pi_UN[x,t]=0;
        }
        for(i=0; i<NWALKERS; i++){
            Pi_UN[X[i,t],t]++
        }
    }

    Pi = Pi_UN/NWALKERS
    doubleArrToFile(Pi "walker_Pi.data")

}

//////////////////////////

# define NHIST 1000
void forhistograms(){
    double arr[NHIST];

    for(long i=0; i<NHIST; i++){
        arr[i] = sample_semicirc(1.);
    }
    doubleArrToFile("semicirc.data");

    for(long i=0; i<NHIST; i++){
        arr[i] = sample_gaussian(1.);
    }
    doubleArrToFile("gaussian.data");
}

int main(){
    forhistograms();
    return 0;
}
