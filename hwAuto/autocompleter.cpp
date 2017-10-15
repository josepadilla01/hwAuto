#include "autocompleter.h"
#include <algorithm>

Autocompleter::Autocompleter(string filename)
{
	ifstream inFile;
	inFile.open("words.txt");

	vector<Entry> vEntries;
	Entry e;

	while (true)
	{
		inFile >> e.s;
		inFile >> e.freq;

		if (e.s == "")
			break;

		vEntries.push_back(e);
	}

	inFile.close();
	sort(vEntries.begin(), vEntries.end(), compare_s);

	balanced_tree_recurse(vEntries, 0, vEntries.size() - 1);
	
}

//int Autocompleter::size()
//{
//	return size_recurse(root);
//}
//
//int Autocompleter::size_recurse(Node *root)
//{
//	return (size_recurse(root->left) + 1 + size_recurse(root->right));
//}
//
//void Autocompleter::completions(string x, vector<string> &C)
//{
//	vector<Entry> E;
//	completions_recurse(x, root, E);
//	for (int i = 0; i < E.size(); i++)
//	{
//		C.push_back(E[i].s);
//	}
//}
//
//void Autocompleter::completions_recurse(string x, Node* root, vector<Entry> &E)
//{
//	
//	if (root == nullptr)
//		return;
//	
//	//recurse
//	if (root->e.s <= x)
//	{
//		
//		E.push_back(root->e);
//		completions_recurse(x, root->left, E);
//		cout << root->left->e.freq;
//	}
//	else
//		completions_recurse(x, root->right, E);
//}