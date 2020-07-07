#pragma once
#include <string>
#include <vector>

void generate(bool newItems = false);

class Item
{
	std::string id, backendType;

	public:
	Item(std::string id, std::string backendType);
	std::string toString();
};

std::vector<Item> getItemIds(std::string url);

void writeToFile(std::string filename, std::vector<Item> items);