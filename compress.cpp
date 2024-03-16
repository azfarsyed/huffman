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
    
    vector<int> freqs(256, 0); 
    int currByte = 0; 
    
    while((currByte = input.read_byte()) != -1){ 
        freqs[currByte]++; 
    }
    input.reset();
    if(input.read_byte() != -1) { 
        HCTree HFT; 
        HFT.build(freqs); 
        int charCount = 0; 
        FancyOutputStream output(compressed); 
        unordered_set<int> values; 
        input.reset(); 
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
        while((currByte = input.read_byte()) != -1) { 
            HFT.encode(static_cast<char>(currByte), output);
        } 
    } else { 
        FancyOutputStream output(compressed); 
        return 0; 
    }

}

