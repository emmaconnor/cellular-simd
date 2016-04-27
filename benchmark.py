import subprocess

versions = ['automata-naive', 'automata-simd']

def get_times(ngens, avg_of=5):
    width = 192

    times = {}

    for ver in versions:
        args = ['./'+ver, str(width), str(ngens), 'n']
        print(' '.join(args))
        total_t = 0
        for _ in range(avg_of):
            op = subprocess.check_output(args, universal_newlines=True)
            t = float(op.strip())
            total_t += t
        times[ver] = total_t / avg_of

    return times

ns = []
times = {ver:[] for ver in versions}

max_n = 20000
for n in range(1000, max_n, 1000):
    ns.append(n)
    for ver, t in get_times(n, avg_of=1000).items():
        times[ver].append(t)

for ver, ts in times.items():
    with open('times-{}.txt'.format(ver), 'w') as f:
        f.write(', '.join(str(x) for x in ns) + '\n')
        f.write(', '.join(str(x) for x in ts) + '\n')



