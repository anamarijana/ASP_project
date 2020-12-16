#pragma once

#include"VEG.h"
#include"Exceptions.h"
#include<iostream>
#include<algorithm>

using namespace std;

//fja unosi promene nad origanlnim pokazivacem i na njega kaci objekat

Graph createEmptyGraph(int vertex_num) {
	Graph* new_graph = new Graph(vertex_num);
	return *new_graph;
}

Graph::Graph(int vertex_num,int cur_child_num) :vertex_num_(vertex_num) ,cur_children_num_(cur_child_num){
	
	//alociramo niz cvorova grafa


	for (int i = 0; i < vertex_num; i++) {
		Vertex* new_vertex = new Vertex(i,i*cur_children_num_);

		vertices_.push_back(*new_vertex);
	}

	//svakome obezbedjujemo 16oro dece
	for (int i = 0; i < vertex_num * cur_children_num_; i++) {
		Edge* new_edge = new Edge;
		edges_.push_back(*new_edge);
	}

}

void subVertex(Graph* op_graph, int sub_vertex_id) {
	op_graph->removeVertex(sub_vertex_id);
}


void Graph::removeVertex(int vertex_id) {
	
	int iterator = -1;
	Vertex* er_vertex=0;
	try {
		for (int i = 0; i < vertices_.size(); i++) {
			if (vertex_id == vertices_[i].getID()){
				iterator = i;
				er_vertex = &vertices_[i];
				break;
			}
				
		}

		if (iterator == -1) throw InvalidIndex("Ne postoji ovaj èvor! ");


		//auto first = edges_.begin() + iterator * cur_children_num_;
		//auto last = edges_.begin() + iterator * cur_children_num_ + cur_children_num_;

		


		//brisemo one grane kojima je trazeni cvor sused
		for (int i = 0; i < edges_.size(); i++) {
			
			int id = edges_[i].getToVertex();
			if(id!=-1){
				if (id == vertex_id)
				{
					
					edges_[i].setWeight(-1); //obeležavamo cvorove kojima je on sused
				}
				
			}
			

			
		}

		//izbacujemo one grane kojima je izbacen cvor sused
		for (int j = 0; j < vertex_num_; j++) {
			int child_num = vertices_[j].getChildNum();
			int new_child_num = child_num;
			for (int k = 0; k < child_num; k++) {

				int it = k + j * cur_children_num_;
				int end = j * cur_children_num_ + child_num - 1;
				Edge* cur = &(edges_[k + j * cur_children_num_]);
				Edge* end_v = &(edges_[j * cur_children_num_ + child_num - 1]);

				

				if (cur->getWeight() == -1) {
					if (it != end) {
						cur->setWeight(end_v->getWeight());
						cur->setToVertex(end_v->getToVertex());

					}
					end_v->setWeight(0);
					end_v->setToVertex(-1);

					//treba tom susedu smanjiti broj dece
					new_child_num--;

				}
			}
			vertices_[j].setChildNum(new_child_num);




		}

		int first_it = iterator * cur_children_num_;
		int last_it = iterator * cur_children_num_ + cur_children_num_;

		//uzemljavamo grane na koje on pokazuje
		for (int i = iterator * cur_children_num_; i < iterator * cur_children_num_ + cur_children_num_; i++) {


			edges_[i].setWeight(-1);
		}
		//brisemo grane na koje on pokazuje
		edges_.erase(std::remove_if(edges_.begin(), edges_.end(), isMarked), edges_.end());



		

		//brisemo cvor iz spiska cvorova
		vertices_.erase(vertices_.begin() + iterator);
		vertex_num_--;

	}
	catch (InvalidIndex& e) {
		e.what();
	}
}

bool operator==(const Vertex& v1, const Vertex& v2)
{
	if (v1.vertex_id_ == v2.vertex_id_) return 1;
	return 0;
}

bool operator<(const Edge& e1, const Edge& e2)
{
	if (e1.weight_ < e2.weight_) return true;
	return false;
}

bool operator>(const Edge& e1, const Edge& e2)
{
	if (e1.weight_ > e2.weight_) return true;
	return false;
}

bool operator==(const Edge& e1, const Edge& e2)
{
	if ((e1.weight_ == e2.weight_) && (e1.from_vertex_ == e2.from_vertex_) && (e1.to_vertex_ == e2.to_vertex_)) {
		return true;
	}
	return false;

	
}

std::ostream& operator<<(std::ostream& os, const Edge& ed)
{

	int vertex_from_id = ed.from_vertex_;
	int vertex_to_id = ed.to_vertex_;
	return os << "(" << vertex_from_id << ',' << vertex_to_id << ") " << "cena- " << ed.weight_<<'\n';
}

bool operator<(const Pair& p1, const Pair& p2)
{
	if(p1.distance_ < p2.distance_) return true;
	return false;
}

bool operator>(const Pair& p1, const Pair& p2)
{
	if (p1.distance_ > p2.distance_) return true;
	return false;
}

bool operator==(const Pair& p1, const Pair& p2){
	if (p1.it_ == p2.it_)
		return true;
	return false;
}

bool isMarked(Edge ed){
	if (ed.getWeight() == -1) return 1;
	else return 0;
}



void addVertex(Graph* op_graph) {
	// treba staviti njegove buduce susede
	op_graph->insertVertex();

}
//napraviti verziju sa granama
void Graph::insertVertex(){
	int id = 0;
	for (int i = 0; i < vertices_.size(); i++) {
		if (vertices_[i].getID() > id){
			id = vertices_[i].getID();
		}
			
	}

	int new_id = id+1;
	Vertex* new_one = new Vertex(new_id, new_id * cur_children_num_);
	vertices_.push_back(*new_one);

	for (int i = 0; i < cur_children_num_; i++) {
		Edge* new_edge = new Edge;
		edges_.push_back(*new_edge);
	}
	vertex_num_++;
}


void addEdge(Graph* op_graph,int first,int second, int weight, int exists) {

	op_graph->insertEdge(first, second, weight,exists);
}


void Graph::insertEdge(int first, int second, int weight, int exists)
{
	
	//ubacujemo granu izmedju dva cvora prema njihovom id
	//izuzetak
	int it1 = -1;
	int it2 = -1;
	Vertex* v1 = 0;
	Vertex* v2 = 0;
	try {
		for (int i = 0; i < vertices_.size(); i++) {

			if (first == vertices_[i].getID()) {
				it1 = i;
				v1 = &vertices_[i];
			}

			if (second == vertices_[i].getID()) {
				it2 = i;
				v2 = &vertices_[i];
			}
		}

		if (it1 == -1 || it2 == -1)
			throw InvalidIndex("ne postoje ti cvorovi! \n");

		//treba proci kroz grane vezane za prvi cvor i videti da li postoji grana za drugi
		int start1 = it1 * cur_children_num_;
		int end1 = start1 + v1->getChildNum();

		for (int i = start1; i < end1; i++) {
			if (edges_[i].getToVertex() == second)
				throw ExistingEdge("grana vec postoji! \n");
		}

		//ako vec ima popunjenu svu decu
		if (v1->getChildNum() == cur_children_num_) {
			edgesRealocation();
		}

			

		edges_[it1 * cur_children_num_ + v1->getChildNum()].setWeight(weight);
		edges_[it1 * cur_children_num_ + v1->getChildNum()].setToVertex(second);
		edges_[it1 * cur_children_num_ + v1->getChildNum()].setFromVertex(first);

		v1->setChildNum(v1->getChildNum() + 1);


		//optimizacija samo njemu povecati decu
		//ako vec ima popunjenu svu decu
		if (v2->getChildNum() == cur_children_num_) {
			edgesRealocation();
		}

		int start2 = it2 * cur_children_num_;
		int end2 = start2 + v2->getChildNum();

		//neusmeren graf ne moramo ponovo da proveravamo da li postoji grana

		edges_[it2 * cur_children_num_ + v2->getChildNum()].setWeight(weight);
		edges_[it2 * cur_children_num_ + v2->getChildNum()].setToVertex(first);
		edges_[it2 * cur_children_num_ + v2->getChildNum()].setFromVertex(second);

		v2->setChildNum(v2->getChildNum() + 1);



		


	}
	catch (ExistingEdge& e1) {
		std::cout << e1.what();
	}
	catch (InvalidIndex& e2) {
		std::cout << e2.what();
	}


}



void Graph::edgesRealocation(){

	int new_child_num = pow(log2(cur_children_num_) + 1, 2);
	
	std::vector<Edge> new_edges_;
	for (int i = 0; i < vertex_num_ * new_child_num; i++) {
		Edge* new_edge = new Edge;
		new_edges_.push_back(*new_edge);
	}


	Vertex* cur_vertex;
	for (int i = 0; i < vertices_.size(); i++) {
		cur_vertex = &vertices_[i];
		
		for (int j = 0; j < cur_vertex->getChildNum(); j++) {
			//operator = po difoltu plitku kopiju
			new_edges_[j + i * new_child_num] = edges_[j + i * cur_children_num_];
		}
	}

	//uzemljavamo stare i brisemo grane

	edges_.clear();
	
	
	edges_ = new_edges_;
	cur_children_num_ = new_child_num;
	
	new_edges_.clear();
}

void subEdge(Graph* op_graph, int first, int second) {
	op_graph->removeEdge(first, second);
}
void Graph::removeEdge(int first, int second){
	try {

		int it1 = -1;
		int it2 = -1;
		Vertex* er_vertex1 =0;
		Vertex* er_vertex2 =0;

		for (int i = 0; i < vertex_num_; i++) {
			if (vertices_[i].getID() == first) {
				er_vertex1 = &vertices_[i];
				it1 = i;
			}
			if (vertices_[i].getID() == second) {
				er_vertex2 = &vertices_[i];
				it2 = i;
			}
		}
		if (it1 == -1 || it2 == -1) throw InvalidIndex("Ne postoje cak ni cvorovi!\n");

		int new_child_num1 = er_vertex1->getChildNum();
		int new_child_num2 = er_vertex2->getChildNum();

		for (int i = 0; i < er_vertex1->getChildNum(); i++) {
			
			int it = i + it1 * cur_children_num_;
			int end = it1 * cur_children_num_ + er_vertex1->getChildNum() - 1;

			Edge* cur = &(edges_[it]);
			Edge* end_v = &(edges_[end]);

			//uklanjamo granu koja povezuje prvi sa drugim 
			if (edges_[it].getToVertex() == second) {

				if (it != end) {
					cur->setWeight(end_v->getWeight());
					cur->setToVertex(end_v->getToVertex());

				}
				end_v->setWeight(0);
				end_v->setToVertex(-1);
				//smanjujemo decu
				new_child_num1--;

			}

		}

		er_vertex1->setChildNum(new_child_num1);

		//isto obavljamo i za drugi cvor

		for (int i = 0; i < er_vertex2->getChildNum(); i++) {

			int it = i + it2 * cur_children_num_;
			int end = it2 * cur_children_num_ + er_vertex2->getChildNum() - 1;

			Edge* cur = &(edges_[it]);
			Edge* end_v = &(edges_[end]);

			//uklanjamo granu koja povezuje drugi sa prvim
			if (edges_[it].getToVertex() == first) {

				if (it != end) {
					cur->setWeight(end_v->getWeight());
					cur->setToVertex(end_v->getToVertex());

				}
				end_v->setWeight(0);
				end_v->setToVertex(-1);
				//smanjujemo decu
				new_child_num2--;

			}

		}

		er_vertex2->setChildNum(new_child_num2);

	}
	catch (InvalidIndex& e) {
		cout<<e.what();
	}
	catch (NonExistingEdge& e) {
		cout<<e.what();
	}

}


void Edge::setWeight(int weight){

	weight_ = weight;
}

void printGraph(Graph* op_graph) {
	op_graph->print();
}

void Graph::print(){

	for (int i = 0; i < vertex_num_; i++) {
		cout << "cvor " << vertices_[i].getID() << " ima susede: ";
		for (int j = 0; j < vertices_[i].getChildNum(); j++) {
			int sused = edges_[i * cur_children_num_ + j].getToVertex();
			cout << sused << " ";
		}
		cout << '\n';
	}
}


void deleteGraph(Graph* op_graph) {
	op_graph->removeGraph();
}

void Graph::removeGraph(){
	
	edges_.clear();
	

	vertices_.clear();


}

Vertex* Graph::findByID(int ID)
{
	int it = -1;
	for (int i = 0; i < vertices_.size(); i++) {
		if (ID == vertices_[i].getID()) {
			it = i;
			break;
		}
			 
	}

	return &vertices_[it];
}


int Graph::isThereBranch(int iterator, int ID){
	
	int first_it = iterator * cur_children_num_;
	int last_it = iterator * cur_children_num_ + cur_children_num_;

	//prolazimo kroz grane jednog cvora i pitamo da li je cvor sa ID povezan sa tim cvorom
	for (int i = first_it; i < last_it; i++) {
		if (ID == edges_[i].getToVertex()) {
			return edges_[i].getWeight();
		}

		
	}

	return INT_MAX;
	
}

void Vertex::setName(std::string name) {
	name_ = name;
}

void Kruskal::fillPrirorityQueue(Graph* op_graph){

	
	for (int i = 0; i < op_graph->edges_.size(); i++) {
		
		if (op_graph->edges_[i].getWeight()!=0) {

			priority.push_back(op_graph->edges_[i]);
		}
	}

	for (int i = 0; i < priority.size(); i++) {
		if (alreadyThere(priority[i])) {
			priority[i].setWeight(-1);
		}
	}
	priority.erase(std::remove_if(priority.begin(), priority.end(), isMarked), priority.end());

	std::sort(priority.begin(), priority.end());

}


bool Kruskal::alreadyThere(Edge ed){
	
	// da li se pre njega nalazi dvojnik
	
	//poziciju grane kojoj trazimo dvojnika
	int stop;//pozicija te grane
	for (stop= 0; stop < priority.size(); stop++) {
		if (priority[stop] == ed) break;
	}

	for (int i = 0; i < stop; i++) {
		//trazimo granu sa istom tezinom ali sa suprotnim cvorovima
		if ((priority[i].getWeight() == ed.getWeight()) && (priority[i].getFromVertex() == ed.getToVertex()) && (priority[i].getToVertex()== ed.getFromVertex())) {
			return 1;
		}
	
	}

	return 0;
}

void Kruskal::makeSpanningTree(Graph* op_graph){
	int edg_num = 0;
	int i = 0;
	while (edg_num < vertex_num_ - 1) {
		Edge* branch = &priority[i];
		i++;
	
		int merge1 = -1; //on mi pamti u kom su skupu
		int merge2 = -1;
		int ver_num = vertex_sets_.size();
		for (int j = 0; j < ver_num; j++) {
			int set_size = vertex_sets_[j].size();
			for (int k = 0; k < set_size; k++) {
				int id1 = branch->getFromVertex();
				Vertex from = *(op_graph->findByID(id1));
				//Vertex from = *(branch->getFromVertex());
				if (vertex_sets_[j][k] == from) {
					merge1 = j;

				}
				int id2 = branch->getToVertex();
				Vertex to = *(op_graph->findByID(id2));

				if (vertex_sets_[j][k] == to) {
					merge2 = j;
				}

			}
		}
			//ako se razlikuju skupovi u kojima su svorovi onda je to grana stabla
			if (merge1 != merge2) {
				spanning_tree_.push_back(branch);
				edg_num++;
				price_ += branch->getWeight();
				//iz drugog skupa sve prebacujemo u prvi
				for (int m = 0; m < vertex_sets_[merge2].size(); m++) {
					vertex_sets_[merge1].push_back(vertex_sets_[merge2][m]);
				}
				vertex_sets_[merge2].clear();
				//mislim da je ok ne brisati taj skup
			}
		

	}


}
void Kruskal::printSpanningTree(){

	cout << '\n' << "Pririotetno stablo: \n";
	for (int i = 0; i < spanning_tree_.size(); i++) {
		cout << i + 1 << ". " << *spanning_tree_[i];
	}

	cout << "ukupna cena: " << price_ << '\n';

}
bool Kruskal::sameSet(Edge* ed)
{
	return false;
}


void Kruskal::makeVertexSets(Graph* op_graph){
	int vertex_num = op_graph->vertices_.size();
	for (int i = 0; i < vertex_num; i++) {
		//vector<vector<Vertex>*> vertex_sets_;
		Vertex ver = (op_graph->vertices_[i]);
		vector<Vertex> pera;
		pera.push_back(ver);
		vertex_sets_.push_back(pera);
	}


}


void Kruskal::printPriorityQueue(){
	//priority_queue<Edge> print_queue = pr_edges_;

	for (int i = 0; i < priority.size(); i++) {
		cout <<i+1<<". "<< priority[i];
	}
	/*
	while (!print_queue.empty()) {
		cout << print_queue.top() << "\n";
		print_queue.pop();
	}
	*/
}



int doKruskal(Graph* op_graph, int start_vertex_num) {
	
	Kruskal* kruskal = new Kruskal(start_vertex_num);
	kruskal->fillPrirorityQueue(op_graph);
	kruskal->printPriorityQueue();
	kruskal->makeVertexSets(op_graph);
	kruskal->makeSpanningTree(op_graph);
	kruskal->printSpanningTree();


	return 0;
}

int doDijkstra(Graph* op_graph, int vertex_id){

	Dijkstra* dijkstra = new Dijkstra(vertex_id, op_graph);
	dijkstra->makeVertexId(op_graph);
	dijkstra->makeIt(op_graph);
	dijkstra->makeEachTrace();
	dijkstra->printEachTrace();



	return 0;
}


void Dijkstra::makeIt(Graph* op_graph){
	// nadjem indeks cvora ciji id dobijam
	int it_source = findIndex(op_graph, start_vertex_id_);

	//svim cvorovima na pocetku dodelimo beskonacnu udaljenost
	//osim cvoru od kojeg trazimo udaljenost, tu stavljamo 0
	
	vector<Pair> priority_length_node;
	
	

	distance[it_source] = 0;
	// set u koji stavljamo grane od kojih biramo najmanju, nadajuci se da cemo napraviti minimalni put do svakog cvora
	priority_length_node.push_back(Pair(it_source, 0));

	while (!priority_length_node.empty()) {

		sort(priority_length_node.begin(), priority_length_node.end());
		
		Pair top = priority_length_node.front();

		priority_length_node.erase(priority_length_node.begin());

		//trenutni cvor sa kojim pokusavamo da napravimo novi put
		int source_node = top.it_; 
		int source_ID = op_graph->vertices_[source_node].getID();
		 
		int child_num = op_graph->vertices_[source_node].getChildNum();
		//treba da prodjem kroz grane tog cvora

		int first_it = top.it_ * op_graph->cur_children_num_;
		int last_it = top.it_ * op_graph->cur_children_num_ + child_num;

		
		for (int i = first_it; i < last_it; i++) {

			//indeks cvora na koji pokazuje grana
			int adj_ID = op_graph->edges_[i].getToVertex();
			
			int adj_node = findIndex(op_graph, adj_ID);

			int length_to_adjnode = op_graph->edges_[i].getWeight();

			//distance[source_node]; treutna udaljenost cvora preko kog pokusavamo da napravimo novi put
			// distance[adj_node]; to je trenutna udaljenost cvora od zadatog cvora 

			if (distance[adj_node] > length_to_adjnode + distance[source_node]) {

				if (distance[adj_node] != INT_MAX) {
				// vec postoji neki put do tog cvora koji cemo mi da relaksiramo


					
					priority_length_node.erase(std::remove(priority_length_node.begin(), priority_length_node.end(), Pair(adj_node, distance[adj_node])), priority_length_node.end());


				}
				trace_distance[adj_node] = source_ID;
				distance[adj_node] = length_to_adjnode + distance[source_node];
				//kad god utvrdimo da smo nasli najkraci put do nekog cvora taj cvor fiksiramo i trazimo put preko njega do ostalih cvorova
				priority_length_node.push_back(Pair(adj_node, distance[adj_node]));




			}


		}


	}
	/*
	for (int i = 0; i < op_graph->vertices_.size(); i++) {
		cout << "pocetni cvor(" << start_vertex_id_ << ") -> zavrsni cvor(" << i << ") : " << distance[i] << endl;
	}
	*/

	/*
	cout << "Matrica prethodnika: " << endl;
	for (int i = 0; i < trace_distance.size(); i++) {
		cout << trace_distance[i] << " ";
	}
	cout << endl;
	*/
}




int Dijkstra::findIndex(Graph* op_graph, int start_vertex_id_){
	
	int iterator = -1;
	for (int i = 0; i < op_graph->vertices_.size(); i++) {
		if (start_vertex_id_ == op_graph->vertices_[i].getID()) {
			iterator = i;

			break;
		}

	}

	return iterator;
	
}

void Dijkstra::makeEachTrace(){


	for (int i = 0; i < trace_distance.size(); i++) {
		int it = i;
		vector<int> pera;
		each_trace_.push_back(pera);
		
		while (1) {
			
			if (trace_distance[it] == -1) {
				break;
			}
			if (trace_distance[it] == start_vertex_id_) {
				break;
			}
			each_trace_[i].push_back(trace_distance[it]);
			it = trace_distance[it];
			
		}
	}

}

void Dijkstra::makeVertexId(Graph* op_graph){

	for (int i = 0; i < op_graph->vertices_.size(); i++) {
		vertex_id_.push_back(op_graph->vertices_[i].getID());
	}
}

void Dijkstra::printEachTrace(){

	for (int i = 0; i < vertex_id_.size(); i++) {
		cout << "put od " << vertex_id_[i] << "do " << start_vertex_id_;
		if (each_trace_[i].empty() && vertex_id_[i] == start_vertex_id_) { cout << "je nulti! "<<endl; continue; }
		else if (each_trace_[i].empty()) cout << "je direktan!";
		else{
			cout << "ide preko cvorova: ";
			for (int j = 0; j < each_trace_[i].size(); j++) {
				cout << each_trace_[i][j] << " ";

			}
		}
		
		cout <<" udaljenost puta je: "<<distance[i] <<endl;
	}

}
