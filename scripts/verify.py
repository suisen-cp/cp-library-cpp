from concurrent.futures import ThreadPoolExecutor
import os
from pathlib import Path
import subprocess
import json

tmpdir = Path('tmp')
timestamp_file = Path('.verify-helper') / Path(f'timestamps.{"remote" if "GITHUB_ACTION" in os.environ else "local"}.json')

timestamp = {}

def task(tests):
    verify_cmd = ['oj-verify', 'run', '--timeout', '6000', *tests]
    subprocess.check_call(verify_cmd)
    timestamp.update(json.load(timestamp_file.open()))

def main():
    UNIT = 20
    
    buckets = [[]]

    for testfile in Path('test').glob('**/*.test.cpp'):
        buckets[-1].append(str(testfile))
        if len(buckets[-1]) == UNIT:
            buckets.append([])

    with ThreadPoolExecutor() as executor:
        for bucket in buckets:
            executor.submit(task, bucket)
    
    json.dump(
        timestamp,
        timestamp_file.open('w'),
        indent=4,
        sort_keys=True,
    )

main()