/**
 * @file magnetic_field_calculator.c
 * @brief This file contains functions to calculate magnetic fields.
 */

#ifndef common_h
#define common_h

#define M_PI 3.14159265358979323846
/**
 * @struct point
 * @brief Represents a 3D point with x, y, and z coordinates.
 */
typedef struct {
    double x; /**< x-coordinate. */
    double y; /**< y-coordinate. */
    double z; /**< z-coordinate. */
} point;

/**
 * @struct target_field
 * @brief Represents a 3D target field in space and the computed field vector.
 */
typedef struct {
    point* location;     // 3D array for the magnetic field points  (x, y, z)
    point* field_vectors; // 3D array for the calculated magnetic field vector  (x, y, z)
    int size;               /**< Number of points. */
} target_field;

/**
 * @struct wire_path
 * @brief Represents a sinusoidal wire with specified properties.
 */
typedef struct {
    point* coordinates; /**< Array of points representing wire coordinates. */
    int m; /**< Number of segments. */
} wire_path;

/**
 * @brief Calculates the Euclidean distance between two points.
 *
 * @param p1 First point.
 * @param p2 Second point.
 * @return Euclidean distance between p1 and p2.
 */
double calculate_distance(point p1, point p2);


/**
 * @brief Creates a linear target field on the y-axis with specified properties.
 *
 * @param num_points Number of points (minimum 1).
 * @param y_min Minimum y-coordinate.
 * @param y_max Maximum y-coordinate.
 * @return A pointer to the newly created target field structure.
 */
target_field* create_linear_y_field(int num_points, double y_min, double y_max);

/**
 * @brief Creates a 2D target field on the xy-plane with specified properties.
 *
 * @param m Number of rows.
 * @param n Number of columns.
 * @param x_min Minimum x-coordinate.
 * @param x_max Maximum x-coordinate.
 * @param y_min Minimum y-coordinate.
 * @param y_max Maximum y-coordinate.
 * @param z_position Constant z-coordinate for all points.
 * @return A pointer to the newly created target field structure.
 */
target_field* create_xy_planar_target_field(int m, int n, double x_min, double x_max, double y_min, double y_max, double z_position);

/**
 * @brief Loads the target field points from a file
 *
 * @param filename The file name.
 * @return A pointer to the newly created sinusoidal wire structure.
 */
target_field *read_target_field_from_file(const char *filename);


/**
 * @brief Frees the allocated memory for the target field structure.
 *
 * @param field Pointer to the target field structure.
 */
void free_target_field(target_field* field);

/**
 * @brief Creates a sinusoidal wire with specified properties.
 *
 * @param m Number of segments (minimum of 1, i.e. 2 points linking x_min and x_max).
 * @param x_min Minimum x-coordinate of the wire.
 * @param x_max Maximum x-coordinate of the wire.
 * @return A pointer to the newly created sinusoidal wire structure.
 */
wire_path* create_linear_wire(int m, double x_min, double x_max);

/**
 * @brief Creates a sinusoidal wire with specified properties.
 *
 * @param m Number of segments.
 * @param mag Magnitude of the wire.
 * @param x_min Minimum x-coordinate of the wire.
 * @param x_max Maximum x-coordinate of the wire.
 * @param z_value z-coordinate of the wire.
 * @param n Number of wavelengths.
 * @return A pointer to the newly created sinusoidal wire structure.
 */
wire_path* create_sinusoidal_wire(int m, double mag, double x_min, double x_max, double z_value, double n);


/**
 * @brief Loads the wire path from a file
 *
 * @param filename The file name.
 * @return A pointer to the newly created sinusoidal wire structure.
 */
wire_path* read_wire_path_from_file(const char* filename);

/**
 * @brief Frees the allocated memory for the sinusoidal wire structure.
 *
 * @param wire Pointer to the sinusoidal wire structure.
 */
void free_wire_path(wire_path* wire);

/**
 * @brief Calculates the magnetic field at each point in the target field using the Biot-Savart law.
 *
 * @param field Pointer to the target field structure.
 * @param wire Pointer to the sinusoidal wire structure.
 * @param current The constant current passing through the wire.
 */
void calculate_magnetic_field(target_field* field, wire_path* wire, double current);

#endif