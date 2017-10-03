#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <map>
#include "db.h"
using namespace std;

void db::init(){
	//Do your db initialization.
    index = 0;
}

void db::setTempFileDir(string dir){
	//All the files that created by your program should be located under this directory.
    t = dir;
    t += "/ans";
}

void db::import(string csvFileName){
	//Inport a csv file to your database.
	fstream file_in;
	fstream file_out;
	string str;
	string str_time;
	string str_all;
	file_in.open(csvFileName.c_str(),ios::in);
	file_out.open(t.c_str(),ios::out | ios::app);
	getline(file_in,str,'\n');	
	while(!file_in.eof())
	{
		for(int i=0;;i++)
		{
			getline(file_in,str,',');
			if(i==14 || i==16 || i==17)
			{
				if(str=="NA")
				{
				//	str="0";
					getline(file_in, str, '\n');
                    break;
                    
				}
				if(i==14)
				{
					str_time=str;
				}
				else if(i==16)
				{
					str_all = str;
				}
				else if(i==17)
				{
					str_all = str+str_time+str_all;
					file_out<<str_all;
					switch(str_all.length()){
                        case 7: file_out << "    "; break;
                        case 8: file_out << "   "; break;
                        case 9: file_out << "  "; break;
                        case 10: file_out << " "; break;
                        default : break;
                    }
                    
                    getline(file_in, str, '\n');
                    break;
				}
			}
		}
	}
	file_in.close();
    file_out.close();
}

void db::createIndex(){
	//Create index.
    int count = 0;
	index = 1;
    string str;
	string str_place;
    fstream file_in;
    file_in.open(t.c_str(), ios::in);
    while(!file_in.eof())
	{
        file_in >> str;
        str_place = str.substr(0,6);
        table[str_place].push_back(count);
        count++;
    }
}

double db::query(string origin, string dest){
	//Do the query and return the average ArrDelay of flights from origin to dest.
	//This method will be called multiple times.
    FILE* file_ptr;
	fstream file_in;
    string str;
	double avg;
	string str_place;
	string str_num;
    int  sum = 0;
	int j;
	int count = 0;
    
    file_ptr = fopen((char*)t.c_str(), "rb");
    file_in.open(t.c_str(), ios::in);
    if(index == 1)
	{
        str_place = origin + dest;
        for(int i = 0;i < table[str_place].size();i++)
		{
            fseek(file_ptr, table[str_place][i]*11 + 6, SEEK_SET);
            char buffer[6];
            fread(buffer, sizeof(char), 5, file_ptr);
            j = atoi(buffer);
            sum += j;
            count++;
        }
    }
    else
	{
        while(!file_in.eof())
		{
            file_in >> str;
            for(int i = 0;i < str.length();i++)
			{
                if(i < 3)
				{
                    if(str[i] != origin[i]) break;
                }
                else if(i < 6)
				{
                    if(str[i] != dest[i-3]) break;
                }
                else 
				{
                    str_num = str.substr(6, str.length()-6);
                    stringstream ss(str_num);
                    ss >> j;
                    sum += j;
                    count++;
                    break;
                }
            }
        }
    }
    avg = (double)sum/(double)count;
    
    return avg; //Remember to return your result.
}

void db::cleanup(){
	//Release memory, close files and anything you should do to clean up your db class.
    remove(t.c_str());
}
