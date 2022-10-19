import numpy as np
import matplotlib.pyplot as plt

rng = np.random.default_rng()
rand1 = rng.random

NWALKERS=1000000
TMAX=100
def foo():
    Xlist = []
    PIlist = []

    Xslice = np.zeros(NWALKERS, dtype=int)
    PIslice = np.empty(2*TMAX+1, dtype=float)
    for xx in range(2*TMAX+1):
        xphys = xx - TMAX
        PIslice[xx] = np.count_nonzero(Xslice==xphys)/NWALKERS

    Xlist.append(Xslice.copy())
    PIlist.append(PIslice.copy())
    for _ in range(TMAX):
        choose = rand1(NWALKERS)
        step = 2*np.array(choose<0.5,dtype=int) - 1
        Xslice = Xslice + step

        for xx in range(2*TMAX+1):
            xphys = xx - TMAX
            PIslice[xx] = np.count_nonzero(Xslice==xphys)/NWALKERS

        Xlist.append(Xslice.copy())
        PIlist.append(PIslice.copy())

    x_vals = np.arange(2*TMAX+1) - TMAX

    fig, axs = plt.subplots(figsize=(8,4), nrows=1, ncols=1)
    #axs.plot(x_vals, PIlist[90], '.')
    #axs.hist(PIlist[90], bins=100, histtype='step')
    axs.hist(Xlist[90], bins=100, range=(-100,100), histtype='step')

    #axs.plot(PIlist[10], '.')
    #axs.plot(PIlist[20], '.')
    #axs.plot(PIlist[30], '.')
    #axs.plot(PIlist[40], '.')
    #axs.plot(PIlist[50], '.')
    #axs.plot(PIlist[60], '.')
    #axs.plot(PIlist[70], '.')
    #axs.plot(PIlist[80], '.')
    #axs.plot(PIlist[90], '.')
    #fig.savefig(f'data/walker_Pi-recreated.png')
    plt.show()

foo()
