#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <bitset>
#include<bits/stdc++.h>
using namespace std;
class CacheLine {
public:
    std::vector<int> lru;
    std::vector<std::string> tag;

    CacheLine() : tag(64, "") {}

    void updateLRU(int index) {
        lru.erase(std::remove(lru.begin(), lru.end(), index), lru.end());
        lru.push_back(index);
    }
};

bool check(std::unordered_map<std::string, CacheLine>& cache, const std::string& command, int cacheSizeKB, int associativity,int blockSize) {
    std::string address = command.substr(4, 8);
    std::bitset<32> addressBits(std::stoul(address, nullptr, 16));

    //int blockSize = 16; // Block size is 4 bytes

    int numSets = (cacheSizeKB * 1024) / (blockSize * associativity); // Number of sets
    int numIndexBits = log2(numSets); // Calculate the number of index bits
    int numByteOffsetBits = log2(blockSize); // 2 bits for 4-byte block size
    int numTagBits = 32 - numIndexBits - numByteOffsetBits; // Remaining bits for the tag

    // Extract bits for byte offset, index, and tag
    std::string byteOffset = addressBits.to_string().substr(32 - numByteOffsetBits, numByteOffsetBits);
    std::string index = addressBits.to_string().substr(32 - numByteOffsetBits - numIndexBits, numIndexBits);
    std::string tag = addressBits.to_string().substr(0, numTagBits);

    CacheLine& line = cache[index];

    bool hit = false;
    auto it = std::find(line.tag.begin(), line.tag.end(), tag);
    if (it != line.tag.end()) {
        int ind = std::distance(line.tag.begin(), it);
        hit = true;
        line.updateLRU(ind);
    } else {
        if (line.lru.size() == associativity) {
            int ind = line.lru.front();
            line.lru.erase(line.lru.begin());
            line.lru.push_back(ind);
            line.tag[ind] = tag;
        } else {
            int ind = line.lru.size();
            line.lru.push_back(ind);
            line.tag[ind] = tag;
        }
    }
    return hit;
}

int main() {
    vector<string> v={"twolf.trace","gcc.trace","gzip.trace","mcf.trace","swim.trace"};
     int sz=0;
     int associativity=0;
     int blocksize=0;
cout<<"block size-> ";
cin>>blocksize;
    cout<<"size of cache ";
    cin>>sz;
    cout<<" associativity-> ";
    cin>>associativity;

    
    cout<<"for "<<associativity<<"-way"<<endl;
    for(auto &s:v) {    
    std::unordered_map<std::string, CacheLine> cache;
    std::ifstream file(s);
   
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::string command;
    int miss = 0;
    int total = 0;

    while (std::getline(file, command)) {
        total++;
        bool hit = check(cache, command,sz,associativity,blocksize);
        if (!hit) {
            miss++;
        }    
    }

    file.close();

    std::cout <<"cache size-> "<<sz<<" "<<s<<"-> "<< "Miss Rate = " << (100.0 * miss) / total << "%" << std::endl;
    }

    return 0;
}
