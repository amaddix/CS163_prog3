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


#include "header.h"

//constructor for table to initialize the variables from table class
table::table ()
{	

	hash_table= new node * [SIZE]; // creating an array of size 'size', of node pointers

	// each index of the array, set its pointer = to NULL
	for (int i=0; i<SIZE; ++i)
	{
		hash_table[i]=NULL;
	}

	table_size=SIZE; //set table size= size
}	

//destructor for table class, to delete all memory allocated
table::~table ()
{

	for (int i=0;i< table_size ; ++i)
	{
		if(hash_table[i])
		{
			node * temp=hash_table[i];

			while (temp)
			{

				delete [] hash_table[i]->term.name;
				delete [] hash_table[i]->term.def;
				delete [] hash_table[i]->term.ref;
				delete [] hash_table[i]->term.citation;

				delete hash_table[i];

				temp=temp->next;	
				hash_table[i]=temp;

			}

		}
		table_size=0;	

	}
}

// function to find the index give a particular key value passed in
int table::hash_function (char * key_value)
{
	int sum=0;

	//for each charecter of the array key_value, add to sum
	for (int i=0; key_value[i]!= '\0'; ++i)
	{
		sum +=key_value[i];
	}

	//return the sum moded by table_size
	return sum %=table_size;
}

//function to add a term added either from user or a file 
int table::add (char * key_value, definition users)
{
	int index= 0;

	//save value returned from hash_function as index
	index=hash_function(key_value);

	node * temp= new node;
	// set temp before the head of the hash_table and index 'index';
	temp->next=hash_table[index];
	//set temp as the new head
	hash_table[index]=temp;
	//call function to copy the information from 'users' into the current head of our
	//hash table
	copy(users, index);

	return 1;


}

//function to copy the information from users into hash_tables current index's head
int table::copy (definition users, int index)
{
	hash_table[index]->term.name=users.name;
	hash_table[index]->term.def=users.def;
	hash_table[index]->term.ref=users.ref;
	hash_table[index]->term.citation=users.citation;
}


//function to find a match to the key_value passed in by the user, and save it into 
//'users' to 'give' back to the user
int table::retrieve (char * key_value, definition & users)
{
	int index= 0;

	//save value returned from hash_function as index
	index=hash_function(key_value);

	cout<<"key_value  :   "<<key_value<<endl;

	//create temp node pointing to head of the hash_table array
	node * current= hash_table[index];
	// while current is not NULL and while we have NOT found a match, traverse to next
	while( current && strcmp(current->term.name, key_value)!=0)	
	{
		current=current->next;
	}

	//if we stopped when current is NULL
	if (!current)
		return 0;
	//otherwise, save the information found at match, and save into 'users' members
	else
	{
		users.name=current->term.name;
		users.def=current->term.def;
		users.ref=current->term.ref;
		users.citation=current->term.citation;
		return 1;
	}
}

// function to remove all the terms with a source matching the key_value passed in.
int table::remove_all_source (char * key_value)
{
	int deleted=0;
	//for each index of out hash_table array	
	for (int i=0; i< table_size; ++i)
	{
		// if we have any terms in the current index of our has_table array
		if(hash_table[i])
		{ 
			//if we have a head and a head's next
			if (hash_table[i] && hash_table[i]->next)
			{
				//create a temp node pointing at both
				node * previous=hash_table[i];
				node * current=hash_table[i]->next;

				//while our current is not NULL...
				while (current)
				{
					//if we found a matching source...
					if (strcmp(current->term.ref, key_value)==0)
					{
						//set previous's next to currents next
						previous->next=current->next;
						//delete current
						delete current;
						//set current = to previous
						current=previous;								
						//increase deleted to incease the count 
						//of deleted items
						++deleted;
					}
					//traverse previous and current
					previous=current;		
					current=current->next;
				}
			}

			//check to see if head was a match
			if (strcmp(hash_table[i]->term.ref, key_value)==0)
			{ 
				// if it was, set head to heads next, and delete head
				node * temp=hash_table[i];
				hash_table[i]=hash_table[i]->next;
				delete temp;
				//increase deleted to incease the count of deleted items
				++ deleted;
			}
		}
	}
	// return the number of deleted terms
	return deleted;

}

//function to display all the terms matching a key_value passed in.
int table::display ( char * key_value)
{
	int index= 0;
	int displayed=0;

	index=hash_function(key_value); //call function to get index based in key_value

	//create temp node pointing to the head of the hash_table at index
	node * current= hash_table[index];	
	//countinue traversing though the list until we reach NULL
	while(current)
	{
		// if there is a match display that terms information
		if (strcmp(current->term.name, key_value)==0)
		{
			cout<<endl<<current->term.name<<endl
				<<current->term.def<<endl
				<<current->term.ref<<endl
				<<current->term.citation<<endl<<endl;

			//increase count of displayed items	
			++displayed;
		}
		current=current->next;
	}
	//return the count of displayed items
	return displayed;

}

// function to display all the terms inside the hash_table
int table::display_all ()
{
	int count=0;
	//go thtough each index of the hash_table array

	for (int index=0; index < table_size ; ++index)
	{
		cout<<endl<<" INDEX  "<<index<<endl<<endl;
		count += display_all_recursion(hash_table[index]);
	}

	return count;
}

int table::display_all_recursion(node * head)
{
	if (!head)
		return 0;

	//display the current nodes term info
	cout<<endl<<head->term.name<<endl
		<< head->term.def <<endl
		<< head->term.ref <<endl
		<< head->term.citation <<endl
		<<endl;

	return 1 + display_all_recursion(head->next);
}
