
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <bits/stdc++.h> // sharad

using namespace std;
unsigned long long BLOCKSIZE ;
unsigned long long L1_SIZE ;
unsigned long long L1_ASSOC; 
unsigned long long L2_SIZE ;
unsigned long long L2_ASSOC ;



// int tag[8]={0};
// int valid[8]={0};
// int dirty[8]={0};

// C++ program to convert
// Hexadecimal number to Binary
// function to convert
// Hexadecimal to Binary Number



// for (auto it = commands.begin(); it != commands.end(); ++it) {
//     command =commands[it];



//     }

    // vector<vector<string>> commands;


struct cache{
    vector<vector<int>> tag1;
	vector<vector<int>> tag2;
    vector<vector<int>> data1;
	vector<vector<int>> data2;
	vector<vector<int>>lru_l1;
	vector<vector<int>>lru_l2;
    vector<vector<string>> commands;


	
    
        
    int index_size_l1 = L1_SIZE/(BLOCKSIZE* L1_ASSOC );
    
	        

    int index_size_l2 = L2_SIZE/(BLOCKSIZE*L2_ASSOC);
   

	void go(){

	for (int i = 0 ; i<index_size_l1 ; i++){
		vector<int> t;
		for (int j=0 ; j< L1_ASSOC ; j++){
			t.push_back(0);

		}
		lru_l1.push_back(t);
	}
	for (int i = 0 ; i<index_size_l2 ; i++){
		vector<int> t;
		for (int j=0 ; j< L2_ASSOC ; j++){
			t.push_back(0);

		}
		lru_l2.push_back(t);
	}
	for (int i = 0 ; i<index_size_l1 ; i++){
		vector<int> t;
		for (int j=0 ; j< L1_ASSOC ; j++){
			t.push_back(-1);

		}
		tag1.push_back(t);
	}
	for (int i = 0 ; i<index_size_l2 ; i++){
		vector<int> t;
		for (int j=0 ; j< L2_ASSOC ; j++){
			t.push_back(-1);

		}
		tag2.push_back(t);
	}
	for (int i = 0 ; i<index_size_l1 ; i++){
		vector<int> t;
		for (int j=0 ; j< L1_ASSOC ; j++){
			t.push_back(0);

		}
		data1.push_back(t);
	}
	for (int i = 0 ; i<index_size_l2 ; i++){
		vector<int> t;
		for (int j=0 ; j< L2_ASSOC ; j++){
			t.push_back(0);

		}
		data2.push_back(t);
	}}









    int l1_read =0;
    int l1_read_miss=0;
    int l1_wrt=0;
    int l1_wrt_miss=0;
    int l1_miss_rate=0;
    int l1_wrtbk=0;
    int l2_read=0;
    int l2_read_miss=0;
    int l2_wrt=0;
    int l2_wrt_miss=0;
    int l2_miss_rate=0;
    int l2_wrtbk=0;

	void constructCommands(ifstream &file)
	{
		string line;
		while (getline(file, line))
			parseCommand(line);
		file.close();
	}
	void parseCommand(string line){
    vector<string> command ;
    boost::tokenizer<boost::char_separator<char>> tokens(line, boost::char_separator<char>(" \t"));
    for (auto&s : tokens){
        command.push_back(s);}

    commands.push_back(command);}


    cache(ifstream &file){
            constructCommands(file);
    
    
    }

    void read_req_l1(vector<string> commands){
		int address = stoi(commands[1],nullptr,16);

		int index_l1 = (address/BLOCKSIZE) % index_size_l1;
    	int tag_l1 = (address % BLOCKSIZE) % index_size_l1;
		int found = 0;
		for (int i:tag1[index_l1]){
			if (tag1[index_l1][i]==tag_l1){
					int it = i;
					found = 1;
				}
    		if (found == 1) {
				 // Check if the element was found
				l1_read++;
				for (int j=0;j<L1_ASSOC;j++){
					if (j!=it){
						lru[index_l1][j]++;

					}

				};				
				break;

    } }
		if ( found==0){
			l1_read_miss++;
			read_req_l2(vector<string> commander);
			for (int i:tag1[index_l1]);
			if (it != tag1[index_l1].end()){
				for (int j=0;j<L1_ASSOC;j++){
					if (j!=it){
						lru[index_l1][j]++;

					}

				}
				
				tag[index_l1][it] = commander[1];
			}
			else{
				for (int j=0;j<L1_ASSOC;j++){
					if (j!=it){
						lru[index_l1][j]++;

					}

				}
				

				//implement lru replacement
			}			
			}
		}
    

	void read_req_l2(vector<string> commander){
		int address = stoi(commander[1],nullptr,16);
		int offset = address % BLOCKSIZE;
		int index_l2 = (address/BLOCKSIZE) % index_size_l2;
    	int tag_l2 = (address % BLOCKSIZE) % index_size_l2;
        
		for (int i=tag2.begin(); i< tag2.end(); ++i){

			auto it =find(tag2[i].begin(), tag2[i].end(), tag_l2); // Search for the element
    		if (it != tag2.end()) { // Check if the element was found
        		l2_read++;
				l1_fetch(tag_l2);
				
				break;

    } }
		if  i==tag2.end(){
			// fetch from memory 

		}
		}
    void wrt_req_l1(vector<string> commander){
        int address = stoi(commander[1],nullptr,16);
        int offset = address % BLOCKSIZE;
        

        int index_size_l1 = size/(BLOCKSIZE*L1_ASSOC);
        int index_l1 = (address/BLOCKSIZE) % index_size_l1;
        int tag_l1 = (address % BLOCKSIZE) % index_size;

		for (i=tag1.begin(); i< tag1.end(); ++i){

			auto it =find(tag1[i].begin(), tag1[i].end(), tag_l1); // Search for the element
    		if (it != tag1.end()) { // Check if the element was found
				l1_wrt++;
				data[i][it]= 1;

				break;

    } }
		if i== tag1.end(){
			l1_wrt_miss++;
			read_req_l2(vector<string> commander)

		}
    }
        
    

};


    // void read_req_l1(vector<strings> commander){
    //     bin_ary = HexToBin(commander[1])

    // }


int main(int argc, char *argv[]){


    if (argc !=7) {
        std:: cerr << "wrong arguments!\n";
        return 0;
    }
    else{
    ifstream file(argv[6]);
    long long BLOCKIZE = stoi(argv[1]);
    long long L1_SIZE = stoi(argv[2]);
    long long L1_ASSOC = stoi(argv[3]);
    long long L2_SIZE = stoi(argv[4]);
    long long L2_ASSOC = stoi(argv[5]);
    }
    

}
