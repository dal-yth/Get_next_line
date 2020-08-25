# Get_next_line

Function to read line by line from file descriptor.

##### Score 125/100

### Overview

The basic idea is that the function reads BUFF_SIZE amount of bytes from the file descriptor(fd), strjoins it to the final char array that will be returned and scans the array for '\n' characters. Reading continues as long as there is something to read and '\n' character has not been found. Upon finding the '\n' (or '\0' if we have reached the end of the file), we check it's position in the array and strdup the line up to '\n' (or '\0') to the array given as parameter.

The array where we strjoin all read characters is static. This allows us to remember the read position of some fd and continue from the same position later if the get_next_line is called again with the same fd. It is useful when reading from multiple fds is required, we can read from one, then from another, then keep reading from the positions where we stopped reading earlier.

### Note
This repository does not contain all the necessary files to run the get_next_line function.
If you wish to test my get_next_line, it has been merged with my libft and can be found below.

#### [My libft project](https://github.com/jmakela42/Libft)
