#include <iostream>
#include <string>
#include <fstream>

struct Word {
	std::string word;
	int total = 0;
	int* pageNumbers = new int[100 + 1];
};

int main() {

	std::ifstream infile("file.txt");

	if(!infile.is_open()) {
		std::cout << "Can't open file :(" << std::endl;
		return 0;
	}

/* === Declare variables === */
/* ------------------------- */
	std::string text[5000];
	int currectPage = 1;
	int LINES_PER_PAGE = 45;
	int countLinesAlreadyAdded = 0;
	std::string temp = "";

	Word* array = new Word[10000];
	int alreadyStored = 0;
/* ------------------------- */

	start_reading: 
	if(getline(infile, temp)) {
		if(countLinesAlreadyAdded < 45) {
			countLinesAlreadyAdded ++;
		} else {
			currectPage++, countLinesAlreadyAdded = 1;
		}
		text[currectPage] += temp + " ";
		goto start_reading;
	}
	end_reading:

/***** Storing elements ******/
/*****************************/
	int j = 1;

	storing:
	if(j <= currectPage) {

		std::string page = text[j];
		int currPosition = 0;
		std::string tempWord;

		storeWords:
		if(currPosition < page.size()) {
			if(page[currPosition] == ' ') {
				bool flag = false;
				int i = 0;
				store_max:
				if(i < alreadyStored) {
					if(array[i].word == tempWord) {
						if(array[i].total >= 100) {
							array[i].total++;
						} else if(array[i].pageNumbers[array[i].total - 1] != j) {
							array[i].pageNumbers[array[i].total++] = j;
						}
						flag = true;
						goto end_store_max;
					}
					i++;
					goto store_max;
				}

				end_store_max:
				if(!flag) {
					array[alreadyStored].word = tempWord;
					array[alreadyStored].total = 1;
					array[alreadyStored].pageNumbers[0] = j;
					alreadyStored++;
				}
				tempWord = "";
			} else {
				if(page[currPosition] >= 'A' && page[currPosition] <= 'Z') 
					page[currPosition] = page[currPosition] - 'A' + 'a';

				if( (page[currPosition] >= 'a' && page[currPosition] <= 'z') 
					|| (page[currPosition] == '\'' && page != "") )
					tempWord += page[currPosition];
			}
			currPosition++;
			goto storeWords;
		}
		j++;
		goto storing;
	}

/********** Sorting **********/
/*****************************/
	sortWords:
	int _i = 0;
	outer_sorting: 
	if(_i < alreadyStored) {
		int _j = 0;
		inner_sort:
		if(_j < alreadyStored - _i) {
			if(array[_j].word > array[_j + 1].word) {
				Word p =  array[_j];
				array[_j] = array[_j + 1];
				array[_j + 1] = p;
			} 
			_j++;
			goto inner_sort;
		}

		end_inner_sort:
		_i++;
		goto outer_sorting;
	}

	
	end_outer_sorting: 
/********* Printing **********/
/*****************************/

	int wordIterator = 0;
	printing:
	if(wordIterator < alreadyStored) {
		if(array[wordIterator].total < 100 && array[wordIterator].word != "" && array[wordIterator].word != " ") {
			std::cout << array[wordIterator].word << " - ";
			int tempCounter = 0;
			printWordPages:
			if(tempCounter < array[wordIterator].total) {
				std::cout << array[wordIterator].pageNumbers[tempCounter];
				if(tempCounter != array[wordIterator].total - 1) {
					std::cout << ", ";
				}
				tempCounter++;
				goto printWordPages;
			}
			std::cout << std::endl;
		}
		wordIterator++;
		goto printing;
	}

	return 0;
}