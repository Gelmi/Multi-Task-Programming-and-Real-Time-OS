#!/bin/bash

# Source file
EXEC="td2c"

# Output file for measurements
OUTPUT="results.csv"

# Remove old results
rm -f $OUTPUT

# Header for CSV
echo "nLoops,time_seconds" >> $OUTPUT

# Test values (adjust if needed)
VALUES=(
    100
    1000
    10000
    100000
    1000000
    5000000
    10000000
    50000000
    100000000
    500000000
    1000000000
    5000000000
    10000000000
    50000000000
)

echo "Running measurements..."

for N in "${VALUES[@]}"
do
    echo "Running with nLoops = $N"
    RESULT=$(./$EXEC $N)

    # Append to CSV
    echo "$RESULT" >> $OUTPUT
done

echo "All runs completed."
echo "Results saved in $OUTPUT"

