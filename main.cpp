#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

int add(){
    ofstream file("repo.dat",ios::binary);
    char str[4][4];
    int siz[4];
    for(int i=0;i<4;i++)
        cin.getline(str[i],4);
    for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
        cout<<str[i][j];
    //file.write(reinterpret_cast<char*>(siz),4*sizeof(int));
    for(int i=0;i<4;i++)
        file.write(reinterpret_cast<char*>(&str[i]),4*sizeof(char));

    file.close();
    return 1;
}
int read(){
    ifstream file("repo.dat",ios::binary);
    char str[5][4];
    int siz[4];
    //file.read(reinterpret_cast<char*>(siz),4*sizeof(int));
    for(int i=0;i<4;i++)
        file.read(reinterpret_cast<char*>(&str[i]),4*sizeof(char));
    for(int i=0;i<4;i++)
        cout<<str[i];
    file.close();
}

int main(){
    add();
    read();

}
