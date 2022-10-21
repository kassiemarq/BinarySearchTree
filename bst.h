#include <iostream>
using namespace std;

#ifndef BST
#define BST

//using template
class Bst{

public:
	//constructor
	Bst();

	bool empty() const;

	//search for data
	bool search(const char item) const;

	void insert(const char item);
	void remove(const char item);


	//accessory func
	void displayPreorder(ostream &out) const;
	void displayCountLeaves(ostream &out) ;
	void displaySibling(ostream &out, const char item) const;

private:
	class LRNode{
	public:
		char data;
		LRNode *left;
		LRNode *right;


	//default const for LRNODE
	LRNode()
	:data(0), left(0), right(0)
	{}

	//explicit const for LRNODE
	LRNode(char item)
	:data(item),left(0),right(0)
	{}

	};//end of class LRNode


	void search2(const char item, bool &found, LRNode* &locptr, LRNode* &parent) const;
	void preorder(ostream &out, Bst :: LRNode* treePtr) const;
	int countLeaves(Bst :: LRNode* treePtr);
	void sibling(ostream &out, Bst :: LRNode* treePtr, const char item) const;

	LRNode* myRoot;

}; //end of BST



//definition of constructor BinST
inline Bst::Bst()
:myRoot(0)
{}


//definition of insert
inline void Bst::insert(const char item){

	//***local variables
Bst::LRNode* locptr;
Bst::LRNode* parent;
locptr = myRoot; //**locptr serves as the search
parent = 0;
bool found = false;


//case I: TREE IS NOT EMPTY, this case will search and determine if we need to go to nxt case
while(!found && locptr != 0){ //**once locptr = null, we stop and go to next case (locptr == 0)
	parent = locptr; //set parent to placehold root

	//case to descend left since item is less than
	if(item < locptr->data)
		locptr = locptr->left;

	//case to descend right since item is >
	else if(item > locptr -> data)
		locptr = locptr->right;

	else
		found = true;
}

//case II: (locptr = 0) tree is either empty or we hit an empty spot.
if(!found ){

	//**replace locptr with new value node since we hit the null spot.
	locptr = new Bst::LRNode(item);

	//case where it's empty tree
	if (parent == 0)
		myRoot = locptr;

	//**REMEMBER WE STILL HAVE OUR PARENT NODE

	//**descend left if item <
	else if(item < parent->data)
		parent->left = locptr;
	else
		parent->right = locptr;
}

//case III: already found in root node
else
	cout << "Item is already in the tree. Ignore next message." <<endl;

}//end insert





//definition of empty
inline bool Bst::empty() const{
return myRoot == 0; //***returns empty true if root is null
}






//definition of search
inline bool Bst::search(const char item) const{

	Bst::LRNode* locptr = myRoot;
	bool found = false;

	while(!found && locptr != 0){

		//case where we descend left since item is less than
		if(item < locptr->data)
		locptr = locptr ->left;

		//case where we descend right since item is greater than
		else if(item > locptr->data)
		locptr = locptr->right;

		else
			found = true;
	}
	return(found);
}




//definition of search2
inline void Bst::search2(const char item, bool &found, LRNode* &locptr, LRNode* &parent) const{
	/* search2 will aid the remove process.
	 * search 2 will carry the memory address of a node if found in variable locptr.
	 *technique we will use is having both a parent and locptr
	 */
	locptr = myRoot;
	parent = 0;
	found = false;

	while(!found && locptr != 0){//locptr continues until we reached the end

		if(item < locptr-> data){
			parent = locptr;
			locptr = locptr->left;
		}

		else if(item > locptr->data){
			parent = locptr;
			locptr = locptr-> right;
		}

		else
			found = true;
	}
}//end search2





//definition of of remove
inline void Bst::remove(const char item){
	/*remove will use search2 function to locate if item exists in bst.
	 * if so, search2 will return the locptr and find the case.
	 * III CASES IN REMOVE
	 * I. node has 2 children
	 * II. node has 1 child
	 * III. node has no child
	 */
	bool found;
	Bst::LRNode* x;
	Bst::LRNode *parent;

	//recall args in search2(const char item, bool &found, LRNode* &locptr, LRNode* &parent) const
	search2(item, found, x, parent);

//EITHER NOT FOUND
	if(!found){
		cout << "Item not in BST" << endl;
		return;
	}

//OR FOUND

	if(x->left != 0 && x->right !=0){ //CASE WITH 2 CHILDREN
									   //we must find pred OR suc & it's parent
									   //we will use the parent to use its ptrs to manipulate to REMOVE
		                               //inorder pred/suc has mem address we want to delete & data we use for locptr

	//declare new node called xSucc(left most child of the right subtree)
	Bst::LRNode* xSucc = x->right; //this will take us to the right subtree side of locptr/x(node that we want to remove)

	//now we find the leftmost child of x's right subtree so we can replace its data to the node we want to delete
	parent = x; //initialize parent to x

	while(xSucc->left != 0){ //while we haven't reached the left most child
	parent = xSucc; 		 //parent will follow xSuc until xSuc has reached null.
	xSucc = xSucc->left;
	}

	//now that we have the left most child, lets proceed

	x->data = xSucc->data; //x's new data replaced with the inorder successor

	x = xSucc; // x is now pointing to the place we want to remove
				//**WE BASICALLY DELETE x BY OVERWRITING IT WITH A A CORRECT VALUE IN A NODE
				//**THEN THE NODE WE CHOSE TO OVERWRITE IT WITH WE DELETe it

	}//end if

	Bst::LRNode* subtree;
	subtree = x->left;

	if(subtree == 0) //NO LEFT CHILD
		subtree = x->right; //CHECK THE RIGHT CHILD
	if(parent == 0)
		myRoot = subtree;

	else if(parent->left == x)
		parent->left = subtree;

	else
		parent->right = subtree;

	cout << x->data << " has been removed from the BST" << endl;
	delete x;

}//end remove


inline void Bst::preorder(ostream &out, Bst :: LRNode* treePtr) const{
	/*	 *Algorithm Preorder(tree)
   1. Visit the root.
   2. Traverse the left subtree, i.e., call Preorder(left-subtree)
   3. Traverse the right subtree, i.e., call Preorder(right-subtree)
	 */



	  Bst::LRNode* leftptr;
	  Bst::LRNode *rightptr;


	if (treePtr != 0){
		out << treePtr->data << " ";

		      leftptr = treePtr->left;
			  rightptr = treePtr->right;

			  if(leftptr == 0)
			  cout << "null" << " ";
			  else
			  cout << "Left child is: "<< leftptr->data << " ";

			   if(rightptr == 0)
			  cout << "null" << endl;
			  else
			  cout << "Right child is: "<< rightptr->data << endl;

		preorder(out, treePtr->left);

		preorder(out, treePtr->right);
	}

} //end preorder

inline void Bst::displayPreorder(ostream &out) const{
	preorder(out, myRoot);
}

inline int Bst::countLeaves( Bst :: LRNode* treePtr){

	if(treePtr == NULL)
		return(0);

	if(treePtr->left == NULL && treePtr->right ==NULL)
		return(1);
	else
		return( countLeaves(treePtr->left) + countLeaves(treePtr->right) );

}


inline void Bst::displayCountLeaves(ostream &out) {
	out << "Number of leaves: " << countLeaves(myRoot);
	out << endl;
}//end displayLeaves



inline void Bst::sibling(ostream &out, Bst :: LRNode* treePtr, const char item) const{
	/*
	 * Enter the item and it will display the sibling of that item.
	 */
	bool found;
	Bst::LRNode* x;
	Bst::LRNode *parent;
	Bst::LRNode *child;

	search2(item, found, x, parent); //search2 will provide you with the address of locptr/x
	if(found == false)
		cout << "Item not found in the tree." << endl;

	//else if found
	else{
	//we know x points to the place where its found
		if(parent == 0)
			cout << "No siblings." << endl;
		else if(parent->right == x){ //then print the left child
		child = parent->left;
		if(child == NULL){
			cout << "Item has no sibling." <<endl;
		}
		else
			cout << "Sibling is: " << child->data << endl;

		}

		else if(parent->left == x){ // then the sibling is on the right side
		child = parent->right;
		if(child == NULL){
			cout << "Item has no sibling." <<endl;
			}
				else
			cout << "Sibling is: " << child->data << endl;
		}


	}//end else of found
}

inline void Bst::displaySibling(ostream &out, const char item) const{
	sibling(cout, myRoot, item);
}


#endif
