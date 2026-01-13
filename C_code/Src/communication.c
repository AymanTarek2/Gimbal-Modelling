#include <stdio.h>
#include <stdlib.h>
#include "communication.h"

int read_robot_state(RobotState *state) {
    // Read the full struct from stdin binary stream
    size_t n = fread(state, sizeof(RobotState), 1, stdin);
    return (n == 1); // Return 1 if successful, 0 if stream closed/error
}

void write_control_output(ControlOutput *out) {
    // Write the full struct to stdout binary stream
    fwrite(out, sizeof(ControlOutput), 1, stdout);
    
    // FLUSH is critical to ensure Python receives data immediately
    fflush(stdout); 
}