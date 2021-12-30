#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<iomanip>

using namespace std;

struct Display
{
	string words;;
	int count;
};

struct Node
{
	Display value;
	Node* pLeft;
	Node* pRight;
};

Node* add(Node* tree, Display value);
Node* addNode(Node* tree, Node* toAdd);

bool treeContains(Node* tree, string word) ;
void displayAlphabetTree(Node* tree);

int main()
{
	Display value;
	string choiceStr;
	char choice;
	bool eofReached = false;

	value.count = 0;

	Node* tree = 0;

	string txtFile;

	cout << "Enter filename: ";
	cin >> txtFile;
	cout << endl;

	ifstream read(txtFile.c_str());

	if(!read)
	{
		cout << "Error, can't open file" << endl;
		exit(1);
	}
	else
	{
		while(!read.eof())
		{
			read >> value.words;
			eofReached = read.eof();

			if (treeContains(tree, value.words) == false)
			{
				tree = add(tree, value);
			}
		}
	}

	read.close();

	do
	{
		cout << "  a - display alphabetic list" << endl;
		cout << "  f - display frequency ordered list" << endl;
		cout << "  s - display statistics" << endl;
		cout << "  x - exit" << endl;
		cout << endl;
		cout << "Enter choice: ";
		cin >> choiceStr;

		choice = choiceStr.length() == 0 ? choice = 'e' : choice = choiceStr[0];

		switch(choice)
		{
		case 'a':
		case 'A':
			displayAlphabetTree(tree);
			break;
		case 'x':
		case 'X':
			break;
		default:
			cout << "Error, invalid choice";
			break;
		}
	}
	while(choice != 'x');
}

Node* add(Node* tree, Display value)
{
        //tempPtr is a temporary pointer

	Node* tempPtr = new Node;
	tempPtr->value = value;
	tempPtr->pLeft  = 0;
	tempPtr->pRight = 0;
	return addNode(tree, tempPtr);
}

Node* addNode(Node* tree, Node* toAdd)
{
	if (tree == 0)
	{
		return toAdd;
	}
	else
	{
		if(toAdd->value.words < tree->value.words)
		{
			tree->pLeft = addNode(tree->pLeft, toAdd);
			return tree;
		}
		else if(toAdd->value.words == tree->value.words)
		{
			tree->value.count++;
			return tree;
		}
		else
		{
			tree->pRight = addNode(tree->pRight, toAdd);
			return tree;

		}
	}

}

bool treeContains(Node* tree, string word)
{
	// If a word is in the binary
        // tree then true is returned.
	// Vice versia, false is returned if not.

	if (tree == NULL)
	{
        // Tree is empty, so it certainly doesn't contain item.
        return false;
    }
   else if (word == tree->value.words)
   {
       //The word matches to one in the root node.
       return true;
    }
    else if (word < tree->value.words)
	{
		// The word is less than the one in the root node
		// and must be sent to the left subtree.
		return treeContains(tree->pLeft, word);
    }
    else
	{
		// The word is more than the one in the root node
		// and must be sent to the right subtree.
        return treeContains(tree->pRight, word);
     }
}


void displayAlphabetTree(Node* tree)
{
    if(tree != 0)
	{
		displayAlphabetTree(tree->pLeft);
		displayAlphabetTree(tree->pRight);
		cout<<tree->value.words<<"  "<<"["<<tree->value.count<<"]"<<endl;
	}
}
