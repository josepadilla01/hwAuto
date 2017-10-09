
#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <vector>
#include <string>

using namespace std;

class Autocompleter
{
	// For the mandatory running times below:
	// n is the number of strings in the dictionary of possible completions.
	// k is the number of completions of a given input.

	public:
		// Creates a dictionary of words and associated frequencies,
		// using the file as a source. The file is assumed to have
		// the following format:
		// word1 freq1
		// word2 freq2
		// ...
		// wordN freqN
		//
		// Hint: a rough idea for an algorithm is 
		// 1. Read the word-frequency pairs into a list of Entry objects (see below) 
		// 2. Sort the array.
		// 3. Build a balanced BST from the sorted array.
		//
		// Hint: check out the stol function in <string>
		//
		// Must run in O(n*log(n)) time.
		Autocompleter(string filename);

		// Returns the number of words in the dictionary
		// of possible completions. 
		// 
		// Must run in O(n) time.
		int size();

		// Returns the number of words in the dictionary
		// that start with x.
		// 
		// Must run in O(log(n) + k) time.
		int completion_count(string x);
	
		// Fills C with the completions of x, ordered from most
		// most-to-least frequent.
		// 
		// Must run in O(log(n) + k*log(k)) time.
		void completions(string x, vector<string> &C);

	private:
		// A helper class that stores
		// a word and a frequency.
		class Entry
		{
			public:
				string s;
				long long int freq; // Real frequencies can be very big	
		};

		// Useful for sorting a list of Entry objects from
		// small-to-large by their strings.
		// Use as third argument of the sort() function in <algorithm>
		static bool compare_s(Entry &e1, Entry &e2)
		{
			return e1.s < e2.s;
		}

		// Useful for sorting a list of Entry objects from
		// large-to-small by frequencies.
		// Use as third argument of the sort() function in <algorithm>
		static bool compare_freq(Entry &e1, Entry &e2)
		{
			return e1.freq > e2.freq;
		}



		// A helper class that implements a binary search tree node.
		class Node
		{
			public:
				Entry e;
				Node* left;
				Node* right;
		};

		// Root of the binary-search-tree-based data structure
		Node* root;


		// Optional helper methods (you'll probably want them).

		// Returns a pointer to the root of a tree containing 
		// the elements of Ve from indices start to end.
		Node* balanced_tree_recurse(vector<Entry> &Ve, int start, int end);

		// Returns the size of the tree with the given root.	
		int size_recurse(Node* root);

		// Returns the number of strings starting with x in 
		// the tree with the given root.
		int completion_count_recurse(string x, Node* root);

		// Fills a vector with the strings that start with x in 
		// the tree with the given root.
		void completions_recurse(string x, Node* root, vector<Entry> &E);
};

#endif

