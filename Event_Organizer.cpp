#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

const int months[]={31,28,31,30,31,30,31,31,30,31,30,31};
const int monthsl[]={31,29,31,30,31,30,31,31,30,31,30,31};
const string monname[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

struct Event
{
  int month;
  int day;
  int starth;
  int startm;
  int endh;
  int endm;
  string desc;
  struct Event* next;
};

class calendar
{
  int year;
  struct Event** list[12];
  bool leap;

  public:

  calendar(int yyyy)
  {
    year=yyyy;

    if (yyyy%4==0)
    {
      if (yyyy%100==0)
      {
        if (yyyy%400==0) leap=true;
        else leap=false;
      }
      else leap=true;
    }
    else leap=false;}
  void init()
  {  if (leap)
   { for (int i=0; i<12; i++)
    {
      list[i]=new Event*[monthsl[i]];
      for (int j=0; j<monthsl[i]; j++) list[i][j]=NULL;
    }
   }
    else for (int i=0; i<12; i++)
    {
      list[i]=new Event*[months[i]];
      for (int j=0; j<months[i]; j++) list[i][j]=NULL;
    }
  }
   void insert(int mmonth,int mday,int mstarth,int mstartm,int mendh,int mendm,string mdesc)
{
    //create a newnode with values
    struct Event *newNode = new Event();
    newNode->month = mmonth;
    newNode->day = mday;
    newNode->starth = mstarth;
    newNode->startm = mstartm;
    newNode->endh = mendh;
    newNode->desc = mdesc;
    newNode->next = NULL;

    //calculate hash key
    int key = mday;
//cout<<"key="<<key;
if(key==0)
key++;
    //check if chain[key] is empty

    if(list[mmonth-1][key-1] == NULL)
    {
    //cout<<"in if";
    list[mmonth-1][key-1] = newNode;
	}

    //collision
    else
    {
        //add the node at the start of chain[key].

        //cout<<"in else";
        newNode->next=list[mmonth-1][key-1];
        list[mmonth-1][key-1]=newNode;


    }

}

  void create ()
  {
    int mmonth, mday,mstarth,mstartm,mendh,mendm; string mdesc;


    do
    {
      cout<<"Enter month(1-12): "; cin>>mmonth;
      if (mmonth>=1&&mmonth<=12) {break;}
      else cout<<"Invalid month. Try again\n";
    } while (1);

    do
    {
      cout<<"Enter date(1-31): "; cin>>mday;

      if (leap)
      {if (mday>=1&&mday<=monthsl[mmonth-1])
      {
        break;
      }
      else cout<<"Invalid date. Try again\n";}

      else
      {if (mday>=1&mday<=months[mmonth-1])
      {
        break;
      }
      else cout<<"Invalid date. Try again\n";}

    } while (1);

    cout<<"Enter event start time:";

    do
    {
      cout<<"\nHours (0-23): ";
      cin>>mstarth;

      if (mstarth>=0&&mstarth<=23) {break;}
      else cout<<"Invalid. Try again.\n";
    } while (1);

    do
    {
      cout<<"Minutes (0-59): ";
      cin>>mstartm;

      if (mstartm>=0&&mstartm<=59) {break;}
      else cout<<"Invalid. Try again.\n";
    } while (1);

    cout<<"Enter event end time:";

    do
    {
      cout<<"\nHours (0-23): ";
      cin>>mendh;

      if (mendh>=0&&mendh<=23) {break;}
      else cout<<"Invalid. Try again.\n";
    } while (1);

    do
    {
      cout<<"Minutes (0-59): ";
      cin>>mendm;

      if (mendm>=0&&mendm<=59) { break;}
      else cout<<"Invalid. Try again.\n";
    } while (1);

    cout<<"Enter event name/description: ";
    while ((getchar()) != '\n'){}
    getline(cin,mdesc);


    insert(mmonth,mday,mstarth,mstartm,mendh,mendm,mdesc);

    system("cls");
    return;
  }


    void display()
  {
    int m,d;
    cout<<"Check events for a particular day. Enter month(1-12): ";                     //get required and valid month and date from the user
    do
    {
      cin>>m;
      if (m>=1 && m<=12) break;
      else cout<<"Invalid! Try again: ";
    } while (1);

    cout<<"Enter date(1-31): ";
    do
    {
      cin>>d;
      if (leap)
      {
        if (d>=1 && d<=monthsl[m-1]) break;
      }

      else
      {
        if (d>=1 && d<=months[m-1]) break;
      }

      cout<<"Invalid! Try again: ";

    } while (1);

    int key = d;
    if(key==0)
    key++;

    if (list[m-1][key-1]==NULL)                             //check if chain[key] is empty
	{
	cout<<"No events found.\n";
	}
    else                                                    //traverse the list and display the events
    {
      cout<<endl<<endl<<d<<" "<<monname[m-1]<<" "<<year;
      Event* traverse=list[m-1][key-1];

      while (traverse!=NULL)
      {
        cout<<"\n"<<traverse->starth<<":"<<traverse->startm<<" to "<<traverse->endh<<":"<<traverse->endm<<endl<<traverse->desc<<endl;
        traverse=traverse->next;

      }
    }

    cout<<endl<<endl;
    cout<<"Press enter to continue"; while ((getchar()) != '\n'){} getchar();
    system("cls");

    return;
  }

  void del()
  {
    int m,d;                                                        //get required and valid month and date
    cout<<"\n\nEnter month: ";
    do
    {
      cin>>m;
      if (m>=1 && m<=12) break;
      else cout<<"Invalid! Try again: ";
    } while (1);

    cout<<"Enter date: ";
    do
    {
      cin>>d;
      if (leap)
      {
        if (d>=1 && d<=monthsl[m-1]) break;
      }

      else
      {
        if (d>=1 && d<=months[m-1]) break;
      }

      cout<<"Invalid! Try again: ";

    } while (1);

    int key = d;

    if(key==0)
    key++;

    //check if chain[key] is empty

    if(list[m-1][key-1] == NULL) cout<<"No events found.";              //check if events exist on the entered date

    else                                                                //display the events if they exist along with s. no.
    {
      int i=0; int dch;

      cout<<endl<<endl<<d<<" "<<monname[m-1]<<" "<<year;
      Event* traverse=list[m-1][key-1];

      while (traverse!=NULL)
      {
        cout<<"\n"<<++i<<") "<<traverse->starth<<":"<<traverse->startm<<" to "<<traverse->endh<<":"<<traverse->endm<<endl<<traverse->desc<<endl;
        traverse=traverse->next;
      }

      cout<<"\n\nEnter the S.no. of the event you want to delete (0 to cancel): ";              //get s. no. of event to delete

      while (1)
      {
        cin>>dch;
        if (dch==0) break;
        if (dch<1 || dch>i) cout<<"Enter a valid no.: ";
        else break;
      }

      if (dch)                                                  //to make sure we delete only if the user did not enter 0 (cancel)
      {
        traverse=list[m-1][key-1];
        if (dch==1 && traverse->next==NULL)                     //check if event is the first one
        {
          delete traverse;
          list[m-1][key-1]=NULL;
        }
        else if (dch==1)
        {
          list[m-1][key-1]=traverse->next;
          delete traverse;
        }
        else                                                    //traverse to the event before the event to be deleted and then delete the required event
        {
          dch--;
          while (--dch) traverse=traverse->next;
          Event* temp=traverse->next;
          if (traverse->next->next==NULL) traverse->next=NULL;
          else traverse->next=traverse->next->next;
          delete temp;
        }
        cout<<"\nEvent has been deleted.";
      }
    }

    cout<<endl<<endl;
    cout<<"Press enter to continue"; while ((getchar()) != '\n'){} getchar();
    system("cls");

    return;
  }

  void menu()
  {
    char ch;

    while (1)
    {
      cout<<"\n\nWelcome to your "<<year<<" organizer.";
      cout<<"\n\n1. Add event\n\n2. View event by date\n\n3. Delete an event\n\n4. Exit\n\n";
      cout<<"Enter your choice from menu: ";
      cin>>ch;                  //get a menu choice

      switch (ch)               //execute the required function
      {
        case '1': create(); cout<<"\nEvent successfully added.\n"; break;
        case '2': display();  break;
        case '3': del(); break;
        case '4': return;
        default: cout<<"Invalid choice! Try again. ";
      }
    }


  }};



int main()
{
    int year;
    cout<<"Welcome to your event organizer! Enter the year to set up your calendar for the year: ";

  do
  {
    cin>>year;
    if (year>=2000&&year<=2025) break;
    else cout<<"Invalid! Enter a valid year from 2000 to 2025: ";
  } while(1);

  calendar C1 (year);
  C1.init();
  C1.menu();
  cout<<"Thank you!";

  return 0;

}
