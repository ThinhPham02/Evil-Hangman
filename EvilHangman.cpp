#include <iostream>
#include <fstream>
#include <string> 
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class EvilHangman {
    int lives;
    string form;
    int correctNum;
    int wordLength;
    string wordState;
    vector<char> inputLetter;
    vector<string> pickedwords;
    unordered_map<int, vector<string>> sizeMap;
    unordered_map<string, vector<string>> posMap;

        void setUp() {
            string word;
            ifstream file("Dictionary.txt");

            if (!file) {
                cerr << "Could not open file." << endl;
                return;
            }

            while (file >> word) { pickedwords.push_back(word); }

            filterBySize();
            pickSize();
        }

        void filterBySize() {
            for (auto& word : pickedwords) {
                sizeMap[word.size()].push_back(word);
            }
        }

        void pickSize() {
            int maxSize = 0;
            vector<vector<string>> maxList;
            for (const auto& pair : sizeMap) {
                if (pair.second.size() > maxSize) {
                    maxSize = pair.second.size();
                    maxList.clear();
                    maxList.push_back(pair.second);
                } else if (pair.second.size() == maxSize) {
                    maxList.push_back(pair.second);
                }
            }

            if (maxList.empty()) {
                cerr << "No suitable word groups found." << endl;
                return;
            }

            int index = rand() % maxList.size();
            pickedwords = maxList[index];
            wordLength = pickedwords[0].size();

            wordState = string(wordLength, '_');
        }

        string transformWord(string word, char letter) {
            string state = "";
            for (char w : word) {
                (w == letter) ? state += w : state += '_';
            }
            return state;
        }

        bool compareWordForm(string state, string word) {
            for (int i = 0; i < word.size(); i++) {
                if (state[i] != '_') {
                    if (word[i] != state[i]) {
                        return false;
                    }
                }
            }
            return true;
        }

        void updateWordState(string stateWord, char letter) {
            for (int i = 0; i < stateWord.size(); i++) {
                if (stateWord[i] == letter) {
                    wordState[i] = letter;
                }
            }
        }

    public:
        EvilHangman() { 
            srand(time(nullptr));
            lives = 6;
            correctNum = 0;
            setForm();
            setUp(); 
        }

        void setForm() {
            switch(lives) {
                case 0:
                    form = " ________\n |      |\n |      o\n |     /|\\\n |     / \\\n/|\\\n";
                    break;
                case 1:
                    form = " ________\n |      |\n |      o\n |     /|\\\n |     /\n/|\\\n";
                    break;
                case 2:
                    form = " ________\n |      |\n |      o\n |     /|\\\n |\n/|\\\n";
                    break;
                case 3:
                    form = " ________\n |      |\n |      o\n |     /|\n |\n/|\\\n";
                    break;
                case 4:
                    form = " ________\n |      |\n |      o\n |     /\n |\n/|\\\n";
                    break;
                case 5:
                    form = " ________\n |      |\n |      o\n |\n |\n/|\\\n";
                    break;
                default:
                    form = " ________\n |      |\n |\n |\n |\n/|\\\n";
                    break;
            }
        }

        bool isContain(char letter) {
            int size = 0;
            vector<vector<string>> maxList;
            posMap.clear();

            for (string word : pickedwords) {
                posMap[transformWord(word, letter)].push_back(word);
            }

            for (auto& e : posMap) {
                if (e.second.size() > size) {
                    size = e.second.size();
                    maxList.clear();
                    maxList.push_back(e.second);
                }
                else if (e.second.size() == size) {
                    maxList.push_back(e.second);
                }
            }

            int index = rand() % maxList.size();
            pickedwords = maxList[index];

            string pattern = transformWord(pickedwords[0], letter);
            updateWordState(pattern, letter);

            return pattern.find(letter) != string::npos;
        }

        int getLength() {
            return wordLength;
        }

        int getCorrectNum() {
            return correctNum;
        }

        int checkWord(char c) {
            int num = count(wordState.begin(), wordState.end(), c);
            correctNum += num;
            return num;
        }

        void minusLives() {
            lives--;
        }

        void getForm() {
            cout << form; 
        }

        string getWord() {
            int index = rand() % pickedwords.size();
            return pickedwords[index];
        }

        void addInput(char c) {
            inputLetter.push_back(c);
        }

        bool checkInput(char c) {
            return (find(inputLetter.begin(), inputLetter.end(), c) != inputLetter.end());
        }

        string getWordState() {
            string holder;
            for (char& letter : wordState) {
                holder += " " + string(1, letter);
            }
            return holder;
        }

        bool isWin() const {
            return wordState.find('_') == string::npos;
        }

        bool checkLose() {
            return lives == 0;
        }

        void printInputLetter() {
            cout << "[ ";
            for (char e : inputLetter) {
                cout << e << " ";
            }
            cout << "]" << endl;
        }
};

int main() {
    char inputLetter;

    EvilHangman evilHangman = EvilHangman();

    cout << "=====================================\n";
    cout << "     🎮 Welcome to EVIL HANGMAN! 🎮\n";
    cout << "=====================================\n\n";
    cout << "😈 Think you know Hangman? This version fights back. Good luck...\n";
    cout << "🕹️  A mysterious word awaits you...\n";
    cout << "📏  It has " << evilHangman.getLength() << " letters. Can you guess it?\n\n";
    cout << "   " << evilHangman.getWordState();
    cout << "\n\n💡  Type a letter and press Enter to begin!\n\n";
    cout << "Good luck, challenger!\n";

    while (true) {
        cout << "\nGuessed Letters:\n";
        evilHangman.printInputLetter();
        cout << "\n🔤 What letter will you try next?\n";
        cin >> inputLetter;
        inputLetter = tolower(inputLetter);

        if (evilHangman.checkInput(inputLetter)) {
            cout << "⚠️  You've already guessed '" << inputLetter << "'. Try something new.\n";
            continue;
        }

        evilHangman.addInput(inputLetter);
        

        if (evilHangman.isContain(inputLetter)) {
            int num = evilHangman.checkWord(inputLetter);
            cout << "✅ Nice! You found " << num << " '" << inputLetter << "' in the word!\n";
            cout << "🧩 Only " << (evilHangman.getLength() - evilHangman.getCorrectNum()) << " more to go. Keep it up!\n";
        } else {
            evilHangman.minusLives();
            evilHangman.setForm();
            cout << "❌ Oops! No '" << inputLetter << "' in the word.\n";
            cout << "💡 Don't give up - try again!\n";
        }

        evilHangman.getForm();
        cout << "\n  " << evilHangman.getWordState() << "\n";

        if (evilHangman.checkLose()) {
            cout << "=======================================";
            cout << "\n The word is '" << evilHangman.getWord() << "'.\n";
            cout << "=======================================\n\n";
            cout << "\n💀 Game Over! You've run out of chances.\n";
            cout << "🔁 Better luck next time!\n\n";
            break;
        }

        if (evilHangman.isWin()) {
            cout << "=======================================";
            cout << "\n The word is '" << evilHangman.getWord() << "'.\n";
            cout << "=======================================\n\n";
            cout << "\n🎉 Congratulations! You've guessed the word!\n";
            cout << "🏆 Victory is yours, word master!\n\n";
            break;
        }
    }   

    return 0;
}