#ifndef HELPER_H
#define HELPER_H

/*function to read the file at 'file_name' into the integer array 
  'file_array'*/
void read_file_in(char *file_name, int* file_array);


/*function to count the number of integers in the file 
  'file_name' and return an array of that length.*/
int count_integers(char *file_name, int* &array_created);

/*Function returns true if all machine configurations 
  are digits*/
bool check_data_is_numeric(int argc, char *argv[]);

/*Function returns true if all entries for machine 
  configurations are between 0 and 25 inclusive. */
bool check_indices_valid(int argc, char *argv[]);

/*Function to check array for duplicate entries, if they exist
  return false otherwise return true.*/
bool check_for_duplicates(int* array_ptr, int array_length);

/*Function to check if'array_length' is an even number, 
  an even length returns true otherwise function returns false */
bool length_is_even(int array_length);


#endif
