import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

versions = [
    ('automata-simd', 'blue'), 
    ('automata-naive', 'red'),
]

plt.xlabel('Generations')
plt.ylabel('CPU time (seconds)')
legends = []
for ver, color in versions:
    with open('times-{}.txt'.format(ver), 'r') as f:
        ns, ts = [[float(x) for x in l.replace(',','').split()] for l in list(f)[:2]]
    plt.plot(ns, ts, color=color, marker='o')
    legends.append(mpatches.Patch(color=color, label=ver))

plt.legend(handles=legends, loc='upper left')
plt.show()
