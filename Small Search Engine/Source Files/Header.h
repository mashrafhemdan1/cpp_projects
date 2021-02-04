#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

class WebGraph {//customized nodes
	map<string, vector<string>> adjList;//here the adjacency list is reversed each row contains the nodes pointing to the node corresponding to it
	map<string, float> PR;
	map<string, int> impressions;
	map<string, int> no_of_outEdges;
	map<string, int> click_through;
	map<string, float> CTR;
	map<string, float> score;
public:
	WebGraph() {};
	void addEdge(string websiteFrom, string websiteTo) {
		if (adjList.find(websiteTo) != adjList.end()) {//found
			adjList[websiteTo].push_back(websiteFrom);
		}
		else {//not found
			vector<string> list;
			list.push_back(websiteFrom);
			adjList.insert({websiteTo, list});
			impressions.insert({ websiteTo, 0 });
			click_through.insert({ websiteTo, 0 });
			CTR.insert({ websiteTo, 0 });
			score.insert({ websiteTo, 0 });
		}
		if (adjList.find(websiteFrom) == adjList.end()) {//found
			vector<string> list;
			adjList.insert({ websiteFrom, list });
			impressions.insert({ websiteFrom, 0 });
			click_through.insert({ websiteFrom, 0 });
			CTR.insert({ websiteFrom, 0 });
			score.insert({ websiteFrom, 0 });
		}
		//Update the number of websited referenced in this website (websiteFrom)
		if (no_of_outEdges.find(websiteFrom) != no_of_outEdges.end()) {//found
			no_of_outEdges[websiteFrom]++;
		}
		else {
			no_of_outEdges.insert({ websiteFrom,1 });
		}
		if (no_of_outEdges.find(websiteTo) == no_of_outEdges.end()) {//found
			no_of_outEdges.insert({ websiteTo,0 });
		}
	}
	void initialize_PR() {
		map<string, float>::iterator i;
		for (i = score.begin(); i != score.end(); i++) {
			string key = i->first;
			PR[key] = 1.0 / score.size();
		}
	}
	void update_PageRank(int iterations) {
		for (int i = 0; i < iterations; i++) {
			map<string, float> new_PR;
			map<string, vector<string>>::iterator j;
			for (j = adjList.begin(); j != adjList.end(); j++) {
				float value = 0;
				vector<string> pointWebpages = j->second;
				vector<string>::iterator k;
				for (k = pointWebpages.begin(); k != pointWebpages.end(); k++) {
					value += PR[*k] / no_of_outEdges[*k];
				}
				new_PR[j->first] = value;
			}
			PR = new_PR;
		}
	}
	void update_CTR() {
		map<string, float>::iterator i;
		for (i = CTR.begin(); i != CTR.end(); i++) {
			string key = i->first;
			i->second = (impressions[key] == 0)? 0:click_through[key] / impressions[key];
		}
	}
	void build_graph(ifstream& web_graph_file) {
		string websiteFrom, websiteTo;
		string line;
		while (!web_graph_file.eof()) {
			getline(web_graph_file, line);
			istringstream sline(line);
			getline(sline, websiteFrom, ',');
			getline(sline, websiteTo);
			addEdge(websiteFrom, websiteTo);
		}
	}
	void update_score() {
		map<string, float>::iterator i;
		for (i = score.begin(); i != score.end(); i++) {
			string key = i->first;
			float temp = (0.1 * impressions[key]) / (1 + 0.1 * impressions[key]);
			i->second = 0.4 * PR[key] + ((1 - temp) * PR[key] + temp * CTR[key]) * 0.6;
		}
	}
	void intialize_impressions(ifstream& impressions_file) {
		while (!impressions_file.eof()) {
			string sline;
			getline(impressions_file, sline);
			if (sline == "") break;
			istringstream line(sline);
			string website, impressions_str;
			getline(line, website, ',');
			getline(line, impressions_str);
			int impressions_no = stoi(impressions_str);
			impressions[website] = impressions_no;
		}
	}
	bool compare_website(string website1, string website2) {
		return score[website1] < score[website2];
	}
	void merge_websites(vector<string>& arr, int l, int m, int r)
	{
		int n1 = m - l + 1;
		int n2 = r - m;
		vector<string> L;
		vector<string> R;
		for (int i = 0; i < n1; i++)
			L.push_back(arr[l + i]);
		for (int j = 0; j < n2; j++)
			R.push_back(arr[m + 1 + j]);
		int i = 0;
		int j = 0;
		int k = l;
		while (i < n1 && j < n2)
		{
			if (compare_website(L[i] , R[j]))
			{
				arr[k] = L[i];
				i++;
			}
			else
			{
				arr[k] = R[j];
				j++;
			}
			k++;
		}
		while (i < n1)
		{
			arr[k] = L[i];
			i++;
			k++;
		}
		while (j < n2)
		{
			arr[k] = R[j];
			j++;
			k++;
		}
	}

	void mergeSort_websites(vector<string>& arr, int l, int r)
	{
		if (l < r)
		{
			int m = l + (r - l) / 2;
			mergeSort_websites(arr, l, m);
			mergeSort_websites(arr, m + 1, r);
			merge_websites(arr, l, m, r);
		}
	}
	void sort_websites(vector<string>& website) {
		int r = website.size() - 1;
		mergeSort_websites(website, 0, r);
	}
	void increment_impressions(vector<string> website) {
		vector<string>::iterator i;
		for (i = website.begin(); i != website.end(); i++) {
			impressions[*i] = impressions[*i] + 1;
		}
	}
	void increment_clickThrough(string website) {
		click_through[website]++;
	}
	void save_clickTrough(string file) {
		ofstream output_file;
		output_file.open(file, ios::trunc);
		map<string, int>::iterator i;
		for (i = click_through.begin(); i != click_through.end(); i++) {
			output_file << i->first << ',' << i->second;
			if (i != click_through.end()) output_file << endl;
		}
		output_file.close();
	}
	void intialize_clickthrough(ifstream& clickthrough_file) {
		while (!clickthrough_file.eof()) {
			string sline;
			getline(clickthrough_file, sline);
			if (sline == "") break;
			istringstream line(sline);
			string website, clickthrough_str;
			getline(line, website, ',');
			getline(line, clickthrough_str);
			int clickthrough_no = stoi(clickthrough_str);
			click_through[website] = clickthrough_no;
		}
	}
	void update_CTR(string website) {
		CTR[website] = float(click_through[website]) / float(impressions[website]);
	}
	void update_CTR(vector <string> websites) {
		for (int i = 0; i < websites.size(); i++) {
			CTR[websites[i]] = click_through[websites[i]] / impressions[websites[i]];
		}
	}
	void save_impressions(string file) {
		ofstream output_file;
		output_file.open(file, ios::trunc);
		map<string, int>::iterator i;
		for (i = impressions.begin(); i != impressions.end(); i++) {
			output_file << i->first << ',' << i->second;
			if (i != impressions.end()) output_file << endl;
		}
		output_file.close();
	}
};