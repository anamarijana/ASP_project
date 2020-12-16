#pragma once
#include <string>
#include<vector>
#include <queue>
using namespace std;
class Vertex {
public:
	//friend class Graph;
	Vertex(int vertex_id, int start_child_id, int child_num=0):vertex_id_(vertex_id),start_child_id_(start_child_id),child_num_(child_num){}
	void setName(std::string name);
	int getID() { return vertex_id_; }
	int getChildNum() { return child_num_; }
	void setChildNum(int num) { child_num_ = num; }
	friend bool operator==(const Vertex& v1, const Vertex& v2);

	
protected:
private:
	std::string name_;
	int vertex_id_; //drugo ime
	int start_child_id_; //indeks od kog mu skevencijalno kreæu deca
	int child_num_; //koliko zaista dece ima

	
};

//on ne mora da zna za koga je povezan 
class Edge {
public:
	Edge() : to_vertex_(-1), from_vertex_(-1), weight_(0),exists_(1) {}
	//Edge(Edge& edge);
	int getToVertex() { return to_vertex_; }
	void setToVertex(int v) { to_vertex_ = v; }
	void setFromVertex(int v) { from_vertex_ = v; }
	int getFromVertex() { return from_vertex_; }
	void setWeight(const int weight);
	int getWeight() { return weight_; }
	
	friend bool operator<(const Edge& e1, const Edge& e2);
	friend bool operator>(const Edge& e1, const Edge& e2);
	friend bool operator==(const Edge& e1, const Edge& e2);
	friend ostream& operator<<(ostream& os, const Edge& ed);

	void setExists(bool exists) { exists_ = exists; }
	bool getExists() { return exists_; }

protected:
private:

	int weight_; // težina grane
	int to_vertex_;
	int from_vertex_;
	
	//ovo nam pokazuje da li grana zaista postoji ili ju je moguce izgraditi
	//sluzi za poslednji zahtev
	bool exists_;


};

//za implementaciju cvorova cini se da je dobar vektor
//svaki novi cvor mozemo da dodamo na kraj
//Po potrebi brisemo cvor


class Graph {
public:
	friend class Kruskal;
	friend class Dijkstra;
	Graph(int vertex_num, int cur_child_num=2); // ovde menjaj za unapred zadat broj dece
	void removeVertex(int vertex_id);
	void insertVertex();
	void insertEdge(int first, int second,int weight=1, int exists=1);
	void removeEdge(int first, int second);

	void edgesRealocation();
	void print();
	void removeGraph();

	Vertex* findByID(int ID);

	

	int isThereBranch(int iterator, int ID);



protected:
private:
	int vertex_num_;
	int cur_children_num_;
	std::vector<Edge> edges_;
	//n+1 cvorova!!
	std::vector <Vertex> vertices_;

};


class Kruskal {
public:
	Kruskal(int vertex_num):vertex_num_(vertex_num),price_(0){}
	void fillPrirorityQueue(Graph* op_graph);
	void printPriorityQueue();
	bool alreadyThere(Edge ed);
	void makeSpanningTree(Graph* op_graph);
	void printSpanningTree();
	void makeVertexSets(Graph* op_graph);
	bool sameSet(Edge* ed);
	
protected:
private:
	int vertex_num_;
	//priority_queue<Edge> pr_edges_;
	
	vector<Edge> priority;
	vector<Edge*> spanning_tree_;

	//vector<SetElement*> vertex_sets_;
	vector<vector<Vertex>> vertex_sets_;
	
	int price_;
	
	

};
class Dijkstra {
public:
	Dijkstra(int start_vertex_id, Graph* op_graph):start_vertex_id_(start_vertex_id),size_(0){

		for (int i = 0; i < op_graph->vertices_.size(); i++) {
			distance.push_back(INT_MAX);
			trace_distance.push_back(-1);
		}
	
	}
	void makeIt(Graph* op_graph);
	int findIndex(Graph* op_graph, int start_vertex_id_);
	void makeEachTrace();
	void makeVertexId(Graph* op_graph);
	void printEachTrace();
protected:
private:
	vector<int> vertex_id_;
	vector<int> distance;
	vector<int> trace_distance;
	int start_vertex_id_;

	vector<vector <int> > each_trace_;
	
	int size_;
};

class Pair {
public:
	friend class Dijkstra;
	Pair(int it, int dis):it_(it), distance_(dis){}
	friend bool operator<(const Pair& p1, const Pair& p2);
	friend bool operator>(const Pair& p1, const Pair& p2);
	friend bool operator==(const Pair& p1, const Pair& p2);
	

protected:
private:
	int it_;
	int distance_;

};



//globalne funkcije
bool isMarked(Edge ed);
Graph createEmptyGraph(int vertex_num);
void subVertex(Graph* op_graph, int sub_vertex_id);
void addVertex(Graph* op_graph);
void addEdge(Graph* op_graph, int first, int second, int weight=1,int exists =1);
void subEdge(Graph* op_graph, int first, int second);
void printGraph(Graph* op_graph);
void deleteGraph(Graph* op_graph);

int doKruskal(Graph* op_graph, int start_vertex_num);
int doDijkstra(Graph* op_graph, int vertex_id);


//isprobavanje algoritama:
void graphManipulation();
void  KruskalSimulation1();
void  KruskalSimulation2();
void DijskstraSimulation();
void metroSimulation();
