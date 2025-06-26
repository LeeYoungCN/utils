#ifndef UTILS_GETOPT_LONG_H
#define UTILS_GETOPT_LONG_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

static const int32_t no_argument = 0;
static const int32_t required_argument = 1;
static const int32_t optional_argument = 2;

extern const char *utils_optarg;
extern int32_t utils_optopt;
extern int32_t utils_opterr;
extern int32_t utils_optind;

struct utils_option {
    const char *name;
    int32_t has_arg;  // no_argument/required_argument/optional_argument
    int32_t *flag;
    int32_t val;
};

/*
 * utils_getopt_long - Parse command-line options, including both short and long options.
 *
 * This function processes command-line arguments, supporting both traditional
 * single-character options (e.g., -a) and GNU-style long options (e.g., --option).
 * It is compatible with the POSIX getopt interface and extends it to handle long options.
 *
 * Parameters:
 *   argc       - The number of arguments in argv.
 *   argv       - The argument vector.
 *   optstring  - A string containing the legitimate option characters.
 *                If a character is followed by a colon, the option requires an argument.
 *                If the first character is a colon, silent error reporting is enabled.
 *   longopts   - Pointer to an array of struct utils_option, describing the long options.
 *   longindex  - If not NULL, set to the index of the long option relative to longopts.
 *
 * Returns:
 *   The option character if a short option is found.
 *   The value specified in the longopts struct if a long option is found.
 *   0 if a long option sets a flag.
 *   -1 when all options have been processed.
 *   '?' (BADCH) for an unrecognized option character.
 *   ':' (BADARG) if an option requiring an argument is missing its argument and
 *      optstring starts with ':'.
 *
 * Side Effects:
 *   Updates the global variables:
 *     utils_optopt   - Index of the next element to be processed in argv.
 *     utils_optarg   - Argument value for the current option, if applicable.
 *     utils_optopt   - Option character that caused an error, if any.
 *     utils_opterr   - If nonzero, error messages are printed to stderr.
 *
 * Notes:
 *   - Non-option arguments are moved to the end of argv.
 *   - The function handles the special "--" argument to indicate the end of options.
 *   - If a long option is not recognized, an error is reported.
 *   - The function is not thread-safe due to its use of static variables.
 */
int utils_getopt_long(int argc, char *const argv[], const char *optstring, const struct utils_option *longopts,
                      int *longindex);

#ifdef __cplusplus
}
#endif

#endif  // UTILS_GETOPT_LONG_H
