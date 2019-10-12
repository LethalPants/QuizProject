/*
  This project will take questions from a quiz.txt file and display them on a screen and then will expect an input from the user and check 
  the answers against those in the file and generate a score card.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>


#define QUESNO 10
#define TOTALQUES 35

using namespace std;

class Quiz {
private:
	string file_text; //gets the questions and options from file
	string option1, option2, option3, option4, option, correct, category;
	int score;
	int file_loc[TOTALQUES];
	int loc;
private:
	void splash_screen()
	{
		cout << "\n\n\n\n\n\n";
		cout << "\n\t   +----------------------------------------------------------------+\t   ";
		cout << "\n\t   |                                                                |\t   ";
		cout << "\n\t   |       |      |         |            |               /          |\t   ";
		cout << "\n\t   |       |      |         |            |              /           |\t   ";
		cout << "\n\t   |    // |      |         |            |             /            |\t   ";
		cout << "\n\t   |   //  |      |         |            |            /             |\t   ";
		cout << "\n\t   +----------------------------------------------------------------+\t   ";
		cout << "\n\n\n\n\t\t\t  ***** PRESS ENTER TO PLAY *****    ";
		cout << "\n\n\n\t\t\t  RULES OF THE GAME      \n";
		cout << "\t\t\t  1) 4 MARKS WILL BE AWARDED FOR CORRECT     \n";
		cout << "\t\t\t  2) NO MARKS WILL AWARDED FOR INCORRECT     \n";
		cout << "\t\t\t  3) SCORE CARD WILL BE GIVEN AT END         \n";
		system("pause");
		system("cls");
	}

	void check_ans(ofstream& fout)
	{
		cout << "Your Option : ";
		cin >> option;

		//convert option to upper case and save to beginning of options and append a bracket
		transform(option.begin(), option.end(), option.begin(), ::toupper);
		option.append(")");

		fout << category << endl;

		if (option[0] == correct[0])
		{
			if (option[0] == option1[0])
				fout << "\nYour entered correct answer  : " << option1 << endl;
			if (option[0] == option2[0])
				fout << "\nYour entered correct answer  : " << option2 << endl;
			if (option[0] == option3[0])
				fout << "\nYour entered correct answer  : " << option3 << endl;
			if (option[0] == option4[0])
				fout << "\nYour entered correct answer  : " << option4 << endl;

			score += 4;
			fout << "\nYou are awarded 4 marks for this correct answer " << endl;
		}
		else
		{
			string correct_answer;
			if (correct[0] == option1[0])
				correct_answer = option1;
			if (correct[0] == option2[0])
				correct_answer = option2;
			if (correct[0] == option3[0])
				correct_answer = option3;
			if (correct[0] == option4[0])
				correct_answer = option4;

			string wrong_answer;

			if (option[0] == option1[0])
				wrong_answer = option1;
			if (option[0] == option2[0])
				wrong_answer = option2;
			if (option[0] == option3[0])
				wrong_answer = option3;
			if (option[0] == option4[0])
				wrong_answer = option4;

			fout << "You entered     : " << wrong_answer << endl;
			fout << "Correct answer  : " << correct_answer << endl;
			fout << "You are awarded 0 marks for this wrong answer " << endl;


		}
		fout << " -----------------------------------------------------------------------------\n";
		fout << " -----------------------------------------------------------------------------\n";

	}

	void move_file_ptr(int index_file, ifstream& fin) {
		for (int i = file_loc[3 * index_file]; i < file_loc[loc]; i++)
		{
			string empty_string;
			getline(fin, empty_string);
		}
	}

	void generate_content(int index_file, ifstream& fin, ofstream& fout) {
		for (int i = 1; i <= 10; i++)
		{
			getline(fin, file_text);

			if (i == 1)
			{
				cout << "\n\n\n\n\n\nQ" << index_file + 1 << ") " << file_text;
				fout << "\nQ" << index_file + 1 << ") " << file_text << endl;
			}

			if (i == 2)
			{
				fout << file_text << endl;
			}

			if (i == 3)
				option1 = file_text;

			if (i == 4)
				option2 = file_text;

			if (i == 5)
				option3 = file_text;

			if (i == 6)
				option4 = file_text;

			if (i > 1 && i <= 7)
				cout << file_text << endl;

			if (i == 8)
				correct = file_text.substr(0, 40);
			if (i == 9)
				category = file_text.substr(0, 40);
		}

		check_ans(fout);

		if (file_loc[loc] + 10 < file_loc[3 * (index_file + 1)])
		{
			for (int i = file_loc[loc] + 10; i < file_loc[3 * (index_file + 1)]; i++)
			{
				string empty;
				getline(fin, empty);
			}
		}
		system("cls");
	}

	void file_scores() {
		ifstream fout("scores.txt");
		string read;

		while (getline(fout, read))
		{
			cout << read << endl;
		}
	}

public:
	Quiz() {
		file_text = " ";
		option = " ";
		option1 = " ";
		option2 = " ";
		option3 = " ";
		option4 = " ";
		correct = " ";
		category = " ";
		score = 0;
		loc = 0;
	}

	void game_begin()
	{
		splash_screen();

		ifstream fin("questions.txt"); //opens the file with questions
		ofstream fout("scores.txt"); //opens the file with scores of different users

		//checks for errors in opening the file
		if (!fin)
		{
			cerr << "\n\n\n \t\t\t Quiz File Can't Be OPENED \t\t\t \n\n\n";
			return;
		}


		//initialize file location
		for (int i = 0; i < TOTALQUES; i++)
		{
			file_loc[i] = 10 * i + 1;
		}

		//generating 10 questions randomly from file
		for (int index_file = 0; index_file < QUESNO; index_file++)
		{
			//generate random number
			srand(time(NULL));
			int rand_num = rand() % 3;
			loc = (3 * index_file) + rand_num;

			//move file pointer from empty location
			move_file_ptr(index_file, fin);
			//generate question content
			generate_content(index_file, fin, fout);

		}

		//print result
		fout << "\nYou got " << score / 4 << " correct answer with total score : " << score << " out of 40 ";

		fin.close();
		fout.close();

		file_scores();

		system("pause");
	}

};

int main() {
	Quiz Game;
	Game.game_begin();
	return 0;
}







