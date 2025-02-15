# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <vector>
# include <string>
# include <set>

using namespace std;

const int MAX = 1000000;

struct pairs {
	int start;
	int end;
	int dist;
};

void store_file(string);
void print_graph();
map<int, int> dijkstra(int);

map<int, vector<pairs> > graph;
set<int> visited;
set<int> unvisited;

int main(int argc, char** argv) {

	store_file("dijkstraData.txt");

//	print_graph();

	map<int, int> res = dijkstra(1);

	for (map<int, int>::iterator it = res.begin(); it != res.end(); ++it) {
		if (it->first == 7 or it->first == 37 or it->first == 59 or it->first == 82 or it->first == 99 or
			it->first == 115 or it->first == 133 or it->first == 165 or it->first == 188)
			cout << it->second << ",";
		if (it->first == 197)
			cout << it->second << endl;
	}

	return 0;
}

void store_file(string filename) {
	ifstream infile;
	infile.open(filename, ios::in);
	string line;
	while (getline(infile, line)) {
		int tmp;
		istringstream istr_l1(line);
		istr_l1 >> tmp;
		graph.insert(pair<int, vector<pairs> >(tmp, vector<pairs>()));
		unvisited.insert(tmp);
		string token_l1;
		while (istr_l1 >> token_l1) {
			istringstream istr_l2(token_l1);
			int end;
			int dist;
			char comma;
			istr_l2 >> end >> comma >> dist;
			pairs tmp_1 = {tmp, end, dist};
			graph[tmp].push_back(tmp_1);
		}
	}
	infile.close();
}

void print_graph() {
	for (map<int, vector<pairs> >::iterator it = graph.begin(); it != graph.end(); ++it) {
		cout << it->first << ": ";
		for (int i = 0; i < it->second.size(); ++i) {
			cout << "(" << it->second[i].start << ", " << it->second[i].end << ", "
			<< it->second[i].dist << ") ";
		}
		cout << endl;
	}
}

map<int, int> dijkstra(int s) {
	map<int, int> res;
	res.insert(pair<int, int>(s, 0));
	visited.insert(s);
	unvisited.erase(s);
	while (unvisited.size() > 0) {
		int min_len = 1000000;
		int v_star = 0;
		int w_star = 0;
		for (set<int>::iterator it = visited.begin(); it != visited.end(); ++it) {
			for(int i = 0; i < graph[*it].size(); ++i) {
				if (unvisited.find(graph[*it][i].end) != unvisited.end()) {
					int len = res[*it] + graph[*it][i].dist;
					if (min_len > len) {
						min_len = len;
						v_star = *it;
						w_star = graph[*it][i].end;
					}
				}
			}
		}
		unvisited.erase(w_star);
		visited.insert(w_star);
		res.insert(pair<int, int>(w_star, min_len));
	}
	return res;
}
