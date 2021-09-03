import matplotlib.pyplot as plt
import os, sys, time

supports = ['80', '80', '80', '80', '80']
AP = []
FP = []

for support in supports:
    t = time.time()
    os.system(f"./apriori {sys.argv[1]} {support} output")
    AP.append(time.time() - t)
    t = time.time()
    os.system(f"./fpgrowth/fpgrowth/src/fpgrowth -s{support} {sys.argv[1]} output")
    FP.append(time.time() - t)
os.remove('output')

barWidth = 0.34
fig = plt.subplots(figsize =(7, 7))

br1 = [1, 2, 3, 4, 5]
br2 = [x + barWidth for x in br1]

plt.bar(br1, AP, color ='y', width = barWidth, edgecolor ='grey', label ='Apriori')
plt.bar(br2, FP, color ='g', width = barWidth, edgecolor ='grey', label ='FP Tree') 
 
plt.title('Performance Graph')
plt.ylabel('Running Time', fontweight ='bold', fontsize = 15)
plt.xlabel('Support Threshold', fontweight ='bold', fontsize = 15)
plt.xticks([x + barWidth/2 for x in br1], ['5%', '10%', '25%', '50%', '90%'])

plt.legend()
plt.savefig("plot.png")
