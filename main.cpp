#include <iostream>
#include <fstream>
#include <cstring>
#include "errors.h"
#include "helper.h"
#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"



using namespace std;

int main(int argc, char *argv[]){

  /*check if there are enough arguments, at least a plugboard,
    a reflector*/
  if (argc < 3){

    cerr << "usage: enigma plugboard-file reflector-file"
	 <<"(<rotor-file>* rotor-positions)?"
	 << endl;
    return (INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }

  //Go thought files in argv, check that they are well formed.
  for (int i = 1; i <= argc; i++){

    if(!check_indices_valid(i, argv)){
      cerr << "A value less than 0 of greater than"
	   <<"25 was found in file " 
	   << argv[i] <<endl;
      return (INVALID_INDEX);
    }
    
    if (!check_data_is_numeric(i, argv)){
      cerr << "Non-numeric character in file "
	   << argv[i] <<endl;
      return(NON_NUMERIC_CHARACTER);
    }
    
  }
  
  typedef char *CharPtrType;
  CharPtrType plugboard_file, reflector_file;
 
  plugboard_file =argv[1];
  reflector_file = argv[2];
 
  //Construct, initialise and error check plugboard
  Plugboard plugboard;

  plugboard.set_pb_array(plugboard_file);
  int error_code_pb = plugboard.error_check();
  if (error_code_pb > 0){
    return (error_code_pb);
  }

  //Construct, initialise and error check reflector
  Reflector reflector;
  reflector.set_reflector_array(reflector_file);
  int error_code_reflector = reflector.error_check();
  if (error_code_reflector > 0){
    return (error_code_reflector);
  }

  int number_of_rotors, number_of_rotor_positions;

  if(argc > 3){
    number_of_rotors = argc - 4;
  }else{
    number_of_rotors = 0;
  }

  /*If there are one or more rotors make rotor_positions array,
    specifying the starting position of each rotor*/
  typedef Rotor *rotor_ptr_type;
  rotor_ptr_type *rotors = new rotor_ptr_type[number_of_rotors];
  CharPtrType rotor_position_file, rotor_file;

  if(number_of_rotors > 0){

    rotor_position_file = argv[argc-1];
   
    int *rotor_positions;
    number_of_rotor_positions = 
      count_integers(rotor_position_file, rotor_positions);
    read_file_in(rotor_position_file, rotor_positions);

    if(rotor_positions == NULL){
      cerr << "Error opening file: " << rotor_position_file << endl;
      return (ERROR_OPENING_CONFIGURATION_FILE);
    }

    //Construct, initialise and error check rotors
    for (int i = 0; i < number_of_rotors ; i++){
      rotor_file = argv[3 + i];
      rotors[i] = new Rotor; 
      rotors[i]->set_rotor_array(rotor_file, *(rotor_positions + i));
  
      int error_code_rotor = rotors[i]->error_check();
      if (error_code_rotor > 0){
	cerr << rotor_file <<endl;
	return (error_code_rotor);
      }
    } 
  } else {
    number_of_rotor_positions = 0;
  }

  if (number_of_rotor_positions < number_of_rotors){
    cerr << "A starting position has not been specified for all rotors."
	 <<endl;
    return (NO_ROTOR_STARTING_POSITION);
  }


  char character;
  
  cin >> ws >>character;

  while(!cin.eof()){
    
    if ((character <'A')||(character > 'Z')){
      cerr << character << " is not a valid input character" 
	   <<" (input characters must be upper case letters A-Z)!" << endl;
      return(INVALID_INPUT_CHARACTER);
    }
     
    //convert character to it's integer equivalent-A=0...Z=25.
    int position = static_cast<int>(character) - 65;
 
    if (number_of_rotors > 0){
      rotors[number_of_rotors - 1]->rotate();
      /*rotate the first rotor, if it is at a notch rotate
	the next one along and so on for all rotors*/
      for (int i = number_of_rotors - 1 ; i > 0; i--){
	if (rotors[i]->at_notch()){
	  rotors[i-1]->rotate();
	}
      }
    }
    
    /*Position is input to plugboard and output to give
      new position.*/
    position = plugboard.pb_output_position(position);
   
    /*Position is input to each rotor and output to give
      new position in turn. Direction of mapping is
      plugboard to reflector */
    if (number_of_rotors > 0){
      for(int i = number_of_rotors - 1 ; i >= 0; i--){
	position = rotors[i]->rotor_output_forwards(position); 
      } 
    }
  
    /*Position is input to reflector and output to give
      new position.*/
    position = reflector.reflector_output_position(position);
    
    /*Position is input to each rotor and output to give
      new position in turn. Direction of mapping is
      reflector to plugboard */
    if (number_of_rotors >0){
      for(int i = 0; i<number_of_rotors; i++){
	position = rotors[i]->rotor_output_backwards(position);
      }
    }

    /*Position is input to plugboard and output to give
      new position.*/
    position = plugboard.pb_output_position(position);
    
    //return position to its character equivalent.
    character = static_cast<char>(position + 65);
    
    cout << character;
 
    cin >> ws >> character;
    
    
  }
  

  if (number_of_rotors > 0){
    for (int i=0; i < number_of_rotors; i++){
      delete rotors[i];
    }
  }

  delete [] rotors;

  return (NO_ERROR);


}


