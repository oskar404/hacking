#!/usr/bin/env bash
# Just dump libc version
# Works on glibc - no idea how other libc implementations work

LIBC=$(ldd $(which ls) | grep libc | awk '{print $3}')
echo ${LIBC}
${LIBC}
