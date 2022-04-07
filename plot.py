#%%
import matplotlib.pyplot as plt
import numpy as np
import os

f = open('./data/test_results/pitches/brut', 'r')
content = f.readlines()

times = {
    "brut": []
}

alg = os.path.basename(f.name)

for line in content:
    if line[:4] == "real":
        time = line[4:].strip()[:-1].split("m")
        time = int(time[0])*60 + float(time[1])
        times[alg].append(time)
        
x = [i for i in np.arange(1,101)]

plt.plot(x,times[alg])
# %%
