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
	inline Graph<T>(const int& ksize) {//Конструктор графа, в параметр передаётся размер графа(то есть кол-во вершин)
		this->size = ksize;
		labelList.resize(ksize, 1000000);
		this->adjMatrix = vector<vector<T>>(ksize, vector<T>(ksize));
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				this->adjMatrix[i][j] = 0;
			};
		};
	}
	inline bool isfull() { //Проверка графа на то, что он заполнен
		return this->vetrexList.size() == this->size;
	}
	inline bool isEmpty() {//Проверка графа на то, что он пуст
		return this->vetrexList.size() == 0;
	}
	inline void insertVetrex(const T& vert) {//Функция, которая добавляет вершину
		if (this->isfull()) {
			cout << "Невозможно добавить вершину." << endl;
			return;
		}
		this->vetrexList.push_back(vert);
	}
	inline int GetVertPos(const T& g) {//Получение индекса вершин
		for (int i = 0; i < vetrexList.size(); i++) {
			if (this->vetrexList[i] == g) {
				return i;
			}
		}
		return -1;
	}
	inline int GetAmountVerts() {//Получение количества вершин
		return this->vetrexList.size();
	}
	inline int GetWeight(const T& g1, const T& g2) {//Получение веса между вершинами
		if (this->isEmpty()) {
			return 0;
		}
		int g1_p = this->GetVertPos(g1);
		int g2_p = this->GetVertPos(g2);
		if (g1_p == -1 || g2_p == -1) {
			cout << "Одного из выбранных узлов в графе не существует!";
			return 0;
		}
		return this->adjMatrix[g1_p][g2_p];
	}
	vector<T> GetNbrs(const T& vetrex) {//Получение вектора соседей
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
	void InsertEdge(const T& vetrex1, const T& vetrex2, int weight = 1) {//Вставка ребра для неориентированного графа
		if (GetVertPos(vetrex1) != (-1) && this->GetVertPos(vetrex2) != (-1)) {
			int vertPos1 = GetVertPos(vetrex1);
			int vertPos2 = GetVertPos(vetrex2);
			if (this->adjMatrix[vertPos1][vertPos2] != 0 && this->adjMatrix[vertPos2][vertPos1] != 0) {
				cout << "Ребро между вершинами уже есть" << endl;
				return;
			}
			else {
				this->adjMatrix[vertPos1][vertPos2] = weight;
				this->adjMatrix[vertPos2][vertPos1] = weight;
			}
		}
		else {
			cout << "Какой-либо вершины нет в графе" << endl;
			return;
		}
	}
	void PrintMatrix() {//Печать матрицы смежности графа
		if (!this->isEmpty()) {
			cout << "Матрица смежности: " << endl;
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
			cout << "Граф пуст" << endl;
		}
	}
	int GetAmoutEdges() {//Получение количества ребер для неориентированного графа
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
	T& front() {//Получение первого элемента в очереди
		return VertsQueue.front();
	}
	void removeVertex(const T& vertex) {
		int pos = GetVertPos(vertex);
		if (pos == -1) {
			cout << "Вершины " << vertex << " нет в графе." << endl;
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

		cout << "Вершина " << vertex << " удалена." << endl;
	}

	void removeEdge(const T& vertex1, const T& vertex2) {//Функция, которая удаляет ребро
		int pos1 = GetVertPos(vertex1);
		int pos2 = GetVertPos(vertex2);

		if (pos1 == -1 || pos2 == -1) {
			cout << "Одной из вершин нет в графе." << endl;
			return;
		}

		if (adjMatrix[pos1][pos2] == 0) {
			cout << "Ребра между вершинами " << vertex1 << " и " << vertex2 << " нет." << endl;
			return;
		}

		adjMatrix[pos1][pos2] = 0;
		adjMatrix[pos2][pos1] = 0;

		cout << "Ребро между вершинами " << vertex1 << " и " << vertex2 << " удалено." << endl;
	}
	void editEdgeWeight(const T& vertex1, const T& vertex2, int newWeight) {//Функция, которая меняет вес между ребрами
		int pos1 = GetVertPos(vertex1);
		int pos2 = GetVertPos(vertex2);

		if (pos1 == -1 || pos2 == -1) {
			cout << "Одной из вершин нет в графе." << endl;
			return;
		}

		if (adjMatrix[pos1][pos2] == 0) {
			cout << "Ребра между вершинами " << vertex1 << " и " << vertex2 << " нет." << endl;
			return;
		}

		adjMatrix[pos1][pos2] = newWeight;
		adjMatrix[pos2][pos1] = newWeight;

		cout << "Вес ребра между вершинами " << vertex1 << " и " << vertex2 << " изменен на " << newWeight << "." << endl;
	}
	void DFS(T& startVertex, bool* visitedVerts) {//Обход графа в глубину

		cout << "Вершина " << startVertex << " посещена " << endl;
		visitedVerts[this->GetVertPos(startVertex)] = true;
		vector<T> neighbors = this->GetNbrs(startVertex);
		for (int i = 0; i < neighbors.size(); i++) {
			if (!visitedVerts[this->GetVertPos(neighbors[i])]) {
				this->DFS(neighbors[i], visitedVerts);
			}
		}
	}
	void BFS(T& startVertex, bool* visitedVerts) {//Обход графа в ширину
		if (visitedVerts[this->GetVertPos(startVertex)] == false) {
			this->VertsQueue.push(startVertex);
			cout << "Вершина " << startVertex << " обработана" << endl;
			visitedVerts[this->GetVertPos(startVertex)] = true;
		}

		vector<T> neighbors = this->GetNbrs(startVertex);

		for (int i = 0; i < neighbors.size(); ++i) {
			if (!visitedVerts[this->GetVertPos(neighbors[i])]) {
				this->VertsQueue.push(neighbors[i]);
				visitedVerts[this->GetVertPos(neighbors[i])] = true;
				cout << "Вершина " << neighbors[i] << " обработана" << endl;
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
			labelList[i] = 1000000; // инициализация большими значениями
		}
		int pos = GetVertPos(startVertex);
		labelList[pos] = 0;
	}

	bool AllVisiited(vector<bool>& visitedVerts) {
		for (int i = 0; i < vetrexList.size(); i++) {
			if (!visitedVerts[i]) { // проверка на непосещенные вершины
				return false;
			}
		}
		return true;
	}

	void Dijkstra(const T& startVertex) {//Алгортим обхода Дейкстры
		int n = this->GetAmountVerts();
		vector<int> dist(n, INT_MAX); // Инициализация расстояний до всех вершин как бесконечности
		vector<bool> visited(n, false); // Инициализация всех вершин как непосещенных
		int startIdx = this->GetVertPos(startVertex); // Получение индекса начальной вершины
		dist[startIdx] = 0; // Расстояние до самого себя равно 0

		for (int i = 0; i < n - 1; ++i) {
			// Находим вершину с минимальным расстоянием от начальной вершины, из еще не посещенных вершин
			int minDist = INT_MAX, minIdx{};
			for (int j = 0; j < n; ++j) {
				if (!visited[j] && dist[j] <= minDist) {
					minDist = dist[j];
					minIdx = j;
				}
			}

			// Помечаем выбранную вершину как посещенную
			visited[minIdx] = true;

			// Обновляем значение расстояния для всех соседей выбранной вершины
			for (int j = 0; j < n; ++j) {
				if (!visited[j] && this->adjMatrix[minIdx][j] && dist[minIdx] != INT_MAX
					&& dist[minIdx] + this->adjMatrix[minIdx][j] < dist[j]) {
					dist[j] = dist[minIdx] + this->adjMatrix[minIdx][j];
				}
			}
		}

		// Выводим полученные расстояния от начальной вершины до всех остальных
		cout << "Вершина \tРасстояние от начальной вершины\n";
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
	cout << "Введите количество вершин: " << endl;
	cin >> Verts;
	cout << "Введите количество ребер графа: " << endl;
	cin >> Edges;
	cout << endl;
	for (int i = 0; i < Verts; i++) {
		cout << "Вершина: ";
		cin >> vertex;
		graph.insertVetrex(vertex);
		cout << endl;
	}
	for (int i = 0; i < Edges; i++) {
		cout << "Исходная вершина: ";
		cin >> sourceVertex;
		cout << endl;
		cout << "Конечная вершина: ";
		cin >> targetVetrex;
		cout << endl;
		cout << "Вес ребра: ";
		cin >> Weight;
		cout << endl;
		int* targetVerPtr = &targetVetrex;
		graph.InsertEdge(sourceVertex, targetVetrex, Weight);
	}
	cout << endl;
	graph.PrintMatrix();
	int N;
	cout << "Введите вершину, с которой начать обход: ";
	cin >> vertex;
	cout << endl;
	cout << "Обход в глубину: " << endl;
	graph.DFS(vertex, visitedVerts);
	cout << "Введите вершину, с которой начать обход: ";
	cin >> vertex;
	cout << endl;
	cout << "Обход в ширину: " << endl;
	graph.BFS(vertex, visitedVerts);
	cout << "Введите вершину, с которой начать обход: ";
	cin >> vertex;
	cout << endl;
	cout << "Обход дейкстры: " << endl;
	graph.Dijkstra(vertex);
	delete[] visitedVerts;
	cout << "Введите вершину, которую хотите удалить: ";
	cin >> N;
	graph.removeVertex(N);
	graph.PrintMatrix();
	cout << "Текущий размер графа: " << graph.GetAmountVerts();
	cout << endl;
	int g, k;
	cout << "Введите кол-во вершин, которые вы хотите добавить: ";
	cin >> g;
	cout << "Введите кол-во ребёр, которые хотите добавить: ";
	cin >> k;
	for (int i = 0; i < g; i++) {
		cout << "Вершина: ";
		cin >> vertex;
		graph.insertVetrex(vertex);
		cout << endl;
	}
	for (int i = 0; i < k; i++) {
		cout << "Исходная вершина: ";
		cin >> sourceVertex;
		cout << endl;
		cout << "Конечная вершина: ";
		cin >> targetVetrex;
		cout << endl;
		cout << "Вес ребра: ";
		cin >> Weight;
		cout << endl;
		int* targetVerPtr = &targetVetrex;
		graph.InsertEdge(sourceVertex, targetVetrex, Weight);
	}
	graph.PrintMatrix();
	cout << "Введите номера вершин, между которыми нужно удалить ребро: ";
	cin >> vertex;
	cin >> vertex1;
	graph.removeEdge(vertex, vertex1);
	cout << "Граф после удаления ребра: ";
	cout << endl;
	graph.PrintMatrix();
	cout << endl << endl;
	cout << "Введите номера вершин, между которыми нужно изменить вес ребра: ";
	cin >> vertex;
	cin >> vertex1;
	cout << endl << endl;
	cout << "Введите нужный вес: ";
	cin >> Weight;
	graph.editEdgeWeight(vertex, vertex1, Weight);
	cout << "Граф после изменения веса ребра: ";
	cout << endl;
	graph.PrintMatrix();
	return 0;
}