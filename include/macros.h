#ifndef MACROS_H
#define MACROS_H

enum DEBUG_STATE { INACTIVE, ACTIVE };

#define DEBUG ACTIVE
/** @brief Prints to the console only if DEBUG = 1 **/
#define dbg(fmt, ...) do { \
  if (DEBUG == ACTIVE) \
    fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
} while (0)

#define dbg_no_info(fmt, ...) do { \
  if (DEBUG == ACTIVE) \
    fprintf(stderr, fmt, __VA_ARGS__); \
} while (0)

#endif