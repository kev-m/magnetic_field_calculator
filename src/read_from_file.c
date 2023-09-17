#include <stdio.h>
#include <stdlib.h>

#include "common.h"

wire_path *read_wire_path_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s.\n", filename);
        return NULL;
    }

    int num_elements;
    if (fscanf(file, "%d", &num_elements) != 1 || num_elements <= 0)
    {
        fprintf(stderr, "Invalid number of elements in file %s.\n", filename);
        fclose(file);
        return NULL;
    }

    wire_path *wire;
    if ((wire = (wire_path *)malloc(sizeof(wire_path))) == NULL)
    {
        puts("ERROR: Unable to allocate memory for wire_path!");
        return NULL;
    }
    wire->m = num_elements;
    if ((wire->coordinates = (point *)malloc(num_elements * sizeof(point))) == NULL)
    {
        puts("ERROR: Unable to allocate memory for wire->coordinates!");
        return NULL;
    }

    for (int i = 0; i < num_elements; i++)
    {
        if (fscanf(file, "%lf, %lf, %lf", &wire->coordinates[i].x, &wire->coordinates[i].y, &wire->coordinates[i].z) != 3)
        {
            fprintf(stderr, "Error reading coordinates from file %s.\n", filename);
            fclose(file);
            free(wire->coordinates);
            free(wire);
            return NULL;
        }
    }

    fclose(file);
    return wire;
}

target_field *read_target_field_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s.\n", filename);
        return NULL;
    }

    int num_elements;
    if (fscanf(file, "%d", &num_elements) != 1 || num_elements <= 0)
    {
        fprintf(stderr, "Invalid number of elements in file %s.\n", filename);
        fclose(file);
        return NULL;
    }

    target_field *target;
    if ((target = (target_field *)malloc(sizeof(target_field))) == NULL)
    {
        puts("ERROR: Unable to allocate memory for target_field!");
        return NULL;
    }
    if ((target->location = (point *)malloc(num_elements * sizeof(point))) == NULL)
    {
        puts("ERROR: Unable to allocate memory for target->location!");
        return NULL;
    }
    if ((target->field_vectors = (point *)malloc(num_elements * sizeof(point))) == NULL)
    {
        puts("ERROR: Unable to allocate memory for target->field_vectors!");
        return NULL;
    }
    target->size = num_elements;

    for (int i = 0; i < num_elements; i++)
    {
        if (fscanf(file, "%lf, %lf, %lf", &target->location[i].x, &target->location[i].y, &target->location[i].z) != 3)
        {
            fprintf(stderr, "Error reading coordinates from file %s.\n", filename);
            fclose(file);
            free(target->location);
            free(target);
            return NULL;
        }
    }

    fclose(file);
    return target;
}
