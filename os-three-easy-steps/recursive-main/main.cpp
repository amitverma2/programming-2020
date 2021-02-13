#include<iostream>
using namespace std;

extern char **environ;

int main(int argc, char *argv[], char *arge[]) {
    static int x = 1;
    cout << x << endl;
    x++;

    cout << "Parameters\n";
    while (*argv) {
        cout << *argv << endl;
        ++argv;
    }

    cout << "Environment\n";
    while (*environ) {
        cout << *environ << endl;
        ++environ;
    }

    cout << "Environment from arge\n";
    while (*arge) {
        cout << *arge << endl;
        ++arge;
    }
}
