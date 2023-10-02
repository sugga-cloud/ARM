#include<iostream>
#include<fstream>
#include<cstring>
#include<conio.h>
#include<iomanip>
#include<sys/stat.h>
#include<windows.h>

using  namespace std;

void upper(char s[]){
    int i{};
    while(s[i])
    {
       s[i] = (char)toupper(s[i]); 
        i++;
    }
}

struct login_credentials{
    char username[20]{"admin"};
    char password[20]{"password"};

}defaults;

struct student{
    char name[20]{"none"};
    char student_id[20]{"none"};
    char username[20]{"none"};
    char password[20]{"none"};
};

struct subject{
    int total_subject{13};
    char student_id[20]{"none"};
    char subject_code[20][14]{
        {"BOE310"},
        {"BCS301"},
        {"BCS302"},
        {"BCS303"},
        {"BCS351"},
        {"BSC352"},
        {"BCS353"},
        {"BCC351"},
        {"BVE301"},
        {"BCC301"},
        {"TQA/LR"},
        {"TVA"},
        {"LIB"},
    };
    char subject_name[20][30]{
        {"Digital Electronics"},
        {"Data Structure"},
        {"COA"},
        {"Discrete Maths"},
        {"DS Lab"},
        {"COA Lab"},
        {"Web Designing Workshop"},
        {"Internship"},
        {"Human Values"},
        {"Cyber Security"},
        {"QA"},
        {"English"},
        {"Library"},
    };
    int subject_attendance[20]{};
    int subject_id[20]{0,1,2,3,4,5,6,7,8,9,10,11,12};
    int periods[6][10]{
        {0,12,2,0,1,4,4},
        {7,7,1,9,0,8,3},
        {3,0,12,1,0,10,1},
        {6,6,2,9,3,5,5},
        {2,3,2,8,9,12,0},
        {11,1,2,10,8,4,4},
    };
    int periods_perday{7};
    int subject_total_classes[30]{};
};

class ARM{
    public:
        ARM(){
            system("mkdir studentdata");
            system("mkdir student_subject_data");
            system("cls");
            ifstream file;
            file.open("encrypt_data.dat",ios::binary);
            if(file.is_open()){
            file.close();
            }
            else{
            file.close();
            ofstream file;
            file.open("encrypt_data.dat",ios::binary|ios::app);
            file.write((char*)&defaults,sizeof(defaults));
            file.close();
            }
            int choice{};
            cout<<"\t\t\t\tWelcome To Attendance Record Manager\n";
            cout<<"Please pick a choice";
            cout<<"\n1. Admin Login";
            cout<<"\n2. Student Login";
            cout<<"\n3. Quit";
            cout<<"\n\nPlease pick a choice : ";
            cin>>choice;
            switch (choice)
            {
            case 1:
                admin_form(1);
                break;
            
            case 2:
                student_form(1);
                break;
            
            case 3:
                exit(0);
                break;
            
            default:
                cout<<"\n Have enterd invalid choice ";
                getchar();
                ARM();
                break;
            }
        }

    int admin_form(int i);
    int admin();
    int student_form(int i);
    int student_registration(int o);
    int view_student();
    int remove_student();
    int factory_data_reset();
    int subject_registration(const string &s,struct student& stud);
    int verify(struct login_credentials ic, struct login_credentials lc);
    int verify(struct login_credentials ic);
    int create_new_Schedule(struct subject& sub,struct student& stud);
    int default_Schedule(struct subject& sub,struct student& stud);
    int mark_attendance(struct student);
    int view_attendance(struct student);
    int student_dashboard(char a[]);
};

int ARM::verify(struct login_credentials ic)
{   
    struct student lc;
    ifstream file;
    file.open("studentdata/stdata.dat",ios::binary);
    //file.read((char*)&lc,sizeof(student));
    while(!file.eof()){
    file.read((char*)&lc,sizeof(student));
   
    if((!strcmp(lc.username,ic.username)&& !strcmp(lc.password,ic.password)))
    {file.close();
    return 0;
    }
    }
        file.close();
        return 1;
    
}



int ARM::admin_form(int i=1){
    system("cls");
    ifstream file;
    file.open("encrypt_data.dat",ios::binary);
   
    struct login_credentials lc,ic;
    file.read((char*)&lc,sizeof(struct login_credentials));
    cout<<"\t\t\t\tAdmin Login\n";
    cout<<"\n";
    file.close();
    if(i==0)
    cout<<"Invalid Credentials\n";
    cout<<"\nEnter Username : ";
    cin>>ic.username;
    cout<<"\nEnter Password : ";
    cin>>ic.password;
    cout<<"\n";
    if(verify(ic,lc)==1)
        admin();
    else
        admin_form(0);

}

int ARM::student_form(int i=1){
    system("cls");
    struct login_credentials ic;

    cout<<"\t\t\t\tStudent Login\n";
    cout<<"\n";
    if(i==0)
    cout<<"Invalid Credentials";
    cout<<"\n";
    cout<<"\nEnter Username : ";
    cin>>ic.username;
    cout<<"\nEnter Password : ";
    cin>>ic.password;
    cout<<"\n";
    if(verify(ic)==0)
        student_dashboard(ic.username);
    else
        student_form(0);

}

int ARM::verify(struct login_credentials ic, struct login_credentials lc)
{
    if(!strcmp(ic.username,lc.username)&&(!strcmp(ic.password,lc.password)))
        return 1;
    else
        return 0;
}

int ARM::admin(){
    system("cls");
    int choice{};
    cout<<"\t\t\t\tWelcome Admin!\n";
    cout<<"Please pick a choice";
    cout<<"\n1. New Student Registration";
    cout<<"\n2. View Students";
    // cout<<"\n3. Remove Students";
    cout<<"\n3. Factory Data Reset";
    cout<<"\n4. Quit";
    cout<<"\n\nPlease pick a choice : ";
    cin>>choice;
    switch (choice)
    {
        case 1:
            student_registration(0);
            break;
            
         case 2:
             view_student();
             break;
            
        // case 3:
        //     remove_student();
        //     break;
            
        case 3:
            factory_data_reset();
            break;
            
        case 4:
            exit(0);
            break;
            
        default:
            cout<<"\n Have enterd invalid choice ";
            getchar();
             admin();
             break;
    }

}


int ARM::view_student(){
    ifstream file;
    student st;
    file.open("studentdata/stdata.dat",ios::binary);
    int i{};
    if(file.is_open()){
    file.read((char*)&st,sizeof(student));
    while (!file.eof())
    {
        /* code */
        cout<<"Srl No : "<<++i<<endl;
        cout<<"Name : "<<st.name<<endl;
        cout<<"Student ID : "<<st.student_id<<endl;
        cout<<"Username : "<<st.username<<endl;
        cout<<"Password : "<<st.password<<endl;
        cout<<"--------------------------------"<<endl;
        file.read((char*)&st,sizeof(student));
    }
    }
    else{cout<<"Error! \nError Code : 460";}
    file.close();
    cout<<"\nPress Enter To GoTo Dashboard....";
    getch();
    admin();
}

int ARM::remove_student()
{   
    system("cls");
    ifstream file;
    ofstream file1;
    ifstream subfile;
    ofstream subfile1;
    student st;
    subject sub;
    file.open("studentdata/stdata.dat",ios::binary);
    file1.open("studentdata/temp.dat",ios::binary|ios::app);
    subfile.open("student_subject_data/subdata.dat",ios::binary);
    subfile1.open("student_subject_data/temp.dat",ios::binary|ios::app);
    int i{};
    char id[20];
    cout<<"Enter Student ID : "<<endl;
    cin>>id;
    upper(id);
    file.read((char*)&st,sizeof(student));
    subfile.read((char*)&sub,sizeof(subject));
    while (!file.eof())
    {
        /* code */
        
        if(!strcmp(st.student_id,id)&& (!strcmp(sub.student_id,id)))
        {     
        cout<<"Srl No : "<<++i<<endl;
        cout<<"Name : "<<st.name<<endl;
        cout<<"Student ID : "<<st.student_id<<endl;
        cout<<"Username : "<<st.username<<endl;
        cout<<"Password : "<<st.password<<endl;
        cout<<"Press Enter To Delete or OTHER KEY to Cancel...\n--------------------------------"<<endl;
        i=getch();
            if(i==13)
            {
                file.seekg(0);
                subfile.seekg(0);
                while(!file.eof())
                {
                file.read((char*)&st,sizeof(student));
                subfile.read((char*)&st,sizeof(student));
                    if((!strcmp(st.student_id,id))&&(!strcmp(sub.student_id,id)))
                    {}
                    else{
                    file1.write((char*)&st,sizeof(student));
                    file.read((char*)&st,sizeof(student));
                    subfile1.write((char*)&sub,sizeof(subject));
                    subfile.read((char*)&sub,sizeof(subject));
                    }
                }
                file.close();
                file1.close();
                subfile.close();
                subfile1.close();
                remove("studentdata/stdata.dat");
                remove("student_subject_data/subdata.dat");
                rename("student_subject_data/temp.dat","student_subject_data/subdata.dat");
                rename("studentdata/temp.dat","studentdata/stdata.dat");
            
                cout<<"Removing Student Database"; 
                for(int j=0;j<10;j++){
                for(i=0;i<5;i++)
                {
                cout<<".";
                Sleep(100);
            
                }
                cout<<"\b\b\b\b\b     \b\b\b\b\b";
                }
                i=1;
            }
            // file.close();
            // file1.close();
            // subfile.close();
            // subfile1.close();
            cout<<"\nDone!\n";
            break;
        }

        file.read((char*)&st,sizeof(student));
                subfile.read((char*)&sub,sizeof(subject));

    }
    remove("studentdata/temp.dat");
    remove("student_subject_data/temp.dat");
                
    file.close();
    file1.close();
    subfile.close();
    subfile1.close();
    if(i==0){cout<<"No Data Found\n"<<endl;}
    cout<<"Press Enter To GoTo Dashboard....";
    getch();
    admin();
}

int ARM::factory_data_reset()
{
    system("cls");
    int i{};
    cout<<"Are You Sure?(y/n) ";
    i=getch();
    if((i==121)||(i==89))
    {   
        system("cls");
        remove("studentdata/stdata.dat");
        remove("studentdata/temp.dat");
        remove("student_subject_data/subdata.dat");
        remove("student_subject_data/temp.dat");
        remove("encrypt_data.dat");
        cout<<"\nDeleting DataBase";
        for(int j=0;j<10;j++){
        for(i=0;i<5;i++)
        {
            cout<<".";
            Sleep(100);
        
        }
        cout<<"\b\b\b\b\b     \b\b\b\b\b";
        }
        system("rmdir student_subject_data");
        system("rmdir studentdata");
        cout<<"\nRemoving Temp files, Admin Data etc";
        for(int j=0;j<10;j++){
        for(i=0;i<5;i++)
        {
            cout<<".";
            Sleep(100);
        }
        cout<<"\b\b\b\b\b     \b\b\b\b\b";
        }
        cout<<"\nDone!\n";
        
        cout<<"\nClosing Software";
        for(int j=0;j<10;j++){
        for(i=0;i<5;i++)
        {
            cout<<".";
            Sleep(100);
        }
        cout<<"\b\b\b\b\b     \b\b\b\b\b";
        }
        
    }
    else if((i==110)||(i==78))
    {
        admin();
    }
    else{factory_data_reset();}
}

int ARM::student_registration(int o=0){

    system("cls");
    if(o!=0)
    {
        cout<<"\n\nUsername Already Exist.\nEnter Details Again\n";
    }
    char a[10],b[19];
    int i;
    struct student s,s1;
    cout<<"\nEnter First Name : ";
    cin>>a;
    cout<<"\nEnter Last Name : ";
    cin>>b;
    strcat(a," ");
    strcat(a,b);
    strcpy(s.name,a);

    // cin.ignore('\n');
    cout<<"\nStudent ID : ";
    cin.ignore();
    cin>>s.student_id;
    upper(s.student_id);
    
    cout<<"\nUsername : ";
    cin>>s.username;
    cin.ignore();
    cout<<"\nPassword : ";
    cin>>s.password;
    cin.ignore();
    cout<<"Wanna continue...?( y for continue & any key for reset) : ";
    i=getch();
    ifstream fi;
    fi.open("studentdata/stdata.dat",ios::binary);
    if(fi.is_open())
    {
        while(!fi.eof())
        {
            fi.read((char*)&s1,sizeof(student));
            if(!strcmp(s1.username,s.username))
            {   
                fi.close();
                student_registration(1);
            }
            // fi.read((char*)&s1,sizeof(student));

        }

    }
    if(i==121 || i==89){
        subject_registration(s.student_id, s);
    }
    else{
        student_registration();
    }
}

int ARM::subject_registration(const string& s,struct student& stud)
{
    system("cls");
    int i{};
    struct subject sub;
    system("cls");
    cout<<"Select an option";
    cout<<endl<<"1. Create new Schedule";
    cout<<endl<<"1. Use Default(Section C)";
    cout<<"\nPick A Choice : ";
    for(i=0;i<sizeof(s);i++)sub.student_id[i] = s[i];
    cin>>i;
    switch (i)
    {
    case 1:
        create_new_Schedule(sub,stud);
        break;
    
    case 2:
        default_Schedule(sub,stud);
        break;
    
    default:
        cout<<"\nInvalid Option";
        getch();
        subject_registration(stud.student_id,stud);
        break;
    }

   
    // sub.student_id = s;
   
    // go:
    // system("cls");
    // cout<<"Select an option";
    // cout<<endl<<"1. Create new Schedule";
    // cout<<endl<<"1. Use Default(Section C)";
    // cout<<"\nPick A Choice : ";
    // cin>>i;
    // switch (i)
    // {
    // case 1:
    //     create_new_Schedule(sub,stud);
    //     break;
    
    // case 2:
    //     default_Schedule(sub,stud);
    //     break;
    
    // default:
    //     cout<<"\nInvalid Option";
    //     getch();
    //     goto go;
    //     break;
    // }

}

    int ARM::create_new_Schedule(struct subject& sub,struct student& stud)
    {
        int i{},n{},k{};
        system("cls");
         
    cout<<uppercase<<"Register your subjects"<<endl;
    cout<<"Enter Total Subjects : ";
    cin>>sub.total_subject;
    cin.ignore();
    cout<<endl<<endl;
   
    for(i=0;i<sub.total_subject;i++)
    {
        sub.subject_id[i]=i;
        cout<<"Subject ID (Auto Generated) : "<<sub.subject_id[i]+1;
        cout<<endl<<"Enter Subject Code : ";
        gets(sub.subject_code[i]);
        // -cin.ignore('\n');
        cout<<endl<<"Enter Subject Name : ";
        gets(sub.subject_name[i]);
        // cin.ignore();
        cout<<"\n-------------------------------------------";
    }

    system("cls");
    // cout<<setw(20);
    cout<<left<<setw(20)<<"ID "<<setw(20)<<" CODE"<<setw(20)<< "NAME"<<endl;
    for(i=0;i<sub.total_subject;i++){
        cout<<left<<setw(20)<<sub.subject_id[i]+1;cout<<left<<setw(20)<<sub.subject_code[i];cout<<left<<setw(20)<<sub.subject_name[i]<<endl;
    }
    cout<<endl<<"Press Enter To Continue.. OR Press Other key to Enter details Again"<<endl;
    i = getch();
    if(i!=13)
    {
        subject_registration(stud.student_id,stud);
    }

        system("cls");
        string days[6]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
        cout<<"\nEnter Number Of Periods Per Day : ";
        cin>>n;
        sub.periods_perday=n;
        cout<<"-------------------------------------------------"<<endl;
        cout<<setw(20);
        cout<<"ID "<<setw(20)<<" CODE"<<setw(20)<< "NAME"<<endl;
        for(i=0;i<sub.total_subject;i++)
        {
        cout<<left<<setw(20)<<sub.subject_id[i]+1;cout<<left<<setw(20)<<sub.subject_code[i];cout<<left<<setw(20)<<sub.subject_name[i]<<endl;
        }
        cout<<"-----------------------------------------\n"<<"Enter Subject ID To Add Subject!\nEnter Carefully As You Can't Change It\n";
        for(i=0;i<6;i++)
        {
            cout<<"----------------------------------------------------";
            cout<<endl<<days[i]<<" : \n";
            for(int j=0;j<n;j++)
            {
                cout<<"Period : "<<j+1<<endl;
                cout<<"Subject ID : ";
                cin>>k;
                sub.periods[i][j]=k-1;
                cout<<endl;
                cin.ignore();
            }
        }
        
        ofstream file1,file2;
        file1.open("studentdata/stdata.dat",ios::binary|ios::app);
        file2.open("student_subject_data/subdata.dat",ios::binary|ios::app);
        file1.write((char*)&stud,sizeof(struct student));
        file2.write((char*)&sub,sizeof(sub));
        file1.close();
        file2.close();
        cout<<"Registration Succesfull....\nYou Are Redirecting To Student Login";
        for(int j=0;j<10;j++){
        for(i=0;i<5;i++)
        {
            cout<<".";
            Sleep(100);
        }
        cout<<"\b\b\b\b\b     \b\b\b\b\b";
}
       student_form(1);

        
    } 


int ARM::student_dashboard(char a[]){
    system("cls");
    
    struct student lc;
    int i{};
    ifstream file;
    file.open("studentdata/stdata.dat",ios::binary);
    //file.read((char*)&lc,sizeof(student));
    while(!file.eof()){
    file.read((char*)&lc,sizeof(student));
    if((!strcmp(lc.username,a)))
    break;
    }
    file.close();
    cout<<uppercase<<"student dashboard";
    cout<<endl<<endl;
    cout<<"Student Details : \n";
    cout<<uppercase<<"Name : "<<lc.name<<endl;
    cout<<"UserName : "<<lc.username<<endl;
    cout<<"Student ID : "<<lc.student_id<<endl;
    cout<<"password : ***********"<<endl;
    cout<<" -------------------------------------------------------"<<endl;
    
    cout<<endl<<endl;
    cout<<uppercase<<"Pick Options\n";
    cout<<"1. Mark Attendance"<<endl;
    cout<<"2. View Attendance"<<endl;
    cout<<"3. Log Out"<<endl;
    cout<<"Please pick a choice : ";
    cin>>i; 
    switch (i)
    {
    case 1:
        mark_attendance(lc);
        break;
    case 2:
        view_attendance(lc);
        break;
    case 3:
        ARM();
        break;
    
    default:
        cout<<"invalid choice";
        getch();
        student_dashboard(a);
        break;
    }   
}

int ARM::default_Schedule(struct subject& sub,struct student& stud)
{
    system("cls");
    int i{};
    ofstream file1,file2;
        file1.open("studentdata/stdata.dat",ios::binary|ios::app);
        file2.open("student_subject_data/subdata.dat",ios::binary|ios::app);
        file1.write((char*)&stud,sizeof(struct student));
        file2.write((char*)&sub,sizeof(sub));
        file1.close();
        file2.close();
        cout<<"Registration Succesfull....\nYou Are Redirecting To Student Login";
        for(int j=0;j<10;j++){
        for(i=0;i<5;i++)
        {
            cout<<".";
            Sleep(100);
        }
        cout<<"\b\b\b\b\b     \b\b\b\b\b";
}
       student_form(1);

        
} 

int ARM::mark_attendance(struct student stud)
{
    system("cls");
    struct subject sub,sub1;
    int k{};
    ifstream file;
    file.open("student_subject_data/subdata.dat",ios::binary);
    //file check
    if(!file.is_open())
    {cout<<"Database Error!";}
    while(!file.eof()){
    file.read((char*)&sub,sizeof(subject));
    if((!strcmp(sub.student_id,stud.student_id)))
    break;
    }
    file.close();
    char days[6][10]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    int day{};
    cout<<"Enter Day  (i.e For Monday enter 1) : ";
    cin>>day;
    day-=1;

    cout<<"\n Mark Attendance for : "<<days[day]<<endl;
    for(int i=0;i<sub.periods_perday;i++)
    {
        cout<<"Period : "<<i+1<<endl;
        cout<<"Subject Code : "<<sub.subject_code[sub.periods[day][i]]<<endl;
        cout<<"Subject Name : "<<sub.subject_name[sub.periods[day][i]]<<endl;
        cout<<"Attendance : ";
        cin>>k;
        cin.ignore();
        sub.subject_attendance[sub.periods[day][i]]+=k;
        sub.subject_total_classes[sub.periods[day][i]]+=1;
        cout<<"-------------------------------------------------------"<<endl;
    }
    fstream file1("student_subject_data/subdata.dat",ios::in|ios::out|ios::ate|ios::binary);
    file1.seekg(0);
    while(!file1.eof()){
    file1.read((char*)&sub1,sizeof(subject));
    if(!strcmp(sub1.student_id,sub.student_id))
    {
        break;
    }
    }

    file1.seekp(file1.tellg() - (unsigned)sizeof(subject));
    file1.write((char*)&sub,sizeof(subject));
    file1.close();
    cout<<"done!"<<"Press Enter To Return To DashBoard";
    getch();
    student_dashboard(stud.username);

} 
int ARM::view_attendance(struct student stud)
{   
    system("cls");
    int i{},sum1{},sum2{};
    float per{};
    struct subject sub;
    ifstream file;
    file.open("student_subject_data/subdata.dat",ios::binary);
    //file check
    if(!file.is_open())
    {cout<<"Database Error!";}
    while(!file.eof()){
    file.read((char*)&sub,sizeof(subject));
    if((!strcmp(sub.student_id,stud.student_id)))
    break;
    }
    file.close();
    cout<<left<<setw(10)<<"Srl No."<<setw(20)<<"Subject Code"<<setw(30)<<"Subject Name"<<setw(20)<<"Total Attendance"<<setw(20)<<"Present In Classes"<<endl;
    for(i=0;i<sub.total_subject;i++)
    {   
        cout<<left<<setw(10)<<sub.subject_id[i]+1<<setw(20)<<sub.subject_code[i]<<setw(30)<<sub.subject_name[i]<<setw(20)<<sub.subject_total_classes[i]<<setw(20)<<sub.subject_attendance[i]<<endl;
        sum1=sum1+sub.subject_attendance[i];
        sum2+=sub.subject_total_classes[i];
    }
    per = ((float)sum1/sum2)*100;
    cout<<"\n\nTotal Classes : "<<sum2<<endl;
    cout<<"\n\nTotal Presents : "<<sum1<<endl;
    cout<<"\n\nTotal Percentage : "<<per<<"%"<<endl;
    cout<<"done!"<<endl<<"Press Enter To Return To DashBoard";
    getch();
    student_dashboard(stud.username);
}   