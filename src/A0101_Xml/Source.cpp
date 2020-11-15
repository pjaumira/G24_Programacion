// Activitat 01 XML
// ENTI 2020-2021
// Pol Jaumira

//includes estandard
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream> 

//includes XML
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

//structs i enums per fer la llista d'enemics

enum weapontypes { Ranged, Melee, Magic, Fire, Ice, Rock, Wind };

struct weapon {
	std::string ID;
	enum weapontypes type;
	int range;
};

struct enemy {
	int health;
	int attack;
	int defense;
	int atspeed;
	int exp;
	std::vector <weapon> weaponset;
};

//llista d'enemics
std::list <enemy> enemylist;

int main() {


	rapidxml::xml_document <> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	//Imprimir el nom del primer node i el seu valor 
	//std::cout << "Nom de l'arrel : " << doc.first_node()->name() << "\n";
	//std::cout << "Valor :" << doc.first_node()->value() << "\n";

	//definicions de nodes
	rapidxml::xml_node<>* pRoot = doc.first_node();
	rapidxml::xml_attribute<>* pAttr;

/*
	for (rapidxml::xml_node<> *pNode = pRoot->first_node("enemy"); pNode; pNode = pNode->next_sibling()) {

		std::cout << pNode->name() << ':' << '\n';
		// atributos del nodo enemy (nom)
		for (rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(); pAttr; pAttr = pAttr->next_attribute()) {
			std::cout << '-' << pAttr->name() << '-' << pAttr->value() << '\n';
		};

		for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {

			std::cout << pNodeI->name() << ':' << pNodeI->value() << '\n';

			//atributs de cada element
			for (rapidxml::xml_attribute<>* pAttr = pNode->first_attribute(); pAttr; pAttr = pAttr->next_attribute()) {
				std::cout << '-' << pAttr->name() << '-' << pAttr->value() << '\n';
			}
		}
		std::cout << '\n';
	}*/

	for (rapidxml::xml_node<>* pNode = pRoot->first_node("enemy"); pNode; pNode = pNode->next_sibling()) {
		std::cout << pNode->name() << ':' << '\n';
		// imprimir nomes x atribut
		pAttr = pNode->first_attribute("name");
		std::cout << '-' << pAttr->name() << '-' << pAttr->value() << '\n';
		std::cout << '\n';
	}



}