#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class coin_placement {

	// Task data
	int faces;			// N
	int tails;			// M
	int needFaces;		// L
	int step;			// S
	int numberOfSteps;	// K

	// Spots for coins
	vector<bool> places;
	vector<bool> flips;

	void fill_flips(int faces, int tails);
	void fill_no_flips(int faces, int tails);
	void place_coins(const int &faces_on_flips);

	int count_flips() const; // Calculates number of 'true' values in 'flips' vector
	void simulateFlips();	 // Simulates game process

	int makeMoreFaces(const int &balance);
	int makeLessFaces(const int &balance);

	void printTask();
public:
	coin_placement(char* input);
	~coin_placement(){};

	void printPlacement();

	void calculate();
};

// Constructor
coin_placement::coin_placement(char* input) {
	ifstream in(input);

	in >> faces >> tails >> needFaces >> step >> numberOfSteps;

	this->flips.resize(faces + tails, false);
	this->places.resize(faces + tails, false);
}

// Counts coins that change their orientation in game
int coin_placement::count_flips() const {
	int counter = 0;
	int coins = faces + tails;
	for (int i = 0; i < coins; i++) {
		if (flips.at(i)) ++counter;
	}
	return counter;
}

// Simulate flipping process
void coin_placement::simulateFlips() {
	int current_pos = 0;
	for (int i = 0; i < numberOfSteps; i++) {
		for (int j = 0; j < step; j++, ++current_pos);
		current_pos %= (faces + tails);

		// Flip 'current_pos' place
		flips.at(current_pos) = !(flips.at(current_pos));
	}
}

// Fills flipped spots with stated types
void coin_placement::fill_flips(int faces, int tails) {
	int coins = flips.size();
	for (int i = 0; i < coins; i++) {
		if (flips.at(i) == 1) {
			if (faces > 0) {
				places.at(i) = 1;
				faces--;
			}
			else if (tails > 0) {
				places.at(i) = 0;
				tails--;
			}
		}
	}
}

void coin_placement::fill_no_flips(int faces, int tails) {
	int coins = flips.size();
	for (int i = 0; i < coins; i++) {
		if (flips.at(i) == 0) {
			if (faces > 0) {
				places.at(i) = 1;
				faces--;
			}
			else if (tails > 0) {
				places.at(i) = 0;
				tails--;
			}
		}
	}
}

// Algorithmic part
int coin_placement::makeMoreFaces(const int &balance) {
	// Get values needed
	int total_flips = count_flips();
	int flipped_spots_for_tails = balance;
	int free_flipped_spots = total_flips - flipped_spots_for_tails;

	int &ffs = free_flipped_spots; // Short reference

	// First set of conditions - impossible IF:
	// 1) Need to flip more than possible
	// 2) We cannot divide remaining spots into two parts
	// 3) We need to place more faces on remaining spots than possible
	// 4) We need more tails than available

	if ( ffs < 0 || ffs % 2 || ffs / 2 > faces || ffs / 2 + balance > tails) {
		return 1;
	}

	// Second set of conditions - impossible if:
	// 1) We don't have a free face to place on starting position
	if ((flips.at(0) == 0) && (faces - ffs / 2 == 0) ) {
		return 1;
	}

	// Fill flipped spots with faces and tails
	fill_flips(ffs / 2, balance + ffs / 2);

	int rest_faces = faces - ffs / 2;
	int rest_tails = tails - balance - ffs / 2;

	// Fill unflipped spots with faces and tails
	fill_no_flips(rest_faces, rest_tails);

	return 0;
}

int coin_placement::makeLessFaces(const int &balance) {
	// Get values needed
	int total_flips = count_flips();
	int flipped_spots_for_faces = balance;
	int free_flipped_spots = total_flips - flipped_spots_for_faces;

	int &ffs = free_flipped_spots; // Short reference

	// First set of conditions - impossible IF:
	// 1) Need to flip more than possible
	// 2) We cannot divide remaining spots into two
	// 3) We need to place more tails on remaining spots than possible
	// 4) We need more faces than available

	if ( ffs < 0 || ffs % 2 || ffs / 2 > tails || ffs / 2 + balance > faces) {
		return 1;
	}

	// Second set of conditions - impossible if:
	// 1) We don't have a free face to place on starting position
	if ((flips.at(0) == 0) && (faces - (ffs / 2 + balance) == 0) ) {
		return 1;
	}

	// Fill flipped spots with faces and tails
	fill_flips(balance + ffs / 2, ffs / 2);

	int rest_faces = faces - balance - ffs / 2;
	int rest_tails = tails - ffs / 2;

	// Fill unflipped spots
	fill_no_flips(rest_faces, rest_tails);

	return 0;
}

// Main function, calls 'make more' or 'make less'
void coin_placement::calculate() {
	printTask();

	simulateFlips();

	int faces_balance = needFaces - faces;

	// If balance is positive, call function to make
	// more faces, else call function to make less
	int result;
	if (faces_balance > 0) result = makeMoreFaces(faces_balance);
	else result = makeLessFaces(faces_balance);

	if (result) {
		cout << "Impossible!" << endl;
	}
	else printPlacement();
}

// Console output methods
void coin_placement::printTask() {
	cout << "Faces: " << faces << "; Tails: " << tails << "; Step size: " << step << endl;
	cout << "Get " << needFaces << " faces in " << numberOfSteps << " steps." << endl;
}
void coin_placement::printPlacement() {
	for (int i = 0; i < places.size(); i++) {
		if (places.at(i)) cout << "F ";
		else cout << "T ";
	}
	cout << endl;
}


int main() {
	coin_placement game("input_task6.txt");
	game.calculate();

	return 0;
}
