#include <stdio.h>

#define printe(...) \
          do { \
            fprintf(stderr, "docker-include: " __VA_ARGS__); \
          } while (0)

#define die(exitNum, check, ...) \
          while (!check) { \
            printe(__VA_ARGS__); \
            exit(exitNum); \
          }

