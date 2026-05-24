#include<iostream>
#include<string>
using namespace std;

void print_nchar(int count, char mychar){
    for (int i = 0; i < count; i++)
    {
        cout << mychar;
    }
    
}

int main(){
    for(int i = 0; i < 3; i++)
    {
        print_nchar(2-i,' ');
        print_nchar(2*i+1,'*');
        cout << "\n";
    }
    for (int i = 1; i < 3; i++)
    {
        print_nchar(i,' ');
        print_nchar(5-2*i,'*');
        cout << '\n';
    }
}