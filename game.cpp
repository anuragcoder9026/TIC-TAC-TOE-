#include<iostream>
using namespace std;
#include<fstream>
#include<vector>
#include<cstring>
fstream fin("store.txt",ios::in);
class player{
private:
    string name;
    string email;
    string password;
    int match;
    int win;
    int lost;
public:
    player(){
        match=0;
        win=0;
        lost=0;
    }
    void get_details(){ //function to get details of player
        cout<<"Enter Email Id:";
        cin>>email;
        cout<<"Enter Your Name:";
        cin>>name;
        cout<<"Enter Password:";
        cin>>password;
    }
    string get_name(){return name;}
    string get_id(){return email;}
    string get_password(){return password;}
    void set_win_Lost(int w,int l,int m){   //update the status of matches
         win=w;
         lost=l;
         match=m;
         }

    int get_win(){return win;}
    int get_lost(){return lost;}
    int get_match(){return match;}
};
int c1=0,c2=0,c=0,dr=0;
void printboard(char board[10]);
int checkwin(char board[10]);
void system();
void score(int player,int result);
vector<string> vstore;
void new_store(player &p){  //add the new player into vstore vector on signup
    vstore.push_back(p.get_name());
    vstore.push_back(p.get_password());
    vstore.push_back(p.get_id());
    vstore.push_back(to_string(p.get_win()));
    vstore.push_back(to_string(p.get_lost()));
    vstore.push_back(to_string(p.get_match()));
}
bool AlrExist(string name){//to check if player with same id already exist
    bool ans=false;
    for(int i=2;i<vstore.size();i=i+6){
        if(vstore[i]==name) {
            ans=true;
            break;
            }
    }
    return ans;
}
void set_file(int n,player &p){//updating the status of total matches of a player in vstore vector
    vstore[n+1]=to_string(p.get_win()+stoi(vstore[n+1]));
    vstore[n+2]=to_string(p.get_lost()+stoi(vstore[n+2]));
    vstore[n+3]=to_string(p.get_match()+stoi(vstore[n+3]));
}
//function to display the past matches informatino after login or signup
void pastBoard(int n,int m){
    cout<<endl<<endl<<"    "<<"\e[44m";
    cout<<"\e[1;37m"<<"            Past Board            "<<endl;
    cout<<"\e[40m    ";
    cout<<"\e[43m"<<"\e[1;37m"<<"   Player  "<<"\e[45m"<<"\e[1;37m"<<"  Player 1 "<<"\e[40m"<<" "<<"\e[45m"<<"  Player 2 "<<endl;
    cout<<"\e[40m    ";
    cout<<"\e[47m"<<"\e[1;37m"<<"   Mtches  "<<"\e[42m"<<"\e[1;36m"<<"      "<<vstore[n+3]<<"    "<<"\e[40m"<<" "<<"\e[42m"<<"      "<<vstore[m+3]<<"    "<<endl;
    cout<<"\e[40m    ";
    cout<<"\e[46m"<<"\e[1;37m"<<"   Wins    "<<"\e[42m"<<"\e[1;36m"<<"      "<<vstore[n+1]<<"    "<<"\e[40m"<<" "<<"\e[42m"<<"      "<<vstore[m+1]<<"    "<<endl;
    cout<<"\e[40m    ";
    cout<<"\e[41m"<<"\e[1;37m"<<"   Lost    "<<"\e[42m"<<"\e[1;36m"<<"      "<<vstore[n+2]<<"    "<<"\e[40m"<<" "<<"\e[42m"<<"      "<<vstore[m+2]<<"    "<<endl;
    cout<<endl<<endl<<endl;
}
int main(){
      system("cls");
    string pl[2];
    player p[2];
    int plitr[2];
    
        char line[20];
        //entering the file data into vector of strings
        while(fin.getline(line,20)){
          vstore.push_back(line);
        }
    for(int i=0;i<2;i++){

        ac:
    cout<<"Window for Player "<<i+1<<":"<<endl;
    cout<<"Enter 'S' for Sign up and 'L' for Log In:";
    char sel;
    cin>>sel;
    if(sel=='S'||sel=='s'){   //signup
    p[i].get_details();
    if(AlrExist(p[i].get_id())) {
          system("cls");
        cout<<endl<<"User Already Exist !!! Please Enter Details Again:"<<endl;
        goto ac;
    }
    //appending new player to file
    fstream appfile("store.txt",ios::app);
    appfile<<p[i].get_name()<<endl;
    appfile<<p[i].get_password()<<endl;
    appfile<<p[i].get_id()<<endl;
    appfile<<p[i].get_win()<<endl;
    appfile<<p[i].get_lost()<<endl;
    appfile<<p[i].get_match()<<endl;
    new_store(p[i]);//adding new player to vstore vector
    plitr[i]=vstore.size()-4;//index of id of new player in vector
    pl[i]=p[i].get_name();//storing the name of player in string array pl
    }
    else if(sel=='L'||sel=='l'){
        am: //Login
        string idcheck,passwordcheck;
        cout<<"Enter Your Email Id:";
        cin>>idcheck;
        cout<<"Enter Your Password:";
        cin>>passwordcheck;
        int j;
        int  cnd=0;
        //Id and Password check
        for(j=2;j<vstore.size();j=j+6){
          if(vstore[j]==idcheck && vstore[j-1]==passwordcheck){
              pl[i]=vstore[j-2];
              plitr[i]=j;
              cnd=1;//player with details entered is found
              break;
          }
        }
        if(cnd==0){//if no player with Id and password exist in file
            system("cls");
            cout<<endl<<"Email or Password Does not matches.."<<endl;
            cout<<"Please Enter Correct Email and Password: "<<endl<<endl;
            goto am;
        }
    }
    else{
        cout<<"Please Enter Valid key..."<<endl;
        goto ac;
    }
     system("cls");
    }
pastBoard(plitr[0],plitr[1]);//calling the pastboard function with index of Id's in vstore vector
 cout<<"\e[40m    ";


cout<<"Enter 'C' to Play the Match Between "<<pl[0]<<" and "<<pl[1]<<": ";
char in;
cin>>in;
if(in!='C'&&in!='c') return 0;
char board[10]={'0','1','2','3','4','5','6','7','8','9'};
int check[10]={0,0,0,0,0,0,0,0,0,0};//initially no box is checked
     char ch='Y';
    while(ch=='Y'||ch=='y'){
    int gamer=0,input,status=-1;
     cout<<"\e[40m    ";
    printboard(board);// displaying the board with intial condition of no boxes checked
    while(status==-1){
      gamer=(gamer%2==0)?0:1;//to alternate the player turns
    char mark=(gamer==1)?'X':'O';
    ab:
    cout<<"\e[1;36m"<<"ENTER THE NUMBER FOR PLAYER "<<pl[gamer]<<":";
    cin>>input;
    if(input<1||input>9) goto ab;//if the input is out of range
    else if(check[input]==1) goto ab;//else if input box is already checked
    else check[input]=1,board[input]=mark;//else change the entry of board to mark of current player
printboard(board);//printing board after each move

int result=checkwin(board);//checking if the player wins after this move
if(result==1){//if wins
    cout<<"\e[1;36m"<<" ... "<<pl[gamer]<<" is winner...\n";
    score( gamer, result);//updating the score board of current game
    for(int i=0;i<10;i++)  board[i]=i,check[i]=0;
    break;
}
else if(result==0){//draw condition
    dr++;
    cout<<"\e[1;36m"<<"  ....match is draw....\n";
     score( gamer, result);
     for(int i=0;i<10;i++)  board[i]=i,check[i]=0;
    break;
}
gamer++;//next player
}
  for(int i=0;i<=9;i++){board[i]=char(i+48);}

  cout<<endl<<"\e[1;33m""Enter 'Y' for Next Match:";
  c++;
  cin>>ch;
  cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
}
//updating the value of matches into player object
    p[0].set_win_Lost(c1,c-dr-c1,c);
    p[1].set_win_Lost(c2,c-dr-c2,c);
//updating the values in vstore vector
    set_file(plitr[0],p[0]);
    set_file(plitr[1],p[1]);
//rewriting the data of file with any changes
    fstream fout("store.txt",ios::out);
    for(int i=0;i<vstore.size();i++){
        fout<<vstore[i]<<endl;
    }
    return 0;
}
void printboard(char board[10]){//display the board on screen
    system("cls");
    cout<<"\n\n";
    int b;
    for(int i=0;i<25;i++){cout<<"\e[0;34m"<<(char)219;}
    cout<<endl;
    cout<<"\e[44m";
    cout<<"\e[1;37m"<<" WELCOME TO GAMING WORLD "<<endl;
    cout<<endl;
    cout<<"\e[40m";
    cout<<"   "<<"\e[45m";
    cout<<"\e[1;37m"<<"!!! TIC TAC TOE !!!";
    cout<<"\e[40m";
    cout<<endl<<endl;
    for(int i=1;i<=3;i++){
        b=(3*i)-3;
    for(int j=1;j<=3;j++){
        for(int k=1;k<=3;k++) {
            ++b;
            if(board[b]=='X'){
                cout<<"\e[1;31m"<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<"  ";
            }
            else if(board[b]=='O'){
                cout<<"\e[1;34m"<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<"  ";
            }
            else if(j==2) cout<<"\e[1;33m"<<(char)219<<(char)219<<(char)219<<"\e[0;103m"<<"\e[1;34m"<<board[b]<<"\e[40m"<<"\e[1;33m"<<(char)219<<(char)219<<(char)219<<"  ";
            else if(j==1|| j==3) cout<<"\e[1;33m"<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<"  ";
        }
            b=(3*i)-3;
        cout<<endl;
    }
    cout<<endl;
    }
}
void score(int player,int result){//update the number of wins of corresponding player
    system("cls"); 
    if(result==1){
        if(player==0) c1++;
        else c2++;
    }
     cout<<endl<<endl<<"    "<<"\e[44m"<<"\e[1;37m"<<"   Score Board   "<<endl<<"\e[40m";
    cout<<" "<<"\e[45m"<<"\e[1;37m"<<"  Player 1 "<<"\e[40m"<<" "<<"\e[45m"<<"  Player 2 "<<endl<<"\e[40m";
     cout<<" "<<"\e[42m"<<"\e[1;36m"<<"      "<<1<<"    "<<"\e[40m"<<" "<<"\e[42m"<<"      "<<2<<"    "<<"\e[40m"<<endl;
    cout<<"\e[40m";
}
//function to check win or draw condition
int checkwin(char board[10]){
   if(board[1]==board[2]&&board[2]==board[3]){
    return 1;
   }
   if(board[1]==board[4]&&board[4]==board[7]){
    return 1;
   }
   if(board[7]==board[8]&&board[8]==board[9]){
    return 1;
   }
   if(board[3]==board[6]&&board[6]==board[9]){
    return 1;
   }
   if(board[1]==board[5]&&board[5]==board[9]){
    return 1;
   }
   if(board[3]==board[5]&&board[5]==board[7]){
    return 1;
   }
   if(board[2]==board[5]&&board[5]==board[8]){
    return 1;
   }
   if(board[4]==board[5]&&board[5]==board[6]){
    return 1;
   }
   int count=0;
   for(int i=0;i<=9;i++){
    if(board[i]=='X'||board[i]=='O'){
    count++;
   }
   }
   if(count==9){
    return 0;
   }
}