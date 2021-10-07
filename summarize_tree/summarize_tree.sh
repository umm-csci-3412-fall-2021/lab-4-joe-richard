#!/usr/bin/env bash

rootDir="$1"

numDir="$(find "$rootDir" -type d | wc -l | tr -d ' ')"
numFiles="$(find "$rootDir" -not -type d | wc -l | tr -d ' ')"

echo "There were $numDir directories."
echo "There were $numFiles regular files."
