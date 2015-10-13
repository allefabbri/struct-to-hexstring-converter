// Copyright 2015 Stefano Sinigardi, Alessandro Fabbri
// for any question, please mail rommacc@yahoo.it

/************************************************************************
* This program is free software: you can redistribute it and/or modify  *
* it under the terms of the GNU General Public License as published by  *
* the Free Software Foundation, either version 3 of the License, or     *
* (at your option) any later version.                                   *
*                                                                       *
* This program is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
* GNU General Public License for more details.                          *
*                                                                       *
* You should have received a copy of the GNU General Public License     *
* along with this program.  If not, see <http://www.gnu.org/licenses/>. *
************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

typedef struct {
  int n;
  unsigned int un;
  float x;
} Mystruct;

int main(){

//////////////////////////////////////////// STRUCT TO HEX STRING ///////////////////////////////////////////////////// 

// Initializing the struct
  Mystruct mystruct;
  mystruct.n  = -12000;
  mystruct.un = 51000;
  mystruct.x  = (float) 9.876e-5;
  cout << "Mystruct contains " << sizeof(mystruct) << " bytes : n = " << mystruct.n << ", un = " << mystruct.un << ", x = " << mystruct.x << endl;

// Serializing the struct in a char*
  char * buffer;
  buffer = new char[sizeof(mystruct)];
  memcpy( buffer, &mystruct, sizeof(mystruct) );
//  for( size_t i=0; i< sizeof(mystruct); i++) printf("%02x ", (unsigned char) buffer[i]); printf("\n");

// Converting the char* to human readable form and then to std::string
  char * buffer_to_char;
  buffer_to_char = new char[2*sizeof(mystruct)+1];
  for( size_t i=0; i<sizeof(mystruct); i++){
    sprintf(&buffer_to_char[i * 2], "%02x", (unsigned char) buffer[i]);
  }
  buffer_to_char[2*sizeof(mystruct)] = '\0';
  std::string buffer_to_string( buffer_to_char );   
  cout << "Struct to string : " << buffer_to_string << endl; // now mystruct is saved as a string in hex format

// A little clean up
  delete[] buffer;
  delete[] buffer_to_char;
  buffer = buffer_to_char = NULL;


//////////////////////////////////////////// HEX STRING TO STRUCT /////////////////////////////////////////////////////

// Converting the human readable hex string to char*
  unsigned char * ubuffer;
  unsigned int * uibuffer;
  ubuffer = new unsigned char[buffer_to_string.size() / 2];
  uibuffer = new unsigned int[buffer_to_string.size() / 2];

  for (size_t i = 0; i<buffer_to_string.size() / 2; i++){
    sscanf(&(buffer_to_string.c_str()[i * 2]), "%02x", &uibuffer[i]);
    ubuffer[i] = (unsigned char) uibuffer[i];
  }

// Reconstruction of the struct
  Mystruct mystruct_cloned;
  memcpy( &mystruct_cloned, ubuffer, sizeof(mystruct_cloned) );
  cout << "Clone contains " << sizeof(mystruct_cloned) << " bytes : n = " << mystruct_cloned.n << ", un = " << mystruct_cloned.un << ", x = " << mystruct_cloned.x << endl;

// Or using a pointer
  Mystruct * pointer_to_struct;
  pointer_to_struct = (Mystruct *) ubuffer;
  cout << "Pointer contains " << sizeof(*pointer_to_struct) << " bytes : n = " << pointer_to_struct->n << ", un = " << pointer_to_struct->un << ", x = " << pointer_to_struct->x << endl;


// Another little clean up
  delete[] ubuffer;
  delete[] uibuffer;
  ubuffer = nullptr;
  uibuffer = nullptr;

  return 0;
}
