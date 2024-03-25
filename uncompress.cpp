#include "HCTree.hpp"
#include <vector>
#include <iostream>
#include <string> 
#include "Helper.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if(argc == 1) { // if only one argument 
        error("Please enter a valid string"); 
    }
    FancyInputStream input(argv[1]);  
    char* uncompressed = argv[2];  
    
    if(input.read_byte() != -1) {     
        vector<int> freqs(256, 0);
        int currByte = 0;  
        input.reset(); 

        //parse through file till end of header file which contains the frequnecies of each letter
        while((currByte = input.read_byte()) != '\0') { 
            freqs[currByte] += input.read_int(); 
        }
        HCTree HFT; 
        HFT.build(freqs); 

        //next int is the number of characters in the file
        int count = input.read_int(); 

        FancyOutputStream output(uncompressed); 

        unsigned char symbol; 
        int i = 0; 
        //content after header which includes the encoded data: this data gets decoded through the decode function and written to the output file
        while(i < count) { 
            symbol = HFT.decode(input); 
            output.write_byte(symbol); 
            i++; 
        }  
    } else { 
        FancyOutputStream output(uncompressed); 
    }

}

