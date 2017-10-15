#include "autocompleter.h"

int Autocompleter::size()
{
	return size_recurse(root);
}

int Autocompleter::size_recurse(Node *root)
{
	return (size_recurse(root->left) + 1 + size_recurse(root->right));
}

void Autocompleter::completions(string x, vector<string> &C)
{
	
}

void Autocompleter::completions_recurse(string x, Node* root, vector<Entry> &E)
{
	if (root == nullptr)
		return;
	
	//recurse
	if (root->e.s[0] == x[0])
	{
		E.push_back(root->e.s);
		return(completions_recurse(x, root->left, E) && completions_recurse(x, root->right, E));
	}
}