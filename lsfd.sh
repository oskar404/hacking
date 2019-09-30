#!/usr/bin/env bash
# Figure out open PIDs for current process. Take a peek into /proc filesystem

echo "ls -l /proc/$$/fd/"
ls -l /proc/$$/fd/

echo "ls -l /dev/fd/ >/dev/fd/2"
ls -l /dev/fd/ >/dev/fd/2

# FD list id not really interesting when this script does not do anything
