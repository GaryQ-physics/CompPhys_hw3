import numpy as np
import matplotlib.pyplot as plt

TMAX = 100

def hist(name):
    arr = np.fromfile(f'data/{name}.data', dtype=np.float64)

    fig, axs = plt.subplots(figsize=(8,4), nrows=1, ncols=1)
    axs.hist(arr, bins=100, histtype='step')
    fig.savefig(f'data/{name}.png')

hist('gaussian')
hist('semicirc')

def walk():
    Pi=np.fromfile('data/walker_Pi.data', dtype=np.float64).reshape((2*TMAX+1,TMAX+1))

    fig, axs = plt.subplots(figsize=(8,4), nrows=1, ncols=1)
    x_vals = np.arange(2*TMAX+1) - TMAX
    #axs.plot(x_vals, Pi[:,20], '.')
    axs.plot(Pi[:,10], '.')
    axs.plot(Pi[:,20], '.')
    axs.plot(Pi[:,30], '.')
    axs.plot(Pi[:,40], '.')
    axs.plot(Pi[:,50], '.')
    axs.plot(Pi[:,60], '.')
    axs.plot(Pi[:,70], '.')
    axs.plot(Pi[:,80], '.')
    axs.plot(Pi[:,90], '.')
    fig.savefig(f'data/walker_Pi.png')

def walk2():
    Pi=np.fromfile('data/walker_Pi.data', dtype=np.float64).reshape((2*TMAX+1,TMAX+1))

    fig, axs = plt.subplots(figsize=(8,4), nrows=1, ncols=1)
    x_vals = np.arange(2*TMAX+1) - TMAX
    #axs.plot(x_vals, Pi[:,20], '.')
    axs.hist(Pi[:,10], bins=100, histtype='step')
    axs.hist(Pi[:,20], bins=100, histtype='step')
    axs.hist(Pi[:,30], bins=100, histtype='step')
    axs.hist(Pi[:,40], bins=100, histtype='step')
    axs.hist(Pi[:,50], bins=100, histtype='step')
    axs.hist(Pi[:,60], bins=100, histtype='step')
    axs.hist(Pi[:,70], bins=100, histtype='step')
    axs.hist(Pi[:,80], bins=100, histtype='step')
    axs.hist(Pi[:,90], bins=100, histtype='step')
    fig.savefig(f'data/walker_Pi2.png')

walk()
walk2()
