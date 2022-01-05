//Ashley Maddix, CS163 spring 2018
//Program 3

//main.cpp
//	main
//	menu
// 	save users

//table.cpp
//	constructor
//	destructor
//	hash function
//	add
//	copy
//	retrieve
//	remove all source
// 	display
//	display all

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

const int SIZE= 61;

// struct for all the information that goes into a 'definition'
struct definition
{
	char * name;
	char * def;
	char * ref;
	char * citation;
};

//struct for the nodes storing each term added
struct node
{
	//pointer to type definition
	definition term;
	//pointer to the next pointer in the list
	node * next;
};

//Class for our hash table
class table
{
	public:
		table (); //constructor, to initialize the data members of our table
		~table (); // destructor, to delete all the memory allocated to data members in the 
		// table class
		int add (char * key_value, definition users); 
		//function to add a a term stored into
		// 'users' and save into an index of the hash table
		int retrieve (char * key_value, definition & users); 
		// function to take a key_value
		//(passed in from the client program), and search through the hash 
		//table until it has found a term matching the key_value
		int remove_all_source (char * key_value); // function to take a key value 
		//(passed in from the client program), and delete all occurenced 
		//where a term's source matches the key_value
		int display ( char * key_value); //function to display the information of a term
		//matching the key_value passed in
		int display_all (); //function to display all the terms ( and its information).

	private:
		// a node pointer to an array
		node ** hash_table;
		//the size of our table (array)
		int table_size;

		int hash_function (char * key_value); // function to take in the key value 
		//(the term being added) and preform some sort of algorithm to end up 
		//with an index ( between 0-size)
		int display_all_recursion(node * head); //function to preform the recursive/ repetitive parts of 
		//my display_all function.
		int copy (definition users, int index); //function to copy all the definition 
		//information into the hash_table's array current index.
};

char menu (); //function to display all the actions the user may choose
int read_file(char * key_value, definition & users, table & my_table); 
//function to read in terms from a file and save them into the hash_table as their read
void save_users (definition & users); //function to prompt user for 
