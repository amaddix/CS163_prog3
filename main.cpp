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

int main()
{
	table my_table; //create an instance of table class
	definition users; // create an instance of definition struct
	char * key_value; // pointer to char array holding the 'key_value'
	// to be sent to an ADT function 	
	char choose=0; //variable to read in a choice from user
	int worked=0;

	do
	{
		choose=menu(); //fall function to read the users choice of action

		//add terms from a file	
		if (choose == '1')
		{
			worked=read_file(key_value, users, my_table);

			//outpur error or success messages	
			if (!worked)
				cout<<"***looks like there was some problems accessing "
					<<"your file***"<<endl;
			else
				cout<<"*** successfully added terms from file ***"<<endl;
		}


		//code used to test 'retrieve' function

		/*
		   char temp[100]; //temp array to read in users responce
		//prompt user for what term they would like to retrieve
		cout<<"what term would you like to use??"<<endl;
		cin.get(temp, 100, '\n');
		cin.ignore(100, '\n');

		// allocate memory for key_value of size temp
		key_value=new char[strlen(temp)+1];
		//copy key_value into temp
		strcpy( key_value, temp);

		//call retieve function	
		worked=my_table.retrieve(key_value, users);
		//outpur error or success messages	
		if (!worked)
		cout<<" *** looks like theres no matching key value ***"<<endl;
		else
		{
		cout<<" *** found << worked << "match(s)" <<endl;
		// outputting some retrieved info
		cout<<"retrieved  :   "<<users.name<<
		users.citation<<endl;
		}
		 */



		//add new new term (not in file)
		if (choose == '2')
		{
			save_users (users); //call function to read in 
			//the users term
			key_value= new char [strlen(users.name) +1]; 
			//allocate memory of size users.name (which was added
			//from 'save_users'
			strcpy (key_value, users.name);
			// copy users.name into key_value
			worked=my_table.add (key_value, users);
			//call add function
			//outpur error or success messages	
			if (!worked)
				cout<<"*** looks like there was some issues adding "<<
					"your term ***"<<endl;
			else
				cout<<"***successfully added your term***"<<endl;
		}

		//remove all terms from a certain source
		if (choose == '3')
		{
			char temp_term [100]; //create a temp var to store users input
			cout<<"what is the name of the source you'd like to delete all"
				<<" occurences of?"<<endl;
			cin.get(temp_term, 100, '\n');	
			cin.ignore(100,'\n');

			//allocate memory for key_value of size temp+1	
			key_value= new char [strlen(temp_term) +1];
			// copy temp into key_value
			strcpy (key_value,temp_term);

			//call function to remove	
			worked=my_table.remove_all_source (key_value);
			//outpur error or success messages	
			if (!worked)
				cout<<"*** looks like there was nothing to remove***"<<endl;
			else 
				cout<<"*** successfully deleted "<<worked<<" items who's "
					<<"source matched "<<key_value<<" ***"<<endl;
		}

		// display terms matching users input
		if (choose == '4')
		{
			char temp_term [100]; //create temp array to hold users input
			cout<<"what is the term that you would like to display?"<<endl;
			cin.get(temp_term, 100, '\n');	
			cin.ignore(100,'\n');

			//allocate memory for key_value of size temp_term +1	
			key_value= new char [strlen(temp_term) +1];
			// copy temp_term into key_value
			strcpy (key_value,temp_term);

			//call function to find match and display
			worked=my_table.display (key_value);

			//outpur error or success messages	
			if (!worked)
				cout<<"*** looks like there was no match***"<<endl;
			else
				cout<<"***displayed "<<worked<<" items ***"<<endl;
		}

		//display all terma
		if (choose == '5')
		{
			worked=my_table.display_all ();
			//outpur error messages	
			if (!worked)
				cout<<"***looks like there was no terms added***"<<endl;
			else
				cout<<"***displayed :  "<<worked<<" items***"<<endl;
		}

		//continue looping through until the user types 6
	}while (choose != '6');

}

//function to putput all the options the user has to choose from
char menu ()
{
	char choose='0';

	cout<<endl<<endl<<endl;
	cout<<" Please choose an action you want the program to preform"<<endl<<endl
		<<"1.	add definition terms from an exisiting file."<<endl
		<<"2.	add a new definition term."<<endl
		<<"3.	remove all the terms given by a particular source"<<endl
		<<"4.	display a particular term"<<endl
		<<"5.	display all terms in list"<<endl
		<<"6.	quit"<<endl<<endl<<endl;

	cin>>choose;
	cin.ignore (100, '\n');

	//return value choosen by user	
	return choose;
} 

//function to prompt user for information on a term
void save_users (definition & users)
{
	char temp[500]; // temp array to store users initial responce

	//prompt for term
	cout<<"what is the term you are adding?"<<endl;

	cin.get(temp, 500, '\n');
	cin.ignore(100, '\n');

	//allocate memory fro users.name of size temp +1
	users.name= new char[strlen(temp)+1];
	//copy temp into users.name
	strcpy (users.name, temp);
	//###########################################//
	//continue same routine as ^ for rest of definition info
	cout<<"what is the definition for "<<users.name<<" ?"<<endl;

	cin.get(temp, 500, '\n');
	cin.ignore(100, '\n');

	users.def= new char[strlen(temp)+1];
	strcpy (users.def, temp);
	//###########################################//
	cout<<"what is the source for this definition of "<<users.name<<" ?"<<endl;

	cin.get(temp, 500, '\n');
	cin.ignore(100, '\n');

	users.ref= new char[strlen(temp)+1];
	strcpy (users.ref, temp);
	//###########################################//
	cout<<"what is the citation for this source ?"<<endl;

	cin.get(temp, 500, '\n');
	cin.ignore(100, '\n');

	users.citation= new char[strlen(temp)+1];
	strcpy (users.citation, temp);
}

//function to read in terms from a file
int read_file(char * key_value, definition & users, table & my_table)
{
	char temp[500]; //temp variable to read in users initail info

	ifstream read_in; //create a variable of ifstream to read in info from a file

	read_in.open("CS_terms.txt"); //using var to read in, open file

	//return if we could not open file	
	if (!read_in)
		return 0;
	//otherwise...
	else
	{
		//read in the first past of definition (the term)
		read_in.get(temp, 500, '|');
		read_in.ignore (500, '|');

		//allocate memory for users.name of that length
		users.name= new char[strlen(temp)+1];
		//copy temp into users.name
		strcpy (users.name, temp);

		//while we have not reached the end of file...
		while(!read_in.eof())
		{
			//allocate memory for key_value of length users.name
			key_value= new char [strlen(users.name) +1];
			//save the last read term as the key value
			strcpy (key_value, users.name);


			//read in the next section of the definition ( the actual
			// definition)
			read_in.get(temp, 500, '|');
			read_in.ignore (500, '|');

			//allocate memory for users.def
			users.def= new char[strlen(temp)+1];
			strcpy (users.def, temp);

			//read in next section of definition (the source)	
			read_in.get(temp, 500, '|');
			read_in.ignore (500, '|');

			users.ref= new char[strlen(temp)+1];
			strcpy (users.ref, temp);

			//read in the last section of definition (the citation)	
			read_in.get(temp, 500, '\n');
			read_in.ignore (500, '\n');

			users.citation= new char[strlen(temp)+1];
			strcpy (users.citation, temp);

			//call function to add the last term read in by user in
			//the hash table
			my_table.add (key_value, users);

			//read in the next term from our file	
			read_in.get(temp, 500, '|');
			read_in.ignore (500, '|');

			users.name= new char[strlen(temp)+1];
			strcpy (users.name, temp);
		}
		//close file
		read_in.close();
	}	
}
