import sys

path = "../../WFLOP instances/site/"
instances = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J"]

def average(values: list[float]) -> float:
    acc = 0
    
    for i in range(len(values)):
        acc += values[i]
    
    return acc / len(values)

if len(sys.argv) == 2:
    instance = sys.argv[1]
    
def cost(depth: float) -> float:
    return 659933.9999999129 + depth * -72606.60000000268
    
allD = []
allC = []

for i in range(len(instances)):
    f = open(path + instances[i] + "/availablePositions.txt", "r")


    for line in f.readlines():
        _x, _y, d, c, _z = line.split()
        
        allD.append(float(d))
        allC.append(float(c))

    f.close()

averageD = average(allD)
averageC = average(allC)

sumTop = 0.0
sumBottom = 0.0

for i in range(len(allD)):
    sumTop += (allD[i] - averageD) * (allC[i] - averageC)
    sumBottom += (allD[i] - averageD) ** 2

beta = sumTop / sumBottom

alfa = averageC - beta * averageD

print(f"Beta: {beta} , alfa: {alfa}")

