#!/bin/python3
import sys
from termcolor import colored

def color_values(v1, v2):
    v1_colored = None
    v2_colored = None
    if v1 > v2:
        v2_colored = colored(str(v2) + ' [ms]', 'green')
        if v1 > 1.3 * v2:
            v1_colored = colored(str(v1) + ' [ms]', 'red')
        elif v1 > 1.05 * v2:
            v1_colored = colored(str(v1) + ' [ms]', 'yellow')
        else:
            v1_colored = colored(str(v1) + ' [ms]', 'green')
    else:
        v2_colored, v1_colored = color_values(v2, v1)
    return v1_colored, v2_colored


reading_sgc = False
sgc_value = None
stl_value = None
for line in sys.stdin:
    if line.startswith('##'):
        print(colored(line.strip('\n').strip('## '), 'magenta'))

    if 'c sgc' in line:
        reading_sgc = True

    if 'c++ stl' in line:
        reading_sgc = False

    if 'Time' in line:
        if reading_sgc:
            sgc_value = float(line.split('ms')[0].split(':')[1])
        else:
            stl_value = float(line.split('ms')[0].split(':')[1])
            if sgc_value is None:
                raise Exception("Invalid input")

            sgc_colored, stl_colored = color_values(sgc_value, stl_value)

            print('c sgc:', sgc_colored, '-- c++ stl:', stl_colored)
            print()
