#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard{

 private:
  int *pb_ptr;
  int pb_length;

 public:
  /*constructor function for class Plugboard, sets pb_ptr 
    and pb_length to null.*/
  Plugboard();

  /*Destructor function for class Plugboard*/
  ~Plugboard();

  /*Function to  count integers in pb_data_file, set pb_length 
    to this number. ptr_to_pb_data_array points to an integer array of
    the plugboard configuration*/
  void set_pb_array(char pb_data_file[]);
  /*Function to check the plugboard configuration for errors and 
    return appropriate error code*/
  int error_check() const;
 
  /* position entered  is swapped with corresponding
     position on plugboard.*/
  int pb_output_position(int position) const;
};

#endif



