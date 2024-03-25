#include "HCTree.hpp"
#include <vector>
#include <iostream>
#include <string> 
#include <unordered_set>
#include "Helper.hpp"

int main(int argc, char* argv[]) { 
    if(argc == 1) { 
        error("Please enter a valid string"); 
    }
    FancyInputStream input(argv[1]);
    char* compressed = argv[2]; 

    // creates a frequency int vector of characters ranging from 0-255(ASCII) 
    vector<int> freqs(256, 0); 
    int currByte = 0; 

    // goes through the input and updates frequencies of each char
    while((currByte = input.read_byte()) != -1){ 
        freqs[currByte]++; 
    }
    input.reset();

    if(input.read_byte() != -1) { 
        HCTree HFT; 
        HFT.build(freqs); 
        int charCount = 0; 
        FancyOutputStream output(compressed);  // initializes output stream 
        
        unordered_set<int> values; 
        input.reset(); 

        // appends character and frequency of each character to the compressed file so that it may be uncompressed
        while((currByte = input.read_byte()) != -1){ 
            if(values.find(currByte) == values.end()) {
                values.insert(currByte); 
                output.write_byte(static_cast<char>(currByte)); 
                output.write_int(freqs[currByte]); 
            }
            charCount += 1;
        }
        output.write_byte('\0'); 
        output.write_int(charCount);  
        input.reset(); 

        // calls encode function to encode regular file using huffman scheme 
        while((currByte = input.read_byte()) != -1) { 
            HFT.encode(static_cast<char>(currByte), output);
        } 
    } else {  // if nothing in file 
        FancyOutputStream output(compressed); 
        return 0; 
    }

}

