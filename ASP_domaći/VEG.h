#pragma once
#include <string>
#include<vector>
#include <queue>
using namespace std;
class Vertex {
public:
	//friend class Graph;
	Vertex(int vertex_id, int start_child_id, int child_num=0):vertex_id_(vertex_id),start_child_id_(start_child_id),child_num_(child_num) {}
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
	Edge( Vertex* to_vertex=0, int weight=0) : to_vertex_(to_vertex), weight_(weight) {}
	//Edge(Edge& edge);
	Vertex* getToVertex() { return to_vertex_; }
	void setToVertex(Vertex* v) { to_vertex_ = v; }
	void setFromVertex(Vertex* v) { from_vertex_ = v; }
	Vertex* getFromVertex() { return from_vertex_; }
	void setWeight(const int weight);
	int getWeight() { return weight_; }
	
	friend bool operator<(const Edge& e1, const Edge& e2);
	friend bool operator>(const Edge& e1, const Edge& e2);
	friend bool operator==(const Edge& e1, const Edge& e2);
	friend ostream& operator<<(ostream& os, const Edge& ed);



protected:
private:

	int weight_; // težina grane
	Vertex* to_vertex_;
	Vertex* from_vertex_;


};

//za implementaciju cvorova cini se da je dobar vektor
//svaki novi cvor mozemo da dodamo na kraj
//Po potrebi brisemo cvor


class Graph {
public:
	friend class Kruskal;
	Graph(int vertex_num, int cur_child_num=2); // ovde menjaj za unapred zadat broj dece
	void removeVertex(int vertex_id);
	void insertVertex();
	void insertEdge(int first, int second,int weight=1);
	void removeEdge(int first, int second);

	void edgesRealocation();
	void print();
	void removeGraph();



protected:
private:
	int vertex_num_;
	int cur_children_num_;
	std::vector<Edge> edges_;
	//n+1 cvorova!!
	std::vector <Vertex> vertices_;

};

class SetElement {
public:
	SetElement(Vertex* cur) :cur_(cur), next_(0) {}
protected:
private:
	Vertex* cur_;
	Vertex* next_;
	
};

class Kruskal {
public:
	Kruskal(int vertex_num):vertex_num_(vertex_num),price_(0){}
	void fillPrirorityQueue(Graph* op_graph);
	void printPriorityQueue();
	bool alreadyThere(Edge ed);
	void makeSpanningTree();
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


//globalne funkcije
bool isMarked(Edge ed);
Graph createEmptyGraph(int vertex_num);
void subVertex(Graph* op_graph, int sub_vertex_id);
void addVertex(Graph* op_graph);
void addEdge(Graph* op_graph, int first, int second, int weight=1);
void subEdge(Graph* op_graph, int first, int second);
void printGraph(Graph* op_graph);
void deleteGraph(Graph* op_graph);

int doKruskal(Graph* op_graph, int start_vertex_num);

