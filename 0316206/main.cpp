#include <iostream>
#include <time.h>
#include <stdio.h>
#include "db.cpp"
using namespace std;

int main(int argc, char* argv[]){
   
    
	//declear db object
	db mydb;

	//init db
	mydb.init();

	//set temp directory
	mydb.setTempFileDir("temp");

	//Import data
	clock_t tImport = clock();
	mydb.import("data/2006.csv");
	mydb.import("data/2007.csv");
	mydb.import("data/2008.csv");
	double import_time = (double)(clock() - tImport) / CLOCKS_PER_SEC;

	//Create index on one or two columns.
	clock_t tIndex = clock();
	mydb.createIndex();
	double index_time = (double)(clock() - tIndex) / CLOCKS_PER_SEC;

	//Do queries
	//These queries are required in your report.
	//We will do different queries in the contest.
	//Start timing
	clock_t tQuery = clock();
	double result1 = mydb.query("IAH", "JFK");
    //clock_t tQuery2 = clock();
    double result2 = mydb.query("IAH", "LAX");
	//clock_t tQuery3 = clock();
    double result3 = mydb.query("JFK", "LAX");
	//clock_t tQuery4 = clock();
    double result4 = mydb.query("JFK", "IAH");
	//clock_t tQuery5 = clock();
    double result5 = mydb.query("LAX", "IAH");

	//End timing
	//double query_time = (double)(clock() - tQuery) / CLOCKS_PER_SEC;
    //clock_t tEND = clock();
    cout<<"________________"<<endl;
    cout<<"| Origin | Dest|"<<"   Result"<<endl;
     cout<<"________________"<<endl;
    cout<<"|  IAH   | JFK |"<<" "<<result1<<endl;
    cout<<"________________"<<endl;
    cout<<"|  IAH   | LAX |"<<" "<<result2<<endl;
     cout<<"________________"<<endl;
    cout<<"|  JFK   | LAX |"<<" "<<result3<<endl;
     cout<<"________________"<<endl;
    cout<<"|  JFK   | IAH |"<<" "<<result4<<endl;
     cout<<"________________"<<endl;
    cout<<"|  LAX   | IAH |"<<" "<<result5<<endl;
    cout<<"________________"<<endl;
    
	/*printf("Time taken for import: %.2fs\n", import_time);
	printf("Time taken for creating index: %.2fs\n", index_time);
	printf("Time taken for making queries: %.2fs\n", query_time);*/
    
    double query_time = (double)(clock() - tQuery) / CLOCKS_PER_SEC;
    
    printf("Time taken for import: %.2fs\n", import_time);
    printf("Time taken for creating index: %.2fs\n", index_time);
    printf("Time taken for making queries: %.2fs\n", query_time);
    //Cleanup db object
	mydb.cleanup();
}
