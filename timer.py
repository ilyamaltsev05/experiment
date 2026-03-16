import subprocess, math, time, sys

COMMAND = sys.argv[1:]
N = 5
times = []

for i in range(N):
    start = time.perf_counter()
    subprocess.run(COMMAND, check=True, stdout=subprocess.DEVNULL)
    elapsed = time.perf_counter() - start
    times.append(elapsed)
    print(f"Run {i+1}: {elapsed:.3f}s")

mean = sum(times) / N
std = math.sqrt(sum((x - mean)**2 for x in times) / N)
print(f"\nMean: {mean:.3f}s")
print(f"Stddev: {std:.3f}s")
