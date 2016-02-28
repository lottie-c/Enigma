#include <iostream>
#include <fstream>

using namespace std;

bool check_data_is_numeric(int argc, char *argv[]){

  char character;

  for (int i=1; i <= argc; i++){
    ifstream in_stream(argv[i]);
    
    in_stream >> ws >> character;
    while (!in_stream.eof()){
      if (!isdigit(character)){
	return false;
      }
      in_stream >> ws >> character;
    }
  }
  return true;
}

bool check_indices_valid(int argc, char *argv[]){
  
  int n;

  for(int i=1; i < argc; i++){
    
    ifstream in_stream(argv[i]);
    in_stream >> n;
   
    while(!in_stream.eof()){
      if ((n < 0) || (n > 25)){
	return false;
      }
      in_stream >> n;
    }
  }
  return true;
}


int count_integers(char *file_name, int* &array_created){
  
  ifstream in_stream;
  int n, count = 0;

  in_stream.open(file_name);
  in_stream >> n;
  while (!in_stream.eof()){
    count++;
    in_stream >> n;
  }
  
  array_created = new int[count];

  return (count); 
}


void read_file_in(char file_name[],int* file_array){
  
  ifstream in_stream;
  int n;
 
  in_stream.open(file_name);
  in_stream >> n;
 
  for (int i = 0; !in_stream.eof();i++){ 
  
    *(file_array + i) = n;
    in_stream >> n;
        
  }  
}


bool check_for_duplicates(int* array_ptr, int array_length){
  for (int i = 0; i < array_length - 1 ; i++){
    for (int j = i + 1; j < array_length; j++){
      if (*(array_ptr + i)== *(array_ptr + j)){
	return false;
      }
    } 
  }
  return true;
}

bool length_is_even(int array_length){
  if (!(array_length % 2 == 0)){
    return false;
  }
  return true;
}

