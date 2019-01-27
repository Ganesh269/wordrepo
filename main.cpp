#include<iostream>
#include<fstream>
#include<string.h>
#include<math.h>
using namespace std;
int MAX=100;
int n_data_items=0;
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
    n_data_items++;
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
int retrieve(int pos=1,bool all=false){   //pos indexed from 1
    ifstream file("repo.dat",ios::binary);
    cout<<"came"<<all;
    file.seekg(0,ios::end);   //goto the end i.e, 0 from the end
    int endpoint=file.tellg();  // tell the position we are at present i.e, no.of bytes from the beginning
    int num=endpoint/400;        //since each object is 400 in size
    if(pos>num){
        cout<<"ERROR 400 : INVALID INPUT"<<endl;
        return 0;
    }
    char s[4][MAX];
    if(all){
        for(int j=1;j<=num;j++){
            file.seekg((j-1)*400,ios::beg);
            for(int i=0;i<4;i++)
                file.read(reinterpret_cast<char*>(&s[i]),MAX*sizeof(char));
            for(int i=0;i<4;i++)
                cout<<s[i]<<" ";
        }
    }
    else{
        file.seekg((pos-1)*400,ios::beg);
        for(int i=0;i<4;i++)
            file.read(reinterpret_cast<char*>(&s[i]),MAX*sizeof(char));
        for(int i=0;i<4;i++)
            cout<<s[i]<<" ";
    }
    return 1;
}
int tonumber(char t[]){
    int n=strlen(t),res=0;
    int placevalue=pow(10,n-1);
    for(int i=0; i<n;i++,placevalue/=10){
        res+=placevalue*(t[i]-48);
    }
    return res;
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
    int choice;
    char cont,temp[100];
    do{
        cout<<"\n1.Add 2.Retrieve:";
        cin>>choice;
        switch(choice){
            case 1: add();
                    break;
            case 2: cout<<"\nEnter a string or position(1 indexed):";
                    cin>>temp;
                    int tmp;
                    if(!strcmp(temp,"-all"))
                        retrieve(1,true);
                    else if(isdigit(temp[0])){
                        tmp=tonumber(temp);
                        retrieve(tmp);
                    }
                    else
                        retrieve(temp);
                    break;
            default:cout<<"\nEnter Valid Choice";
        }
        cout<<"\nContinue (Y/N):";
        cin>>cont;
    }while(cont!='n');
    return 0;
}
