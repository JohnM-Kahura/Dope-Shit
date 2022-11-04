#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include<iostream>
using namespace std;

// Defines a class BST
class BST
{
// Defines a structure for node
struct Node
{
// To store value
string value;
// To store key
int key;
// Pointer to point to left child
Node* leftChild;
// Pointer to point to right child
Node* rightChild;
// To store the height of the tree
int height;
};// End of structure

// Declares root node
Node* root;

// Function to clear the tree
void clearTree(Node* root)
{
// Checks if root is null then tree is empty
if(root == NULL)
return;
// Otherwise recursively call with left child
clearTree(root->leftChild);
// Otherwise recursively call with right child
clearTree(root->rightChild);
// Delete the current node
delete root;
}// End of function

// Function to insert a node and return the new reference
Node* insertNode(string val, int k, Node* newNode)
{
// Checks if newNode is null then tree is empty
if(newNode == NULL)
{
// Creates a new node
newNode = new Node;
// Assigns parameter value
newNode->value = val;
// Assigns parameter key
newNode->key = k;
// Sets the height to 0
newNode->height = 0;
// Sets new node left and right child is null
newNode->leftChild = newNode->rightChild = NULL;
}// End of if condition

// Otherwise checks if parameter key is less than the new node key value
else if(k < newNode->key)
{
// Recursively call the function with left child
newNode->leftChild = insertNode(val, k, newNode->leftChild);

// Checks if difference between the left and right height is 2
if(height(newNode->leftChild) - height(newNode->rightChild) == 2)
{
// Checks if parameter key value is less than the new node left key value
if(k < newNode->leftChild->key)
// Calls the function for single rotation
newNode = singleRightRotate(newNode);
// Otherwise calls the function for double rotation
else
newNode = doubleRightRotate(newNode);
}// End of if condition
}// End of else if condition

// Otherwise checks if parameter key is greater than the new node key value
else if(k > newNode->key)
{
// Recursively call the function with right child
newNode->rightChild = insertNode(val, k, newNode->rightChild);

// Checks if difference between the right and left height is 2
if(height(newNode->rightChild) - height(newNode->leftChild) == 2)
{
// Checks if parameter key value is less than the new node right key value
if(k > newNode->rightChild->key)
// Calls the function for single rotation
newNode = singleLeftRotate(newNode);
// Otherwise calls the function for double rotation
else
newNode = doubleLeftRotate(newNode);
}// End of if condition
}// End of else if condition

// Calls the function to get the height of the tree
newNode->height = max(height(newNode->leftChild), height(newNode->rightChild)) + 1;
// Returns the new root reference
return newNode;
}// End of function

// Function to perform single right rotation
Node* singleRightRotate(Node* &root)
{
// Creates a temporary node points to left child
Node* temp = root->leftChild;
// Root left child points to temp right child
root->leftChild = temp->rightChild;
// Temp right child points to root
temp->rightChild = root;
// Calls the function to get the maximum height and stores it as root height
root->height = max(height(root->leftChild), height(root->rightChild)) + 1;
// Calls the function to get the maximum height and stores it as temp height
temp->height = max(height(temp->leftChild), root->height) + 1;
// Returns the temp
return temp;
}// End of function

// Function to perform single left rotation
Node* singleLeftRotate(Node* &root)
{
// Creates a temporary node points to left child
Node* temp = root->rightChild;
// Root right child points to temp left child
root->rightChild = temp->leftChild;
// Temp left child points to root
temp->leftChild = root;
// Calls the function to get the maximum height and stores it as root height
root->height = max(height(root->leftChild), height(root->rightChild)) + 1;
// Calls the function to get the maximum height and stores it as temp height
temp->height = max(height(root->rightChild), root->height) + 1 ;
return temp;
}// End of function

// Function to perform double left rotation
Node* doubleLeftRotate(Node* &root)
{
// Calls the function to perform single right rotation
// stores the reference in root right child
root->rightChild = singleRightRotate(root->rightChild);
return singleLeftRotate(root);
}// End of function

// Function to perform double right rotation
Node* doubleRightRotate(Node* &root)
{
// Calls the function to perform single right rotation
// stores the reference in root right child
root->leftChild = singleLeftRotate(root->leftChild);
return singleRightRotate(root);
}// End of function

// Function to return the node reference having minimum key value
Node* findMin(Node* root)
{
// Checks if root is NULL then tree is empty return NULL
if(root == NULL)
return NULL;

// Otherwise checks if root left child is NULL then return the current node
else if(root->leftChild == NULL)
return root;

// Otherwise recursively call the function with left child
else
return findMin(root->leftChild);
}// End of function

// Function to return the node reference having maximum key value
Node* findMax(Node* root)
{
// Checks if root is NULL then tree is empty return NULL
if(root == NULL)
return NULL;

// Otherwise checks if root right child is NULL then return the current node
else if(root->rightChild == NULL)
return root;

// Otherwise recursively call the function with right child
else
return findMax(root->rightChild);
}// End of function

// Function to delete a node
Node* removeNode(string val, int k, Node* root)
{
// Declares a temporary node
Node* temp;

// Checks if root is NULL then tree is empty return NULL
if(root == NULL)
return NULL;

// Otherwise checks if parameter key value is less than the current node key value
else if(k < root->key)
// Recursively call the function with left child
root->leftChild = removeNode(val, k, root->leftChild);

// Otherwise checks if parameter key value is greater than the current node key value
else if(k > root->key)
// Recursively call the function with right child
root->rightChild = removeNode(val, k, root->rightChild);

// Element found with 2 children
else if(root->leftChild && root->rightChild)
{
temp = findMin(root->rightChild);
root->key = temp->key;
root->rightChild = removeNode(root->value, root->key, root->rightChild);
}
// With one or zero child
else
{
temp = root;
if(root->leftChild == NULL)
root = root->rightChild;
else if(root->rightChild == NULL)
root = root->leftChild;
delete temp;
}
if(root == NULL)
return root;

root->height = max(height(root->leftChild), height(root->rightChild)) + 1;

// If node is unbalanced
// If left node is deleted, right case
if(height(root->leftChild) - height(root->rightChild) == 2)
{
// right right case
if(height(root->leftChild->leftChild) - height(root->leftChild->rightChild) == 1)
return singleLeftRotate(root);
// right left case
else
return doubleLeftRotate(root);
}
// If right node is deleted, left case
else if(height(root->rightChild) - height(root->leftChild) == 2)
{
// left left case
if(height(root->rightChild->rightChild) - height(root->rightChild->leftChild) == 1)
return singleRightRotate(root);
// left right case
else
return doubleRightRotate(root);
}
// Returns the updated root
return root;
}// End of function

// Function to return height of the tree
int height(Node* root)
{
return (root == NULL ? -1 : root->height);
}// End of function

// Function to balance the tree
int getBalance(Node* root)
{
if(root == NULL)
return 0;
else
return height(root->leftChild) - height(root->rightChild);
}// End of function

// Function to traverse inorder
void inorder(Node* root)
{
if(root == NULL)
return;
inorder(root->leftChild);
cout << root->value<< " -> "<<root->key<<endl;
inorder(root->rightChild);
}// End of function

public:
// Default constructor to initialize root to NULL
BST()
{
root = NULL;
}// End of constructor

void insertNode(string value, int key)
{
root = insertNode(value, key, root);
}// End of function

void removeNode(string value, int key)
{
root = removeNode(value, key, root);
}// End of function

void display()
{
inorder(root);
cout << endl;
}// End of function
int height()
{
height(root);
}// End of function

// Function to search a key if found returns true otherwise returns false
bool search(const int &key, Node *root)
{
if(root == NULL)
return false;

else if(key < root->key)
return search(key, root->leftChild);

else if(key > root->key)
return search(key, root->rightChild);

else
return true;
}// End of function

bool search(const int &key)
{
if (search(key, root))
{
return true;
}
else
return false;
}// End of function
};// End of class

// main function definition
int main()
{
// Creates an object of the class BST
BST root;

// Calls the function to insert node
root.insertNode("twenty", 20);
root.insertNode("ten", 10);
root.insertNode("six", 6);
root.insertNode("fiffty six", 56);
root.insertNode("seventy five", 75);
root.insertNode("thirty nine", 39);

// Calls the function display tree nodes
root.display();

// Calls the function to delete a node from the tree
root.removeNode("twenty", 20);
// Calls the function display tree nodes
root.display();

// Calls the function to display height of the tree
cout<<"\n the  height of the tree is = "<<root.height();

// Calls the function to search a node in tree
if(root.search(90))
cout<<"\n 90 was found in the tree";
else
cout<<"\n 90 was not found in the tree";

// Calls the function to search a node in tree
if(root.search(56))
cout<<"\n56 was found in the tree";
else
cout<<"\n 56 was not found in the tree";
}
