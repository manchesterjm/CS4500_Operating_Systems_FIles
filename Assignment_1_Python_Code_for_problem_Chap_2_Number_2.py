import matplotlib.pyplot as plt

# Define colors for processes
colors = {
    'P1': 'blue',
    'P2': 'green',
    'P3': 'red',
    'P4': 'yellow'
}

# Create a figure with 5 subplots (one per scheduling policy)
fig, axs = plt.subplots(5, 1, figsize=(12, 10), constrained_layout=True)

# ---------------------------
# FCFS
# P1: 0-6, P2: 6-9, P3: 9-11, P4: 11-17
intervals_fcfs = [
    (0, 6, 'P1'),
    (6, 3, 'P2'),
    (9, 2, 'P3'),
    (11, 6, 'P4')
]
for start, duration, proc in intervals_fcfs:
    axs[0].broken_barh([(start, duration)], (10, 8), facecolors=colors[proc], edgecolor='black')
    axs[0].text(start + duration/2, 14, proc, ha='center', va='center', color='black', fontsize=10)
axs[0].set_xlim(0, 18)
axs[0].set_ylim(10, 18)
axs[0].set_title('FCFS')
axs[0].set_yticks([])
axs[0].set_xlabel('Time (ms)')

# ---------------------------
# Round Robin with quantum = 2
# Timeline based on assignment:
# P1: 0-2, P2: 2-4, P1: 4-6, P2: 6-7, P3: 7-9, P4: 9-11, P1: 11-13, P4: 13-15, P4: 15-17
intervals_rr2 = [
    (0, 2, 'P1'),
    (2, 2, 'P2'),
    (4, 2, 'P1'),
    (6, 1, 'P2'),
    (7, 2, 'P3'),
    (9, 2, 'P4'),
    (11, 2, 'P1'),
    (13, 2, 'P4'),
    (15, 2, 'P4')
]
for start, duration, proc in intervals_rr2:
    axs[1].broken_barh([(start, duration)], (10, 8), facecolors=colors[proc], edgecolor='black')
    axs[1].text(start + duration/2, 14, proc, ha='center', va='center', color='black', fontsize=10)
axs[1].set_xlim(0, 18)
axs[1].set_ylim(10, 18)
axs[1].set_title('Round Robin (Quantum = 2)')
axs[1].set_yticks([])
axs[1].set_xlabel('Time (ms)')

# ---------------------------
# Round Robin with quantum = 4
# Timeline:
# P1: 0-4, P2: 4-7, P3: 7-9, P4: 9-13, P1: 13-15, P4: 15-17
intervals_rr4 = [
    (0, 4, 'P1'),
    (4, 3, 'P2'),
    (7, 2, 'P3'),
    (9, 4, 'P4'),
    (13, 2, 'P1'),
    (15, 2, 'P4')
]
for start, duration, proc in intervals_rr4:
    axs[2].broken_barh([(start, duration)], (10, 8), facecolors=colors[proc], edgecolor='black')
    axs[2].text(start + duration/2, 14, proc, ha='center', va='center', color='black', fontsize=10)
axs[2].set_xlim(0, 18)
axs[2].set_ylim(10, 18)
axs[2].set_title('Round Robin (Quantum = 4)')
axs[2].set_yticks([])
axs[2].set_xlabel('Time (ms)')

# ---------------------------
# SJF Non-preemptive
# Order: P1, then P3, then P2, then P4.
# P1: 0-6, P3: 6-8, P2: 8-11, P4: 11-17
intervals_sjf_np = [
    (0, 6, 'P1'),
    (6, 2, 'P3'),
    (8, 3, 'P2'),
    (11, 6, 'P4')
]
for start, duration, proc in intervals_sjf_np:
    axs[3].broken_barh([(start, duration)], (10, 8), facecolors=colors[proc], edgecolor='black')
    axs[3].text(start + duration/2, 14, proc, ha='center', va='center', color='black', fontsize=10)
axs[3].set_xlim(0, 18)
axs[3].set_ylim(10, 18)
axs[3].set_title('SJF Non-preemptive')
axs[3].set_yticks([])
axs[3].set_xlabel('Time (ms)')

# ---------------------------
# SJF Preemptive (SRTF)
# Timeline:
# P1: 0-1, P2: 1-4, P3: 4-6, P1: 6-11, P4: 11-17
# Note: P1 appears in two segments.
intervals_sjf_p = [
    (0, 1, 'P1'),
    (1, 3, 'P2'),
    (4, 2, 'P3'),
    (6, 5, 'P1'),
    (11, 6, 'P4')
]
for start, duration, proc in intervals_sjf_p:
    axs[4].broken_barh([(start, duration)], (10, 8), facecolors=colors[proc], edgecolor='black')
    axs[4].text(start + duration/2, 14, proc, ha='center', va='center', color='black', fontsize=10)
axs[4].set_xlim(0, 18)
axs[4].set_ylim(10, 18)
axs[4].set_title('SJF Preemptive (SRTF)')
axs[4].set_yticks([])
axs[4].set_xlabel('Time (ms)')

plt.show()
