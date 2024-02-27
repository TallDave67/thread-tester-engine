import json

start_keys = ["start"]
finsh_keys = ["finish", "finish_success", "finish_failure"]

def organize_scenario_durations(test_output_file):
    # read events into array
    events = []
    try:
        with open(test_output_file, "r") as file:
            for line in file:
                line = line.strip() # strip() removes trailing newline characters
                tokens=line.split(']')
                value = json.loads(tokens[1][1:]) 
                events.append(value)
    except FileNotFoundError:
        print(f"Error: File '{test_output_file}' not found.")
    except Exception as e:
        print(f"Error: {e}")

    # loop across events and organize them into dictionary of Scenario objects
    title = "Test"
    scenarios = {}
    for event in events:
        if event["object"] == "test":
            title = event["id"]
        elif event["object"] == "scenario":
            if event["event_type"] == "run":
                if event["event"] == "start":
                    scenarios[event["id"]] = {}
                    scenarios[event["id"]][event["event_type"]] = {}
                    scenarios[event["id"]][event["event_type"]][event["event"]] = event["duration"]
                elif event["event"] == "finish":
                    scenarios[event["id"]][event["event_type"]][event["event"]] = event["duration"]
            elif event["event_type"] == "short_loop" or \
                event["event_type"] == "long_loop":
                if event["event"] == "start":
                    if event["event_type"] not in scenarios[event["id"]]:
                        scenarios[event["id"]][event["event_type"]] = []
                    scenarios[event["id"]][event["event_type"]].append({})
                    current = len(scenarios[event["id"]][event["event_type"]]) - 1
                    scenarios[event["id"]][event["event_type"]][current][event["event"]] = event["duration"]
                elif event["event"] == "finish":
                    current = len(scenarios[event["id"]][event["event_type"]]) - 1
                    scenarios[event["id"]][event["event_type"]][current][event["event"]] = event["duration"]
        else:
            if event["event_type"] == "acquire_lock" or \
                event["event_type"] == "use_lock" or \
                event["event_type"] == "wait":
                if event["event"] == "start":
                    if event["event_type"] not in scenarios[event["parent_id"]]:
                        scenarios[event["parent_id"]][event["event_type"]] = {}
                    scenarios[event["parent_id"]][event["event_type"]][event["id"]] = {}
                    scenarios[event["parent_id"]][event["event_type"]][event["id"]][event["event"]] = event["duration"]
                elif event["event"] == "finish" or \
                    event["event"] == "finish_success" or \
                    event["event"] == "finish_failure":
                    scenarios[event["parent_id"]][event["event_type"]][event["id"]][event["event"]] = event["duration"]
    print(title)
    print(scenarios)
    return title, scenarios

if __name__ == "__main__":
    organize_scenario_durations("tests/output/lockOrderInverted_latest_output.txt")