#ifndef IO_H
#define IO_H

/**
 * @brief Reads and returns blink source file.
 * 
 * @param[in] filepath String of path to source file.
 * @return buffer Returns read characters of blink 
 *         source file. Otherwise, the program will print an error and exit.
 */
char* get_file_contents(const char* filepath);

#endif
