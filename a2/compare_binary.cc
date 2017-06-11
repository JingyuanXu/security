#include <iostream>
#include <string>
#include <string.h>
using namespace std;

string convert2Binary(char c) {
    switch (c) {
        case '0': 
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'a':
        case 'A':
            return "1010";
        case 'b':
        case 'B':
            return "1011";
        case 'c':
        case 'C':
            return "1100";
        case 'd':
        case 'D':
            return "1101";
        case 'e':
        case 'E':
            return "1110";
        case 'f':
        case 'F':
            return "1111";
    }
    return "";
}

int main(int argc, char** argv) {
    if (argc != 3) return 1;
    char* str1 = argv[1];
    char* str2 = argv[2];
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int same = 0;
    int notsame = 0;
    for (int i = 0; i < len1 && i < len2; ++i) {
        string s1 = convert2Binary(str1[i]);
        string s2 = convert2Binary(str2[i]);
        for (int j = 0; j < 4; ++j) {
            if (s1[j] == s2[j]) same += 1;
            else notsame += 1;
        }
    }
    cout << "same:" << same << endl;
    cout << "not same:" << notsame << endl;
    return 0;
}
