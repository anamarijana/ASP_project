#include"VEG.h"
#include"Exceptions.h"

#include <iostream>
#include <queue>

using namespace std;
void metroSimulation() {
	cout << "Zdravo, unesi broj kljucnih lokacija u gradu: " << endl;
	int start_vertex_num;
	cin >> start_vertex_num;

	Graph* op_graph = 0;
	Graph pera = createEmptyGraph(start_vertex_num);
	op_graph = &pera;
	cout << "unesite parove rednih brojeva gde je moguca izgradnja metroa i cenu toga puta" << endl;
	cout << "za prekid unosa grana unesite -1" << endl;
	int id1;
	int id2;
	int price;
	while (1) {

		cin >> id1;
		if (id1 == -1) break;
		cin >> id2;
		cin >> price;
		addEdge(op_graph, id1, id2,price);

		
	}
	doKruskal(op_graph, start_vertex_num);



}



void menuSimulation() {

	cout << "Zdravo, unesi broj èvorova grafa: " << endl;
	int start_vertex_num;
	cin >> start_vertex_num;

	Graph* op_graph = 0;
	Graph pera = createEmptyGraph(start_vertex_num);
	op_graph = &pera;
	while (1) {
		cout << "Unesi 1 za dodavanje nove grane u grafu" << endl;
		cout << "Unesi 2 za izbacivanje grane iz grafa" << endl;
		cout << "Unesi 3 za dodavanje cvora u grafu" << endl;
		cout << "Unesi 4 za izbacivanje cvora iz grafa" << endl;
		cout << "Unesi 5 za ispis reprezentacije grafa" << endl;
		cout << "Unesi 6 za brisanje grafa grafa" << endl;
		cout << "Unesi 0 za prekidanje programa" << endl;


		int choice;
		cin >> choice;
		if (choice == 0) break;
		int id1;
		int id2;
		int id;

		switch (choice)
		{

		case 1:
			cout << "Unesi odvojeno enterom cvorove grane:" << endl;

			cin >> id1;
			cin >> id2;
			addEdge(op_graph, id1, id2);
			break;
		case 2:
			cout << "Unesi odvojeno enterom cvorove grane:" << endl;

			cin >> id1;
			cin >> id2;
			subEdge(op_graph, id1, id2);
			break;
		case 3:
			addVertex(op_graph);
			break;
		case 4:
			cout << "Unesi redni broj cvora koji zelis da se ukloni" << endl;
			cin >> id;
			subVertex(op_graph, id);
			break;
		case 5:
			printGraph(op_graph);
			break;
		case 6:
			deleteGraph(op_graph);
			op_graph = 0;
			break;
		default:
			cout << "nemojte da se igrate! " << endl;
			break;
		}

		if (op_graph == 0) break;

	}
	cout << "vidimo se uskoro!" << endl;
}



void graphManipulation() {


	cout << "Zdravo!\n";

	int vertex_num = 5;
	Graph* op_graph = 0;
	Graph pera = createEmptyGraph(vertex_num);

	op_graph = &pera;

	addEdge(op_graph, 1, 2);
	addEdge(op_graph, 0, 3);
	addEdge(op_graph, 2, 3);
	addEdge(op_graph, 4, 3);
	addEdge(op_graph, 2, 4);
	addEdge(op_graph, 4, 0);

	addEdge(op_graph, 0, 2);
	addEdge(op_graph, 0, 1); //realokacija niza grana


	printGraph(op_graph);

	cout << endl << "graf manje jedan cvor:" << endl;
	subVertex(op_graph, 0); //izbacujemo drugi cvor
	printGraph(op_graph);


	cout << endl << "graf plus jedan cvor:" << endl;
	addVertex(op_graph);
	printGraph(op_graph);

	cout << endl << "graf manje (2,4)" << endl;
	subEdge(op_graph, 2, 4);
	subEdge(op_graph, 2, 4);
	printGraph(op_graph);


	deleteGraph(op_graph);

}

void KruskalSimulation1() {
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


	addEdge(op_graph, 6, 5, 2);

	addEdge(op_graph, 1, 2, 8);

	addEdge(op_graph, 0, 7, 8);
	addEdge(op_graph, 2, 5, 4);

	addEdge(op_graph, 3, 5, 14);

	addEdge(op_graph, 5, 4, 10);



	doKruskal(op_graph, start_vertex_num);

	

}

void  KruskalSimulation2() {



	int start_vertex_num;
	cin >> start_vertex_num;
	Graph* op_graph = 0;
	Graph pera = createEmptyGraph(start_vertex_num);
	op_graph = &pera;

	addEdge(op_graph, 0, 1, 8);
	addEdge(op_graph, 0, 4, 19);
	addEdge(op_graph, 1, 4, 34);
	addEdge(op_graph, 2, 4, 14);
	addEdge(op_graph, 1, 2, 18);
	addEdge(op_graph, 1, 5, 3);
	addEdge(op_graph, 2, 5, 6);
	addEdge(op_graph, 2, 3, 12);
	addEdge(op_graph, 3, 5, 13);


	doKruskal(op_graph, start_vertex_num);

	

}

void DijskstraSimulation() {
	int start_vertex_num = 6;

	Graph* op_graph = 0;
	Graph pera = createEmptyGraph(start_vertex_num);
	op_graph = &pera;

	addEdge(op_graph, 0, 1, 5);
	addEdge(op_graph, 0, 2, 1);
	addEdge(op_graph, 0, 3, 4);

	addEdge(op_graph, 1, 2, 3);
	addEdge(op_graph, 1, 4, 8);

	addEdge(op_graph, 2, 3, 2);
	addEdge(op_graph, 2, 4, 1);

	addEdge(op_graph, 3, 4, 2);
	addEdge(op_graph, 3, 5, 1);

	addEdge(op_graph, 4, 5, 3);

	//ja mu dajem ID cvora od kog hocu da mi racuna najmanju udaljenost
	doDijkstra(op_graph, 0);
	cout << endl;
	doDijkstra(op_graph, 5);

}