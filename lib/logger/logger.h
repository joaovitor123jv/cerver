#ifndef CERVER_LOGGER_H
#define CERVER_LOGGER_H

#include <stdio.h>

void info(const char *msg);
void error(const char *msg);
void debug(const char *msg);
void warn(const char *msg);

#endif /* CERVER_LOGGER_H */
