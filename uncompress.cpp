#include "HCTree.hpp"
#include <vector>
#include <iostream>
#include <string> 
#include "Helper.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if(argc == 1) { 
        error("Please enter a valid string"); 
    }
    FancyInputStream input(argv[1]);  
    char* uncompressed = argv[2];  
    if(input.read_byte() != -1) { 
        vector<int> freqs(256, 0);
        int currByte = 0;  
        input.reset(); 
        while((currByte = input.read_byte()) != '\0') { 
            freqs[currByte] += input.read_int(); 
        }
        HCTree HFT; 
        HFT.build(freqs); 

        int count = input.read_int(); 

        FancyOutputStream output(uncompressed); 

        unsigned char symbol; 
        int i = 0; 
        while(i < count) { 
            symbol = HFT.decode(input); 
            output.write_byte(symbol); 
            i++; 
        }  
    } else { 
        FancyOutputStream output(uncompressed); 
    }

}

