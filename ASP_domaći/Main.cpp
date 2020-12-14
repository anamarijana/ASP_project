#include"VEG.h"
#include"Exceptions.h"
#include<iostream>

using namespace std;

int main1() {
	cout << "Zdravo!\n";
	
	int vertex_num = 5;
	Graph* op_graph = 0;
	Graph pera = createEmptyGraph(vertex_num);
	op_graph = &pera;

	addVertex(op_graph);
	subVertex(op_graph, 2); //izbacujemo drugi cvor
	
	addEdge(op_graph, 1, 2); //dodajemo granu za koji cvor ne postoji

	addEdge(op_graph, 0, 3);
	addEdge(op_graph, 0, 3);
	addEdge(op_graph, 0, 4);
	addEdge(op_graph, 0, 1); //realokacija niza grana


	addEdge(op_graph, 4, 5,8);
	addEdge(op_graph, 1, 3,7);
	

	subEdge(op_graph, 1, 2); //uklanjamo granu koja ne postoji
	subEdge(op_graph, 4, 5);
	
	printGraph(op_graph);
	deleteGraph(op_graph);

	return 0;

}

int main() {
	int start_vertex_num = 9;

	Graph* op_graph = 0;
	Graph pera = createEmptyGraph(start_vertex_num);
	op_graph = &pera;

	addEdge(op_graph, 3, 4, 9);
	addEdge(op_graph, 7, 8, 7);
	addEdge(op_graph, 1, 7, 11);
	addEdge(op_graph, 8, 2, 2);

	addEdge(op_graph, 7, 6, 1);
	addEdge(op_graph, 0, 1, 4);

	addEdge(op_graph, 2, 3, 7);
	addEdge(op_graph, 8, 6, 6);


	addEdge(op_graph, 6, 5,2);

	addEdge(op_graph, 1, 2,8);

	addEdge(op_graph, 0, 7,8);
	addEdge(op_graph, 2, 5,4);
	
	addEdge(op_graph, 3, 5,14);

	addEdge(op_graph, 5, 4,10);





	doKruskal(op_graph, start_vertex_num);



}