#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
int MAX=100;
int add(){
    ofstream file("repo.dat",ios::binary|ios::app);
    char str[4][MAX];
    cout<<"\nWord : ";
    cin.getline(str[0],MAX);
    cout<<"\nPOS  : ";
    cin.getline(str[1],MAX);
    cout<<"\nEXP  : ";
    cin.getline(str[2],MAX);
    cout<<"\nE.G. : ";
        cin.getline(str[3],MAX);
    //file.write(reinterpret_cast<char*>(siz),4*sizeof(int));
    for(int i=0;i<4;i++)
        file.write(reinterpret_cast<char*>(&str[i]),MAX*sizeof(char));

    file.close();
    return 1;
}
int read(int n){
    ifstream file("repo.dat",ios::binary);
    char str[5][MAX];
    //file.read(reinterpret_cast<char*>(siz),4*sizeof(int));
    file.seekg((n-1)*400,ios::beg);
    for(int i=0;i<4;i++)
        file.read(reinterpret_cast<char*>(&str[i]),MAX*sizeof(char));
    for(int i=0;i<4;i++){
        cout<<str[i]<<" ";
    }
    file.close();
}
int retrieve(int pos=0){
    ifstream file("repo.dat",ios::binary);
    file.seekg(0,ios::end);
    int endpoint=file.tellg();
    int num=endpoint/400;
    if(pos>num){
        cout<<"ERROR 400 : INVALID INPUT"<<endl;
        return 0;
    }
    char s[4][MAX];
    file.seekg((pos-1)*400,ios::beg);
    for(int i=0;i<4;i++)
        file.read(reinterpret_cast<char*>(&s[i]),MAX*sizeof(char));
    for(int i=0;i<4;i++)
        cout<<s[i]<<" ";
    return 1;
}
int retrieve(char str[100]){
    ifstream file("repo.dat",ios::binary);
    char s[4][MAX];
    int found=0;
    file.seekg(0,ios::end);
    int endpoint=file.tellg();
    int num=endpoint/400;
    for(int i=1;i<=num;i++){
        file.seekg((i-1)*400,ios::beg);
        file.read(reinterpret_cast<char*>(&s[0]),MAX*sizeof(char));
        if(!strcmp(str,s[0])){
            for(int i=1;i<4;i++)
                file.read(reinterpret_cast<char*>(&s[i]),MAX*sizeof(char));
            found=1;
            break;
        }
    }
    if(found)
        for(int i=0;i<4;i++)
        cout<<s[i]<<" ";
    else
        cout<<"ERROR 404 : NOT FOUND"<<endl;
    return 1;


}
int main(){
    int entries=0;
    char a[4]="ma";
    retrieve(a);


}
