import math

FFT_SIZE = 64
cut =  int(FFT_SIZE/4) + 1

sin_table = []
cos_table = []
for i in range(cut):
    theta = 2 * math.pi * i / cut
    sin_table.append(str(math.sin(theta)))
    cos_table.append(str(math.cos(theta)))


with open("cos_qtable.txt", 'w') as f:
    f.write(','.join(cos_table))
with open("sin_qtable.txt", 'w') as f:
    f.write(','.join(sin_table))
