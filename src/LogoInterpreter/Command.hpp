#pragma once
#include<string>
#include<vector>

using namespace std;

class Command
{
public:
	Command(string name, string arg="")
	{
		this->name = name;
		this->arg = arg;
	}

	string name;
	string arg;
	vector<Command> commands;


};