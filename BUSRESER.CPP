#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
class TourBus
{
int b_id;
char destination[200];
char time[50];
int max_seats;
int booked;
public:
   TourBus()
   {
   b_id=0;
   max_seats=50;
   booked=0;
   strcpy(time,"9:30am");
   strcpy(destination," ");
   }
   void input();
   void show();
   void display();

   int getid()
   {
   return b_id;
   }
   void book()
   {
   booked++;
   }
   char* getdestination()
   {
   return destination;
   }
   char* getTime()
   {
   return time;
   }
   int getbooked()
   {
   return booked;
   }
   int getmax()
   {
   return max_seats;
   }
};
class Ticket
{
	  char name[50];
	  TourBus bus;
	  public:

	  void generate(char cname[], TourBus tb)
	  {
	       strcpy(name,cname);
	       bus=tb;
	  }
	  void display()
	  {
	  cout<<"Customer Name "<<name<<endl;
	  cout<<"Details of Bus "<<endl;
	  bus.show();
	  }
};
void TourBus::input()
{
   cout<<"enter bus id:";
   cin>>b_id;
   cout<<"enter bus destination:";
   cin>>destination;
   cout<<"enter time of bus:";
   cin>>time;
}
void TourBus::display()
{
     cout<<b_id<<"\t"<<destination<<"\t"<<time<<"\t"<<max_seats<<"\t"<<booked<<"\n";
}
void TourBus::show()
{
   cout<<"bus id" <<b_id <<endl;
   cout<<"destination "<<destination <<endl;
   cout<<"Time "<<time<<endl;
   cout<<"No. of remaining seats" <<max_seats-booked <<endl;
}
void main()
{
       int ch;
       fstream F,G;
       TourBus b;
       do
       {
       clrscr();
       cout<<"press 1 -Add new Tour bus"<<endl;
       cout<<"press 2 -show select bus"<<endl;
       cout<<"press 3 -display all buses"<<endl;
       cout<<"press 4 -delete a bus"<<endl;
       cout<<"press 5 -book a ticket"<<endl;
       cout<<"press 6 -display booked ticket"<<endl;
       cout<<"press 7 -Exit"<<endl;
       cout<<"enter your choice:";
       cin>>ch;
       switch(ch)
       {
       case 1:
	    F.open("tour.dat",ios::app | ios::binary);     //open apend mode
	    b.input();
	    F.write((char*)&b, sizeof(b));               //write to file
	    F.close();
	    cout<<"bus added successful"<<endl;
	    getch();
	    clrscr();
	    break;
       case 2:
	    int id,chk=0;
	    cout<<"enter the bus id to be display:";
	    cin>>id;
	    F.open("tour.dat",ios::in | ios::binary);
	    if(F.fail())
		   cout<<"can't open file"<<endl;
	    else
	    {
	    while(F.read((char*)&b,sizeof(b)))
	    {
		if(b.getid()==id)
		{
		b.show();
		chk=1;
		break;
	    }
       }
       if(chk==0)
	    cout<<"bus not found"<<endl;
       }
       F.close();
       break;

       case 3:
	    F.open("tour.dat",ios::in | ios::binary);     //open input mode
	    if(F.fail())
		   cout<<"can't open file"<<endl;
	    else
	    {
		   while(F.read((char*)&b,sizeof(b)))      //read to file
			b.display();
	    }
	    F.close();
	    cout<<"press a key to continue"<<endl;
	    getch();
	    clrscr();
       break;

       case 4:
	    chk=0;
	    cout<<"enter the bus id to be deleted:";
	    cin>>id;
	    F.open("Tour.dat",ios :: in | ios :: binary);
	    G.open("jeet.dat",ios :: out | ios ::binary);
	    if(F.fail())
		 cout<<"can't open file "<<endl;
	    else
	    {
		 while(F.read((char*)&b,sizeof(b)))
		 {
		       if(b.getid()!=id)
		       {
		       G.write((char*)&b,sizeof(b));
		       }
		       else
		       {
			   b.show();
			   chk=1;
		       }
		 }
		 if(chk==0)
			 cout<<"bus not found"<<endl;
		 else
			 cout<<"bus deleted "<<endl;
		 }
		 F.close();
		 G.close();
		 remove("tour.dat");
		 rename("jeet.dat","tour.dat");
		 break;
	   case 5:
		  char dest[50],cname[50];
		  int b_id;
		  Ticket t;
		  cout<<"Enter the destination ";
		  gets(dest);
		  F.open("tour.dat",ios::in | ios::out | ios::binary);
		  if(F.fail())
			    cout<<"Can't open file "<<endl;
		  else
		  {
		      while(F.read((char*)&b, sizeof(b)))
		      {

		      if(strcmp(b.getdestination(),dest)==0)
		      {
			    b.show();
			    chk=1;
			    cout<<"Enter the customer name ";
			    gets(cname);
			    b.book();
			    t.generate(cname,b);
			    G.open("tickets.dat",ios::app | ios:: binary);
			    G.write((char*)&t, sizeof(t));
			    G.close();
			    F.seekp(F.tellg() -sizeof(b),ios::beg);
			    b.book();
			    F.write((char*)&b,sizeof(b));
			    cout<<"Ticket booked"<<endl;
			    getch();
			    break;
			    }
		      }
		      if(chk==0)
			cout<<"No bus found"<<endl;
		      }
		      F.close();
		      break;
	   case 6:
		cout<<"Booked Tickets"<<endl;
		G.open("tickets.dat",ios :: in | ios :: binary);
		if(G.fail())
		   cout<<"can't open file"<<endl;
		else
		{
		     while(G.read((char*)&t,sizeof(t)))
		     t.display();
		}
		G.close();
		cout<<"press a key to continue ->";
		getch();
	   }
       }while(ch!=7);
}






