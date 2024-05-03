#!/bin/bash

# Check if a topic name is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <topic_name>"
    exit 1
fi

# Get the topic name
topic_name=$1
sole_topic_name="${topic_name:3}"
SOLE_TOPIC_NAME="${sole_topic_name^^}"

# Create the hpp file
hpp_file="include/${topic_name}.hpp"
hpp_file_content=$(cat <<EOF
#ifndef ${SOLE_TOPIC_NAME}_HPP
#define ${SOLE_TOPIC_NAME}_HPP

void $sole_topic_name(void);

#endif /* ${SOLE_TOPIC_NAME}_HPP */

EOF
)

printf "%b\n" "$hpp_file_content" >> $hpp_file

# Create the cpp file
cpp_file="src/${topic_name}.cpp"
cpp_file_content=$(cat <<EOF
#include "utility.hpp"

/* ==============================================================================

---------------------------
---------------------------


--------------------------- */
/* ---------------------------

============================================================================== */

void $sole_topic_name(void)
{
	STARTT();
	ENDT();
}

EOF
)

printf "%b\n" "$cpp_file_content" >> $cpp_file

# Add the header include to the main file
main_file="src/main.cpp"
sed -i "/\/\/ ADD HEADER/i #include \"$topic_name.hpp\"" "$main_file"

# Add the function call to the main file
sed -i "/\/\/ ADD FUNCTION/i\\
	${sole_topic_name}();" "$main_file"