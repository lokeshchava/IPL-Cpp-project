#include<iostream>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<process.h>
#include<ctype.h>
#include<fstream>
using namespace std;
class data
{
	char name[30];
	char team[50];
	int playercode;
	int m1r,m2r,m3r;
	int total_run;
	public:
	data()
	{
		playercode=0;
		strcpy(name,"");
		strcpy(team,"");
		m1r=0;
		m2r=0;
		m3r=0;
		total_run=0;
	}
	void enter_name_runs()			//to take entry of new record
	{
		cout<<"\n Enter players name:";
		cin>>name;
		cout<<"\n Enter players code:";
		cin>>playercode;
		cout<<"\n Enter players team:";
		cin>>team;
		cout<<"\nfirstmatchruns:";
		cin>>m1r;
		cout<<"\nsecondmatchruns:";
		cin>>m2r;
		cout<<"\nthirdmatchruns:";
		cin>>m3r;
		total_runs();
	}
	void show_record()		//to display the record
	{
		cout<<"\nplayer code:"<<playercode;
		cout<<"\nplayername:"<<name;
		cout<<"\nfirstmatchruns:"<<m1r;
		cout<<"\nsecondtmatchruns:"<<m2r;
		cout<<"\nthirdmatchruns:"<<m3r;
		cout<<"\nTotalruns:"<<total_run;
		cout<<"\nPlayersTeam:"<<team;
	}
	void total_runs()
	{
		total_run=m1r+m2r+m3r;
	}
	int getplayercode()
	{
		return playercode;
	}
	int gettotalruns()
	{
		return total_run;
	}
	char* get_name()
	{
		return name;
	}
void modify_data()	//take data to modify exesting records
	{
		cout<<"\n ............enter new data to modify.........";
		cout<<"\nfirstmatchruns:";
		cin>>m1r;
		cout<<"\nsecondmatchruns:";
		cin>>m2r;
		cout<<"\nthirdmatchruns:";
		cin>>m3r;
		total_runs();		
	}
};
data d;
fstream file;
fstream file1;
void highest()
{
	file.open("recordipl.txt",ios::in|ios::binary);
	int post=0,tr=0,plr_code=0,run=0;
	file.read((char *)&d,sizeof(d));
	while(file)
	{
		run=d.gettotalruns();
		if(run>tr)
		{
			post=file.tellg();
			tr=run;
		}
		file.read((char *)&d,sizeof(d));
	}
	file.close();
	file.open("recordtxt.txt",ios::in|ios::binary);
	file.seekg(post-sizeof(d));
	file.read((char *)&d,sizeof(d));
	cout<<"\nHighest runs scored by:"<<d.get_name();
	cout<<"\nplayer total runs are:"<<tr;
	float avg;
	avg=(tr)/3;
	cout<<"\n players average is:"<<avg;
	file.close();
}
void insert()	//for insearting new record
{
	int i,no;
	file.open("recordipl.txt",ios::in|ios::app|ios::binary);
	cout<<"\nhow many records you want to enter:";
	cin>>no;
	for(i=0;i<no;i++)
	{
		d.enter_name_runs();
		file.write((char *)&d,sizeof(d));
	}
	file.close();
}
void search()
{
	int p,r,srch=0;
	file.open("recordipl.txt",ios::in|ios::binary);
	cout<<"\nEnter the player code to see his record:";
	cin>>r;
	file.seekg(0);
	file.read((char *)&d,sizeof(d));
	while(file)
	{
		p=d.getplayercode();
		if(r==p)
		{
			d.show_record();
			srch=1;
			break;
		}
		else
		{
			file.read((char *)&d,sizeof(d));
		}
	}
	file.close();
	if(srch==0)
	{
		cout<<"\n there is no record which have this player id:";
	}
}
void display()
{
	file.open("recordipl.txt",ios::in|ios::out|ios::binary);
	cout<<"the entered record is";
	file.read((char *)&d,sizeof(d));
	while(file)
	{
		d.show_record();
		file.read((char *)&d,sizeof(d));
	}
	file.close();
}
void modify()
{
	int poi=0,got=0,dmd=0;
	cout<<"/nEnter the players code whose record is to be modified:";
	cin>>dmd;
	int ifdata=1;
	file.open("recordipl.txt",ios::in|ios::out|ios::binary);
	poi=file.tellg();
	while(file)
	{
		file.read((char *)&d,sizeof(d));
		got=d.getplayercode();
		if(dmd==got)
		{
			file.seekg(poi);
			d.modify_data();
			ifdata=2;
			file.write((char *)&d,sizeof(d));
			break;
		}
		poi=file.tellg();
	}
	file.close();
	if(ifdata==1)
	{
		cout<<"\n Data not avalable";
	}
}
void delete_record()
{
	int pointer=0,remove_record=0,size=0,code_get=0;
	cout<<"\nEnter the players code whose record has to be deleted";
	cin>>remove_record;
	file.open("recordipl.txt",ios::in|ios::out|ios::binary);
	file1.open("tempo.txt",ios::in|ios::out|ios::binary);
	file.seekg(0);
	while(file)
	{
		file.read((char *)&d,sizeof(d));
		code_get=d.getplayercode();
		if(remove_record==code_get)
		{
			cout<<"";
		}
		else
		{
			file.write((char *)&d,sizeof(d));
		}
	}
	file.close();
	file1.close();
	remove("recordipl.txt");
	rename("tempo.txt","recordipl.txt");
}
int main()
{
	int choice;
	char ans='n';
	do
	{
		cout<<"\nPLAYERS RECORD MAINTAIANANCE";
		cout<<"\n 1.insertRecord\n2.DisplayRecord\n3.SearchRecord\n4.ModifyRecord\n5.Highestruns\n6.DeletepreviousenteredRecord\n7.EXIT";
		cout<<"\n Enter Your choice:";
		cin>>choice;
		switch(choice)
		{
			case 1:insert();
			break;
			case 2:display();
			break;
			case 3:search();
			break;
			case 4:modify();
			break;
			case 5:highest();
			break;
			case 6:delete_record();
			break;
			case 7:exit(0);
			break;		
			default:cout<<"\n Enter choice between 1 to 6";	
		}
		cout<<"\n Do you want to choose any other option ?:(y/n):";
		cin>>ans;
	}
	while(ans=='y'||ans=='y');
	{
		getch();
	}
	return 0;
}

