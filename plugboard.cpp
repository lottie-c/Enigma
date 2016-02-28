#include <iostream>
#include <cstring>
#include "errors.h"
#include "plugboard.h"
#include "helper.h"
using namespace std;

Plugboard::Plugboard(){
  pb_ptr = NULL;
  pb_length = 0;
  
}

Plugboard::~Plugboard(){
  if (!(pb_ptr == NULL)){
    delete [] pb_ptr;
  }
}

void Plugboard::set_pb_array(char pb_data_file[]){
  
  pb_length = count_integers(pb_data_file, pb_ptr);
  read_file_in(pb_data_file, pb_ptr);
}


int Plugboard::error_check() const{

  if(!length_is_even(pb_length)){
    cerr <<"Incorrect number of parameters in plugboard file." << endl;
    return (INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
  }
  
  if(pb_length > 26){
    cerr <<"Incorrect number of parameters in plugboard file." << endl;
    return (INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
  }

  if(!check_for_duplicates(pb_ptr, pb_length)){
    cerr << "Invalid mapping in plugboard file (Cannot map "
	 <<"one input to more than one output)." << endl;
    return (IMPOSSIBLE_PLUGBOARD_CONFIGURATION);      
  }
  return(0);
}

int Plugboard::pb_output_position(int position) const{
    
  for (int i = 0; i<=pb_length; i++){
    
    if (*(pb_ptr + i) == position){
      if (i%2 == 0){
	position =*(pb_ptr +(i+1));
	break;
      }else{
	position = *(pb_ptr +i-1);
      }
    }
  }
  return (position);
}

