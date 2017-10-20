#include "autocompleter.h"
#include <algorithm>

Autocompleter::Autocompleter(string filename)
{
	ifstream inFile;
	inFile.open(filename);

	vector<Entry> vEntries;

	while (!inFile.eof())
	{
		Entry e;
		inFile >> e.s;
		inFile >> e.freq;
		vEntries.push_back(e);
		
	}


	inFile.close();
	sort(vEntries.begin(), vEntries.end(), compare_s);

	root = balanced_tree_recurse(vEntries, 0, vEntries.size() - 1);


}

Autocompleter::Node* Autocompleter::balanced_tree_recurse(vector<Entry> &Ve, int start, int end)
{
	if (start > end)
		return NULL;

	int midpoint = (start + end) / 2;

	Node *r = new Node(Ve[midpoint]);

	r->left = balanced_tree_recurse(Ve, start, midpoint - 1);
	r->right = balanced_tree_recurse(Ve, midpoint + 1, end);

	return r;


}

int Autocompleter::size()
{
	return size_recurse(root);
}

int Autocompleter::size_recurse(Node *root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return (1 + size_recurse(root->left) + size_recurse(root->right));
}

int Autocompleter::completion_count(string x)
{
	return completion_count_recurse(x, root);
}

int Autocompleter::completion_count_recurse(string x, Node* root)
{
	if (root == nullptr)
	{
		return 0;
	}

	int sLength = x.size();

	if (root->e.s.substr(0, sLength) == x)
	{
		return 1 + completion_count_recurse(x, root->left);
	}
	else if (root->e.s.substr(0, sLength) > x)
	{
		return 0 + completion_count_recurse(x, root->left);
	}
	else
		completion_count_recurse(x, root->right);
}

//void Autocompleter::completions(string x, vector<string> &C)
//{
//	vector<Entry> E;
//	completions_recurse(x, root, E);
//	for (int i = 0; i < E.size(); i++)
//	{
//		C.push_back(E[i].s);
//	}
//}
////
//void Autocompleter::completions_recurse(string x, Node* root, vector<Entry> &E)
//{
//	
//	if (root == nullptr)
//		return;
//	
//
//	//Get the substring from the string in the entry
//	//that equals in size of input string
//	int sLength = x.size();
//
//	//recurse
//	//if input string is equal to the substring of the entry
//	if (root->e.s.substr(0, sLength) <= x)
//	{
//		
//		E.push_back(root->e); //E.push_back(completions_recurse(x, root->left, E);????????
//		completions_recurse(x, root->left, E);
//		cout << root->left->e.freq;
//	}
//	else
//		completions_recurse(x, root->right, E);
//}