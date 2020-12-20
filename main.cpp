#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <cmath>

using namespace std;

int get(unsigned char c) {
    return c - '0';
}

string multiply(vector <vector <int>> &a, string &b) {
    string res;
    for (int i = 0; i < a.size(); i++) {
        int now = 0;
        for (int j = 0; j < b.size(); j++)
            now += a[i][j] * get(b[j]);
        res += to_string(now % 2);
    }
    return res;
}

string code(string &data) {
    vector <vector <int>> G = { { 1, 0, 1, 1 },
                                { 1, 1, 0, 1 },
                                { 0, 0, 0, 1 },
                                { 1, 1, 1, 0 },
                                { 0, 0, 1, 0 },
                                { 0, 1, 0, 0 },
                                { 1, 0, 0, 0 } };
    return multiply(G, data);
}

string check(string &data) {
    vector <vector <int>> H = { { 0, 0, 0, 1, 1, 1, 1 },
                                { 0, 1, 1, 0, 0, 1, 1 },
                                { 1, 0, 1, 0, 1, 0, 1 } };
    return multiply(H, data);
}

void fix(string &check_sum, string &data) {
    int pos = get(check_sum[2]) + get(check_sum[1]) * 2 + get(check_sum[0]) * 4;
    if (pos != 0)
        data[pos - 1] = '0' + (get(data[pos - 1]) + 1) % 2;
}

string char_to_bin(unsigned char d) {
    string res;
    while (res.length() < 8 || d != 0) {
        res += to_string(d % 2);
        d /= 2;
    }
    return res;
}

string bin_to_char(string &s) {
    unsigned char c = 0;
    for (int i = 0; i < 8; i++)
        c += get(s[i]) * pow(2, i);
    return string(1, c);
}

string string_to_bin(string &s) {
    string res;
    for (char c: s)
        res += char_to_bin(c);
    return res;
}

string bin_to_string(string &s) {
    string res;
    for (int i = 0; i < s.length() / 8; i++) {
        string substring = s.substr(i * 8, 8);
        res += bin_to_char(substring);
    }
    return res;
}

string code_string(string &s) {
    string res;
    for (int i = 0; i < s.length() / 4; i++) {
        string substring = s.substr(4 * i, 4);
        res += code(substring);
    }
    return res;
}

void corrupt(string &s) {
    unsigned long pos = rand() % s.length();
    s[pos] = '0' + (get(s[pos]) + 1) % 2;
}

string decode_string(string &s, map <string, string> &preprocessed_data) {
    string decoded_string;
    for (int i = 0; i < s.length() / 7; i++) {
        string substring = s.substr(7 * i, 7);
        string check_sum = check(substring);
        fix(check_sum, substring);
        decoded_string += preprocessed_data[substring];
    }
    return bin_to_string(decoded_string);
}

map <string, string> preprocessing() {
    map <string, string> res;
    for (int i = 0; i < 16; i++) {
        int now = i;
        string s;
        while (s.length() < 4 || now != 0) {
            s += to_string(now % 2);
            now /= 2;
        }
        res[code(s)] = s;
    }
    return res;
}

int main() {
    srand(time(nullptr));
    map <string, string> preprocessed_data = preprocessing();
    string input;
    cin >> input;
    string bin_input = string_to_bin(input);
    cout << bin_input << " - bin string" << endl;
    string coded_string = code_string(bin_input);
    cout << coded_string << " - coded string" << endl;
    corrupt(coded_string);
    cout << coded_string << " - corrupted string" << endl;
    string decoded_string = decode_string(coded_string, preprocessed_data);
    cout << decoded_string << " - result" << endl;
}
