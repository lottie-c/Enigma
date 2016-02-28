#include <iostream>
#include <cstring>
#include "errors.h"
#include "reflector.h"
#include "helper.h"

using namespace std;

Reflector::Reflector(){

  reflector_ptr = NULL;
  reflector_length = 0;
}


Reflector::~Reflector(){
  if (!(reflector_ptr == NULL)){
    delete [] reflector_ptr;
  }
}

void Reflector::set_reflector_array(char reflector_data_file[]){

 
  reflector_length = count_integers(reflector_data_file, reflector_ptr);
  read_file_in(reflector_data_file, reflector_ptr);
}

int Reflector::reflector_output_position(int position) const{

  for (int i = 0; i <=reflector_length; i++){
    
    if (*(reflector_ptr + i) == position){
      if (i%2 == 0){
	position =*(reflector_ptr +(i+1));
	break;
      }else{
	position = *(reflector_ptr +i-1);
      }
    }
  }
  return (position);   
}

int Reflector::error_check() const{

  if (reflector_ptr == NULL){
    cerr <<"Reflector configuration not set."<< endl;
    return(ERROR_OPENING_CONFIGURATION_FILE);
  }

  if(!(reflector_length % 2 == 0)){
    cerr << "Incorrect (odd) number of parameters in reflector file.";
    return (INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  }
  if(reflector_length < 26){
    cerr << "Insufficient number of mappings in reflector file.";
    return (INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  }

  if(reflector_length > 26){
    cerr << "Number of mappings in reflector file is too high, "
	 <<"there must be exactly 13 pairs.";
    return (INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  }
 
  if(!check_for_duplicates(reflector_ptr, reflector_length)){
    cerr << "Invalid mapping in reflector file, each input must "
	 << "map to only one output.";
    return (INVALID_REFLECTOR_MAPPING);
  }
  return(0);
}
