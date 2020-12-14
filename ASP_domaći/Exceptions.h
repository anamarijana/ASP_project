#pragma once


#include<exception>

class Exceptions:public std::exception {
public:
	Exceptions(const char* err): exception(err){}
};

class InvalidIndex :public std::exception {
public:
	InvalidIndex(const char* err) : exception(err) {}
};

class ExistingEdge :public std::exception {
public:
	ExistingEdge(const char* err) : exception(err) {}
};

class NonExistingEdge :public std::exception {
public:
	NonExistingEdge(const char* err) : exception(err) {}
};