#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Converts a string to lowercase.
// Author: [Team Member Name]
string toLowerCase(string text)
{
    for (char& character : text)
    {
        character = static_cast<char>(
            tolower(static_cast<unsigned char>(character))
            );
    }

    return text;
}

// Loads all words from the dictionary file into a vector.
// Author: [Team Member Name]
vector<string> loadDictionary(const string& dictionaryFileName)
{
    vector<string> dictionaryWords;
    ifstream dictionaryFile(dictionaryFileName);

    if (!dictionaryFile)
    {
        cerr << "Error: Could not open dictionary file: "
            << dictionaryFileName << endl;
        return dictionaryWords;
    }

    string word;

    while (dictionaryFile >> word)
    {
        dictionaryWords.push_back(toLowerCase(word));
    }

    return dictionaryWords;
}

// Checks whether a word appears in the dictionary.
// Author: [Team Member Name]
bool isDictionaryWord(const vector<string>& dictionaryWords,
    const string& word)
{
    return binary_search(dictionaryWords.begin(),
        dictionaryWords.end(),
        word);
}

// Removes punctuation from the beginning and end of a word.
// Author: [Team Member Name]
string cleanWord(const string& originalWord)
{
    string word = originalWord;

    while (!word.empty() &&
        ispunct(static_cast<unsigned char>(word.front())))
    {
        word.erase(word.begin());
    }

    while (!word.empty() &&
        ispunct(static_cast<unsigned char>(word.back())))
    {
        word.pop_back();
    }

    return toLowerCase(word);
}

// Checks every word in the input file.
// Author: [Team Member Name]
void checkSpelling(const string& inputFileName,
    const vector<string>& dictionaryWords)
{
    ifstream inputFile(inputFileName);

    if (!inputFile)
    {
        cerr << "Error: Could not open input file: "
            << inputFileName << endl;
        return;
    }

    string originalWord;

    while (inputFile >> originalWord)
    {
        string word = cleanWord(originalWord);

        if (!word.empty() &&
            !isDictionaryWord(dictionaryWords, word))
        {
            cout << word << endl;
        }
    }
}

// Main program.
// Author: [Team Member Name]
int main()
{
    const string dictionaryFileName = "/usr/share/dict/words";
    string inputFileName;

    cout << "Enter the name of the file to check: ";
    cin >> inputFileName;

    vector<string> dictionaryWords =
        loadDictionary(dictionaryFileName);

    if (dictionaryWords.empty())
    {
        return 1;
    }

    sort(dictionaryWords.begin(), dictionaryWords.end());

    cout << "\nWords not found in the dictionary:\n";
    checkSpelling(inputFileName, dictionaryWords);

    return 0;
}
