#include<stdlib.h>
#include<iostream>
#include<fstream>

using namespace std;

#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 6
#define DB_NAME "database"

static int i=0;

typedef struct flight{
	
	char flightcode[MAX_FLIGHTCODE_LEN];
	char arrival_city[MAX_CITYCODE_LEN];
	
	typedef struct date_time{
		int month, day, hour, minute;
	}date_time_t;
	
	date_time_t departure_dt;
	date_time_t arrival_dt;
	
}flight_t;

flight_t flights[MAX_NUM_FLIGHTS];



void input(flight_t obj[] ){
	
	i = 0;
	cout<<"Enter Flight Code> ";
	cin>>obj[0].flightcode;
	
	int flag2 = 0;
	while(flag2 == 0){
		if((obj[0].flightcode[0]>='A' && obj[0].flightcode[0]<='Z') && (obj[0].flightcode[1]>='A' && obj[0].flightcode[1]<='Z') && (obj[0].flightcode[2]>='0' && obj[0].flightcode[2]<='9') && (sizeof(obj[0].flightcode) <= 6)){
			flag2 = 1;
		}
		else{
			cout<<"\nInput Again";
			cout<<"\nEnter Flight Code> ";
			cin>>obj[0].flightcode;
		}
	}
	
	cout<<"\nEnter Departure info for the flight leaving SYD.";
	cout<<"\nEnter month, date, hour, minute seprated by spaces> ";
	cin>>obj[0].departure_dt.month>>obj[0].departure_dt.day>>obj[0].departure_dt.hour>>obj[0].departure_dt.minute;
	int flag = 0;
	while(flag == 0){
		if((obj[0].departure_dt.month<13 && obj[0].departure_dt.month>0) && (0<obj[0].departure_dt.day && obj[0].departure_dt.day<32) && (-1<obj[0].departure_dt.hour && obj[0].departure_dt.hour<24) && (-1<obj[0].departure_dt.minute && obj[0].departure_dt.minute<60)){
			flag = 1;
			cout<<"hello";
		}
		else{
			cout<<"\nInput Again";
			cout<<"\nEnter month, date, hour, minute seprated by spaces> ";
			cin>>obj[0].departure_dt.month>>obj[0].departure_dt.day>>obj[0].departure_dt.hour>>obj[0].departure_dt.minute;
		}
	}
	
	cout<<"\nEnter the arrival city code> ";
	cin>>obj[0].arrival_city;
	
	
	cout<<"\nArrival city info.";
	cout<<"\nEnter month, date, hour, minute seprated by spaces> ";
	cin>>obj[0].arrival_dt.month>>obj[0].arrival_dt.day>>obj[0].arrival_dt.hour>>obj[0].arrival_dt.minute;
	int flag1 = 0;
	while(flag1 == 0){
		if((obj[0].arrival_dt.month<13 && obj[0].arrival_dt.month>0) && (0<obj[0].arrival_dt.day && obj[0].arrival_dt.day<32) && (-1<obj[0].arrival_dt.hour && obj[0].arrival_dt.hour<24) && (-1<obj[0].arrival_dt.minute && obj[0].arrival_dt.minute<60)){
			flag1 = 1;
			cout<<"hello";
		}
		else{
			
			cout<<"\nInput Again";
			cout<<"\nEnter month, date, hour, minute seprated by spaces> ";
			cin>>obj[0].arrival_dt.month>>obj[0].arrival_dt.day>>obj[0].arrival_dt.hour>>obj[0].arrival_dt.minute;
		}
	}
	i++;
	
}


void display(flight_t obj[]){
	
	cout<<"\nFlight Origin          Destination    ";
	cout<<"\n------ --------------- --------------\n";
	for(int x=0;x<i;x++){
		if((obj[x].departure_dt.hour <10)){
			cout<<obj[x].flightcode<<"    "<<"SYD "<<obj[x].departure_dt.month<<"-"<<obj[x].departure_dt.day<<" "<<"0"<<obj[x].departure_dt.hour<<":"<<obj[x].departure_dt.minute<<" "<<obj[x].arrival_city<<" "<<obj[x].arrival_dt.month<<"-"<<obj[x].arrival_dt.day<<" "<<obj[x].arrival_dt.hour<<obj[x].arrival_dt.minute<<"\n";  
		}
		else{
			cout<<obj[x].flightcode<<"    "<<"SYD "<<obj[x].departure_dt.month<<"-"<<obj[x].departure_dt.day<<" "<<obj[x].departure_dt.hour<<":"<<obj[x].departure_dt.minute<<" "<<obj[x].arrival_city<<" "<<obj[x].arrival_dt.month<<"-"<<obj[x].arrival_dt.day<<" "<<obj[x].arrival_dt.hour<<obj[x].arrival_dt.minute<<"\n";  
		}
		
	}

}



void save(flight_t obj[]){
	fstream iff("flight_data.dat", ios::binary | ios::app);
	iff.write((char *)&obj[0], sizeof(obj[0]));
	iff.close();
	cout<<"Data saved";
}

void load(){
	flight_t obj[1];
	//flight_t flights[MAX_NUM_FLIGHTS];
	i =0;
	fstream iff("flight_data.dat", ios::binary | ios::in);
	while((iff.read((char *)&obj[0], sizeof(obj[0])))){
	
		flights[i] = obj[0];
		i++;
	}
	iff.close();
		
}

void print_menu (){


    cout<<"\n";
    cout<<"1. add a flight\n";
    cout<<"2. display all flights to a destination\n";
    cout<<"3. save the flights to the database file\n";
    cout<<"4. load the flights from the database file\n";
    cout<<"5. exit the program\n";
    cout<<"Enter choice (number between 1-5)> ";
}

int main()
{
    print_menu();
    
    int n;
    int flag1 = 0;

    while(1){
		cin>>n;
		if(n == 2 && flag1 == 0){
			cout<<"First Input the data\n";
    		input(flights);
    		flag1 = 1;
		}    
    	else{
    		switch(n){
    			case 1:
    				input(flights);
    				flag1 = 1;
    				break;
    			case 2:
    				display(flights);
    				break;
    			case 3:
    				save(flights);
    				break;
    			case 4:
    				 load();
					 flag1 = 1;
    				break;
    			case 5:
    				exit(0);
    			default:
    				cout<<"invalid choice";
			}
		}	
	}
	
    return 0;
}
