#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

template <class T>
class Graph {
private:
	vector<T> vetrexList;
	vector<vector<int>> adjMatrix;
	int size;
	queue<T> VertsQueue;
	vector<int> labelList;
public:
	inline Graph<T>(const int& ksize) {//����������� �����, � �������� ��������� ������ �����(�� ���� ���-�� ������)
		this->size = ksize;
		labelList.resize(ksize, 1000000);
		this->adjMatrix = vector<vector<T>>(ksize, vector<T>(ksize));
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				this->adjMatrix[i][j] = 0;
			};
		};
	}
	inline bool isfull() { //�������� ����� �� ��, ��� �� ��������
		return this->vetrexList.size() == this->size;
	}
	inline bool isEmpty() {//�������� ����� �� ��, ��� �� ����
		return this->vetrexList.size() == 0;
	}
	inline void insertVetrex(const T& vert) {//�������, ������� ��������� �������
		if (this->isfull()) {
			cout << "���������� �������� �������." << endl;
			return;
		}
		this->vetrexList.push_back(vert);
	}
	inline int GetVertPos(const T& g) {//��������� ������� ������
		for (int i = 0; i < vetrexList.size(); i++) {
			if (this->vetrexList[i] == g) {
				return i;
			}
		}
		return -1;
	}
	inline int GetAmountVerts() {//��������� ���������� ������
		return this->vetrexList.size();
	}
	inline int GetWeight(const T& g1, const T& g2) {//��������� ���� ����� ���������
		if (this->isEmpty()) {
			return 0;
		}
		int g1_p = this->GetVertPos(g1);
		int g2_p = this->GetVertPos(g2);
		if (g1_p == -1 || g2_p == -1) {
			cout << "������ �� ��������� ����� � ����� �� ����������!";
			return 0;
		}
		return this->adjMatrix[g1_p][g2_p];
	}
	vector<T> GetNbrs(const T& vetrex) {//��������� ������� �������
		vector<T> nbrsList;
		int pos = this->GetVertPos(vetrex);
		if (pos != -1) {
			for (int i = 0; i < this->vetrexList.size(); i++) {
				if (this->adjMatrix[pos][i] != 0) {
					nbrsList.push_back(this->vetrexList[i]);
				}
			}
		}
		return nbrsList;
	}
	void InsertEdge(const T& vetrex1, const T& vetrex2, int weight = 1) {//������� ����� ��� ������������������ �����
		if (GetVertPos(vetrex1) != (-1) && this->GetVertPos(vetrex2) != (-1)) {
			int vertPos1 = GetVertPos(vetrex1);
			int vertPos2 = GetVertPos(vetrex2);
			if (this->adjMatrix[vertPos1][vertPos2] != 0 && this->adjMatrix[vertPos2][vertPos1] != 0) {
				cout << "����� ����� ��������� ��� ����" << endl;
				return;
			}
			else {
				this->adjMatrix[vertPos1][vertPos2] = weight;
				this->adjMatrix[vertPos2][vertPos1] = weight;
			}
		}
		else {
			cout << "�����-���� ������� ��� � �����" << endl;
			return;
		}
	}
	void PrintMatrix() {//������ ������� ��������� �����
		if (!this->isEmpty()) {
			cout << "������� ���������: " << endl;
			cout << "- ";
			for (int i = 0; i < vetrexList.size(); i++) {
				cout << " " << vetrexList[i] << " ";
			}
			cout << endl;
			for (int i = 0; i < this->vetrexList.size(); i++) {
				cout << this->vetrexList[i] << " ";
				for (int j = 0; j < this->vetrexList.size(); j++) {
					cout << " " << this->adjMatrix[i][j] << " ";
				}
				cout << endl;
			}
		}
		else {
			cout << "���� ����" << endl;
		}
	}
	int GetAmoutEdges() {//��������� ���������� ����� ��� ������������������ �����
		int amount = 0;
		if (!this->isEmpty()) {
			for (int i = 0; i < this->vetrexList.size(); i++) {
				for (int j = 0; j < this->vetrexList.size(); j++) {
					if (this->adjMatrix[i][j] != 0) {
						amount++;
					}
				}
			}
		}
		return amount / 2;
	}
	T& front() {//��������� ������� �������� � �������
		return VertsQueue.front();
	}
	void removeVertex(const T& vertex) {
		int pos = GetVertPos(vertex);
		if (pos == -1) {
			cout << "������� " << vertex << " ��� � �����." << endl;
			return;
		}

		for (int i = 0; i < size; i++) {
			if (adjMatrix[pos][i] != 0) removeEdge(vertex, vetrexList[i]);
			if (adjMatrix[i][pos] != 0) removeEdge(vetrexList[i], vertex);
		}

		vetrexList.erase(vetrexList.begin() + pos);

		for (int i = 0; i < size; i++) {
			adjMatrix[i].erase(adjMatrix[i].begin() + pos);
		}
		adjMatrix.erase(adjMatrix.begin() + pos);
		size--;

		cout << "������� " << vertex << " �������." << endl;
	}

	void removeEdge(const T& vertex1, const T& vertex2) {//�������, ������� ������� �����
		int pos1 = GetVertPos(vertex1);
		int pos2 = GetVertPos(vertex2);

		if (pos1 == -1 || pos2 == -1) {
			cout << "����� �� ������ ��� � �����." << endl;
			return;
		}

		if (adjMatrix[pos1][pos2] == 0) {
			cout << "����� ����� ��������� " << vertex1 << " � " << vertex2 << " ���." << endl;
			return;
		}

		adjMatrix[pos1][pos2] = 0;
		adjMatrix[pos2][pos1] = 0;

		cout << "����� ����� ��������� " << vertex1 << " � " << vertex2 << " �������." << endl;
	}
	void editEdgeWeight(const T& vertex1, const T& vertex2, int newWeight) {//�������, ������� ������ ��� ����� �������
		int pos1 = GetVertPos(vertex1);
		int pos2 = GetVertPos(vertex2);

		if (pos1 == -1 || pos2 == -1) {
			cout << "����� �� ������ ��� � �����." << endl;
			return;
		}

		if (adjMatrix[pos1][pos2] == 0) {
			cout << "����� ����� ��������� " << vertex1 << " � " << vertex2 << " ���." << endl;
			return;
		}

		adjMatrix[pos1][pos2] = newWeight;
		adjMatrix[pos2][pos1] = newWeight;

		cout << "��� ����� ����� ��������� " << vertex1 << " � " << vertex2 << " ������� �� " << newWeight << "." << endl;
	}
	void DFS(T& startVertex, bool* visitedVerts) {//����� ����� � �������

		cout << "������� " << startVertex << " �������� " << endl;
		visitedVerts[this->GetVertPos(startVertex)] = true;
		vector<T> neighbors = this->GetNbrs(startVertex);
		for (int i = 0; i < neighbors.size(); i++) {
			if (!visitedVerts[this->GetVertPos(neighbors[i])]) {
				this->DFS(neighbors[i], visitedVerts);
			}
		}
	}
	void BFS(T& startVertex, bool* visitedVerts) {//����� ����� � ������
		if (visitedVerts[this->GetVertPos(startVertex)] == false) {
			this->VertsQueue.push(startVertex);
			cout << "������� " << startVertex << " ����������" << endl;
			visitedVerts[this->GetVertPos(startVertex)] = true;
		}

		vector<T> neighbors = this->GetNbrs(startVertex);

		for (int i = 0; i < neighbors.size(); ++i) {
			if (!visitedVerts[this->GetVertPos(neighbors[i])]) {
				this->VertsQueue.push(neighbors[i]);
				visitedVerts[this->GetVertPos(neighbors[i])] = true;
				cout << "������� " << neighbors[i] << " ����������" << endl;
			}
		}

		if (this->VertsQueue.empty())
			return;

		T nextVertex = VertsQueue.front();
		VertsQueue.pop();
		BFS(nextVertex, visitedVerts);
	}

	void FillLabels(T& startVertex) {
		for (int i = 0; i < vetrexList.size(); i++) {
			labelList[i] = 1000000; // ������������� �������� ����������
		}
		int pos = GetVertPos(startVertex);
		labelList[pos] = 0;
	}

	bool AllVisiited(vector<bool>& visitedVerts) {
		for (int i = 0; i < vetrexList.size(); i++) {
			if (!visitedVerts[i]) { // �������� �� ������������ �������
				return false;
			}
		}
		return true;
	}

	void Dijkstra(const T& startVertex) {//�������� ������ ��������
		int n = this->GetAmountVerts();
		vector<int> dist(n, INT_MAX); // ������������� ���������� �� ���� ������ ��� �������������
		vector<bool> visited(n, false); // ������������� ���� ������ ��� ������������
		int startIdx = this->GetVertPos(startVertex); // ��������� ������� ��������� �������
		dist[startIdx] = 0; // ���������� �� ������ ���� ����� 0

		for (int i = 0; i < n - 1; ++i) {
			// ������� ������� � ����������� ����������� �� ��������� �������, �� ��� �� ���������� ������
			int minDist = INT_MAX, minIdx{};
			for (int j = 0; j < n; ++j) {
				if (!visited[j] && dist[j] <= minDist) {
					minDist = dist[j];
					minIdx = j;
				}
			}

			// �������� ��������� ������� ��� ����������
			visited[minIdx] = true;

			// ��������� �������� ���������� ��� ���� ������� ��������� �������
			for (int j = 0; j < n; ++j) {
				if (!visited[j] && this->adjMatrix[minIdx][j] && dist[minIdx] != INT_MAX
					&& dist[minIdx] + this->adjMatrix[minIdx][j] < dist[j]) {
					dist[j] = dist[minIdx] + this->adjMatrix[minIdx][j];
				}
			}
		}

		// ������� ���������� ���������� �� ��������� ������� �� ���� ���������
		cout << "������� \t���������� �� ��������� �������\n";
		for (int i = 0; i < n; ++i) {
			cout << this->vetrexList[i] << "\t\t" << dist[i] << "\n";
		}
	}

};
int main()
{
	system("chcp 1251>NULL");
	Graph<int> graph(6);
	int Verts, Edges, vertex, sourceVertex, targetVetrex, Weight, vertex1;
	bool* visitedVerts = new bool[6];
	bool* visitedVerts1 = new bool[6];
	fill(visitedVerts, visitedVerts + 20, false);
	cout << "������� ���������� ������: " << endl;
	cin >> Verts;
	cout << "������� ���������� ����� �����: " << endl;
	cin >> Edges;
	cout << endl;
	for (int i = 0; i < Verts; i++) {
		cout << "�������: ";
		cin >> vertex;
		graph.insertVetrex(vertex);
		cout << endl;
	}
	for (int i = 0; i < Edges; i++) {
		cout << "�������� �������: ";
		cin >> sourceVertex;
		cout << endl;
		cout << "�������� �������: ";
		cin >> targetVetrex;
		cout << endl;
		cout << "��� �����: ";
		cin >> Weight;
		cout << endl;
		int* targetVerPtr = &targetVetrex;
		graph.InsertEdge(sourceVertex, targetVetrex, Weight);
	}
	cout << endl;
	graph.PrintMatrix();
	int N;
	cout << "������� �������, � ������� ������ �����: ";
	cin >> vertex;
	cout << endl;
	cout << "����� � �������: " << endl;
	graph.DFS(vertex, visitedVerts);
	cout << "������� �������, � ������� ������ �����: ";
	cin >> vertex;
	cout << endl;
	cout << "����� � ������: " << endl;
	graph.BFS(vertex, visitedVerts);
	cout << "������� �������, � ������� ������ �����: ";
	cin >> vertex;
	cout << endl;
	cout << "����� ��������: " << endl;
	graph.Dijkstra(vertex);
	delete[] visitedVerts;
	cout << "������� �������, ������� ������ �������: ";
	cin >> N;
	graph.removeVertex(N);
	graph.PrintMatrix();
	cout << "������� ������ �����: " << graph.GetAmountVerts();
	cout << endl;
	int g, k;
	cout << "������� ���-�� ������, ������� �� ������ ��������: ";
	cin >> g;
	cout << "������� ���-�� ����, ������� ������ ��������: ";
	cin >> k;
	for (int i = 0; i < g; i++) {
		cout << "�������: ";
		cin >> vertex;
		graph.insertVetrex(vertex);
		cout << endl;
	}
	for (int i = 0; i < k; i++) {
		cout << "�������� �������: ";
		cin >> sourceVertex;
		cout << endl;
		cout << "�������� �������: ";
		cin >> targetVetrex;
		cout << endl;
		cout << "��� �����: ";
		cin >> Weight;
		cout << endl;
		int* targetVerPtr = &targetVetrex;
		graph.InsertEdge(sourceVertex, targetVetrex, Weight);
	}
	graph.PrintMatrix();
	cout << "������� ������ ������, ����� �������� ����� ������� �����: ";
	cin >> vertex;
	cin >> vertex1;
	graph.removeEdge(vertex, vertex1);
	cout << "���� ����� �������� �����: ";
	cout << endl;
	graph.PrintMatrix();
	cout << endl << endl;
	cout << "������� ������ ������, ����� �������� ����� �������� ��� �����: ";
	cin >> vertex;
	cin >> vertex1;
	cout << endl << endl;
	cout << "������� ������ ���: ";
	cin >> Weight;
	graph.editEdgeWeight(vertex, vertex1, Weight);
	cout << "���� ����� ��������� ���� �����: ";
	cout << endl;
	graph.PrintMatrix();
	return 0;
}