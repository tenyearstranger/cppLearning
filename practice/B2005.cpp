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
    char a;
    cin >> a;
    for(int i = 0; i < 3; i++)
    {
        print_nchar(2-i,' ');
        print_nchar(2*i+1,a);
        cout << "\n";
    }
}