#include <iostream>
using namespace std;
#include "bst.h"


void insertNodes(int numNodes, Bst *tree);

int main(void){

	Bst tree;
	int choice;
	char node;
	int numNodes;


	cout << "WELCOME TO BST!" << endl;
	cout << "-------------------- MENU ----------------------" << endl;
	cout << "1. Insert node(s)" << endl;
	cout << "2. Traverse Preorder" << endl;
	cout << "3. Search BST" << endl;
	cout << "4. Delete node" << endl;
	cout << "5. Leaf Count" << endl;
	cout << "6. Sibling of a node" << endl;
	cout << "7. Quit" << endl;

	cout << "Enter your choice: " << endl << endl;

	if(cin >> choice){

	while (choice != 7) {
		if (choice == 1) {

	while(1){
			cout << "Enter number of items to insert:" << endl;
			if(cin >> numNodes)
			break;

			else {
				cout << "Invalid input. Please try again.";
				cin.clear();
				while(cin.get() != '\n');
			}
	}//end while true
		insertNodes(numNodes, &tree);
		}//end choice one


		else if (choice == 2) {

			tree.displayPreorder(cout);
			cout << endl;
		}
		else if (choice == 3) {
			cout << "Enter item you want to search for:" << endl;

			cin >> node;
			if(tree.search(node)) {
				cout << node << " is found in the BST" << endl;
			} else {
				cout << node << " is not found in the BST" << endl;
			}
		}
		else if (choice == 4) {
			cout << "Enter item you want to delete:" << endl;
			cin >> node;
			tree.remove(node);

		}
		else if (choice == 5) {
			tree.displayCountLeaves(cout);
		}

		else if (choice == 6) {
			cout << "Enter the item you want to find the sibling of:" << endl;
			cin >> node;
			tree.displaySibling(cout, node);
		}

		else
			cout << "Invalid input" << endl;
		
        cout << "\n";
        cout << "Enter another choice" << endl;
        cout << "-------------------- MENU ----------------------" << endl;
        cout << "1. Insert node(s)" << endl;
        cout << "2. Traverse Preorder" << endl;
        cout << "3. Search BST" << endl;
        cout << "4. Delete node" << endl;
        cout << "5. Leaf Count" << endl;
        cout << "6. Sibling of a node" << endl;
        cout << "7. Quit" << endl;
		cin >> choice;
	}

	cout << "Bye." << endl;
	return 0;

	}//end choice if

	else
		cout << "Invalid input. Program will terminate." <<endl;
}

void insertNodes(int numNodes, Bst *tree) {
	char item;
	for (int i = 0; i <numNodes; i++) {
		cout << "Please note: Uppercase characters only!" <<endl;
		cout << "Enter item" << endl;
		cin >> item;

		if(item < 'A' || item > 'Z' ){
			cout << "Item is either an invalid character or lowercase. Please only enter uppercase." <<endl;
			cout << "Please try again." <<endl;
			return;
		}

		else{
		tree->insert(item);
		cout << "Inserted." << endl;
		}

	}//end for

}

