#include <iostream>
#include <string>
using namespace std;

const int MAX_SIZE = 1000;

void processText(string text, string* words, int& count)
{
    string currentWord;
    for (char c : text) {
        if (isspace(c) || ispunct(c)) {
            if (!currentWord.empty()) {
                words[count] = currentWord;
                count++;
                currentWord.clear();
            }
            words[count] = string(1, c);
            count++;
        } else {
            currentWord += c;
        }
    }
    if (!currentWord.empty()) {
        words[count] = currentWord;
        count++;
    }
}

int main()
{
    string text = "Hello, world! This is a sample text.";
    string words[MAX_SIZE];
    int count = 0;
    processText(text, words, count);
    for (int i = 0; i < count; i++) {
        cout << words[i] << endl;
    }
    return 0;
}