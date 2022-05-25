#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
void menu(int msg);
int main() {
	menu(0);
	return(0);
}

void menu(int msg){
	system("CLS");
	if (msg == 0){
		cout << "The File Editor" << endl << endl; //message that will come up
	}
	if (msg == 1){
		cout << "The File Editor" << endl << endl; 
	}
	if (msg == 2){
		cout << "The File Editor" << endl << endl;
	}
	if (msg == 3){
		cout << "The File Editor" << endl << endl;
	}
	
	cout << "Menu" << endl; //menu
	cout << "Menu" << endl; //features, create
	cout << "Menu" << endl; // delete
	cout << "Menu" << endl; // copy
	cout << "Menu" << endl;
	cout << "Menu" << endl;
	cout << "Please enter the number: ";
	
	int choice = 0;
	string filename;
	string text;
	
	cin >> choice;
	
	if(choice == 1){
		cout << endl << "Please enter the name of the file: ";
		cin.ignore();
		getline(cin, filename);
		fstream myfile((filename + ".txt").c_str());
		myfile.close();
		menu(1);
		cin >> choice;
	}
	
	if(choice == 2){
		cout << endl << "Please enter the name of the file: ";
		cin >> filename;
		if(remove((filename + ".txt").c_str()) == 0){
			
		}
	
	if(choice == 3{
		cout << endl << "Please enter the name of the file to copy from: ";
		cin.ignore();
		getline(cin, filename);
		fstream myfile((filename + ".txt").c_str());
		string line;
		while(getline(myfile, line)){
			text += line + "\n";
		}
		myfile.close());
		cout << endl << "Enter the name of the file to copy to: ";
		
		
	}
	
//	if(choice == 4){
//		cout << endl << "Please enter the name of the file: ";
//		cin.ignore();
//		getline(cin, filename);
//		fstream myfile((filename + ".txt").c_str());
//		myfile.close();
//		menu(1);
//		cin >> choice;
//	}
//	
//	if(choice == 5){
//		cout << endl << "Please enter the name of the file: ";
//		cin.ignore();
//		getline(cin, filename);
//		fstream myfile((filename + ".txt").c_str());
//		myfile.close();
//		menu(1);
//		cin >> choice;
//	}
}
