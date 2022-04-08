#%%
from matplotlib import markers
import matplotlib.pyplot as plt
import numpy as np


times = {
    "aho": [],
    "brut": [],
    "kmp": [],
    #"ukk": [],
    #"wumanber": [],
    #"agrep":[],
    "grep": []  
}

x = [i for i in np.arange(1,101)]
plt.title("English\n")
plt.xlabel("Pattern Size")
plt.ylabel("Time in seconds")
for alg in times.keys():
    f = open(f'./data/english/{alg}', 'r')
    content = f.readlines()

    if alg == "aho":
        label = "Aho-Corasick"
    elif alg == "brut":
        label = "Brute Force"
    elif alg == "kmp":
        label= "KMP"
    elif alg == "ukk":
        label = "Ukkonen"
    elif alg == "wumanber":
        label = "Wu-Manber"
    else:
        label=alg

    for line in content:
        if line[:4] == "real":
            time = line[4:].strip()[:-1].split("m")
            time = int(time[0])*60 + float(time[1])
            times[alg].append(time)
    plt.plot(x,times[alg],label=label)

plt.legend(bbox_to_anchor=(1.04,0), loc="lower left", borderaxespad=0)


# %%
