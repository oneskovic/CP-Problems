import numpy as np

file = open('inputs/6.txt','r')
data = file.readlines()[0].split(',')
timers = np.zeros(9, dtype=np.int64)
for i in range(len(data)):
    val = int(data[i])
    timers[val] += 1

for t in range(256):
    cnt_new = timers[0]
    timers = np.roll(timers, -1)
    timers[6] += cnt_new

print(timers.sum())