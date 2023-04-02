#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stack>
#include <vector>

using namespace std;

int** incidence;
int** adjacency;
int** adjacency2;
int vertices;
int edges;

void initGraph(string fname);
void makeIncidenceMatrix(string line, int lineNumber);
void makeAdjacencyMatrix(string line);
void DFS(int index);

int main()
{
	char fname[] = "graph_01_1.txt";
	initGraph(fname);

    int index;
    cout << "Enter index: "; cin >> index;
    DFS(index);

}

void DFS(int index) {
    stack<int> stack;
    vector<bool> visited(vertices, false);

    int vertex = index;
    int count = 1;

    visited[index - 1] = true;
    stack.push(index);

    cout << "| vertex | DFS number | stack \n";
    cout << "| " << "v" << index << "    | " << count++ << "          | " << index << endl;

    while (!stack.empty()) {
        vertex = stack.top() - 1;
        int vis = -1;

        for (int i = 0; i < vertices; i++) {
            if (adjacency2[vertex][i] == 1 && !visited[i]) {
                vis = i;
                break;
            }
        }

        if (vis != -1) {
            visited[vis] = true;
            stack.push(vis + 1);
            cout << "| " << "v" << vis + 1 << "    | " << count++ << "          | ";
            vector<int> tempVec;
            while (!stack.empty()) {
                tempVec.push_back(stack.top());
                stack.pop();
            }
            for (int i = tempVec.size() - 1; i >= 0; i--) {
                cout << tempVec[i] << " ";
                stack.push(tempVec[i]);
            }
            cout << endl;
        }
        else {
            stack.pop();
        }
    }
}

void initGraph(string fname) {
    ifstream input(fname);
    if (!input.is_open()) {
        cout << "Error opening file " << fname << endl;
        return;
    }

    string line;
    getline(input, line);
    if (!line.empty()) {
        istringstream iss(line);
        iss >> vertices >> edges;
        incidence = new int* [vertices];
        adjacency = new int* [vertices];
        adjacency2 = new int* [vertices];
        for (int i = 0; i < vertices; i++) {
            incidence[i] = new int[edges];
            adjacency[i] = new int[vertices];
            adjacency2[i] = new int[vertices];
        }
    }
    else {
        cout << "Empty input file" << endl;
        return;
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adjacency[i][j] = 0;
            adjacency2[i][j] = 0;
        }
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < edges; j++) {
            incidence[i][j] = 0;
        }
    }

    int lineNumber = 0;
    while (getline(input, line)) {
        makeIncidenceMatrix(line, lineNumber);
        makeAdjacencyMatrix(line);
        lineNumber++;
    }

    input.close();
}

void makeIncidenceMatrix(string line, int lineNumber) {

    int from = stoi(line.substr(0, line.find(" ")));
    int to = stoi(line.substr(line.find(" ") + 1));

    if (from == to) {
        incidence[from - 1][lineNumber] = 2;
    }
    else {
        incidence[from - 1][lineNumber] = -1;
        incidence[to - 1][lineNumber] = 1;
    }
}

void makeAdjacencyMatrix(string line) {

    int from = stoi(line.substr(0, line.find(" ")));
    int to = stoi(line.substr(line.find(" ") + 1));
    adjacency[from - 1][to - 1]++;
    adjacency2[from - 1][to - 1] = 1;
    adjacency2[to - 1][from - 1] = 1;
}