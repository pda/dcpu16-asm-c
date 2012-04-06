#ifndef INCLUDED_FILE_H
#define INCLUDED_FILE_H

/**
 * Loads the contents of the specified file into a buffer,
 * which must be passed to free().
 */
char * load_file(char * path);

#endif
