#include <iostream>
#include <cstring>
#include "errors.h"
#include "rotor.h"
#include "helper.h"
using namespace std;

static int MAX=26;

Rotor::Rotor(){
  rotor_ptr = NULL;
  notch_ptr = NULL;
  number_of_notches = 0;
  offset_from_zero = 0;
}

Rotor::~Rotor(){
  if (!(rotor_ptr == NULL)){
    delete [] rotor_ptr;
  }
}

void Rotor::set_rotor_array(char rotor_data_file[], int _start_position)
{
  offset_from_zero = _start_position;
  number_of_notches = count_integers(rotor_data_file, rotor_ptr) - MAX;
  notch_ptr = rotor_ptr + MAX; 
  read_file_in(rotor_data_file, rotor_ptr);
 
}

int Rotor::recalibrate(int number){
 
  if (number > 25){
    number = number % 26;
    return(number);
  }
  if (number < 0){
    number = (number % 26) + 26;
    return(number);
  }
  return(number);
}

void Rotor::rotate(){
   
  offset_from_zero++;
  offset_from_zero = recalibrate(offset_from_zero);

}

bool Rotor::at_notch() const{

  for(int i = 0; i < number_of_notches; i++){
    if( *(notch_ptr + i) == offset_from_zero){
      return true;
    }
  }
  return false;
}

int Rotor::rotor_output_forwards(int position){

  int exit_position, original_mapping;
  /*take rotation into accout by adjusting according to 
    offset_from_zero*/
  original_mapping = recalibrate(position + offset_from_zero);
  exit_position = *(rotor_ptr + original_mapping) - offset_from_zero;
  exit_position = recalibrate(exit_position);
  return (exit_position);
}

int Rotor::rotor_output_backwards(int position){
 
  int exit_position, original_mapping;
  /*take rotation into accout by adjusting according to 
    offset_from_zero*/
  original_mapping = recalibrate(position + offset_from_zero);
  for (int i = 0; i < MAX; i++){
    if (*(rotor_ptr + i) == original_mapping){
      exit_position = i - offset_from_zero;
    }    
  }
  exit_position = recalibrate(exit_position);
  return (exit_position);
}

int Rotor::error_check() const{

  if (rotor_ptr == NULL){
    cerr <<"Rotor configuration not set for file "<< endl;
    return(ERROR_OPENING_CONFIGURATION_FILE);
  }

  
  if(number_of_notches < 0 ){
    cerr <<"Not all inputs mapped in ";
    return(INVALID_ROTOR_MAPPING);
  }
  
  if(!check_for_duplicates(rotor_ptr, MAX-1)){
    cerr <<"Attempted mapping of an input to more than one output in ";
    return(INVALID_ROTOR_MAPPING);
  }  
  
  return 0;
}

