#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg)
{
    cout << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int len1 = str1.length(), len2 = str2.length();
    
    if(abs(len1 - len2) > d) return false;

    int i = 0, j = 0, diff_count = 0;

    while (i < len1 && j < len2)
    {
        if (str1[i] != str2[j])
        {
            diff_count++;
            if (diff_count > d) return false;

            if (len1 < len2) j++;
            else if (len1 > len2) i++;
            else { i++; j++; }
        }
        else
        {
            i++;
            j++;
        }
    }
    
    diff_count += (len1 - i) + (len2 - j);
    
    return diff_count <= d;
}


bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> q;
    q.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while(!q.empty())
    {
        vector<string> path = q.front();
        q.pop();

        string last_word = path.back();
        if(last_word == end_word) return path;

        for(const string& word : word_list)
        {
                                                //if dog doesnot exist find() returns visited.end();
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end())
            {
                vector<string> new_path = path;
                new_path.push_back(word);
                q.push(new_path);
                visited.insert(word);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream file(file_name);
    if(!file)
    {
        cout <<"Cannot open file "<<  file_name << endl;
        return;
    }

    string word;
    while(file >> word)
    {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) 
{
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << "Word ladder found: " << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " "; 
        }
    }
    cout << " \n";  
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}
