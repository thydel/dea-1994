#include <stdio.h>   // For standard input/output functions like printf, fprintf
#include <assert.h>  // For the assert macro (not used in this snippet but often good practice)
#include <malloc.h>  // For memory allocation functions like malloc (some systems use stdlib.h for this)
#include <memory.h>  // For memory manipulation functions like memset (often string.h is used for memset)
#include <string.h>  // For string manipulation functions like strtok, strcmp

#include "named_func.h" // Assumed to contain definition for Named_Func and Named_Func_get

// External declaration for an array of Named_Func structures.
// This array likely maps function names (strings) to function pointers.
extern Named_Func funcs_names[];

// Global variables
char* cmd_name; // Stores the name of the command (executable name) for usage messages
int debug;      // Flag to enable debugging output (0 = off, 1 = on)

char* tab;      // Pointer to the main data buffer (likely a 2D grid stored linearly)

// String detailing the command-line usage of the program
char* usage = "\n"
    "[-s{ize} <power-of-two>(8) \n"          // Option for setting size (side = 2^<power-of-two>)
    "[-p{lane} <int>(0)] \n"                 // Option for selecting the current bit plane
    "[-d{ensity} <int>(2)] \n"               // Option for setting density for operations
    "\t1/<density> bit to 1 if <density> >= 0 \n" // Density behavior: positive for setting bits to 1
    "\t1/<density> bit to 0 if <density> < 0 \n"  // Density behavior: negative for setting bits to 0
    "[-r{egion} <int>(0) \n"                 // Option for defining a region size for operations
    "\t0 means all frame \n"                 // Special region value: 0 means the entire frame/grid
    "[-f{unc} <str>[:<int>[,<int>]...](fill) ] \n" // Option to call a named function with optional arguments
    "[-1] \n"                                // Shortcut option
    "\t short for -d 1 -r 1 -f fill \n"      //   -1 implies: density 1, region 1, function 'fill'
    "[-D{ebug}] \n";                         // Option to enable debug mode

// Main function of the program
int main(int ac, char** av) {
    // extern char *optarg; // Used by getopt to point to the argument of an option
    // extern int optind;   // Used by getopt to track the index of the next argument to be processed
    // These are typically declared by including <unistd.h> or are implicitly available with getopt

    int c;        // Variable to store the character for the current command-line option
    int errflg;   // Flag to indicate if an error occurred during option parsing

    int shift;    // Determines the size of the grid (side = 1 << shift, so side is 2^shift)
    int (*func)(); // Function pointer to hold the function to be executed (from -f option)
    // int side;  // Variable to store side length (1 << shift), not directly used in main's scope after initialization
    int plane;    // Current active bit plane (0-7)
    int density[8]; // Array to store density values for each of the 8 possible planes
    int region[8];  // Array to store region sizes for each of the 8 possible planes
    int done;     // Flag to indicate if an operation (like -1, -8, or -f) has been performed
    int i;        // Loop counter

    cmd_name = av[0]; // Store the program name (e.g., for error messages)
    errflg = 0;       // Initialize error flag to false
    shift = 8;        // Default shift value (grid size will be 2^8 = 256)
    plane = 0;        // Default active plane is 0
    done = 0;         // No operation performed yet

    // Seed the pseudo-random number generator (lrand48)
    // Uses a combination of current time and process ID for better randomness.
    // Note: srand48 and lrand48 are part of XSI, might need <stdlib.h> and _XOPEN_SOURCE define.
    // time(0) needs <time.h>. getpid() needs <unistd.h>.
    srand48(time(0) & getpid());

    // Initialize region and density arrays for all 8 planes
    for (i = 0; i < 8; ++i) {
        region[i] = 0;    // Default region size 0 (means full frame)
        density[i] = 2;   // Default density 2 (1/2 probability of setting a bit to 1)
    }

    // Parse command-line options using getopt
    // Options "s:p:r:d:f:" expect an argument (indicated by ':')
    // Options "18D" are flags without arguments
    while ((c = getopt(ac, av, "s:p:r:d:f:18D")) != EOF) // EOF is typically -1
        switch (c) {
          case 's': { // Size option
              shift = atoi(optarg); // Convert option argument to integer for shift
              break;
          }
          case 'p': { // Plane option
              plane = atoi(optarg); // Convert option argument to integer for current plane
              // Basic validation for plane could be added here (e.g., 0-7)
              break;
          }
          case 'r': { // Region option
              region[plane] = atoi(optarg); // Set region size for the current plane
              break;
          }
          case 'd': { // Density option
              density[plane] = atoi(optarg); // Set density for the current plane
              break;
          }
          case '1': { // Shortcut option: fill one plane with density 1, region 1
              alloc(shift);                     // Ensure main data buffer 'tab' is allocated
              fill(shift, plane, 1, 1);         // Call fill function for the current plane
              ++done;                           // Mark that an operation has been done
              break;
          }
          case '8': { // Shortcut option: fill all 8 planes with density 1, region 1
              int i;                            // Loop counter for planes

              alloc(shift);                     // Ensure main data buffer 'tab' is allocated
              for (i = 0; i < 8; ++i) {
                  fill(shift, i, 1, 1);         // Call fill function for each plane 'i'
              }
              ++done;                           // Mark that an operation has been done
              break;
          }
          case 'f': { // Function call option
              int n;                            // Counter for function arguments
              int i;                            // Loop counter (not used in this block as 'i')
              int a[8];                         // Array to store integer arguments for the function
              char* p;                          // Pointer for tokenizing the function string

              alloc(shift);                     // Ensure main data buffer 'tab' is allocated
              p = strtok(optarg, ":");          // Get function name (part before ':')
              func = Named_Func_get(funcs_names, p); // Look up function pointer by name
              if (!func) {                      // If function name not found
                  fprintf(stderr, "%s: %s not found\n", cmd_name, p);
                  exit(1);                      // Exit with error
              }
              // Parse arguments for the function (comma-separated integers after ':')
              for (p = strtok(0, ","), n = 0; p; p = strtok(0, ","), ++n) {
                  a[n] = atoi(p);               // Convert argument token to integer
                  if (n >= 7 && strtok(0, ",")) { // Check for too many arguments (max 8 stored in a[0-7])
                      fprintf(stderr, "%s: too many arguments for function\n", cmd_name);
                      // Potentially exit or cap arguments
                      break;
                  }
              }
              // Call the function with a variable number of arguments based on 'n'
              // The first 4 arguments (shift, plane, region, density) are always passed.
              switch(n) { // n is the count of additional integer arguments parsed
                case 0:
                  func(shift, plane, region[plane], density[plane]);
                  break;
                case 1:
                  func(shift, plane, region[plane], density[plane], a[0]);
                  break;
                case 2:
                  func(shift, plane, region[plane], density[plane], a[0], a[1]);
                  break;
                case 3:
                  func(shift, plane, region[plane], density[plane], a[0], a[1], a[2]);
                  break;
                case 4: // Supports up to 4 additional integer arguments (a[0] to a[3])
                  func(shift, plane, region[plane], density[plane], a[0], a[1], a[2], a[3]);
                  break;
                default: // If more than 4 custom args were parsed (and not caught above), handle or error
                  fprintf(stderr, "%s: function called with %d custom arguments, max 4 supported in this switch.\n", cmd_name, n);
                  // Default behavior might be to call with 4, or could be an error.
                  // Assuming the functions can handle potentially more or fewer args if defined that way.
                  // For safety, if functions have fixed arg counts, this needs more robust checking.
                  // This example calls with 4 args if n > 4.
                  if (n > 4) {
                      func(shift, plane, region[plane], density[plane], a[0], a[1], a[2], a[3]);
                  } else {
                      // This case should ideally not be reached if n < 0.
                      // This might indicate an issue or an unhandled number of arguments.
                  }
                  break;
              }
              ++done;                           // Mark that an operation has been done
              break;
          }
          case 'D': // Debug option
            debug = 1;                          // Set debug flag
            break;
          case '?': // Option parsing error (unknown option or missing argument)
            errflg++;                           // Increment error flag
        }

    // After parsing all options, check if any errors occurred
    if (errflg) {
        fprintf(stderr, "%s, usage: %s\n", cmd_name, usage); // Print usage message
        exit(1);                                            // Exit with error
    }

    // Check for any non-option arguments remaining on the command line
    for (; optind < ac; optind++) {
        // If any exist, it's an error as this program doesn't expect them
        fprintf(stderr, "%s: extraneous argument %s\n", cmd_name, av[optind]);
        fprintf(stderr, "%s, usage: %s\n", cmd_name, usage); // Print usage message
        exit(1);                                            // Exit with error
    }

    // If no specific operation was performed via options (-1, -8, -f)
    if (!done) {
        alloc(shift);                           // Ensure main data buffer 'tab' is allocated
        for (i = 0; i < 8; ++i) {               // Iterate through all 8 planes
            // Fill each plane 'i' using its specific region and density settings
            fill(shift, i, region[i], density[i]);
        }
    }

    // Write the entire content of the data buffer 'tab' to standard output (file descriptor 1)
    // The size written is (1 << shift) * (1 << shift), which is side * side.
    // This assumes 'tab' contains raw byte data representing the grid.
    write(1, tab, 1 << (shift << 1)); // (shift << 1) is (shift * 2), so 1 << (shift*2) = (2^shift)^2 = side^2
    // write() needs <unistd.h>
    return 0; // Indicate successful execution
}

// Allocates memory for the global 'tab' if it hasn't been allocated yet.
// The size is determined by 'shift' (side = 2^shift, size = side*side).
int alloc(int shift) // Return type is int, but it doesn't return a meaningful value (could be void)
{
    int side; // Side length of the square grid
    int size; // Total number of bytes for the grid (side * side)

    if (!tab) { // Only allocate if 'tab' is currently NULL
        side = 1 << shift;    // Calculate side length (2 to the power of shift)
        size = side * side;   // Calculate total size
        tab = malloc(size);   // Allocate memory
        if (!tab) {           // Check if malloc failed
            fprintf(stderr, "%s: malloc failed for size %d\n", cmd_name, size);
            exit(1);          // Exit if memory allocation fails
        }
        memset(tab, 0, size); // Initialize allocated memory to zeros
    }
    return 0; // Implicitly returns 0, though not strictly necessary if void
}

// Sets a bit in the 'tab' at coordinates (x,y) for a given 'plane'.
// The setting is probabilistic based on 'density'.
int set(int shift, int plane, int density, int x, int y) // Return type is int, but could be void
{
    int tmp; // Temporary variable to decide if the bit should be set (1) or not (0)

    // Determine 'tmp' based on density
    if (density == 1) { // If density is 1, always set the bit
        tmp = 1;
    } else if (density == 0) { // If density is 0, never set the bit (or handle as error/special case)
        tmp = 0; // Or this could be an invalid density depending on desired behavior
    }
    else { // Probabilistic setting based on density
        int neg; // Flag to check if density is negative

        neg = density < 0; // True if density is negative
        // Calculate a random number modulo the absolute value of density.
        // lrand48() returns a long, >> 16 to reduce range or just use %
        // This gives a 1 in |density| chance for the modulo to be 0.
        tmp = (lrand48() >> 16) % (neg ? -density : density);
        tmp = tmp ? 0 : 1;  // If modulo is 0, tmp becomes 1 (set), otherwise 0 (don't set)
        tmp = neg ? !tmp : tmp; // If density was negative, invert the logic (set if random was non-zero)
                                // So for negative density D: 1 - (1/|D|) chance to set bit to 0.
                                // This means it sets the bit to 1 with chance (1/|D|) when neg is true (effectively clearing with 1-(1/|D|))
                                // The comment in 'usage' says "1/<density> bit to 0 if <density> < 0"
                                // If density is negative (e.g., -2): neg=1. tmp becomes 1 with prob 1/2. !tmp is 0. Bit is cleared.
                                // tmp becomes 0 with prob 1/2. !tmp is 1. Bit is set.
                                // This logic means: if density < 0, it sets the bit to 0 with probability 1/|density|.
                                // So, it sets the bit to 1 with probability 1 - 1/|density|.
                                // Let's re-verify:
                                // If density is -D (D>0): neg=1. `(lrand48() >> 16) % D`.
                                // `tmp` (pre-negation) = 1 with prob 1/D (sets bit), = 0 with prob (D-1)/D.
                                // `tmp` (post-negation) = `!tmp` (pre-negation).
                                // So, if pre-neg tmp was 1 (prob 1/D), post-neg tmp is 0. (Bit OFF)
                                // If pre-neg tmp was 0 (prob (D-1)/D), post-neg tmp is 1. (Bit ON)
                                // This means for negative density -D, the bit is turned OFF with probability 1/D.
                                // And turned ON with probability (D-1)/D.
                                // The usage string says: "1/<density> bit to 0 if <density> < 0"
                                // The current code: "bit is turned OFF with probability 1/|density|". This matches.
    }

    // If 'tmp' is 1, set the corresponding bit for the given 'plane'
    if (tmp) {
        // Calculate the linear index in 'tab': (x * side_length) + y
        // side_length is (1 << shift). So index is (x << shift) + y
        // Then, set the bit at the 'plane'-th position using bitwise OR.
        tab[(x << shift) + y] |= (1 << plane);
    } else if (density < 0) { // If tmp is 0 AND density was negative, explicitly clear the bit
        // This ensures the "set to 0" behavior for negative densities.
        // If tmp is 0 and density was positive, the bit remains unchanged (or 0 if initially 0).
        tab[(x << shift) + y] &= ~(1 << plane);
    }
    // Note: if density > 0 and tmp is 0, the bit is NOT explicitly cleared.
    // It relies on memset(tab,0,size) or previous state.
    // For "1/density bit to 1", it means if tmp is 0 (prob (D-1)/D), the bit is left as is.
    // This interpretation is fine if tab is initially 0.

    return 0; // Could be void
}

// Fills a specified region of a given plane with a certain density.
int fill(int shift, int plane, int region, int density) // Return type is int, could be void
{
    int side;     // Side length of the grid
    int startx;   // Starting x-coordinate of the region
    int starty;   // Starting y-coordinate of the region
    int endx;     // Ending x-coordinate of the region (exclusive)
    int endy;     // Ending y-coordinate of the region (exclusive)
    // int i;     // Loop counter, not used here
    int x;        // Loop counter for x-coordinate
    int y;        // Loop counter for y-coordinate

    side = 1 << shift; // Calculate side length
    if (!region) { // If region is 0, fill the entire frame
        startx = starty = 0;
        endx = endy = side;
    } else { // Otherwise, calculate a centered square region
        // Center of the grid is (side/2, side/2)
        // Start coordinates for a centered region of size 'region'
        startx = starty = side / 2 - region / 2;
        endx = endy = startx + region; // End coordinates

        // Bounds checking (optional, but good practice if region can be > side)
        if (startx < 0) startx = 0;
        if (starty < 0) starty = 0;
        if (endx > side) endx = side;
        if (endy > side) endy = side;
    }

    // Iterate over the specified region and call set() for each cell
    for (x = startx; x < endx; ++x) {
        for (y = starty; y < endy; ++y) {
            set(shift, plane, density, x, y);
        }
    }
    return 0; // Could be void
}

// Draws a horizontal line at row 'y' on a given 'plane'.
// 'region' and 'density' arguments are passed but 'density' is overridden to 1 in set().
// 'region' is not used by this function directly for coordinates.
int hline(int shift, int plane, int region, int density, int y_coord_arg) // Renamed 'y' to avoid conflict
{
    int i;        // Loop counter for columns
    int side;     // Side length of the grid

    side = 1 << shift; // Calculate side length
    // Iterate across all columns 'i' for the given row 'y_coord_arg'
    for (i = 0; i < side; ++i) {
        // Call set() for each cell on the line.
        // Density is hardcoded to 1 (always set the bit).
        // (y_coord_arg, i) maps to (row, column)
        set(shift, plane, 1, y_coord_arg, i);
    }
    return 0; // Could be void
}

// Draws a vertical line at column 'x' on a given 'plane'.
// 'region' and 'density' arguments are passed but 'density' is overridden to 1 in set().
// 'region' is not used by this function directly for coordinates.
int vline(int shift, int plane, int region, int density, int x_coord_arg) // Renamed 'x' to avoid conflict
{
    int i;        // Loop counter for rows
    int side;     // Side length of the grid

    side = 1 << shift; // Calculate side length
    // Iterate across all rows 'i' for the given column 'x_coord_arg'
    for (i = 0; i < side; ++i) {
        // Call set() for each cell on the line.
        // Density is hardcoded to 1 (always set the bit).
        // (i, x_coord_arg) maps to (row, column)
        set(shift, plane, 1, i, x_coord_arg);
    }
    return 0; // Could be void
}

// Array of Named_Func structures, mapping function names to function pointers.
// This allows functions to be called by name using the '-f' command-line option.
// The list is terminated by an entry with a NULL name and function pointer.
Named_Func funcs_names[] = {
    { "fill", fill },   // Maps string "fill" to the fill() function
    { "hline", hline }, // Maps string "hline" to the hline() function
    { "vline", vline }, // Maps string "vline" to the vline() function
    { 0, 0 },           // Terminator for the array
};
