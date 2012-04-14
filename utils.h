#ifndef INCLUDED_UTILS_H
#define INCLUDED_UTILS_H

#define CRASH(message) crash(message, __FILE__, __LINE__);

/**
 * Prints failure message to STDOUT, exits with failure code.
 */
void crash(char * message, char * file, int line);

#endif
