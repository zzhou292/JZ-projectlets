#!/bin/bash

# Directory containing the input files
input_dir="input_pa2"

# Parameter for ./fp, passed as the first argument to the script
parameter=$1

# Check if the parameter is provided
if [ -z "$parameter" ]; then
    echo "Usage: $0 <parameter>"
    exit 1
fi

# Array of base file names without extensions
file_names=("1" "2" "3" "ami33" "ami49" "apte" "hp" "xerox")

# Iterate over each file name
for name in "${file_names[@]}"; do
    block_file="$input_dir/$name.block"
    nets_file="$input_dir/$name.nets"
    output_file="${name}.rpt"

    # Check if both the .block and .nets files exist before running the command
    if [[ -f "$block_file" && -f "$nets_file" ]]; then
        echo "Running: ./fp $parameter $block_file $nets_file $output_file"
        ./fp "$parameter" "$block_file" "$nets_file" "$output_file"
        echo "Running: ./checker/checker.py ${name} $output_file"
        ./checker/checker.py "${name}" "$output_file"
    else
        echo "Skipping $name, because file(s) missing."
    fi
done
