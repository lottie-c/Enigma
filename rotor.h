#ifndef ROTOR_H
#define ROTOR_H


class Rotor{

 private:

  int *rotor_ptr;
  int *notch_ptr;
  int number_of_notches;
  int offset_from_zero;

 public:
  /*constructor function for class Rotor, sets rotor_ptr
    and notch_ptr to null, and sets number_of_notches and 
    offset_from_zero to zero.*/
  Rotor();

  /*Destructor function for class Rotor*/
  ~Rotor();

  /*Function to count the integers in rotor_data_file, and make an array
    that data. If there are notches on the rotor notch_ptr is set to the 
    start of these. offset_from_zero is set to _start_position.*/
  void set_rotor_array(char rotor_data_file[], int _start_position);

  /*Function "rotates" the rotor, adding one to offset_from_zero and
    ensuring that offset_from_zero remains between 0 and 25 inclusive*/
  void rotate();
  
  /*Function takes any number and adjusts it so that 
    it sits in the correct position in a rotating rotor.*/
  int recalibrate(int number);
  
  /*Function returns true if the character aligned with the top of the
    rotor is a notch and false otherwise*/
  bool at_notch() const;

  /*Function takes input 'position'  and maps it forwards through
    the rotor returning to the user the output position, to be used
    when mapping through rotors from the plugboard to the reflector*/
  int rotor_output_forwards(int position);

  /*Function takes input 'position'  and maps it backwards through
    the rotor returning to the user the output position, to be used
    when mapping through rotors from the reflector to the plugboard*/
  int rotor_output_backwards(int position);
  
  /*Function to check the rotor configuration for errors and 
    return appropriate error code*/
  int error_check() const;
};


#endif




