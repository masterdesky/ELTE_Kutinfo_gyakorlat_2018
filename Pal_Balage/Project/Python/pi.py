import sys
import math


def Calculate(number):

    result = 4/3
    for actualnmb in range(2,number):
        result *= ((actualnmb*2)**2 /
                  ((actualnmb*2)**2 - 1))
    return(result)

# main
number = int(sys.argv[1])
result = Calculate(number)
pi = result*2
print("Result is: ", result)
print("Pi is equals to: ", pi)
print("difference from actual: ", math.pi - pi)