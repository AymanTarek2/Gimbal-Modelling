#include <stdio.h>
#include <stdlib.h>
#include "communication_2.h"

int read_robot_state(RobotState *state) {
    // Read 67 doubles (536 bytes) from stdin
    size_t n = fread(state, sizeof(RobotState), 1, stdin);
    return (n == 1);
}

void write_control_output(ControlOutput *out) {
    // Write 15 doubles (120 bytes) to stdout
    fwrite(out, sizeof(ControlOutput), 1, stdout);
    fflush(stdout); // Critical for Python synchronization
}