#!/bin/sh

./build/thread-tester-engine 100 > "tests/output/lockOrderSame_latest_output.txt"
./build/thread-tester-engine 99 > "tests/output/lockOrderInverted_latest_output.txt"
./build/thread-tester-engine 98 > "tests/output/syncLatch_latest_output.txt"
./build/thread-tester-engine 97 > "tests/output/syncBarrier_latest_output.txt"
