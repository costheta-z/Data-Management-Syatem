#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class record *head=NULL;
class record *last=NULL;

struct student{
  string fname;
  string lname;
  string enroll;
  float cgpa;
  int year;
};

class record{
  
  public:
    student s;
    record *nxt;

  record(){
    ofstream details;
    fstream truncate;
    truncate.open("new_student", ios::trunc | ios::out | ios::in); 
    truncate<<"Enter portal\n";
    truncate.close();
    details.open("new_student", ofstream::out | ofstream::app);
    
    ifstream in;
    in.open("ask");

    string line;
    while(getline(in, line)) {
        details<<line<<endl;
    }

    in.close();
    details.close();

    cout<<"enter student data in file \"new student\" then enter 0 in the terminal to proceed"<<endl;
    cout<<"0 to proceed: ";
    int pro;
    cin>>pro;

    in.open("new_student");
    string word="";
    int out_now=4;
    
    while(word!="done") {
        in>>word;
        if(word==":") {
            string temp;
            in>>temp;

            if(out_now==4) s.enroll=temp;
            
            if(out_now==3) {
                s.fname=temp;
                in>>temp;
                s.lname=temp;
            }
            
            if(out_now==2) {
                s.year=0;
                int si=temp.size();
                for(int i=0;i<si;i++) {
                    s.year+=(temp[i]-'0')*(pow(10, (si-i-1)));
                }
            }
            
            else {
                s.cgpa=0;
                int si=temp.size();
                for(int i=0;i<si;i++) {
                    s.cgpa+=(temp[i]-'0')*(pow(10, (si-i-1)));
                }
            }
            out_now--;
        }
    }
    in.close();
  }

  void add(record *temp){
    
    if(!head){
      head=temp;
      last=temp;
      head->nxt=NULL;
      last->nxt=NULL;
    }
    
    else{
      last->nxt=temp;
      last=temp;
      last->nxt=NULL;
    }
  }

  void traverse(){
    
    record* temp=head;
    ofstream details;
    details.open("database", ofstream::out | ofstream::out);
    
    while(temp){
        details<<temp->s.enroll<<endl;
        details<<temp->s.fname<<" "<<temp->s.lname<<endl;
        details<<temp->s.year <<endl;
        details<<temp->s.cgpa<<endl;
        temp=temp->nxt;
        details<<endl;
    }
    details.close();
  }

  record* search(int operation) {
    
    record* temp=head, *pr=NULL;
    string to_find;
    cout<<"enrollment number of student: ";
    cin>>to_find;
    
    while(temp && (temp->s).enroll!=to_find){
        pr=temp;
        temp=temp->nxt;
    }
    
    if(temp) {
        if(operation==4) {
            print_record(temp);
            cout<<"data of student in file named \"single_student_info\""<<endl;
        }
        else cout<<"student deleted\n";
        return pr;
    }
    
    else {
        cout<<"no such enrollment number\n";
        return last;
    }
  }
  
  void print_record(record* to_print) {
    
    ofstream ou;
    ou.open("single_student_info");
    ou.close();
    ou.open ("single_student_info", ofstream::out | ofstream::app);
    ou<<to_print->s.enroll<<endl;
    ou<<to_print->s.fname<<" "<<to_print->s.lname<<endl;
    ou<<to_print->s.year <<endl;
    ou<<to_print->s.cgpa<<endl;
    ou.close();
  }
  
    void del(record* to_del) {
        if(to_del==last) return;
        if(!to_del) {
            record* gone=head;
            head=head->nxt;
            delete(gone);
            return;
        }
        record* gone =to_del->nxt;
        to_del->nxt=gone->nxt;
        delete(gone);
    }
};

int main(){

    fstream truncate;
    truncate.open("new_student", ios::trunc | ios::out | ios::in); 
    truncate<<"Enter portal\n";
    truncate.close();

    ofstream ask;
    ask.open("ask"); 
    ask<<"Enter student details"<<endl;
    ask<<"Enter enrollment number : "<<endl;
    ask<<"Enter name : "<<endl;
    ask<<"Enter year of admission : "<<endl;
    ask<<"Enter cgpa : "<<endl;
    ask<<"done"<<endl;
    ask.close();

    ofstream men;
    men.open("menu"); 
    men<<"menu :"<<endl;
    men<<"1 Add new student to the database ."<<endl;
    men<<"2 Show all student records ."<<endl;
    men<<"3 delete a student from database ."<<endl;
    men<<"4 search for a student record ."<<endl;
    men<<"5 exit ."<<endl;
    men.close();

    ifstream menu;
    menu.open("menu");
    string x;
  
    while(menu >> x) {
        cout<<x<< " ";
        if(x==":" || x==".") cout<<endl;
    }

    while(1) {
        int x;
        cin>>x;
      
        if(x==1){
            record *temp=new record();
            temp->add(temp);
        }
        else if(x==2){
            cout<<"student records in file \"database\""<<endl;
            head->traverse();
        }
        else if(x==3) {
            record *to_del=head->search(3);
            to_del->del(to_del);
        }
        else if (x==4) {
            record* tem=head->search(4);
        }
        else if(x==5) break;
        else cout<<"invalid operation please try again\n";
    }
}