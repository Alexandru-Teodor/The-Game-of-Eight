#include <iostream>
#include <cctype>
using namespace std; 

void InitialMessage();
void PlayGame();
int ChangePlayer(int player);
void DisplayCrtValIN(int initial_number);
void DisplayChoices(int chosen_number, int valid1, int valid2, int valid3);
void CheckValidChoices(int chosen_number, int &valid1, int &valid2, int &valid3);
int GetInput(int player, int chosen_number, int valid1, int valid2, int valid3);
bool CheckInput(int input, int valid1, int valid2, int valid3);
bool IsGameOver(int initial_number);
void DisplayResult(int player, int initial_number);
bool WantToPlayAgain();


int main() {
	InitialMessage();
	do {
		PlayGame();
	} while (WantToPlayAgain());
	return 0;
}

void PlayGame() {
	int initial_number = 8, player = 2, chosen_number = NULL;
	int valid1 = 1, valid2 = 2, valid3 = 3;
	do {
		player = ChangePlayer(player);
		DisplayCrtValIN(initial_number);
		CheckValidChoices(chosen_number, valid1, valid2, valid3);
		chosen_number = GetInput(player, chosen_number, valid1, valid2, valid3);
		initial_number -= chosen_number;

	} while (!IsGameOver(initial_number));
	DisplayResult(player, initial_number);
}

void InitialMessage() {
	cout << "The Game of Eight is played by 2 players.\n" <<
		"The game starts with the initial number 8.\n" <<
		"Each player should choose a valid number(from 1 to 3),\n" <<
		"  which will be substracted from the current value of the initial number.\n" <<
		"The next player cannot choose the number that the last player chose.\n"
		"If the initial number goes to 0 on your turn, then you win.\n" <<
		"Otherwise if the number goes below 0, your opponent wins.\n\n";
}

int ChangePlayer(int player) {
	if (player == 2) {
		return 1;
	}
	return 2;
}

void DisplayCrtValIN(int initial_number) {
	cout << "\nThe current value of the initial number is: " << initial_number << "\n";
}

void DisplayChoices(int chosen_number, int valid1, int valid2, int valid3) {
	int count = 0;
	if (chosen_number == NULL) {
		cout << "1, 2 and 3\n";
	}
	else {
		for (int i = 1; i <= 3; ++i) {
			if (chosen_number != i) {
				cout << i;
				++count;
				if (count == 1) {
					cout << " and ";
				}
			}
		}
		cout << "\n";
	}
}

void CheckValidChoices(int chosen_number, int& valid1, int& valid2, int& valid3) {
	if (chosen_number == NULL) {
		return;
	}
	if (chosen_number == 1) {
		valid1 = NULL, valid2 = 2, valid3 = 3;
	}
	else if (chosen_number == 2) {
		valid1 = 1, valid2 = NULL, valid3 = 3;
	}
	else if (chosen_number == 3) {
		valid1 = 1, valid2 = 2, valid3 = NULL;
	}
}

int GetInput(int player, int chosen_number, int valid1, int valid2, int valid3) {
	const int IGNORE_CHARS = 256;
	int input = NULL;
	bool failure;
	do {
		failure = false;
		cout << "Player " << player << ", please choose a number between: ";
		DisplayChoices(chosen_number, valid1, valid2, valid3);
		cin >> input;
		if (!CheckInput(input, valid1, valid2, valid3)) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << "\nInput error! Please try again!\n";
			failure = true;
		}
	} while (failure);
	cin.ignore(IGNORE_CHARS, '\n');
	return input;
}

bool CheckInput(int input, int valid1, int valid2, int valid3) {
	if (valid1 == NULL && input == 1) {
		return false;
	}
	else if (valid2 == NULL && input == 2) {
		return false;
	}
	else if (valid3 == NULL && input == 3) {
		return false;
	}
	else if (input < 1 || input > 3) {
		return false;
	}
	else if (cin.fail()) {
		return false;
	}
	return true;
}

bool IsGameOver(int initial_number) {
	return initial_number <= 0;
}

void DisplayResult(int player, int initial_number) {
	if (initial_number != 0) {
		player = ChangePlayer(player);
	}
	cout << "Congratulations, Player " << player << ", you won!\n";
}

bool WantToPlayAgain() {
	char answer;
	bool failure;
	const int IGNORE_CHARS = 256;

	do {
		failure = false;
		cout << "\nWould you like to play again? (y/n)\n";
		cin >> answer;
		if (!isalpha(answer)) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << "Input error! Please try again!\n";
			failure = true;
		}
		else {
			cin.ignore(IGNORE_CHARS, '\n');
			answer = tolower(answer);
		}
	} while (failure);
	return answer == 'y';
}