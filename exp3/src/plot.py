import os
import sys
from os.path import basename
from matplotlib.pylab import *
from matplotlib.pyplot import savefig


with open('../result/raw.txt') as f:
    raw_xs = f.readline().replace('\n', '').split(' ')
    raw_xs = np.asarray([float(x) for x in raw_xs if x])
    fs = f.readline().replace('\n', '').split(' ')

data_filename = sys.argv[1]
with open(data_filename) as f:
    xs = f.readline().replace('\n', '').split(' ')
    ys = f.readline().replace('\n', '').split(' ')
    xs = np.asarray([float(x) for x in xs if x])
    ys = np.asarray([float(y) for y in ys if y])
    fs = np.asarray([float(f) for f in fs if f])


figure(figsize=(5, 3), dpi=80)
plot(xs, ys, 'r', linewidth=1)
plot(raw_xs, fs, 'o')

img_dir = '../img/'
if not os.path.isdir(img_dir):
    os.mkdir(img_dir)

savefig(img_dir + basename(data_filename).replace('txt', 'jpg'))
