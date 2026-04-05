import subprocess
import re
import itertools
import pandas as pd
import matplotlib.pyplot as plt

# Parameters
nLoops_values = [1e3, 1e4, 1e5, 1e6, 1e7, 1e8]
nTasks_values = [1, 2, 3, 4, 5]
protect_values = [0, 1]
policies = ["SCHED_OTHER", "SCHED_RR"]

EXEC = "./td2e"

def run_case(nLoops, nTasks, protect, policy):
    cmd = []

    # SCHED_RR requires sudo
    if policy == "SCHED_RR":
        cmd.append("sudo")

    cmd += [EXEC, str(int(nLoops)), str(nTasks), str(protect), policy]

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=30)
        output = result.stdout

        expected = int(re.search(r"Expected:\s+(\d+)", output).group(1))
        got = int(re.search(r"Got:\s+(\d+)", output).group(1))
        time = float(re.search(r"Main execution time:\s+([0-9.]+)", output).group(1))

        return {
            "nLoops": nLoops,
            "nTasks": nTasks,
            "protect": protect,
            "policy": policy,
            "time_ms": time,
            "expected": expected,
            "got": got,
            "correct": expected == got
        }

    except Exception as e:
        print(f"Error with {nLoops}, {nTasks}, {protect}, {policy}: {e}")
        return None


# Run all experiments
results = []

for nLoops, nTasks, protect, policy in itertools.product(
    nLoops_values, nTasks_values, protect_values, policies
):
    print(f"Running: loops={nLoops}, tasks={nTasks}, protect={protect}, policy={policy}")
    res = run_case(nLoops, nTasks, protect, policy)
    if res:
        results.append(res)

# Save data
df = pd.DataFrame(results)
df.to_csv("results.csv", index=False)

# -----------------------------
# 📊 Visualization
# -----------------------------

def plot_case(df, protect, policy):
    subset = df[(df["protect"] == protect) & (df["policy"] == policy)]

    plt.figure()
    
    for nTasks in nTasks_values:
        data = subset[subset["nTasks"] == nTasks]
        plt.plot(data["nLoops"], data["time_ms"], marker='o', label=f"{nTasks} tasks")

    plt.xscale("log")
    plt.xlabel("nLoops (log scale)")
    plt.ylabel("Execution time (ms)")
    plt.title(f"Protect={protect}, Policy={policy}")
    plt.legend()
    plt.grid()

    filename = f"plot_protect{protect}_{policy}.png"
    plt.savefig(filename)
    print(f"Saved {filename}")


# Generate all plots
for protect in protect_values:
    for policy in policies:
        plot_case(df, protect, policy)

# -----------------------------
# 📊 Correctness visualization
# -----------------------------
plt.figure()

for protect in protect_values:
    subset = df[df["protect"] == protect]
    errors = subset.groupby("nTasks")["correct"].mean()
    plt.plot(errors.index, errors.values, marker='o', label=f"protect={protect}")

plt.xlabel("nTasks")
plt.ylabel("Correctness ratio")
plt.title("Correctness vs Tasks")
plt.legend()
plt.grid()
plt.savefig("correctness.png")
print("Saved correctness.png")
