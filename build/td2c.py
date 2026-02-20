import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results.csv")
print(data)
plt.plot(data["nLoops"], data["time_seconds"], marker='o')
plt.xlabel("nLoops")
plt.ylabel("Time (seconds)")
# plt.xscale("log")
plt.title("Execution Time vs nLoops")
plt.grid(True)
plt.savefig("td2c.png")
