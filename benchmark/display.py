#!/usr/bin/env python3

import json
import argparse
from matplotlib import pyplot as pp
from termcolor import colored

TEST_NAMES = [
    "MAP INSERT SMALL",
    "MAP INSERT MEDIUM",
    "MAP INSERT LARGE",
    "MAP ITERATE",
    "UNORDERED MAP INSERT SMALL",
    "UNORDERED MAP INSERT MEDIUM",
    "UNORDERED MAP INSERT LARGE",
    "UNORDERED MAP ITERATE",
    "VECTOR ITERATE",
    "DEQUE INSERT SMALL",
    "DEQUE INSERT LARGE",
    "DEQUE ITERATE",
    "UNORDERED MAP OF VECTORS",
    "PRIORITY QUEUE PUSH POP SMALL",
    "PRIORITY QUEUE PUSH POP LARGE",
]
TEST_NUM = len(TEST_NAMES)


def load_data(file: str) -> tuple:
    sgc_data = [0.0] * TEST_NUM
    std_data = [0.0] * TEST_NUM
    with open(file) as fp:
        fp_json = json.load(fp)
        for i in fp_json["results"]:
            idx = int(i["parameters"]["test_num"])
            val = 1000 * float(i["mean"])
            if i["parameters"]["exe"] == "sgc":
                sgc_data[idx] = val
            else:
                std_data[idx] = val

        return (sgc_data, std_data)


def plot(sgc, std):
    width = 0.4
    hwidth = width / 2
    pp.bar([x - hwidth for x in range(len(sgc))], sgc, width = width)
    pp.bar([x + hwidth for x in range(len(std))], std, width = width)
    pp.legend(["c sgc", "c++ std"])
    pp.grid()
    pp.xticks(labels=TEST_NAMES, ticks=range(0, TEST_NUM), rotation=45, ha="right")
    pp.ylabel(ylabel='time [ms]', rotation='horizontal', loc='top')
    pp.subplots_adjust(bottom=0.30)
    pp.show()


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


def pprint(sgc, std):
    for i in range(len(sgc)):
        print(colored(TEST_NAMES[i], 'magenta'))
        sgc_colored, stl_colored = color_values(round(sgc[i], 2), round(std[i], 2))
        print('c sgc:', sgc_colored, '-- c++ stl:', stl_colored)
        print()


def main():
    sgc, std = load_data("out.json")

    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-t', '--text', action=argparse.BooleanOptionalAction)

    args = parser.parse_args()
    if(args.text):
        pprint(sgc, std)
    else:
        plot(sgc, std)


if __name__ == "__main__":
    main()
