# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <algorithm>

using namespace std;

struct edge{
	int start;
	int end;
	int weight;
};

vector<edge> u_graph;

/* comparator of the u_graph */
bool comp_function(edge ed1, edge ed2) { return (ed1.weight < ed2.weight); }

int store_file(string);			/* return the number of vertices */
void print_all(void);			/* print the vertices */
int clustering(int, int);
bool connected(int*, int, int);		/* helper function in union find */	
int find(int*, int);
bool connected(int*, int, int);
void union_1(int*, int, int, int&, int);	

int main(int argc, char** argv) {
	int num_of_ver = store_file("clustering1.txt");
	sort(u_graph.begin(), u_graph.end(), comp_function);
//	print_all();
	int res = clustering(num_of_ver, 4);
	cout << "spacing: " << res << endl;
	return 0;
}

int store_file(string filename) {
	ifstream infile;
	infile.open(filename, ios::in);
	int num_of_ver = 0;
	infile >> num_of_ver;
	int s, e, w;
	while (infile >> s >> e >> w) {
		edge ed1 = {s, e, w};
		u_graph.push_back(ed1);
	}
	infile.close();
	return num_of_ver;
}

void print_all(void) {
	for (int i = 0; i < u_graph.size(); ++i)
		cout << u_graph[i].start << " " << u_graph[i].end << " " << u_graph[i].weight << endl;
}

int clustering(int num_of_ver, int k) {
	int* id = new int[num_of_ver+1];
	/* constructor */
	int i;
	for (i = 1; i <= num_of_ver; ++i)
		id[i] = i;
	int count = num_of_ver;

	/* kruskal */
	for (i = 0; i < u_graph.size(); ++i) {
		if (!connected(id, u_graph[i].start, u_graph[i].end))
			union_1(id, u_graph[i].start, u_graph[i].end, count, num_of_ver);
		if (count == k)
			break;
	}

	while (i < u_graph.size()) {
		if (connected(id, u_graph[i].start, u_graph[i].end))
			++i;
		else
			return u_graph[i].weight;
	}
}

void union_1(int* id, int u, int v, int& count, int num_of_ver) {
	int u_id = find(id, u);
	int v_id = find(id, v);

	if (u_id == v_id)
		return;

	/* re-point u'component to v's id */
	for (int i = 1; i <= num_of_ver; ++i) {
		if (id[i] == u_id)
			id[i] = v_id;
	}
	--count;
}

int find(int* id, int u) {
	return id[u];
}

bool connected(int* id, int u, int v) {
	return find(id, u) == find(id, v);
}
