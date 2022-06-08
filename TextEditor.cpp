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

void menu(int msg)
{
	system("CLS");
	if (msg == 0){
		cout << "\tWelcome to Text Editor" << endl;
		cout << "\t----------------------" << endl; //message that will come up
	}
	if (msg == 1){
		cout << "File Created Successfully" << endl << endl; 
	}
	if (msg == 2){
		cout << "File Updated Successfully" << endl << endl;
	}
	if (msg == 3){
		cout << "See You Again Soon!!" << endl << endl;
	}
	
	cout << "====TEXT EDITOR MENU==== \n\n"<< endl; //menu
	cout << "Please choose what you wish to do:" << endl; //features, create
	cout << "1. Create a File" << endl; // delete
	cout << "2. Add to File" << endl; // copy
	cout << "3. Print File Content" << endl;
	cout << "4.Exit" << endl;
	cout << "Please enter the number: ";
	
	int choice = 0;
	string filename;
	string text;
	
	cin >> choice;
	
	if(choice == 1){
		cout << endl << "Please enter the name of the file: ";
		cin.ignore();
		getline(cin, filename);
		ofstream myfile((filename + ".txt").c_str());
		myfile.close();
		menu(1);
		cin >> choice;
	}
	
	if(choice == 2){
		text = "";
		cout << endl << "Enter name of file: ";
		cin >> filename;
		cout << endl << "Enter text to write to file: (Enter END to complete)" << endl;
		ofstream myfile;
		myfile.open((filename + ".txt").c_str(), ios::app);
		string line;
		cin.ignore();
		while (getline(cin, line))
		{
			if(line.size() >= 3){
				if(line.substr(line.size() - 3) == "END"){
					text += line.substr(0, line.size()-3);
					break;
				}
				else{
					text  += line+"\n";
				}
			}
			else{
				text  += line+"\n";
			}
		}
		myfile<<text;
		myfile.close();
		menu(2);
		cin>>choice;
		
	}
	
	if(choice == 3){
		text = "";
		cout<<endl<<"Enter name of file ";
		cin>>filename;
		fstream myfile;
		myfile.open((filename + ".txt").c_str());
		while (getline(myfile, text)){
			cout << text << "\n";
		}
		myfile.close();
		char now;
		cout<<endl<<"End of file. Press any key for main menu: ";
		menu(2);
		cin.ignore();
	}
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
