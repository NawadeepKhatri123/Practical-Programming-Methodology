#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <cctype>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <regex>
#include <iomanip>

using namespace std;

using COUNTER = tuple<int, int, int>;  // Tuple to hold number of letters, words, and lines
using WORD = std::string;		// use to store the string
using WORD_LIST = std::set<WORD>;	// sort the characters
using WORD_FREQ_LIST = std::map<char,int>;	// use to store the letters and occurrences
using WORD_FREQ = std::map<WORD,int>;
using FREQ_WORD_LIST = std::multimap<int,WORD>;	// use to store the words and occurrences
using LONGEST = std::priority_queue<WORD>;	// store the longest word


struct DICTION {
	COUNTER stats1{0, 0, 0};
	WORD_LIST words{};
	WORD_FREQ_LIST wordFreq{};
	FREQ_WORD_LIST freqWord{};
	LONGEST longWord{};
	WORD str{""};
	WORD_FREQ word{};
};

// Function to split a word into valid alphabetic chunks (ignoring numbers/special characters)
vector<WORD> splitWord(const WORD& word) {
    vector<WORD> result;
    string clean = "";
    // Iterate through each character in the word
    for (char c : word) {
        if (isalpha(c)) {
            clean += c;  // Append alphabetic characters
        } else {
            if (!clean.empty()) {
                result.push_back(clean);  // Push the valid word
                clean = "";  // Reset for the next segment
            }
        }
    }
    if (!clean.empty()) {
        result.push_back(clean);  // Push the last segment if any
    }
    return result;
}

// Function to count letters, words, and lines in a file and store all letters in a string
DICTION countTextFile(DICTION& stats) {

    int& letterCount = get<0>(stats.stats1);
    int& wordCount = get<1>(stats.stats1);
    int& lineCount = get<2>(stats.stats1);
    ifstream file("file.txt");  // Open file
    lineCount++;
    if (!file.is_open()) {
        cerr << "Error opening file!" << '\n';
        return stats;  // Return the empty struct if file couldn't be opened
    }

    WORD word;

    // Read each line from the file
    while (std::getline(file, word)) {

        stringstream ss(word);

        // Read each word in the line
        while (ss >> word) {
            wordCount++;
 		stats.str += word;          

            // Split word into alphabetic chunks
            vector<WORD> cleanedWords = splitWord(word);

            // Count letters in the word and store them
            for (const auto& clean : cleanedWords) {
                stats.freqWord.insert({clean.length(), clean});
 
		stats.longWord.push(clean);
                for (char c : clean) {
                    stats.wordFreq[c]++;
                    letterCount++;
                }
            }
	    stats.str += " ";
        }
    }

    return stats;  // Return the struct with all the counts and letters
}

int main() {
    int highest{0};
    string longest_word;
    vector<int> vec;
    DICTION stats{};
    countTextFile(stats);

     for (const auto& pair : stats.freqWord) {
	    
	     stats.word[(pair.second)]++;
	     if (pair.first > highest){
		highest = pair.first;
		longest_word = pair.second;
	     }
	    
	}
    cout<<endl;
    cout << "Words in the dictionary : ";
    for(const auto& pair : stats.word){
	cout<<pair.first << "  ";
    }
    cout << endl<<endl;

    cout << "Number of Letters : " << stats.str.length() << '\n';
    cout << "Number of Words : " << get<1>(stats.stats1) << '\n';
    cout << "Number of lines : " << get<2>(stats.stats1) << "\n\n";

    // prints the letter fequency
    
    cout<<"                /---------------------------\\"<<endl;
    cout<<"                |         LETTER FREQ       |"<<endl;
    cout<<"	        \\---------------------------/"<<endl<<endl;
    for (const auto& pair : stats.wordFreq) {
	cout<<"                     ";
        cout << pair.first << " : ";
        for (int i = 0; i < pair.second; i++) {
            cout << "*";
        }
        cout << endl;
    }

    //prints the word frequecy
   cout<<endl; 
    cout<<"                /---------------------------\\"<<endl;
    cout<<"                |         DICTIONARY        |"<<endl;
    cout<<"	        \\---------------------------/"<<endl;
   
    cout << endl;
    highest = 0;
    for (const auto& pair :stats.word){
	cout<<"                ";
	 cout << setw(10)<<left<<pair.first <<setw(20)<<right<<pair.second<< endl;
	 vec.push_back(pair.second);
	 if (pair.second > highest){
		highest = pair.second;
	    }
    }

    cout<<endl<<endl<<endl;
    cout<<"                /---------------------------\\"<<endl;
    cout<<"                |         HISTOGRAM         |"<<endl;
    cout<<"	        \\---------------------------/"<<endl;
    cout<<"       |---------------------------------------------|"<<endl;         
    for (int i = highest; i > 0;i--){
	cout<<"       |";
	for (int j = 0; j < vec.size(); j++){
		if (vec[j] == i){
			cout <<setw(6)<<"*";
			vec[j]--;
		}else{
			cout <<setw(6)<<" ";
		}
	}
	cout <<"   |"<<endl;
    }

    // histogram

    int len = 11;
    int height = 2;
    int den = 36;
    int current = 0;
    int current2 = 0;
    int count = 0;
    cout << "       |---------------------------------------------|"<<endl;
    cout<<"        ";
    for (int i = 0; i < vec.size();i++){
	cout << setw(6) << "^";
    }
    cout << endl;
    for (const auto& pair : stats.word){
		cout << pair.first;
		if (pair.first.length() == 2){
			for(int i = 0; i < len;i++){
				cout<<"-";
			}
		}else{
			current = pair.first.length() - 2 ;
			for(int i = 0; i< (len-current);i++){
				cout <<"-";
			}

		}
		cout << "/";
		
		len = len+6;
		if(current2 == 0){
		for(int j = 0; j < den;j++){
			if(count == 5){
				cout<<"|";
				count = 0;
			}else{
				cout<<" ";
				count++;
			}
			current2++;
		}}else {
		 	for (int j = 0; j < (den);j++){
				if(count == 5){
					cout<<"|";
					count = 0;
				}else{
					cout<<" ";
					count++;
				}
			}
			

		}
		den = den-6;
		cout<<endl;
		current = 0;
    }
    cout<<endl<<"Longest Word is :"<<longest_word<<endl<<endl;
    

    return 0;
}

