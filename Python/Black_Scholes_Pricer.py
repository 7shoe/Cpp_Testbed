import numpy as np 
from math import *
import time

def N_CDF(x):
    'Cumulative distribution function for the standard normal distribution'
    return (1.0 + erf(x / sqrt(2.0))) / 2.0

def BS_Call(S, K, r, t, sigma):
    'Black Scholes Pricing function'
    assert S >0 and K>0 and sigma > 0, "Inputs \'S\', \'K\', and \'sigma\' must be positive."
    assert t >= 0 and K>0, "Inputs \'t\' must be non-negative."

    d_1 = (np.log(S/K) + 0.5*(r + sigma**2)*t) / (np.sqrt(t) * sigma)
    d_2 = d_1 - (np.sqrt(t) * sigma)
    
    return N_CDF(d_1)*S - N_CDF(d_2)*K*np.exp(-r*t)

def BS_Put(S, K, r, t, sigma):
    'Black Scholes Pricing function'
    assert S >0 and K>0 and sigma > 0, "Inputs \'S\', \'K\', and \'sigma\' must be positive."
    assert t >= 0 and K>0, "Inputs \'t\' must be non-negative."

    d_1 = (np.log(S/K) + 0.5*(r + sigma**2)*t) / (np.sqrt(t) * sigma)
    d_2 = d_1 - (np.sqrt(t) * sigma)
    
    return K * np.exp(-r*t) * N_CDF(-d_2) - S * N_CDF(-d_1)

if __name__ == "__main__":

    # start time 
    t0 = time.time()
    # N = int(10E6)
    N = int(10E4)

    # do work
    for i in range(N):
        # one 
        S = np.random.uniform(0.01, 1000.0)
        K = np.random.uniform(1, 500)
        r = np.random.uniform(0.00, 0.2)
        t = np.random.uniform(0.5, 10.0)
        sigma = np.random.uniform(0.05, 1.0)


        C = BS_Call(S, K, r, t, sigma)
        P = BS_Put(S, K, r, t, sigma)
    
    # stop time 
    t1 = time.time()
    print("Runtime: ", round(1000*(t1-t0),3), "ms")