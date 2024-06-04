#include <iostream>
#include <string>
#include <time.h>
#include <ncurses.h>

using namespace std;

int main() {
    string txt = "Жили у бабуси, два весёлых гуся.";
    string inputW;
    string word;
    int count = 0;

    cout << txt << endl << endl;

    for (int i = 0; i < txt.length(); i++) {
        if (txt[i] != ' ' && txt[i] != '.' && txt[i] != ',' && txt[i] != '?' && txt[i] != '!' && txt[i] != '\n') {
            word += txt[i];
        }
        else {
            if (word != "")
                cout << word << endl;
            word.clear();
        }
    }
}