/*--- Author 
	  Hasheem Ahmed ---*/

// Iostream for cout cin
#include <iostream>

//Iomanip for the setw and setfill
#include <iomanip>
using namespace std;

// First Come First Serve Algorithm Class

class SJFS
{
public:

	// Variables
	int NumberOfProcess;
	int* Proc;
	int* AT;
	int* BT;
	int* CT;
	int* WT;
	int* TAT;


	//Default Constructor
	SJFS()
	{
		NumberOfProcess = 0;
		AT = BT = CT = WT = TAT = Proc = NULL;
	}

	//Parameterized Constructor
	SJFS(int Process)
	{
		this->NumberOfProcess = Process;
		Proc = new int[Process];
		AT = new int[Process];
		BT = new int[Process];
		CT = new int[Process];
		WT = new int[Process];
		TAT = new int[Process];
	}

	// Input the arrival time and burst time values
	void ATinput()
	{
		cout << "Enter the Arrival and Burst time : ";
		for (int i = 0; i < NumberOfProcess; i++)
		{
			cout << "P" << i + 1 << " - \n";
			this->Proc[i] = i + 1;
			cout << "Arrival Time : ";
			cin >> this->AT[i];
			cout << "Burst Time : ";
			cin >> this->BT[i];
		}
	}

	// Swap function for Sorting Values using pass by reference
	void swap(int& x, int& y)
	{
		int temp = x;
		x = y;
		y = temp;
	}


	// Function to check the arrival time of the Process
	int ArrivalTimeChecker(int CTValue)
	{
		int value = 0;
		for (int i = 0; i < this->NumberOfProcess; i++)
		{
			if (CTValue > this->AT[i])
			{
				++value;
			}
		}

		// Return the Process that arrival time has reached 
		return value;
	}

	// calculating the completion time
	void CalculatingCT()
	{
		CT[0] = BT[0] + AT[0];
		for (int i = 1; i < this->NumberOfProcess; i++)
		{
			int elements = ArrivalTimeChecker(CT[i - 1]);

			// Take the Shortest Burst Time to the top to calculate the CT
			for (int j = i + 1 ; j < elements; j++)
			{
				if (this->BT[i] > this->BT[j])
				{
					swap(this->AT[j], this->AT[i]);
					swap(this->BT[j], this->BT[i]);
					swap(this->Proc[j],this->Proc[i]);
				}
			}

			this->CT[i] = this->CT[i - 1] + this->BT[i];
		}
	}

	
	// Calculating the waiting time
	void CalculatingWT()
	{
		for (int i = 0; i < NumberOfProcess; i++)
		{
			this->WT[i] = this->CT[i] - (this->AT[i] + this->BT[i]);
		}
	}


	// calculating turn around time
	void CalculatingTAT()
	{
		for (int i = 0; i < NumberOfProcess; i++)
		{
			this->TAT[i] = this->WT[i] + this->BT[i];
		}
	}

	//Sorting the Arrival time values by BUBBLE SORT
	void SortingATandBT()
	{
		bool sort = true;
		while (sort)
		{
			sort = false;
			for (int i = 0; i < this->NumberOfProcess - 1; i++)
			{
				if (this->AT[i] > this->AT[i + 1])
				{
					swap(this->AT[i], this->AT[i + 1]);
					swap(this->BT[i], this->BT[i + 1]);
					swap(this->Proc[i], this->Proc[i + 1]);
					sort = true;
				}
			}
		}
	}

	// calculating the average waiting time
	float AvgWaitingTime()
	{
		float avgWaitingTime = 0;

		for (int i = 0; i < this->NumberOfProcess; i++)
		{
			avgWaitingTime += this->WT[i];
		}

		return avgWaitingTime / this->NumberOfProcess;
	}

};

// Main Function
int main()
{
	// User Input for Number of Process
	int Process;
	cout << "Enter Number of Process : ";
	cin >> Process;

	// making Object of the FCFS class and initializing the Number of process
	SJFS obj(Process);


	// Taking Input of the Arrival time and Burst time
	obj.ATinput();

	// Sorting the Arrival Time For the First Come First Serve - FCFS
	obj.SortingATandBT();

	// Calculating the Completion time, Waiting Time , Turn Around Time
	obj.CalculatingCT();
	obj.CalculatingWT();
	obj.CalculatingTAT();

	// Use to clear console
	system("cls");

	// MAking the Table for the output
	cout << setw(70) << setfill('-') << " \n";
	cout << setfill(' ') << "|              Shortest Job First Serve - SJFS                     |\n";
	cout << setw(70) << setfill('-') << " \n";
	cout << "|" << setfill(' ') << "Process    |    AT    |    BT    |    CT    |   TAT    |     WT   |\n";
	cout << setw(70) << setfill('-') << " \n";
	cout << setfill(' ');


	// Outputting the Values of AT, BT, Ct, WT, TAT
	for (int i = 0; i < obj.NumberOfProcess; i++)
	{
		cout << "|";
		cout << setw(10) << "P" << obj.Proc[i] << "|";
		cout << setw(10) << obj.AT[i] << "|";
		cout << setw(10) << obj.BT[i] << "|";
		cout << setw(10) << obj.CT[i] << "|";
		cout << setw(10) << obj.TAT[i] << "|";
		cout << setw(10) << obj.WT[i] << "|\n";
	}


	// Outputting Average Waiting Time
	cout << setw(70) << setfill('-') << " \n";
	cout << "|" << setw(56) << setfill(' ') << " Average Waiting Time |" << setw(10) << obj.AvgWaitingTime() << "|\n";
	cout << setw(70) << setfill('-') << " \n";

	return 0;
}