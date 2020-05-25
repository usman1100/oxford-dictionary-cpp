#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<list>

// Function Prototyping
using namespace std;
void displayWord(string s);
string getWord(string s);


// BST Impementation
class BST
{

	string data;
	BST* left, * right;
public:

	BST() {
		data = "";
		left = NULL;
		right = NULL;
	}

	BST(string value)
	{
		data = value;
		left = right = NULL;
	}

	BST* Insert(BST* root, string value)
	{
		if (!root)
		{
			return new BST(value);
		}

		if (value > root->data)
		{
			root->right = Insert(root->right, value);
		}
		else
		{
			root->left = Insert(root->left, value);
		}

		return root;
	}

	void Inorder(BST* root)
	{
		if (!root)
		{
			return;
		}
		Inorder(root->left);
		cout<<getWord(root->data);
		cout << endl;
		Inorder(root->right);
	}
	
	
	BST* search(BST* root, string key) 
	{
		if(root == NULL){
			cout<<key <<" was not found\n"; return root;
		}
		
		if (getWord(root->data) == key){
			displayWord(root->data);
			return root;
		}
		

		if (root->data < key) 
			return search(root->right, key); 

		return search(root->left, key); 
	}
	
		
	
	
	
	
	
};


/* Takes in a dictionary line as input
	and displays it's word and meaning
	part separately
*/
void displayWord(string s)
{
	string word, meaning;
	for(int i=0; i<s.length(); i++){
		if(s[i]==' ' && s[i+1] == ' '){
			word = s.substr(0,i);
			meaning = s.substr(i+2, s.length());
			break;
		}
	}
	
	cout<<"\nWord: " <<word
		<<"\nMeaning: " <<meaning;
}


/* 
	This function will extract the first half
    of the string its given which is the word 
*/
string getWord(string s)
{
	string word;
	for(int i=0; i<s.length(); i++){
		if(s[i]==' ' && s[i+1] == ' '){
			word = s.substr(0,i);
			return word;
		}
	}
}

/*
	Used to convert user input from upercase
	to lowercase
	ie hello -> Hello
*/
string toLowerCase(string s){
	
	for(int i=0; i<s.length(); i++)
	{
		if(s[i] >='A' && s[i] <= 'Z')
			s[i] += 32;
	}
	if(s[0] >= 'a' && s[0] <= 'z') s[0] -= 32;
	return s;
}


/*
	User will be able to select a dictionary 
	file depending on thiersystem specifications 
	because loading the full file can crash the
	application on slower systems
*/
string chooseDictionaryFile(){
	int inp;
	do
	{
		cout<<"Select a dictionary file to load\n\n";
		cout<<"Enter 1 for small dictionary\n\t-Contains around 1000 words\n\t-Recommended for slower computers\n\n";
		cout<<"Enter 2 for medium dictionary\n\t-Contains around 12000 words\n\t-Can take some seconds to load\n\n";
		cout<<"Enter 3 for larger dictionary\n\t-Contains around 32000 words\n\t-Not recommended for slower systems\n\n";
		cout<<"Enter 0 for testing dictionary\n\t-Contains only 50 words\n\t-Can be usefull for testing purposes\n\n";
		cout<<"Enter: ";
		cin>>inp;
		system("cls");
		
		if(inp == 1) return "small.txt";
		else if(inp == 2) return "medium.txt";
		else if(inp == 3) return "large.txt";
		else if(inp == 0) return "test.txt";
		else{
			cout<<"Enter a number between 0-3\n\n";
		}
		
	}
	while(inp > 0 || inp < 4);
	
}

void showHelpScreen()
{
	cout<<"\n--------------------------Help Section--------------------------\n";
	cout<<"\n\nFollowing is a list of commands you can enter while in the search mode\n\n";
	cout<<"- clear* | Clear all the text on screen\n";
	cout<<"- exit*  | Exit the dictionary search screen\n";
	cout<<"- help*  | Bring up this menu\n";
	cout<<"\n\nEnter Q to exit: ";
	string x;
	cin>>x;	
}

void welcomeMessage()
{
	system("cls");
	cout<<"\n--------------------------------------------------------------------";
	cout<<"\n--------------------------------------------------------------------";
	cout<<"\n--------------------Welcome to Oxford Dictionary--------------------";
	cout<<"\n--------------------------------------------------------------------";
	cout<<"\n--------------------------------------------------------------------\n\n\n";
	
}

void showMenu()
{
	cout<<"\n\tSelect one of the below options by entering a number\n";
	
	cout<<"\n\t1- Search the Dictionary for words/meaning";
	cout<<"\n\t2- Add your own words and their meanings";
	cout<<"\n\t3- See the list of all available words";
	cout<<"\n\t4- See list of search mode commands";
	cout<<"\n\t0- Exit the dictionary\n\t";
}

string addNewWord()
{
	string word, meaning;
	
	cout<<"\nNOTE: Do not enter words with spaces\n\n";
	
	cout<<"\nEnter word: ";
	cin>>word;
	
	cout<<"\nEnter its meaning: ";
	cin>>meaning;
	
	return word + "  " + meaning;
}


int main()
{
	
	// Main variables declared
	BST b, * root = NULL;
	string fileName = "";
	string temp = "first";
	root = b.Insert(root, temp);
	
	welcomeMessage();
	
	fileName ="data/" + chooseDictionaryFile(); // Deciding what dictionary to choose
	
	cout<<"\nLoading data. Please wait :) ";
	
	ifstream r(fileName.c_str());
	string inputLine;
	
	/*Loading dictionary data in a 
	  Binary Search Tree, line by line*/
	while (getline(r, inputLine)) {
		
		if (!inputLine.empty()) // Checking for empty lines in the file
		{
			b.Insert(root, inputLine);
		}
	}
	
	r.close();
	cout<<"\n\nDone Loading Data\n\n";
	
	showMenu();
	welcomeMessage();

	int choice = 1;
	while(choice != 0)
	{
		showMenu();
		cin>>choice;
		
		if(choice == 1)
		{
			while(true)
			{
				cout<<"\n\nEnter Word: "; 
				cin>>temp;
				temp = toLowerCase(temp);
				
				if(temp=="Clear*")
				{
					system("cls");
					continue;
				}
				
				else if(temp == "Exit*")
				{
					system("cls");
					cout<<"\n\nExiting Search Mode...\n\n";
					break;
				}
					
				else if(temp == "Help*")
				{
					system("cls");
					showHelpScreen();
					system("cls");
				}
					
				else
					b.search(root, temp);
				
			}
		}
		
		else if(choice == 3)
		{
			system("cls");
			b.Inorder(root);
		}
		
		else if(choice == 2)
		{
			system("cls");
			b.Insert(root, addNewWord());
			cout<<"\nAdded new word!\n";
		}
		
		else if(choice == 4)
		{
			system("cls");
			showHelpScreen();
		}
		
		else if(choice == 0)
		{
			system("cls");
			cout<<"------Exiting-------\n";
			cout<<"Thank You For Using!\n\n\n\n";
		}
		else
		{
			system("cls");
			cout<<"\nEnter a valid number....\n";
		}
		
		
	}
	

	
	


}









