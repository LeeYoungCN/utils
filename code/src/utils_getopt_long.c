#include "utils_getopt_long.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BADCH '?'
#define BADARG ':'

const char *utils_optarg = NULL; /* argument associated with option */
int32_t utils_optind = 1;        /* index into parent argv vector */
int32_t utils_opterr = 1;        /* if error message should be printed */
int32_t utils_optopt = BADCH;

static int32_t utils_non_opt_start = -1;

static void move_non_opt_to_end(int32_t argc, char *const argv[])
{
    char *curr_argv = argv[utils_optind];
    char **args = (char **)argv;
    for (int32_t i = utils_optind; i < argc - 1; ++i) {
        args[i] = args[i + 1];
    }
    args[argc - 1] = curr_argv;
    if (utils_non_opt_start == -1) {
        utils_non_opt_start = argc - 1;
    } else {
        utils_non_opt_start--;
    }
}

static void move_all_non_opt_to_end(int32_t argc, char *const argv[])
{
    ++utils_optind;
    while (utils_optind < argc && utils_optind != utils_non_opt_start) {
        move_non_opt_to_end(argc, argv);
    }
}

static int32_t process_long_option(int32_t argc, char *const argv[], const char *optstring,
                                   const struct utils_option *longopts, int32_t *longindex)
{
    const char *curr_argv = argv[utils_optind];
    int32_t ans = 0;
    curr_argv += 2;
    size_t name_length = strcspn(curr_argv, "=");

    uint32_t i = 0;
    for (i = 0; longopts[i].name != NULL; ++i) {
        if (strlen(longopts[i].name) == name_length && strncmp(longopts[i].name, curr_argv, name_length) == 0) {
            break;
        }
    }

    if (longopts[i].name == NULL) {
        if (utils_opterr == 1 && optstring[0] != ':') {
            fprintf(stderr, "Invalid option: %s\n", curr_argv);
        }
        return BADCH;
    }

    ans = longopts[i].val;
    utils_optopt = longopts[i].val;
    if (longopts[i].has_arg == required_argument) {
        if (curr_argv[name_length] == '=') {
            utils_optarg = curr_argv + name_length + 1;
        } else if (utils_optind < (utils_non_opt_start == -1 ? argc : utils_non_opt_start) - 1) {
            utils_optarg = argv[++utils_optind];
        } else {
            if (utils_opterr == 1 && optstring[0] != ':') {
                fprintf(stderr, "Option requires an argument: %s\n", curr_argv);
            }
            ans = (optstring[0] == ':' ? BADARG : BADCH);
        }
    } else if (longopts[i].has_arg == optional_argument) {
        if (curr_argv[name_length] == '=') {
            utils_optarg = curr_argv + name_length + 1;
        }
    } else {
        utils_optarg = NULL;
    }
    if (longindex) {
        *longindex = (int32_t)i;
    }

    if (longopts[i].flag != NULL) {
        *longopts[i].flag = longopts[i].val;
        ans = 0;
    }

    return ans;
}

static int32_t process_sort_option(int32_t argc, char *const argv[], const char *optstring)
{
    const char *curr_argv = argv[utils_optind];
    int32_t ans = 0;
    curr_argv++;
    utils_optopt = (int32_t)curr_argv[0];
    ans = utils_optopt;
    const char *opt_point = strchr(optstring, utils_optopt);
    if (opt_point == NULL) {
        if (utils_opterr == 1 && optstring[0] != ':') {
            fprintf(stderr, "Invalid option: %s\n", curr_argv);
        }
        return BADCH;
    }
    if (opt_point[1] != '\0' && opt_point[1] == ':') {
        curr_argv++;
        if (curr_argv[0] != '\0') {
            utils_optarg = curr_argv;
        } else if (opt_point[2] != '\0' && opt_point[2] != ':' &&
                   utils_optind < (utils_non_opt_start == -1 ? argc - 1 : utils_non_opt_start - 1)) {
            utils_optarg = argv[++utils_optind];
        } else {
            if (utils_opterr == 1 && optstring[0] != ':') {
                fprintf(stderr, "Option requires an argument: %s\n", curr_argv);
            }
            ans = (optstring[0] == ':' ? BADARG : BADCH);
        }
    }
    return ans;
}

int32_t utils_getopt_long(int32_t argc, char *const argv[], const char *optstring, const struct utils_option *longopts,
                          int32_t *longindex)
{
    if (utils_optind >= argc || (utils_non_opt_start != -1 && utils_optind >= utils_non_opt_start)) {
        return -1;
    }

    bool need_loop = false;
    int32_t ans = -1;
    utils_optarg = NULL;
    do {
        need_loop = false;
        const char *curr_argv = argv[utils_optind];
        if (strcmp(curr_argv, "--") == 0) {
            move_all_non_opt_to_end(argc, argv);
            break;
        }

        if (curr_argv[0] == '-' && curr_argv[1] == '-' && curr_argv[2] != '\0') {
            /* long  option. */
            ans = process_long_option(argc, argv, optstring, longopts, longindex);
        } else if (curr_argv[0] == '-' && curr_argv[1] != '\0') {
            /* sort option */
            ans = process_sort_option(argc, argv, optstring);
        } else {
            move_non_opt_to_end(argc, argv);
            need_loop = true;
        }
    } while (need_loop && utils_optind < argc && utils_optind != utils_non_opt_start);

    utils_optind = (utils_optind + 1 > utils_non_opt_start ? utils_non_opt_start : utils_optind + 1);

    return ans;
}
