#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Pair {
	string word = "";
	int count = 0;
};

int main() {
	int N = 5;
	int sizeOfMap = 1000;
	ifstream infile("file.txt");

	if(!infile.is_open()) {
		cout << "Can't open file :(" << std::endl;
		return 0;
	}

	string text = "";
	string s;

	Pair* array = new Pair[10000];

	string stopWords[1000];
	ifstream readFile("stopers.txt");

	if(!readFile.is_open()) {
		cout << "Something went wrong with reading file...";
		return 0;
	}

	string word = "";
	int cntStopWords = 0;

	read_stop_words:
	if(!getline(readFile, word)) {
		goto start_reading;
	} else {
		stopWords[cntStopWords++] = word;
		goto read_stop_words;
	}

	start_reading: 
	if(getline(infile, s)) {
		text += s + " ";
		goto start_reading;
	}
	end_reading:
		int j = 0;
		int len = text.size();
		int alreadyStored = 0;

		std::string temp = "";
		count_words: 
		if(j < len) {
			if(text[j] == ' ') {
				bool flag = false;
				int i = 0;
				store_max:
				if(i < alreadyStored && !flag ) {
					if(array[i].word == temp) {
						array[i].count ++;
						flag = true;
					}
					i++;
					goto store_max;
				} else goto end_store_max;

				end_store_max:
				if(!flag && temp != "") {
					array[alreadyStored].word = temp;
					array[alreadyStored].count = 1;
					alreadyStored++;
				}
				temp = "";
			} else {
				if(text[j] >= 'A' && text[j] <= 'Z') 
					text[j] = text[j] - 'A' + 'a';

				if( (text[j] >= 'a' && text[j] <= 'z') || (text[j] == '\'' && temp != "") ) {
					temp += text[j];
				}
			}
			j++;
			goto count_words;
		}
		int _i = 0;
		outer_sorting: 
		if(_i < alreadyStored) {
			int _j = 0;
			inner_sort:
			if(_j < alreadyStored - _i) {
				if(array[_j].count < array[_j + 1].count) {
					Pair p = array[_j];
					array[_j] = array[_j + 1];
					array[_j + 1] = p;
				}
				_j++;
				goto inner_sort;
			}
			_i++;
			goto outer_sorting;
		}

		end_outer_sorting: 
		int i = 0;
		int selected = 0;
		print:
		if(i < alreadyStored && selected < N) {
			int j = 0;
			bool isStopWord = false;
			check_if_stop_word:
			if(j < cntStopWords) {
				if(array[i].word == stopWords[j]) {
					isStopWord = true;
					goto end_check_if_stop_word;
				}
				j++;
				goto check_if_stop_word;
			}

			end_check_if_stop_word:
			if(!isStopWord) {
				cout << array[i].word << " - " << array[i].count << endl;
				selected++;
			}
			i++;
			goto print;
		} else goto finish;
		finish: 
			return 0;
}