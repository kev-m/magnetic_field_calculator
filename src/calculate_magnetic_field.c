#include <math.h>
#include "common.h"

#define BS_K 1.0e-7

double calculate_distance(point p1, point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z));
}

void calculate_magnetic_field(target_field *field, wire_path *wire, double current)
{
    for (int i = 0; i < field->size; i++)
    {
        double Bx = 0.0;
        double By = 0.0;
        double Bz = 0.0;

        point r = field->location[i]; // Target point
        for (int j = 0; j < wire->m - 1; j++)
        {
            point l1 = wire->coordinates[j];                                               // Start of wire segment
            point l2 = wire->coordinates[j + 1];                                           // End of wire segment
            point l = (point){(l2.x + l1.x) / 2., (l2.y + l1.y) / 2., (l2.z + l1.z) / 2.}; // The point on the wire segment, l
            point dl = (point){(l2.x - l1.x), (l2.y - l1.y), (l2.z - l1.z)};               // The dl term
            point rp = (point){(r.x - l.x), (r.y - l.y), (r.z - l.z)};                     // The r' = r - l

            double r_norm = calculate_distance(rp, (point){0.,0.,0.}); // Magnitude of the relative position vector
            double factor = (BS_K) / (r_norm * r_norm * r_norm);

            Bx += (dl.y * rp.z - dl.z * rp.y)*factor; // r x dl / 
            By += (dl.z * rp.x - dl.x * rp.z)*factor;
            Bz += (dl.x * rp.y - dl.y * rp.x)*factor;
        }

        // Store the calculated magnetic field vector components
        field->field_vectors[i].x = Bx * current;
        field->field_vectors[i].y = By * current;
        field->field_vectors[i].z = Bz * current;
    }
}
