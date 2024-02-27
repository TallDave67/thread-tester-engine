import matplotlib.pyplot as plt
from organize_scenario_durations import organize_scenario_durations

def plot_scenario_durations(title, scenarios):
    # iterate across scenarios to create bar definitions
    bar_groups = {}
    xmax = 0
    group_offset = 0
    group_height = 30
    bar_height = 10
    yticks = []
    labels = []
    for scenario, event_dict in scenarios.items():
        # create the bar group for the scenario
        bar_groups[scenario] = {}
        #
        bar_groups[scenario]["thread"] = {}
        bar_groups[scenario]["thread"]["xranges"] = []
        bar_groups[scenario]["thread"]["yranges"] = (group_offset + bar_height, bar_height - 1)
        bar_groups[scenario]["thread"]["facecolors"] = []
        yticks.append(group_offset + bar_height + 5)
        labels.append(f"{scenario}_thread")
        #
        bar_groups[scenario]["control"] = {}
        bar_groups[scenario]["control"]["xranges"] = []
        bar_groups[scenario]["control"]["yranges"] = (group_offset + 2*bar_height, bar_height - 1)
        bar_groups[scenario]["control"]["facecolors"] = []
        yticks.append(group_offset + 2*bar_height + 5)
        labels.append(f"{scenario}_control")
        #
        bar_groups[scenario]["work"] = {}
        bar_groups[scenario]["work"]["xranges"] = []
        bar_groups[scenario]["work"]["yranges"] = (group_offset + 3*bar_height, bar_height - 1)
        bar_groups[scenario]["work"]["facecolors"] = []
        yticks.append(group_offset + 3*bar_height + 5)
        labels.append(f"{scenario}_work")

        # loop across the events adding them to the correct bar
        for event_type, events in event_dict.items():
            if event_type == "run":
                bar_groups[scenario]["thread"]["xranges"].append((events["start"], events["finish"] - events["start"]))
                bar_groups[scenario]["thread"]["facecolors"].append('tab:gray')

                # adjust the xmax
                if events["finish"] > xmax:
                    xmax = events["finish"]

            elif event_type == "acquire_lock" or event_type == "use_lock" or event_type == "wait":
                for event in events.values():
                    finish_key = "finish"
                    if finish_key not in event:
                        finish_key = "finish_success"
                        if finish_key not in event:
                            finish_key = "finish_failure"
                    bar_groups[scenario]["control"]["xranges"].append((event["start"], event[finish_key] - event["start"]))
                    color = 'tab:orange'
                    if event_type == "acquire_lock":
                        color = 'tab:green'
                        if finish_key == "finish_failure":
                            color = 'tab:red'
                    elif event_type == "use_lock":
                        color = 'tab:pink'
                    bar_groups[scenario]["control"]["facecolors"].append(color)

            elif event_type == "short_loop" or event_type == "long_loop":
                for event in events:
                    bar_groups[scenario]["work"]["xranges"].append((event["start"], event["finish"] - event["start"]))
                    bar_groups[scenario]["work"]["facecolors"].append('tab:blue' if event_type == "long_loop" else 'tab:cyan')

        # adjust the group_offset
        group_offset += group_height

    # Horizontal bar plot with gaps
    fig, ax = plt.subplots()
    for bar_group in bar_groups.values():
        ax.broken_barh(bar_group["thread"]["xranges"], bar_group["thread"]["yranges"], 
                       facecolors=tuple(bar_group["thread"]["facecolors"]))
        ax.broken_barh(bar_group["control"]["xranges"], bar_group["control"]["yranges"], 
                       facecolors=tuple(bar_group["control"]["facecolors"]))
        ax.broken_barh(bar_group["work"]["xranges"], bar_group["work"]["yranges"], 
                       facecolors=tuple(bar_group["work"]["facecolors"]))
    #
    ax.set_ylim(5, group_offset + 15)
    ax.set_xlim(0, xmax)
    ax.set_xlabel('microseconds since start')
    ax.set_yticks(yticks, labels=labels)     # Modify y-axis tick labels
    ax.grid(True)                            # Make grid lines visible
    plt.tight_layout()
    plt.title(f"TEST: {title}")
    plt.show()

if __name__ == "__main__":
    title, scenarios = organize_scenario_durations("tests/output/syncBarrier_latest_output.txt")
    plot_scenario_durations(title, scenarios)