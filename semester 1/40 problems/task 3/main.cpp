#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Represents edges; <K> for edge
// towards us, <O> for edge from us
enum edge {K, O};

// Represents fold of ribbon; <F>
// for front fold, <B> for back fold
enum fold {B, F};

// Front Fold - O,K,O,K
// Back Fold - K,O,K,O

// Edges in ribbon are stored in form
// of binary tree, level by level
typedef vector<edge> ribbon;

// Reads a sequence of folds and fills
// ribbon with appropriate edges
void read_folds(ribbon &tar);

// Reads a sequence of edges and transforms
// it to be stored level by level
void read_edges(ribbon &tar);

// Calculates number of 'levels'
const int getHeight(ribbon &src);

// Adds 'level' of edges to ribbon according to fold type
void add_front_fold(ribbon &tar, int level_length);
void add_back_fold(ribbon &tar, int level_length);

// Prints ribbon to console
void print_edges(ribbon src, int start_edge = 0);

// Checks a segment of ribbon to generate
// a corresponding type of fold
int get_fold(ribbon src, int start, int level);

// Generates folds for every level of edges
void get_sequence(ribbon src);

///-------------------------------------------------------------------------------------------------------------------]

// In case of a Front fold edges appear as
// O K O K ...
void add_front_fold(ribbon &tar, int level_length) {
	for (int i = 0; i < level_length; i++) {
		if (i % 2) {
			tar.push_back(K);
		}
		else tar.push_back(O);
	}
}
// In case of a Front fold edges appear as
// K O K O ...
void add_back_fold(ribbon &tar, int level_length) {
	for (int i = 0; i < level_length; i++) {
		if (i % 2) {
			tar.push_back(O);
		}
		else tar.push_back(K);
	}
}

// Calculates number of 'levels'
const int getHeight(ribbon &src) {
	int base = 2;
	int multiplier = 2;
	int size = src.size();
	int counter;
	for (counter = 1; base < size; counter++) {
		base *= multiplier;
	}
	if (base - 1 - size) return -1;
	return counter;
}

// Reads a sequence of folds entered by user and
// adds them to ribbon one by one
void read_folds(ribbon &tar) {
	double current_level = 0;
	cout << "Please enter sequence of folds - letters 'F' \nand 'B', separated by 'space' symbol" <<endl;
	cout << "Enter 'X' to stop entering folds" << endl;

	char input_symbol = 'K';
	// Loop used to let user decide the quantity of folds
	while (input_symbol != 'X') {
		cin >> input_symbol;

		// Add front fold
		if (input_symbol == 'F') {
			add_front_fold(tar, pow(2, current_level));
		}
		// Add back fold
		else if (input_symbol == 'B') {
			add_back_fold(tar, pow(2, current_level));
		}
		// Every fold gives us a new 'level' of edges
		current_level++;
	}
};

// Read a sequence of edges and transform
// it to be stored level by level
void read_edges(ribbon &tar) {
	cout << "Please enter sequence of folds - letters 'K' \nand 'O', separated by 'space' symbol" <<endl;
	cout << "Enter 'X' to stop entering edges" << endl;

	// For example, for input "K O O (K) K K O"
	// (brackets mean 'middle') levels would be:
	//
	// 0: K
	// 1: O K
	// 2: K O K O
	//
	// and edges should be stored 'level by level'
	// so ribbon must look like "K O K K O K O"

	// Reading edges in temporary ribbon. Edges
	// in tmp are NOT stored level by level!!!

	ribbon tmp;
	char input_symbol = 'K';

	while (input_symbol != 'X') {
		cin >> input_symbol;
		if (input_symbol == 'K') {
			tmp.push_back(K);
		}
		else if (input_symbol == 'O') {
			tmp.push_back(O);
		}
	}

	// Check if sequence has 2^n - 1 elements,
	// where 'n' is height of a tree
	int height = getHeight(tmp);

	// if getHeight returned -1, sequence is too
	// short to be a ribbon (some edges are missing)
	if (height == -1) {
		cout << "Sequence cannot be formed by folds!" << endl;
		return;
	}
	// Number of edges in sequence
	int size = tmp.size();

	// We get start element for every level, calculate
	// level step and push every (level_step)'th edge
	// into target ribbon

	for (int current_level = 0; current_level < height; current_level++) {

		int current_level_start = size / pow(float(2), current_level + 1);
		int current_level_step = pow(float(2), height - current_level);

		for (int i = current_level_start; i < size; i+=current_level_step) {
			tar.push_back(tmp.at(i));
		}
	}

	// Delete temporary ribbon
	tmp.~vector();
}

// Print edges to console
void print_edges(ribbon src, int start_edge) {
	if (start_edge >= src.size()) return;

	print_edges(src, 2 * start_edge + 1);

	if (src[start_edge] == K) cout << "K ";
	else cout << "O ";

	print_edges(src, 2 * start_edge + 2);
}

// Checks a segment of ribbon to generate
// a corresponding type of fold
int get_fold(ribbon src, int start, int level) {
	for (int i = start; i < start + pow(2, static_cast<double>(level)) - 1; i++) {
		if (src[i + 1] == src[i]) return -1;
	}

	return src[start];
}

// Generates folds for every level of edges
void get_sequence(ribbon src) {

	// We look through ribbon level by level
	// Level is defined by starting edge and
	// length which is equal to 2^n
	int current_level = 0;
	int level_start = 0;

	vector<fold> sequence;

	while (level_start < src.size()) {
		// Get fold from current level
		int current_fold = get_fold(src, level_start, current_level);

		// If level is invalid, print a message and quit
		if (current_fold == -1) {
			cout << "No such sequence!" << endl;
			return;
		}
		// Else we add fold to fold sequence, calculate
		// start edge for next level and increase level counter
		else sequence.push_back(static_cast<fold> (current_fold));

		level_start += pow(2, static_cast<double>(current_level));
		++current_level;
	}

	// Print fold sequence to console
	for (int i = 0; i < sequence.size(); i++) {
		if (sequence[i] == 0) cout << "B ";
		else cout << "F ";
	}
}
int main() {

	// Request folds, generate edges
	ribbon generatedRibbon;
	read_folds(generatedRibbon);
	print_edges(generatedRibbon); cout << endl;
	cout << "--------------------------------------" << endl;

	// Request edges, generate folds
	ribbon userRibbon;
	read_edges(userRibbon);
	get_sequence(userRibbon); cout << endl;
	cout << "--------------------------------------" << endl;


	return 0;
}
