#include <iostream>
#include <cstring>
using namespace std;

const char *Name[12] = {"January", "February", "March", "April", "May",
                        "June", "July", "August","September",
                        "October", "November", "December"};

void convert(char *data)
{
    char *year = strtok(data, "/");
    char *month = strtok(NULL, "/");
    char *day = strtok(NULL, "/");

    int num = atoi(month);
    cout<<Name[num-1]<<" "<<day<<", "<<year<<"."<<endl;
}

int main()
{
    char data[50];
    while (true)
    {
        cin >> data;
        convert(data);
    }
}
