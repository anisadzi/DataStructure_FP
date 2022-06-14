#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

struct undo{
    int lineNumber;
    string text;
    int commandNumber;
    int nLine;
};

struct node{
    string data;
    struct node *next;
};

class linked_list{
    private:
        node *head;
        node *tail;
        int numOfLines = 0;
        int next = 1;
        stack<undo> undoStack;
    public:
        std::ofstream outfile;
        linked_list(){
            int choice = -1;
            head = NULL;
            tail = NULL;
            
            while(choice != 0){
                cout<<"=====TEXT EDITOR=====\n"<<endl;
                cout<<"Please choose what to do:"<<endl;
                cout<<"1. Insert text into line N"<<endl;
                cout<<"2. Delete line N"<<endl;
                cout<<"3. Print all"<<endl;
                cout<<"4. Save into a .txt file"<<endl;
                cout<<"5. End\n"<<endl;
                cout<<"Please enter your choice: "<<endl;
                cin>>choice;

                if (choice == 1){
                    int lineGiven;
                    string input;
                    cout<<"Enter line you want the text to be put into: ";
                    cin>>lineGiven;
                    cout<<"Enter text: ";
                    cin.ignore(1);
                    getline(cin,input);
                    input+="\n";
                    
                    if (lineGiven == 1){
                        addToHead(input);
                    }
                    else if (lineGiven > numOfLines){
                        insertAway(input,lineGiven);
                    }
                    else if (lineGiven < numOfLines){
                        insertTextInBetween(input,lineGiven);
                    }
                }
                else if (choice == 2){
                    int lineGiven;
                    cout<<"Enter the line you want to delete: ";
                    cin>>lineGiven;
                    deleteLine(lineGiven);
                }
                else if (choice == 3){
                    printAll();
                    sleep_for(nanoseconds(1000));
                    sleep_until(system_clock::now() + 1s);
                }
                else if (choice == 4){
                    saveAll();
                }
                else if (choice == 5){
                    cout<<"See You Next Time!!";
                    return;
                }
            }
        }
    
    void addToHead(string dataGiven){
        if (head == NULL){
            node *temp;
            temp = new node;
            temp->data = dataGiven;
            temp->next = NULL;
            head = temp;
            tail = head;
            numOfLines++;
        }
        else{
            node *temp;
            temp = new node;
            temp->data = dataGiven;
            temp->next = NULL;
            temp->next = head;
            head = temp;
            numOfLines++;
        }
        undo addedToHead;
        addedToHead.lineNumber = 1;
        addedToHead.commandNumber = 1;
        undoStack.push(addedToHead);
    }

    void whateverAddToTail(string dataGiven){		//an extra function used to add to tail, had to implement to make Undo function work, ignore this one please
		if (head == NULL)					//no node, empty linked list
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			head = temp;
			tail = head;
			numOfLines++;
		}
		else 								//one or more than one node
		{
			node *temp;
			temp = new node;
			temp->data = dataGiven;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
			numOfLines++;
		}
	}

    void insertAway(string dataGiven, int lineGiven){		//will print /n lines if given line is larger than numOfLines
		undo insertedFurtherAway;
		insertedFurtherAway.lineNumber = 0;
		insertedFurtherAway.commandNumber = 9;
		if (head == NULL)
		{
			while(numOfLines < lineGiven-1)
			{
				whateverAddToTail("\n");
				insertedFurtherAway.lineNumber++;
			}
			// insertedFurtherAway.lineNumber++;
			whateverAddToTail(dataGiven);
		}
		else{
			while(numOfLines < lineGiven-1)
			{
				whateverAddToTail("\n");
				insertedFurtherAway.lineNumber++;
			}
			whateverAddToTail(dataGiven);
		}
		undoStack.push(insertedFurtherAway);
	}

    void insertTextInBetween(string dataGiven, int lineGiven){		//this function will insert text in the given line, and will push all the other lines
		if (lineGiven == 0){
			cout<<"There's no line 0, did you mean 1 (cough...Google suggestions...cough)"<<endl;
		}
		else if (lineGiven == 1){
			if (head == NULL)					//no node, empty linked list
			{
				node *temp;
				temp = new node;
				temp->data = dataGiven;
				temp->next = NULL;
				head = temp;
				tail = head;
				numOfLines++;
			}
			else 								//one or more than one node
			{
				node *temp;
				temp = new node;
				temp->data = dataGiven;
				temp->next = NULL;
				temp->next = head;
				head = temp;
				numOfLines++;
			}
			//May be unnecessary, dunno
			undo insertedToHead;
			insertedToHead.lineNumber = 1;
			insertedToHead.commandNumber = 5;
			undoStack.push(insertedToHead);
			// addToHead(dataGiven);
			// numOfLines++;
		}
		else{
			node *prevNode = head;
			node *nextNode = head;
			node *temp = new node();
			temp->data = dataGiven;
			temp->next = NULL;
			int iterator = 2;
			while(iterator < lineGiven)
			{
				prevNode = prevNode->next;
				nextNode = nextNode->next;
				iterator++;
			}
			nextNode = nextNode->next;
			prevNode->next = temp;
			temp->next = nextNode;
			numOfLines++;
			undo insertedInBetween;
			insertedInBetween.lineNumber = lineGiven;
			insertedInBetween.commandNumber = 6;
			undoStack.push(insertedInBetween);
		}
	}

    void deleteLine(int lineGiven){							//this function should delete anything in the given line, also decreases the numOfLines
        if (head == NULL){
            cout<<"There is no line to be deleted/removed."<<endl;
        }
        else if(head == tail){
            node *temp = head;
            delete(temp);
            head = NULL;
            tail = NULL;
            numOfLines--;
        }
        else if(lineGiven == 0){
            cout<<"There's no line 0, did you mean 1 (cough...Google suggestions...cough)"<<endl;
        }
        else if(lineGiven == 1){
            string backup = head->data;
            node *temp = head;
            node *nextNode = head->next;
            head = nextNode;
            delete(temp);
            numOfLines--;
            undo headRemoved;
            headRemoved.text = backup;
            headRemoved.lineNumber = 1;
            headRemoved.commandNumber = 12;
            undoStack.push(headRemoved);
        }
        else if(lineGiven == numOfLines){
            node *temp = head;
            undo deletedLine;
            deletedLine.commandNumber = 11;
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            string backup = temp->next->data;
            delete temp->next;
            temp->next = NULL;
            numOfLines--;
            deletedLine.text = backup;
            deletedLine.lineNumber = lineGiven;
            undoStack.push(deletedLine);

        }
        else if (lineGiven > numOfLines){
            cout<<"Entered line is larger than existing lines..."<<endl;
        }
        else if (lineGiven < numOfLines){
            undo deletedLine;
            deletedLine.commandNumber = 10;
            node *prevNode = head;
            node *nextNode = head;
            node *temp = head;
            int iterator = 2;
            while(iterator < lineGiven)
            {
                prevNode = prevNode->next;
                nextNode = nextNode->next;
                iterator++;
            }
            nextNode = nextNode->next;
            temp = nextNode;
            nextNode = nextNode->next;
            prevNode->next = nextNode;
            string backup = temp->data;
            delete(temp);
            numOfLines--;
            deletedLine.text = backup;
            deletedLine.lineNumber = lineGiven;
            undoStack.push(deletedLine);
        }   
    }

    void printAll(){						//function used to print the whole linked list
		node *temp = head;
		int linePrinted = 1;
		int pagePrinted = 2;
		int choice;
		if (head == NULL)
		{
			cout<<"no elements here, yay!"<<endl;
		}
		else{
			while(temp!=NULL)
			{
				if (linePrinted == 1)
				{
					cout<<"-------------------Page "<<"1"<<"-------------------\n";
				}
				else if ((linePrinted-1) % 10 == 0)
				{
					cout<<"-------------------Page "<<pagePrinted<<"-------------------\n";
					pagePrinted++;

				}
				cout<<linePrinted<<") "<<temp->data<<endl;
				temp = temp->next;
				linePrinted++;
			}
		}
	}

    void saveAll(){     //
		node *temp = head;
		int linePrinted = 1;
		int pagePrinted = 2;
		string fileName;
		cout<<"Enter the file name : ";
		cin>>fileName;
		fileName+=".txt";
		outfile.open(fileName, ios_base::app);
		while(temp!=NULL)
		{
			outfile<<temp->data;
			temp = temp->next;
			linePrinted++;
		}
		outfile.flush();
		outfile.close();
	}
};

int main(int argc, char const *argv[])
{
	linked_list ourList;
	return 0;
}
