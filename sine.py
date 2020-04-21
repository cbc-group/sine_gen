import numpy as np

n_samples = 2048
resolution = 12
filename = 'sine.h'

# sine wave in [-1, 1]
t = np.linspace(0, np.pi*2, n_samples, endpoint=False, dtype=np.float32)
signal = np.sin(t)

# shift to [0, 1]
signal = (signal+1)/2

# discretize
amplitude = 2**resolution-1
signal *= amplitude
signal = np.round(signal)

# generate header file
with open(filename, 'w') as fd:
    fd.write('#ifndef __WAVEFORM_H__\n')
    fd.write('#define __WAVEFORM_H__\n')

    fd.write('\n')

    fd.write('#include <cstdint>\n')

    fd.write('\n')

    fd.write(f'#define RESOLUTION {resolution}\n')
    fd.write(f'#define N_SAMPLES {n_samples}\n')
    fd.write('const uint16_t WAVEFORM[] = {\n')
    for i, value in enumerate(signal):
        if i % 10 == 0:
            fd.write('\t')
        fd.write(f'{int(value)}')
        if i < len(signal)-1:
            fd.write(',\t')
        else:
            fd.write('\n')
        if (i+1) % 10 == 0:
            fd.write('\n')
    fd.write('};\n')

    fd.write('\n')

    fd.write('#endif\n')
