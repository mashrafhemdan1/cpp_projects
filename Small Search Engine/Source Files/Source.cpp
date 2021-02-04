#include "Header.h"
int input(int upper, int lower) {
	cout << "\nType in your choice: ";
	int choice; cin >> choice;
	if (choice > upper || choice < lower) {
		cout << "Wrong Input\n";
		return input(upper, lower);
	}
	return choice;
}
int welcome() {
	cout << "Welcome!\n";
	cout << "What would you like to do?\n";
	cout << "1. New search\n";
	cout << "2. Exit\n";
	return input(2, 1);
}
vector<string> search(ifstream& keyword_file) {
	keyword_file.clear();
	keyword_file.seekg(0);
	cout << "Enter String Query:\n";
	string query;
	cin.ignore();
	getline(cin, query); //SEARCH FOR THIS PROBLEM
	vector <string> website; //results
	string temp;
	//check if AND exists
	int index = query.find("AND"); //TYPE I of queries
	if (index != string::npos) {//this means AND found
		string word1 = query.substr(0, index-1);
		string word2 = query.substr(index + 4, query.length() - 1);
		while (!keyword_file.eof()) {
			getline(keyword_file, temp); //take the website with its keywords
			istringstream line(temp);
			string line_website, keyword;
			getline(line, line_website, ',');
			bool word1_in = false, word2_in = false;
			while (getline(line, keyword, ',')) {
				if (word1 == keyword) {
					word1_in = true;
				}
				else if (word2 == keyword) {
					word2_in = true;
				}
				if (word1_in && word2_in) {
					website.push_back(line_website);
					break;//this means it's found
				}
			}
		}
	}
	else if (query.find("OR") != string::npos) {//TYPE II of queries
		index = query.find("OR");
		//this means OR found
		string word1 = query.substr(0, index - 1);
		string word2 = query.substr(index + 3, query.length() - 1);
		while (!keyword_file.eof()) {
			getline(keyword_file, temp); //take the website with its keywords
			istringstream line(temp);
			string line_website, keyword;
			getline(line, line_website, ',');
			while (getline(line, keyword, ',')) {
				if (word1 == keyword) {
					website.push_back(line_website);
					break;
				}
				else if (word2 == keyword) {
					website.push_back(line_website);
					break;
				}
			}
		}
	}
	else if (query[0] == '\"') {//this means a qoutation to get all the word
		int i = 1;
		string my_Skey = "";
		while (query[i] != '\"') my_Skey.push_back(query[i++]);
		//then search
		while (!keyword_file.eof()) {
			getline(keyword_file, temp); //take the website with its keywords
			istringstream line(temp);
			string line_website, keyword;
			getline(line, line_website, ',');
			while (getline(line, keyword, ',')) {
				if (my_Skey == keyword) {
					website.push_back(line_website);
					break;
				}
			}
		}
	}
	else {
		while (!keyword_file.eof()) {
			getline(keyword_file, temp); //take the website with its keywords
			istringstream line(temp);
			string line_website, keyword, query_key;
			getline(line, line_website, ',');
			while (getline(line, keyword, ',')) {
				istringstream keywords(query);
				while (keywords >> query_key) {
					if (query_key == keyword) {
 						website.push_back(line_website);
						break;
					}
				}
				if (query_key == keyword) break;
			}
		}
	}
	return website;
}
void print_websites(vector <string> website) {
	system("CLS");
	cout << "Search results:" << endl;
	for (int i = 0; i < website.size(); i++) {
		cout << i + 1 << ". " << website[website.size()-1-i] << endl;
	}
	cout << endl;
}
bool search_inner(ifstream& keyword_file, WebGraph& g, vector<string>website);
bool search_wrapper(ifstream& keyword_file, WebGraph& g) {
	vector<string> website = search(keyword_file);
	g.increment_impressions(website);
	g.update_CTR(website);
	g.update_score();
	g.sort_websites(website);
	return search_inner(keyword_file, g, website);
}
bool search_inner(ifstream& keyword_file, WebGraph& g, vector<string>website) {
	print_websites(website);
	cout << "Would you like to\n";
	cout << "1. Choose a webpage to open\n";
	cout << "2. New search\n";
	cout << "3. Exit\n";
	int choice = input(3, 1);
	if (choice == 3) return true;
	if (choice == 2) return search_wrapper(keyword_file, g);
	//choose a page to open
	int index;
	cout << "Enter page Index from above: "; cin >> index;
	string choosen_website = website[index - 1];
	g.increment_clickThrough(choosen_website);
	g.update_CTR(choosen_website);
	system("CLS");
	cout << "You're new visiting " << choosen_website << ".\n";
	cout << "Would you like to\n";
	cout << "1. Back to search Results\n";
	cout << "2. New Search\n";
	cout << "3. Exit\n";
	choice = input(3, 1);
	if (choice == 3) return true;
	if (choice == 2) return search_wrapper(keyword_file, g);
	return search_inner(keyword_file, g, website);
}
int main() {
	ifstream web_graph_file;
	web_graph_file.open("web_graph_file.csv");
	ifstream keyword_file;
	keyword_file.open("keyword_file.csv");
	ifstream impressions_file;
	impressions_file.open("impressions_file.csv");
	ifstream clickthrough_file;
	clickthrough_file.open("clickthrough_file.csv");
	WebGraph g;
	g.build_graph(web_graph_file);
	g.initialize_PR();
	g.intialize_impressions(impressions_file);
	g.intialize_clickthrough(clickthrough_file);
	impressions_file.close();
	g.update_PageRank(3);
	g.update_CTR();
	int choice = welcome();
	if (choice != 2) {
		if (search_wrapper(keyword_file, g)) {
			g.save_impressions("impressions_file.csv");
			g.save_clickTrough("clickthrough_file.csv");
			return 0;
		}
	}
	return 0;
}