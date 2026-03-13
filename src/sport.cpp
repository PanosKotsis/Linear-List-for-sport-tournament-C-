#include <iostream> 
#include <string> 
#include <stdexcept> 
#include <fstream> 
#include <sstream> 
using namespace std; 

class Participant; 

class ParticipantsList 
{ 
	public: 
		ParticipantsList() 
		{
			 first = nullptr; 
		}

		void Clear();
	 	void Insert(int k, const string name, const int id, const int ranking, const string country, const int timestamp); 
		void InsertSortedByID(const string name, const int id, const int ranking, const string country, const int timestamp); 
		void SortedByRanking(); 
		bool SearchedById(int id) const; 
		void DeletedById(int id); 
		bool SearchedByName(string name, string surname);
		void PrintList() const;
		void PrintByTimestamp() const;
	private: 
		Participant *first; 
}; 
	
class Participant 
{
	public: 
		Participant *link; 
		string name; 
		string country; 
		int id; 
		int ranking; 
		int timestamp; 
			
		Participant(string n, int i, int r, string c, int t) 
		{
			link = nullptr; 
			name = n; 
			id = i; 
			ranking = r; 
			country = c; 
			timestamp = t; 
		} 
}; 

void ParticipantsList::Clear() 
{
	Participant* next; 
		 
	while(first) 
	{
		next = first->link; 
		delete first; 
		first = next; 
	} 
} 
	
void ParticipantsList::Insert(int k, const string name, const int id, const int ranking, const string country, const int timestamp) 
{
	if (k<0) 
	{
		throw std::out_of_range("Index out of bounds"); 
	} 
		
	Participant *p = first; 
	
	for (int index=1; index<k && p; index++) 
	{
		 p = p->link; 
	} 
		
	if (k>0 && !p) 
	{
		throw std::out_of_range("Index out of bounds"); 
	} 
		
	Participant *y = new Participant(name, id, ranking, country, timestamp); 
		
	if (k) 
	{ 
		y->link = p->link; 
		p->link = y; 
	} 
	else 
	{ 
		y->link = first; 
		first = y; 
	} 
}
	
void ParticipantsList::InsertSortedByID(const string name, const int id, const int ranking, const string country, const int timestamp) 
{
	Participant* newNode = new Participant(name, id, ranking, country, timestamp); 
	 
	if (first == nullptr || first->id > id) 
	{
		newNode->link = first; 
		first = newNode; return; 
	} 
		
	Participant* current = first; 
	
	while(current->link != nullptr && current->link->id < id) 
	{ 
		current = current->link; 
	} 
		
	newNode->link = current->link; 
	current->link = newNode; 
}
	
void ParticipantsList::SortedByRanking() 
{ 
	bool swapped;

	do 
	{ 
		swapped = false; 
		Participant* current = first; 
		
		while(current->link != nullptr) 
		{
			if(current->ranking < current->link->ranking) 
			{
				swap(current->name, current->link->name); 
				swap(current->id, current->link->id); 
				swap(current->ranking, current->link->ranking); 
				swap(current->country, current->link->country); 
				swap(current->timestamp, current->link->timestamp); 

				swapped = true; 
			} 
				
			current = current->link; 
		} 
	} while(swapped); 
}
	
bool ParticipantsList::SearchedById(int id) const 
{
	Participant* current = first; 
		 
	while(current != nullptr) 
	{ 
		if (current->id == id) 
		{
			cout << "Player found:\n"; 
			cout << "Player: " << current->name << endl;
			cout << "ID: " << current->id << endl; 
			cout << "Ranking: " << current->ranking << endl; 
			cout << "Country: " << current->country << endl; 
			cout << "Timestamp: " << current->timestamp << endl; 
			return true; 
		} 
			
		current = current->link; 
	} 
		
	cout << "Player with ID " << id << " not found\n";
	return false; 
}
	
void ParticipantsList::DeletedById(int id) 
{
	Participant* current = first; 
	Participant* previous = nullptr; 
		
	if (first == nullptr) 
	{
		cout << "List is empty\n"; return; 
	} 
		
	if (current->id == id) 
	{
		first = current->link; 
		delete current; return; 
	} 
		
	while(current != nullptr && current->id != id) 
	{
		previous = current; 
		current = current->link; 
	} 
		
	if (current == nullptr) 
	{
		cout << "Player with ID " << id << " not found\n"; 
		return; 
	} 
		
	previous->link = current->link; 
	delete current; 
} 

bool ParticipantsList::SearchedByName(string name, string surname)
{
	string fullName = name + " " + surname;

	Participant* current = first; 
		 
	while(current != nullptr) 
	{ 
		if (current->name == fullName) 
		{
			cout << "Player found:\n"; 
			cout << "Player: " << current->name << endl;
			cout << "ID: " << current->id << endl; 
			cout << "Ranking: " << current->ranking << endl; 
			cout << "Country: " << current->country << endl; 
			cout << "Timestamp: " << current->timestamp << endl; 

			return true; 
		} 
			
		current = current->link; 
	} 
		
	cout << "Player with name " << fullName << " not found\n";

	return false; 
}

void ParticipantsList::PrintList() const
{
	if (first == nullptr)
	{
		cout << "List is empty\n";
		return;
	}

	Participant* current = first; 
		 
	while(current != nullptr) 
	{ 
		if (current != nullptr) 
		{ 
			cout << "Player: " << current->name << endl;
			cout << "ID: " << current->id << endl; 
			cout << "Ranking: " << current->ranking << endl; 
			cout << "Country: " << current->country << endl; 
			cout << "Timestamp: " << current->timestamp << endl;
			cout << endl; 
			
			current = current->link; 
		} 
	} 
}

void ParticipantsList::PrintByTimestamp() const
{
	if (first == nullptr)
	{
		cout << "List is empty\n";
		return;
	}

	int lastPrinted = -1;

	while(true)
	{
		Participant* current = first;
		Participant* minNode = nullptr;

		while(current != nullptr)
		{
			if (current->timestamp > lastPrinted)
			{
				if (minNode == nullptr || current->timestamp < minNode->timestamp)
				{
					minNode = current;
				}
			}

			current = current -> link;
		}

		if(minNode == nullptr)
		{
			break;
		}

		cout << "Player: " << minNode->name << endl;
		cout << "ID: " << minNode->id << endl; 
		cout << "Ranking: " << minNode->ranking << endl; 
		cout << "Country: " << minNode->country << endl; 
		cout << "Timestamp: " << minNode->timestamp << endl;
		cout << endl; 

		lastPrinted = minNode->timestamp;
	}
}
	
void printMenu() 
{ 
	cout << "\n1. Read players from file, in the order they appear in the file" << endl; 
	cout << "2. Read players from file, sorted by ID" << endl; 
	cout << "3. Sort list by ranking of players" << endl; 
	cout << "4. Delete player by ID" << endl; 
	cout << "5. Delete the complete list of players" << endl; 
	cout << "6. Search for player by name" << endl; 
	cout << "7. Print list of players by current order" << endl; 
	cout << "8. Print list of players by sign-up timestamp" << endl; 
	cout << "9. Exit" << endl; cout << "\nChoose something: "; 
} 
	
int main() 
{
	ParticipantsList tournament; 
	int response = 0; 
	bool created = false; 
		 
	while (response != 9) 
	{ 
		printMenu(); 
		cin >> response; 
			
		while (response < 1 || response > 9) 
		{ 
			cout << "Choose again something (1-9): "; 
			cin >> response; 
		} 
			
		switch(response) 
		{ 
			case 1: 
			{
				if (!created) 
				{
					cout << "\nEnter name of file containing player info: "; 
					string file; 
					
					cin >> file; 
					while (file != "a.txt") 
					{ 
						cout << "Enter again name of file containing player info: "; 
						cin >> file; 
					} 
					
					created = true; 
					ifstream inFile(file); 
					if (!inFile) 
					{ 
						cout << "File could not be opened!"; 
						break; 
					} 
					
					string line; 
					int i=0; 
					while(getline(inFile, line)) 
					{
						stringstream ss(line); 
						string name, id, ranking, country, timestamp; 
						getline(ss, name, ','); 
						getline(ss, id, ','); 
						getline(ss, ranking, ','); 
						getline(ss, country, ','); 
						getline(ss, timestamp, ','); 
						tournament.Insert(i, name, stoi(id), stoi(ranking), country, stoi(timestamp)); 
						i++; 
					} 
					
					inFile.close(); 
					cout << "You have read the list of players\n"; 
				} 
				else 
				{ 
					cout << "You have already created the list\n"; 
				}
					
				break; 
			} 
			case 2: 
				if (!created) 
				{ 
					cout << "\nEnter name of file containing player info: "; 
					
					string file; 
					cin >> file; 
					while (file != "a.txt") 
					{
						cout << "Enter again name of file containing player info: "; 
						cin >> file; 
					} 
					
					created = true; 
					ifstream inFile(file); 
					
					if (!inFile) 
					{
						cout << "File could not be opened!"; 
						break; 
					} 
					
					string line; 
					int i=0; 
					while(getline(inFile, line)) 
					{
						stringstream ss(line); 
						string name, id, ranking, country, timestamp; 
						
						getline(ss, name, ','); 
						getline(ss, id, ','); 
						getline(ss, ranking, ','); 
						getline(ss, country, ','); 
						getline(ss, timestamp, ','); 

						tournament.InsertSortedByID(name, stoi(id), stoi(ranking), country, stoi(timestamp)); 
						i++; 
					} 
						
					inFile.close(); 
				} 
				else 
				{
					cout << "You have already created the list\n"; 
				} 
				
				break; 
			case 3: 
				tournament.SortedByRanking(); 
				cout << "List is sorted by ranking\n";

				break; 
			case 4: 
				int id; 
				
				cout << "Enter the ID player number: "; 
				cin >> id; 
				
				if (tournament.SearchedById(id)) 
				{ 
					tournament.DeletedById(id); 
					
					cout << "Player with ID " << id << " deleted\n"; 
				} 
					 
				break; 
			case 5: 
				tournament.Clear(); 
				created = false; 
				
				cout << "List is deleted\n";
				
				break; 
			case 6: 
			{
				string name;
				string surname;

				cout << "Enter the name player: ";
				cin >> name;

				cout << "\nEnter the surname player: ";
				cin >> surname;

				tournament.SearchedByName(name, surname);

				break; 
			}
			case 7:
				tournament.PrintList();

				break; 
			case 8: 
				tournament.PrintByTimestamp();

				break; 
			} 
		} 
			
	return 0; 
}