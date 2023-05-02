
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
unsigned long long L1_ASSSOC; 
unsigned long long L2_SIZE ;
unsigned long long L2_ASSOC ;



// int tag[8]={0};
// int valid[8]={0};
// int dirty[8]={0};

// C++ program to convert
// Hexadecimal number to Binary
// function to convert
// Hexadecimal to Binary Number
void HexToBin(string hexdec)
{
	//Skips "0x" if present at beggining of Hex string
	size_t i = (hexdec[1] == 'x' || hexdec[1] == 'X')? 2 : 0;

	while (hexdec[i]) {

		switch (hexdec[i]) {
		case '0':
			cout << "0000";
			break;
		case '1':
			cout << "0001";
			break;
		case '2':
			cout << "0010";
			break;
		case '3':
			cout << "0011";
			break;
		case '4':
			cout << "0100";
			break;
		case '5':
			cout << "0101";
			break;
		case '6':
			cout << "0110";
			break;
		case '7':
			cout << "0111";
			break;
		case '8':
			cout << "1000";
			break;
		case '9':
			cout << "1001";
			break;
		case 'A':
		case 'a':
			cout << "1010";
			break;
		case 'B':
		case 'b':
			cout << "1011";
			break;
		case 'C':
		case 'c':
			cout << "1100";
			break;
		case 'D':
		case 'd':
			cout << "1101";
			break;
		case 'E':
		case 'e':
			cout << "1110";
			break;
		case 'F':
		case 'f':
			cout << "1111";
			break;
		case '.':
			cout << ".";
			break;
		default:
			cout << "\nInvalid hexadecimal digit "
				<< hexdec[i];
		}
		i++;
	}
}

// driver code
// int main()
// {

// 	// Get the Hexadecimal number
// 	string hexdec = "1AC5";

// 	// Convert HexaDecimal to Binary
// 	cout << "";HexToBin(hexdec);

// 	return 0;
// }
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

    commands.push_back(command);
}
// for (auto it = commands.begin(); it != commands.end(); ++it) {
//     command =commands[it];



//     }

    // vector<vector<string>> commands;


struct cache{
    vector<vector<string>> tag;
    vector<vector<int>> data;
    vector<vector<string>> commands;
    int l1_read;
    int l1_read_miss;
    int l1_wrt;
    int l1_wrt_miss;
    int l1_miss_rate;
    int l1_wrtbk;
    int l2_read;
    int l2_read_miss;
    int l2_wrt;
    int l2_wrt_miss;
    int l2_miss_rate;
    int l2_wrtbk;


    cache(ifstream &files){
            constructCommands(file);
    
    
    }
    size = BLOCKSIZE*assoc*index

    void read_req_l1(vector<strings> commander){
        int address = stoi(commander[1],nullptr,16);
        int offset = address % BLOCKSIZE;
        

        int index_size_l1 = size/(BLOCKSIZE*L1_ASSOC);
        int index_l1 = (address/BLOCKSIZE) % index_size_l1;
        int tag_l1 = (address % BLOCKSIZE) % index_size;
        
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
