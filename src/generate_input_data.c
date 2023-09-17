#include <math.h>
#include <stdlib.h>

#include "common.h"

// Define the magnetic field
target_field* create_linear_y_field(int num_points, double y_min, double y_max)
{
    target_field *field = malloc(sizeof(target_field));
    field->size = num_points;
    field->location = (point *)malloc(field->size * sizeof(point));
    field->field_vectors = (point *)malloc(field->size * sizeof(point));

    double y = y_min;
    double dy = (y_max - y_min)/((double)num_points);

    for (int i = 0; i < num_points; i++)
    {
        // Set the location coordinates
        field->location[i].x = 0.0;
        field->location[i].y = y;
        field->location[i].z = 0.0;

        // Initialize the field_vectors to zero
        field->field_vectors[i].x = 0.0;
        field->field_vectors[i].y = 0.0;
        field->field_vectors[i].z = 0.0;

        // next point
        y += dy;
    }

    return field;
}


target_field *create_xy_planar_target_field(int m, int n, double x_min, double x_max, double y_min, double y_max, double z_position)
{
    target_field *field = malloc(sizeof(target_field));
    field->size = m * n;
    field->location = (point *)malloc(field->size * sizeof(point));
    field->field_vectors = (point *)malloc(field->size * sizeof(point));

    for (int i = 0; i < field->size; i++)
    {

        int row = i / n;
        int col = i % n;

        double x = x_min + col * (x_max - x_min) / (n - 1);
        double y = y_min + row * (y_max - y_min) / (m - 1);

        // Set the location coordinates
        field->location[i].x = x;
        field->location[i].y = y;
        field->location[i].z = z_position;

        // Initialize the field_vectors to zero
        field->field_vectors[i].x = 0.0;
        field->field_vectors[i].y = 0.0;
        field->field_vectors[i].z = 0.0;
    }

    return field;
}

void free_target_field(target_field *field)
{
    free(field->location);
    free(field->field_vectors);
    free(field);
}

// Now the wire
wire_path *create_sinusoidal_wire(int m, double mag, double x_min, double x_max, double z_value, double n)
{
    wire_path *wire = malloc(sizeof(wire_path));
    wire->m = m;

    // Allocate memory for coordinates and currents
    wire->coordinates = (point *)malloc(m * sizeof(point));

    double lambda = (x_max - x_min) / n;
    double k = 2 * M_PI / lambda;

    for (int i = 0; i < m; i++)
    {
        double x = x_min + i * (x_max - x_min) / (m - 1);
        double y = mag * sin(k * x);
        wire->coordinates[i].x = x;
        wire->coordinates[i].y = y;
        wire->coordinates[i].z = z_value;
    }

    return wire;
}


wire_path* create_linear_wire(int segments, double x_min, double x_max)
{
    wire_path *wire = malloc(sizeof(wire_path));
    wire->m = segments+1;

    // Allocate memory for coordinates and currents
    wire->coordinates = (point *)malloc((wire->m) * sizeof(point));

    double dx = (x_max - x_min) / (segments);
    double x = x_min;

    for (int i = 0; i < wire->m; i++)
    {
        double y = x + dx;
        wire->coordinates[i].x = x;
        wire->coordinates[i].y = 0.0;
        wire->coordinates[i].z = 0.0;

        x = y;
    }

    return wire;
}


void free_wire_path(wire_path *wire)
{
    free(wire->coordinates);
    free(wire);
}
