#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <cctype>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

//--------------------------------------------------------------------------------------------------------
//definig a struct to compare strings

struct Compare{	// comparator for the priority queue
	bool operator()(const string& a, const string& b){
		return a.length()<b.length();// compare the lengths of the string
	}

};

//-------------------------------------------------------------------------------------------------------
//creating alias

using COUNTER = tuple<int, int, int>;  // Tuple to hold number of letters, words, and lines
using WORD = std::string;		// use to store the string
using WORD_LIST = std::set<WORD>;	// sort the characters
using WORD_FREQ_LIST = std::map<char,int>;	// use to store the letters and occurrences
using WORD_FREQ = std::map<WORD,int>;
using FREQ_WORD_LIST = std::multimap<int,WORD>;	// use to store the words and occurrences
using LONGEST = std::priority_queue<WORD,vector<WORD>,Compare>;	// store the longest word

//--------------------------------------------------------------------------------------------------------
// definig a struct and its members

struct DICTION {	
	COUNTER stats1{0, 0, 0};	// is a tuple
	WORD_LIST words{};		// is a set
	WORD_FREQ_LIST wordFreq{};	// is a map
	FREQ_WORD_LIST freqWord{};	// is a multimap
	LONGEST longWord{};		// is a priority queue
	WORD str{""};			// is a string
	WORD_FREQ word{};		// is a map 
};

//--------------------------------------------------------------------------------------------------------
// remove is123is to is is 
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

//-------------------------------------------------------------------------------------------------------
// Function to count letters, words, and lines in a file and store all letters in a string
DICTION Extract(DICTION& stats) {

    int& letterCount = get<0>(stats.stats1);
    int& wordCount = get<1>(stats.stats1);
    int& lineCount = get<2>(stats.stats1);
    ifstream file("file.txt");  // Open file
    lineCount++;
    if (!file.is_open()) {
        cerr << "Error opening file!" << '\n';
        return stats;  // Return the empty struct if file couldn't be opened
    }
//-------------------------------------------------------------------------------------------------------
// start extarcting from the file
    WORD word;
    // Read each line from the file
    while (getline(file, word)) {

        stringstream ss(word);

        // Read each word in the line
        while (ss >> word) {
            wordCount++;	//increase the word count
 	    stats.str += word;  // append the string with the new word         

            // Split word to remove any *special characters
            vector<WORD> cleanedWords = splitWord(word); // call the function

            // Count letters in the word and store them
            for (const auto& clean : cleanedWords) {
                stats.freqWord.insert({clean.length(), clean});	// add to freqWord
		stats.longWord.push(clean);		// add to the queue
                for (char c : clean) {
                    stats.wordFreq[c]++;	// add to wordFreq
                    letterCount++;		// the number of letters
                }
            }
	    stats.str += " ";	// add spacing to the string , make it look nice bro
        }
    }

    return stats;  // Return 
}
//--------------------------------------------------------------------------------------------------------
//main method starts here

int main() {

    int highest{0};		// get the highest number of same characters
    vector<int> vec;		// vector for getting the counts for histogram 
    DICTION stats{};		// initialzie stats
    Extract(stats);	// call the function

//-------------------------------------------------------------------------------------------------------
// copy the words and add the number of occurence to word from freqWord 
    for (const auto& pair : stats.freqWord) {
	    
	     stats.word[(pair.second)]++;	// add words into a new function which has occurence
	} 
    cout<<endl;

//--------------------------------------------------------------------------------------------------------
// print the words in the dicitonay
    cout << "Words in the dictionary : ";
    for(const auto& pair : stats.word){
	cout<<pair.first << "  ";
    }
    cout << endl<<endl;

    cout << "Number of Letters : " << stats.str.length() << '\n';
    cout << "Number of Words : " << get<1>(stats.stats1) << '\n';
    cout << "Number of lines : " << get<2>(stats.stats1) << "\n\n";

//-------------------------------------------------------------------------------------------------------
// prints the letter fequency
    
    cout<<"                /---------------------------\\"<<endl;
    cout<<"                |         LETTER FREQ       |"<<endl;
    cout<<"	        \\---------------------------/"<<endl<<endl;

    // using the wordFreq to get the words and the number of occurence
    for (const auto& pair : stats.wordFreq) {
	cout<<"                     ";
        cout << pair.first << " : ";
        for (int i = 0; i < pair.second; i++) {
            cout << "*";	// using * for each occurrence
        }
        cout << endl;
    }

//-------------------------------------------------------------------------------------------------------
//prints the word frequecy
   cout<<endl; 
    cout<<"                /---------------------------\\"<<endl;
    cout<<"                |         DICTIONARY        |"<<endl;
    cout<<"	        \\---------------------------/"<<endl;
   
    cout << endl;
    // using word to print the dicitonary the words and their occurrence
    for (const auto& pair :stats.word){
	cout<<"                ";
	 cout << setw(10)<<left<<pair.first <<setw(18)<<right<<pair.second<< endl;	
	 vec.push_back(pair.second);		// push values into the vector
	 if (pair.second > highest){		// get the number of highest occurence
		highest = pair.second;
	    }
    }
//-------------------------------------------------------------------------------------------------------    
// print the histogram
    cout<<endl<<endl<<endl;
    cout<<"                /---------------------------\\"<<endl;
    cout<<"                |         HISTOGRAM         |"<<endl;
    cout<<"	        \\---------------------------/"<<endl;
    cout<<"       |---------------------------------------------|"<<endl;   
    
    // loop to first print the occurrence using '*',highest and vector
    for (int i = highest; i > 0;i--){
	cout<<"       |";
	for (int j = 0; j < vec.size(); j++){
		if (vec[j] == i){
			cout <<setw(6)<<"*";
			vec[j]--;	//decrease the value of the element everytime "*" is printed
		}else{
			cout <<setw(6)<<" ";
		}
	}
	cout <<"   |"<<endl;
    }
//-------------------------------------------------------------------------------------------------------
// prints the categories and the arrows headache

    int len = 11;	// 11 is the distance from the column{0} to where the first * is printed
    int den = 36;	// for printing "|" that points to the "*"
    int current = 0;	// used for spacing
    int current2 = 0;	// just to print the first " |"
    int count = 0;	// used for spacing
    cout << "       |---------------------------------------------|"<<endl;
    cout<<"        ";

    for (int i = 0; i < vec.size();i++){
	cout << setw(6) << "^";		// prints the pointers "^" on the chart
    }
    cout << endl;
    
    // prints the "-" for each element
    for (const auto& pair : stats.word){
		cout << pair.first;
		if (pair.first.length() == 2){	// this is only for the first element, used 2 cus my is 2
			for(int i = 0; i < len;i++){
				cout<<"-";	// prints 11 of the dashes
			}
		}else{
			current = pair.first.length() - 2 ;
			for(int i = 0; i< (len-current);i++){
				cout <<"-";	// prints the dashes depending upon the length
			}

		}
		cout << "/";

//------------------------------------------------------------------------------------------------------
//this section deals with printing the vertical arrows for each category

		len = len+6;	// this is used for spacing 
		if(current2 == 0){	// this is to exclude the first category
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
		den = den-6;	// reduces the number of time "-" has to printed as the loop goes on
		cout<<endl;	// new line
		current = 0;	// set current to 0
    }
//-------------------------------------------------------------------------------------------------------
// this prints the longest words in the file using the priority queue
    cout<<endl<<"Longest Word is :"<<stats.longWord.top()<<endl<<endl;
    

    return 0;	// the program ends here
}

