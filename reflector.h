#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector{ 

 private:
  int *reflector_ptr;
  int reflector_length;
 public:
  /*constructor function for class Reflector, sets
    reflector_ptr and reflector_length to null.*/
  Reflector();
  /*Destructor function for class Reflector*/
  ~Reflector();
  /*Function to  count integers in reflector_data_file, 
    set reflector_length to this number. ptr_to_reflector_data_array
    points to an integer array of
    the reflector configuration*/
  void set_reflector_array(char reflector_data_file[]);

  /* position entered is swapped with corresponding
     position on reflector.*/ 
  int reflector_output_position(int position) const;
  
  /*Function to check the reflector configuration for errors and 
    return appropriate error code*/
  int error_check() const;

};


#endif
