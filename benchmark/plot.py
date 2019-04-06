#!/usr/bin/python3
import re
import matplotlib.pyplot as pyplot

file_name = 'output.txt'

data = None
with open(file_name) as file:
    data = file.read()
data = data.split('\n')
n_el = [float(el.split()[4]) for el in data if 'num of elements =' in el]
run_time = [float(el.split()[4]) for el in data if 'Time' in el]

n_el_c = n_el[:len(n_el)//2]
n_el_cpp = n_el[len(n_el)//2:]

run_time_c = run_time[:len(run_time)//2]
run_time_cpp = run_time[len(run_time)//2:]

pyplot.plot(n_el_c, run_time_c, 'r', label = 'c sgc')
pyplot.plot(n_el_cpp, run_time_cpp, 'b', label = 'cpp stl')

pyplot.xlabel('number of elements')
pyplot.ylabel('time [ms]')
pyplot.legend()
pyplot.grid()
pyplot.show()
