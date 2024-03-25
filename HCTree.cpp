#include "HCTree.hpp"
#include <vector>
#include <iostream>
#include <queue>
#include <string> 
#include "Helper.hpp"


void HCTree::build(const vector<int>& freqs) { 
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;  //intializes min heap priority queue 
    for(unsigned int i = 0; i < freqs.size(); i++) {         
        //order characters based on frequencies via min heap 
        
        if(freqs[i] != 0) { 
            HCNode* curr = new HCNode(freqs[i], static_cast<char>(i)); 
            leaves[i] = curr; 
            pq.push(curr); 
        }
    }
    while (pq.size() > 1) { // goes through each leaf node(characters) of priority and builds a huffman tree 
        HCNode* left = pq.top();
        pq.pop();
        HCNode* right = pq.top();
        pq.pop();

        HCNode* parent = new HCNode(left->count + right->count, right->symbol); 
        parent->c0 = left;
        left->p = parent; 
        parent->c1 = right;
        right->p = parent; 

        pq.push(parent);
    }
    if (pq.size() == 1) {
        root = pq.top();
    }
}
//recursively deletes tree
void deleteTree(HCNode* node) {
    if (node) {
        deleteTree(node->c0);
        deleteTree(node->c1);
        delete node;
    }
}

HCTree::~HCTree() {
    if (root != nullptr) {
        deleteTree(root);
        root = nullptr;
    }
}

/**
  * Write to the given FancyOutputStream the sequence of bits coding the given symbol.
  * PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
  */

void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const { 
    HCNode* curr = leaves[symbol]; 
    string code = ""; 

    // goes through HFT and appends 0 or 1 based on left/right traversal 
    while (curr != root) { 
        if(curr->p->c0 == curr) { 
            code = '0' + code; 
        } else { 
            code = '1' + code; 
        }
        curr = curr->p; 
    }

    //writes encoded text to the output file
    int toInt = 0; 
    for(unsigned int i = 0; i < code.length(); i++) { 
        toInt = code[i] - '0'; // turn into integer 0 or 1
        out.write_bit(toInt); 
    }
}

/**
  * Write to the given FancyInputSteam the decoded text file.
  */
unsigned char HCTree::decode(FancyInputStream & in) const { 
    HCNode* curr = root; 
    // traverses through HFT to get to desired leaf node(character)
    while(curr->c0 != nullptr && curr->c1 != nullptr) { 
        if(in.read_bit() == 0){ 
            curr = curr->c0;
        } else { 
            curr = curr->c1; 
        }
    }
    return curr->symbol; 
}
