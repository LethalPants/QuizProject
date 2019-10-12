# Quiz Project
DSL Mini Project: Quiz Platform
A console base quiz platform made in C++ .

# Features

  - Bunch of questions in the questions.txt file
  - Will randomly get questions from the file
  - Will store the players score and answer cards in a scores.txt file

# Class ADT
```C++
class Quiz {
private:
	string file_text; 
	string option1, option2, option3, option4, option, correct, category;
	int score;
	int file_loc[TOTALQUES];
	int loc;
	void splash_screen();
	void check_ans(ofstream& fout);
	void move_file_ptr(int index_file, ifstream& fin)
    void generate_content(int index_file, ifstream& fin, ofstream& fout);
    void file_scores();
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

	void game_begin();
```
