
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <vector>
#include "autocompleter.h"

using namespace std;
using namespace chrono;


inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
        abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


// Used later for testing
string random_string(int length)
{
	string s;
	for (int i = 0; i < length; ++i)
		s += 'a' + (rand() % 26); 
	return s;
} 

void interactive_mode()
{
	Autocompleter words("words.txt");
	vector<string> C;
	while (cin)
	{
		string line;
		getline(cin, line);
		words.completions(line, C);
		for (string s : C)
			cout << "    " << s << endl;
	}
	exit(0);
}

void test_size()
{
	system_clock::time_point start = system_clock::now();

	Autocompleter animals("animals.txt");
	test(animals.size() == 12);

	Autocompleter words("words.txt");
	test(words.size() == 300000);	

	system_clock::time_point end = system_clock::now();
	float dur = duration<float>(end - start).count();
	test(dur < 30.0);
}

void test_completion_count()
{
	system_clock::time_point start = system_clock::now();
	Autocompleter animals("animals.txt");
	test(animals.completion_count("a") == 4);
	test(animals.completion_count("b") == 0);
	test(animals.completion_count("c") == 4);
	test(animals.completion_count("g") == 4);
	test(animals.completion_count("h") == 0);
	test(animals.completion_count("q") == 0);
	test(animals.completion_count("aa") == 1);
	test(animals.completion_count("al") == 2);
	test(animals.completion_count("an") == 0);
	test(animals.completion_count("go") == 3);
	test(animals.completion_count("bi") == 0);
	test(animals.completion_count("cro") == 2);
	test(animals.completion_count("gir") == 1);
	test(animals.completion_count("croc") == 1);
	test(animals.completion_count("crow") == 1);
	test(animals.completion_count("goatcarp") == 0);
	test(animals.completion_count("") == 12);

	Autocompleter words("words.txt");
	test(words.completion_count("a") == 19361);
	test(words.completion_count("b") == 17901);
	test(words.completion_count("c") == 23739);
	test(words.completion_count("x") == 1307);
	test(words.completion_count("y") == 1850);
	test(words.completion_count("z") == 1999);
	test(words.completion_count("au") == 1138);
	test(words.completion_count("ch") == 3358);
	test(words.completion_count("hi") == 1148);
	test(words.completion_count("ma") == 5924);
	test(words.completion_count("wa") == 1872);
	test(words.completion_count("bir") == 183);
	test(words.completion_count("bat") == 235);
	test(words.completion_count("dro") == 141);
	test(words.completion_count("hap") == 69);	
	test(words.completion_count("hur") == 97);	
	test(words.completion_count("rer") == 25);	
	test(words.completion_count("tri") == 609);	
	test(words.completion_count("aldo") == 10);
	test(words.completion_count("code") == 74);
	test(words.completion_count("program") == 53);
	test(words.completion_count("autocomplete") == 1);
	test(words.completion_count("zzyzx") == 0);
	test(words.completion_count("") == 300000);
	system_clock::time_point end = system_clock::now();
	float dur = duration<float>(end - start).count();
	test(dur < 30.0);
}

void test_completions()
{
	system_clock::time_point start = system_clock::now();

	Autocompleter animals("animals.txt");	
	vector<string> results;
	
	animals.completions("a", results);
	test(results.size() == 4);
	test(results[0] == "alpaca");
	test(results[1] == "aardvark");
	test(results[2] == "albatross");
	test(results[3] == "armadillo");

	animals.completions("b", results);
	test(results.size() == 0);

	animals.completions("c", results);
	test(results.size() == 4);
	test(results[0] == "cat");
	test(results[1] == "camel");
	test(results[2] == "crow");
	test(results[3] == "crocodile");

	animals.completions("g", results);
	test(results.size() == 4);
	test(results[0] == "goat");
	test(results[1] == "goose");
	test(results[2] == "gorilla");
	test(results[3] == "giraffe");

	animals.completions("h", results);
	test(results.size() == 0);

	animals.completions("q", results);
	test(results.size() == 0);

	animals.completions("aa", results);
	test(results.size() == 1);
	test(results[0] == "aardvark");

	animals.completions("al", results);
	test(results.size() == 2);
	test(results[0] == "alpaca");
	test(results[1] == "albatross");

	animals.completions("an", results);
	test(results.size() == 0);

	animals.completions("go", results);
	test(results.size() == 3);
	test(results[0] == "goat");
	test(results[1] == "goose");
	test(results[2] == "gorilla");	

	animals.completions("bi", results);
	test(results.size() == 0);
	
	animals.completions("cro", results);
	test(results.size() == 2);
	test(results[0] == "crow");
	test(results[1] == "crocodile");	

	animals.completions("gir", results);
	test(results.size() == 1);
	test(results[0] == "giraffe");

	animals.completions("croc", results);
	test(results.size() == 1);
	test(results[0] == "crocodile");

	animals.completions("crow", results);
	test(results.size() == 1);
	test(results[0] == "crow");

	animals.completions("", results);
	test(results.size() == 12);
	test(results[0] == "cat");
	test(results[1] == "camel");
	test(results[2] == "goat");
	test(results[3] == "crow");
	test(results[4] == "goose");
	test(results[5] == "gorilla");
	test(results[6] == "crocodile");
	test(results[7] == "giraffe");
	test(results[8] == "alpaca");
	test(results[9] == "aardvark");
	test(results[10] == "albatross");
	test(results[11] == "armadillo");
	
	system_clock::time_point end = system_clock::now();
	float dur = duration<float>(end - start).count();
	test(dur < 30.0);
}

void test_perf()
{
	// Test constructor efficiency
	system_clock::time_point start = system_clock::now();
	Autocompleter words("words.txt");
	system_clock::time_point end = system_clock::now();
	float dur = duration<float>(end - start).count();
	test(dur < 7.0);

	// Test size() efficiency
	start = system_clock::now();
	test(words.size() == 300000);
	end = system_clock::now();	
	dur = duration<float>(end - start).count();
	test(dur < 0.02);

	// Test completion_count() efficiency
	start = system_clock::now();
	for (int i = 0; i < 10000; ++i)
		words.completion_count(random_string(3));
	end = system_clock::now();
	dur = duration<float>(end - start).count();
	test(dur < 0.4);

	// Test completions() efficiency
	vector<string> results;
	start = system_clock::now();
	for (int i = 0; i < 10000; ++i)
		words.completions(random_string(3), results);
	end = system_clock::now();
	dur = duration<float>(end - start).count();
	test(dur < 1.3);	
}

int main()
{
	// Setup
	srand(2017);

	// Uncomment line below to use your Autocompleter interactively
	// with the words.txt file.
	// Enter a string and press Enter - the autocompletions
	// results from words.txt are printed.
	// 
	// interactive_mode();

	test_size();             // Deadline 1
	test_completion_count(); // Deadline 2
	test_completions();      // Deadline 3
	test_perf();             // Deadline 4
	cout << "Assignment complete." << endl;
}



