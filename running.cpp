#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <bits/stdc++.h>
#include<algorithm>

using namespace std;

struct cache{

    long long BLOCKSIZE; 
    long long L1_SIZE; 
    long long L1_ASSOC;  
    long long L2_SIZE; 
    long long L2_ASSOC; 
    long long index_size_l1; 
    long long index_size_l2;  


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

    int reads;
    int writes;

    vector<vector<long long>> tag1;
	vector<vector<long long>> tag2;
    vector<vector<int>> data1;
	vector<vector<int>> data2;
	vector<vector<int>>lru_l1;
	vector<vector<int>>lru_l2;




    cache(ifstream &file,long long BLOCKSIZE_0,long long L1_SIZE_0,long long L1_ASSOC_0,long long L2_SIZE_0,long long L2_ASSOC_0)
    {
        constructCommands(file);
    
    BLOCKSIZE = BLOCKSIZE_0;
    L1_SIZE = L1_SIZE_0;
    L1_ASSOC = L1_ASSOC_0; 
    L2_SIZE = L2_SIZE_0;
    L2_ASSOC = L2_ASSOC_0;
    index_size_l1 = L1_SIZE_0/(BLOCKSIZE_0*L1_ASSOC_0);
    index_size_l2 = L2_SIZE_0/(BLOCKSIZE_0*L2_ASSOC_0);    
    }


void act(){
	for (int i = 0 ; i<index_size_l1 ; i++){
		vector<int> t;
		for (int j=0 ; j< L1_ASSOC ; j++){
			t.push_back(0);

		}
		lru_l1.push_back(t);
	}
	for (int i = 0 ; i<index_size_l2 ; i++){
		vector<int> t1;
		for (int j=0 ; j< L2_ASSOC ; j++){
			t1.push_back(0);

		}
		lru_l2.push_back(t1);
	}
	for (int i = 0 ; i<index_size_l1 ; i++){
		vector<long long> t2;
		for (int j=0 ; j< L1_ASSOC ; j++){
			t2.push_back(-1);

		}
		tag1.push_back(t2);
	}
	for (int i = 0 ; i<index_size_l2 ; i++){
		vector<long long> t3;
		for (int j=0 ; j< L2_ASSOC ; j++){
			t3.push_back(-1);

		}
		tag2.push_back(t3);
	}
	for (int i = 0 ; i<index_size_l1 ; i++){
		vector<int> t4;
		for (int j=0 ; j< L1_ASSOC ; j++){
			t4.push_back(0);

		}
		data1.push_back(t4);
	}
	for (int i = 0 ; i<index_size_l2 ; i++){
		vector<int> t5;
		for (int j=0 ; j< L2_ASSOC ; j++){
			t5.push_back(0);

		}
		data2.push_back(t5);
	}}

    void constructCommands(ifstream &file)
        {
            string line;
            while (getline(file, line))
                parseCommand(line);
            file.close();
        }
    void parseCommand(string line)
        {
        vector<string> command ;
        boost::tokenizer<boost::char_separator<char>> tokens(line, boost::char_separator<char>(" \t"));
        for (auto&s : tokens){
            command.push_back(s);}

        commands.push_back(command);
        }

    void executeCommands(){
        for(int i = 0 ; i < commands.size() ; i++){
            if(commands[i][0]=="r"){
                read_req_l1(commands[i]);
                reads++;
            }
            else{
                write_req_l1(commands[i]);
                writes++;
            }
        }
    }

    bool isTag(vector<vector<long long>> tag_list , long long tag, long long index){
        bool result = false;
        for(int i = 0;i<tag_list[index].size();i++){
            if(tag_list[index][i]==tag){
                result = true;
                break;
            }
        }
        return result;

    }

    void stats(){
        cout<<reads<<endl;
        cout<<writes<<endl;
    }


    void write_req_l1(vector<string> commander)
    {
            long long address = stoi(commander[1],nullptr,16);
            long long offset = address % BLOCKSIZE;
            // int index_size_l1 = size/(BLOCKSIZE*L1_ASSOC);
            long long index_l1 = (address/BLOCKSIZE) % index_size_l1;
            long long tag_l1 = (address/(BLOCKSIZE *index_size_l1));



		int found = 0;
        int it;
		for (int i=0;i<tag1[index_l1].size();i++)
            {
                if (tag1[index_l1][i]==tag_l1)
                    {
                        it = i;
                        found = 1;
                        l1_wrt++;
                        data1[index_l1][it] = 1;
                        break;
                    }

            }
        if (found == 1) 
            {
				 // Check if the element was found
            
            for (int j=0;j<L1_ASSOC;j++)
            {
                if (j!=it)
                {
                    lru_l1[index_l1][j]++;
                }
                else{
                    lru_l1[index_l1][j] = 0;
                }

            }
            

            }

        else
        {   read_req_l2(address);
            l1_wrt_miss++;


            int idx = -1;
			for (int i=0;i<L1_ASSOC;i++)
                {
                    if (tag1[index_l1][i] == -1)
                    {
                        idx = i;
                        tag1[index_l1][i] = tag_l1;
                        data1[index_l1][i] = 1;
                        for (int j=0;j<L1_ASSOC;j++)
                            {
                                if (j!=i)
                                {
                                    lru_l1[index_l1][j]++;
                                }
                                else
                                {
                                    lru_l1[index_l1][j] = 0;
                                }

                            }
                        break;
                    }

                
                }

            if(idx == -1)
                {
                    vector<int> jack = lru_l1[index_l1];
                    int max_idx = distance(jack.begin(), max_element(jack.begin(), jack.end()));
                    int dirtyness = data1[index_l1][max_idx];
                    if (dirtyness == 1)
                        {
                            l1_wrtbk++;
                            wrt_back_l1(tag1[index_l1][max_idx]*index_size_l1+index_l1);
                        }
                    tag1[index_l1][max_idx] = tag_l1;
                    data1[index_l1][max_idx] = 1;
                    for (int j=0;j<L1_ASSOC;j++)
                        {
                            if (j!=max_idx)
                            {
                                lru_l1[index_l1][j]++;
                            }
                            else
                            {
                                lru_l1[index_l1][j] = 0;
                            }

                        }
                }

            
        }

    }
    
    
    
    void read_req_l1(vector<string> commander){
		long long address = stoi(commander[1],nullptr,16);
        long long index_l1 = (address/BLOCKSIZE) % index_size_l1;
    	long long tag_l1 = (address / BLOCKSIZE) / index_size_l1;
		int found = 0;
        int it;
		for (int i=0;i<L1_ASSOC;i++)
        {
			if (tag1[index_l1][i]==tag_l1)
                {
					it = i;
					found = 1;
                    break;
				}
        }
    	if (found == 1) 
        {
				 // Check if the element was found
            l1_read++;
            for (int j=0;j<L1_ASSOC;j++)
            {
                if (j!=it)
                {
                    lru_l1[index_l1][j]++;
                }
                else{
                    lru_l1[index_l1][j] = 0;
                }

            }
            // if( data1[index_l1][it] == 1){
            //     wrt_back_l1(address);
            //     data[index_l1][it] = 0;
            // }

        }
        else{
            l1_read_miss++;
			read_req_l2(address);
            int idx = -1;
			for (int i=0;i<L1_ASSOC;i++){
                if (tag1[index_l1][i] == -1){
                    idx = i;
                    tag1[index_l1][i] = tag_l1;
                    data1[index_l1][i] = 0;
                    for (int j=0;j<L1_ASSOC;j++)
                    {
                    if (j!=i)
                    {
                        lru_l1[index_l1][j]++;
                    }
                    else{
                        lru_l1[index_l1][j] = 0;
                    }

                     }
                    break;
                }

            
            }
            if(idx == -1)
            {
                idx = distance(lru_l1[index_l1].begin(), max_element(lru_l1[index_l1].begin(), lru_l1[index_l1].end()));
                int dirtyness = data1[index_l1][idx];
                if (dirtyness == 0)
                {
                    tag1[index_l1][idx] = tag_l1;
                    data1[index_l1][idx] = 0;
                    for (int j=0;j<L1_ASSOC;j++)
                    {
                    if (j!=idx)
                    {
                        lru_l1[index_l1][j]++;
                    }
                    else
                    {
                        lru_l1[index_l1][j] = 0;
                    }

                     }

                }
                else
                {
                   wrt_back_l1(tag1[index_l1][idx]*index_size_l1+index_l1);
                    tag1[index_l1][idx] = tag_l1;
                    data1[index_l1][idx] = 0;
                    for (int j=0;j<L1_ASSOC;j++)
                    {
                        if (j!=idx)
                            {
                                lru_l1[index_l1][j]++;
                            }
                        else
                            {
                                lru_l1[index_l1][j] = 0;
                            }

                    }     
                }

            }


        }
    }
    

    void wrt_back_l1(long long add){
        l1_wrtbk++;
		// int address = stoi(commands[1],nullptr,16);
        long long index_l2 = (add) % index_size_l2;
    	long long tag_l2 = (add) / index_size_l2;
		int found = 0;
        int it;
		for (int i=0;i<tag2[index_l2].size();i++)
            {
                if (tag2[index_l2][i]==tag_l2)
                    {
                        it = i;
                        found = 1;
                        l2_wrt++;
                        data2[index_l2][i] = 1;
                        break;
                    }

            }
        if (found == 1) 
            {
				 // Check if the element was found
            
            for (int j=0;j<L2_ASSOC;j++)
            {
                if (j!=it)
                {
                    lru_l2[index_l2][j]++;
                }
                else{
                    lru_l2[index_l2][j] = 0;
                }

            }
            

            }

        else
        {
            l2_wrt_miss++;


            int idx = -1;
			for (int i=0;i<tag2[index_l2].size();i++)
            {
                if (tag2[index_l2][i] == -1)
                {
                    idx = i;
                    tag2[index_l2][i] = tag_l2;
                    data2[index_l2][i] = 1;
                    for (int j=0;j<L2_ASSOC;j++)
                    {
                    if (j!=i)
                    {
                        lru_l2[index_l2][j]++;
                    }
                    else{
                        lru_l2[index_l2][j] = 0;
                    }

                     }
                    break;
                }

            
            }

            if(idx == -1)
            {
                vector<int> jack = lru_l2[index_l2];
                int max_idx = distance(jack.begin(), max_element(jack.begin(), jack.end()));
                int dirtyness = data2[index_l2][max_idx];
                if (dirtyness == 1){
                    l2_wrtbk++;
                }
                tag2[index_l2][max_idx] = tag_l2;
                data2[index_l2][max_idx] = 1;
                for (int j=0;j<L2_ASSOC;j++)
                {
                    if (j!=max_idx)
                    {
                        lru_l2[index_l2][j]++;
                    }
                    else
                    {
                        lru_l2[index_l2][j] = 0;
                    }

                }
            }

            
        }


            


    }

    void read_req_l2(long long address){
        long long index_l2 = (address/BLOCKSIZE) % index_size_l2;
    	long long tag_l2 = (address / BLOCKSIZE) / index_size_l2;
		int found = 0;
        int it;
		for (int i=0;i<tag2[index_l2].size();i++)
            {
                if (tag2[index_l2][i]==tag_l2)
                    {
                        it = i;
                        found = 1;
                        break;
                    }
            }
    	if (found == 1) 
            {
                    // Check if the element was found
                l2_read++;
                for (int j=0;j<L2_ASSOC;j++)
                {
                    if (j!=it)
                    {
                        lru_l2[index_l2][j]++;
                    }
                    else
                    {
                        lru_l2[index_l2][j] = 0;
                    }

                }


            }
        else
        {
            l2_read_miss++;
            int idx = -1;
			for (int i=0;i<tag2[index_l2].size();i++)
            {
                if (tag2[index_l2][i] == -1)
                {
                    idx = i;
                    tag2[index_l2][i] = tag_l2;
                    data2[index_l2][i] = 0;
                    for (int j=0;j<L2_ASSOC;j++)
                    {
                    if (j!=i)
                    {
                        lru_l2[index_l2][j]++;
                    }
                    else{
                        lru_l2[index_l2][j] = 0;
                    }

                    }
                    break;
                }

            
            }

                if(idx == -1)
                    {
                        vector<int> jack = lru_l2[index_l2];
                        int max_idx = distance(jack.begin(), max_element(jack.begin(), jack.end()));
                        int dirtyness = data2[index_l2][max_idx];
                        if (dirtyness == 1){
                            l2_wrtbk++;
                        }
                        tag2[index_l2][max_idx] = tag_l2;
                        data2[index_l2][max_idx] = 0;
                        for (int j=0;j<L2_ASSOC;j++)
                        {
                            if (j!=max_idx)
                            {
                                lru_l2[index_l2][j]++;
                            }
                            else
                            {
                                lru_l2[index_l2][j] = 0;
                            }

                        }
                    }






        }



        

        
    }
};



int main(int argc, char *argv[]){



    if (argc !=7) {
        std:: cerr << "Please provide all the arguments!\n";
        return 0;
    }
    else{
    ifstream file(argv[6]);
    long long BLOCKSIZE = stoi(argv[1]);
    long long L1_SIZE = stoi(argv[2]);
    long long L1_ASSSOC = stoi(argv[3]);
    long long L2_SIZE = stoi(argv[4]);
    long long L2_ASSOC = stoi(argv[5]);

    cache *cac;
    if (file.is_open()){
    	cac = new cache(file,BLOCKSIZE,L1_SIZE,L1_ASSSOC,L2_SIZE,L2_ASSOC);
    	}
        cac->act();
    	cac->executeCommands();
        cac->stats();
	cout<<"Number of L1 reads : "<<cac->l1_read<<endl;
    cout<<"Number of L1 read misses : "<<cac->l1_read_miss<<endl;
    cout<<"Number of L1 writes : "<<cac->l1_wrt<<endl;
    cout<<"Number of L1 write misses : "<<cac->l1_wrt_miss<<endl;
    cout<<"L1 miss rate : "<<((double)(cac->l1_read_miss+cac->l1_wrt_miss)/(cac->reads+cac->writes))*100<<"%"<<endl;
    cout<<"Number of WriteBacks from L1 memory : "<<cac->l1_wrtbk<<endl;

    cout<<"Number of L2 reads : "<<cac->l2_read<<endl;
    cout<<"Number of L2 read misses : "<<cac->l2_read_miss<<endl;
    cout<<"Number of L2 writes : "<<cac->l2_wrt<<endl;
    cout<<"Number of L2 write misses : "<<cac->l2_wrt_miss<<endl;
    cout<<"L2 miss rate : "<<((double)(cac->l2_read_miss+cac->l2_wrt_miss)/(cac->l2_read+cac->l2_read_miss+cac->l2_wrt+cac->l2_wrt_miss))*100<<"%"<<endl;
    cout<<"Number of WriteBacks from L2 memory : "<<cac->l2_wrtbk<<endl;
    file.close();
    
    return 0;
    }
}
