#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int dummy()
{
    // Test case data
    int elements = 99;
    double x_val = 0.5;
    wire_path *my_wire = create_linear_wire(elements, -x_val, x_val);        // 1 segment, 1 m long
    target_field *my_field = create_linear_y_field(elements, -x_val, x_val); // Only 1 point at 0.0, 1.0, 0.0
    //  Create and populate the sinusoidal wire
    //  wire_path *my_wire = create_sinusoidal_wire(100,0.1,0., 1.0, 0.0, 1.);
    //  Create and populate the target field (create_xy_planar_target_field function from previous response)
    //  target_field *my_field = create_xy_planar_target_field(3, 4, -5.0, 5.0, -5.0, 5.0, 0.0);
    double current = 1.0; // A

    // Calculate magnetic field using Biot-Savart law
    calculate_magnetic_field(my_field, my_wire, current);

    // Access and print the calculated magnetic field
    for (int i = 0; i < my_field->size; i++)
    {
        printf("%4d %.10e, %.10e, %.10e\n", i, my_field->field_vectors[i].x, my_field->field_vectors[i].y, my_field->field_vectors[i].z);
    }
    // Free allocated memory
    free_target_field(my_field);
    free_wire_path(my_wire);

    return 0;
}

void display_help()
{
    puts("Usage: ./calculate_magnetic_field -w <wire_path.txt> -t <target_field.txt> -A <current> [-d]");
    puts("");
    puts("Calculate and print the magnetic field at the target co-ordinates due to the given wire path using the Biot-Savart Law.");
    puts("See: https://en.wikipedia.org/wiki/Biot%E2%80%93Savart_law");
    puts("");
    puts("Both the wire path and target field files have the same syntax:");
    puts("Line 1: The number of subsequent entries, e.g. 100");
    puts("Lines 2 onward: The comma-separated x,y,z co-ordinates, e.g. -0.117668100970,0.484508134559,0.73639054917");
    puts("");
    puts("Options:");
    puts("  -w <path>      Specify the file path for the wire path. Default: wire_path_xyz.csv");
    puts("  -A <current>   Specify the current flowing through the wire (in Amperes). Default: 1.0");
    puts("  -t <path>      Specify the file path for the target field. Default: target_field_xyz.csv");
    puts("  -c             Include the target field co-ordinates in the output (optional).");
    puts("  -d             Enable debug mode (optional).");
    puts("  -h             Display this help message.");
    puts("");
    puts("The output is the comma-separated magnetic field vector at the provided target field positions, i.e. field-x,y,z.");
    puts("Line 1 of the output is the current that was used to calculate the target field.");
    puts("Line 2 is the number of subsequent lines.");
    puts("Line 3 onwards are the comma-separated data, either just the calculated field or the co-ordinates and field:");
    puts("If -c is specified, the target position is repeated in the output, i.e. target-x,y,z,field-x,y,z");
}

// Function to parse command-line arguments
void parse_arguments(int argc, char **argv, char *wire_path, char *target_field, double *current, int *coords, int *debug)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-w") == 0 && i + 1 < argc)
        {
            strcpy(wire_path, argv[i + 1]);
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
        {
            strcpy(target_field, argv[i + 1]);
        }
        else if (strcmp(argv[i], "-A") == 0 && i + 1 < argc)
        {
            *current = atof(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-c") == 0)
        {
            *coords = 1;
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            *debug = 1;
        }
        else if (strcmp(argv[i], "-h") == 0)
        {
            display_help();
            exit(0); // Exit program after displaying help
        }
    }
}

/**
 * @brief Main function to demonstrate the usage of the provided functions.
 *
 * @return Exit status.
 */
int main(int argc, char **argv)
{
    // Default values
    char wire_path_filename[256] = "wire_path_xyz.csv";
    char target_field_filename[256] = "target_field_xyz.csv";
    double current = 1.0; // A
    int debug = 0;
    int coords = 0;

    // Parse command-line arguments
    parse_arguments(argc, argv, wire_path_filename, target_field_filename, &current, &coords, &debug);

    // Load wire path from file
    wire_path *my_wire = read_wire_path_from_file(wire_path_filename);
    // Check successes
    if (my_wire == NULL)
    {
        return -1;
    }

    // Load target field co-ordinates from file
    target_field *my_field = read_target_field_from_file(target_field_filename);
    if (my_field == NULL)
    {
        return -1;
    }

    // Calculate the magnetic field using Biot-Savart law
    calculate_magnetic_field(my_field, my_wire, current);

    // Access and print the calculated magnetic field, 
    printf("%4.10f\n", current);
    printf("%d\n", my_field->size);
    for (int i = 0; i < my_field->size; i++)
    {
        if (debug)
        {
            printf("%4d ", i);
        }
        if (coords)
        {
            printf("%.10e,%.10e,%.10e,", my_field->location[i].x, my_field->location[i].y, my_field->location[i].z);
        }
        printf("%.10e,%.10e,%.10e\n", my_field->field_vectors[i].x, my_field->field_vectors[i].y, my_field->field_vectors[i].z);
    }

    // Free allocated memory
    free_target_field(my_field);
    free_wire_path(my_wire);

    return 0;
}
