import os
import sys
from matplotlib.pylab import *
from matplotlib.pyplot import savefig


with open('runge.txt') as f:
    f.readline()
    fs = f.readline().replace('\n', '').split(' ')

data_filename = sys.argv[1]
with open(data_filename) as f:
    xs = f.readline().replace('\n', '').split(' ')
    ys = f.readline().replace('\n', '').split(' ')
    xs = np.asarray([float(x) for x in xs if x])
    ys = np.asarray([float(y) for y in ys if y])
    fs = np.asarray([float(f) for f in fs if f])


f = figure(figsize=(5, 3), dpi=80)
p = plot(xs, ys, 'r', xs, fs, 'b', linewidth=1)

if not os.path.isdir('img'):
    os.mkdir('img')

savefig('img/' + data_filename.replace('txt', 'jpg'))
