#include <string>
#include <iostream>
#include <cstdlib>
#include<iostream>
#include<fstream>

#include "radix_tree.hpp"

using namespace std;
radix_tree<std::string, int> tree;

void insert(vector<string> config,map<int,string> &m) {
	string addr;
	string server;
	string record;
	string::size_type it;

	cout<<"    " <<"Reading config file"<<"\n";
	
	for(int i=0;i<config.size();i++){
		record=config[i];
		it=record.find("=");
		addr=record.substr(0,it);
		server=record.substr(it+1);
		if(addr.find('*')==0)
			tree[""]=i;
		else
			tree[addr.substr(0,addr.find('*')-1)]=i;
		m[i]=server;
		cout<<"    " <<addr<<"->"<<server<<"\n";
	}

	cout<<"    " <<"-------------------------"<<"\n";

}

void findRoute(std::string key,map<int,string> m)
{
    radix_tree<std::string, int>::iterator it;

    it = tree.longest_match(key);

    if (it != tree.end()) {
        std::cout << "    " << key << "->" << m[it->second] << std::endl;
    } else {
        std::cout << "Could not find the server" << std::endl;
    }

}


int main()
{
	ifstream inFile("config");
	string line;
	vector<string> config;
	map<int,string> m;

	while(getline(inFile,line))
		config.push_back(line);
	inFile.close();
    	insert(config,m);

    	findRoute("customer1.us.ca.sfo",m);
    	findRoute("customer1.us.ca.sjc",m);
    	findRoute("customer2.us.tx.dfw",m);
    	findRoute("customer2.cn.tw.tai",m);
    	findRoute("customer10.us.ny.nyc",m);

    	return EXIT_SUCCESS;
}
