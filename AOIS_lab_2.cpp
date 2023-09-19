#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <vector>
#include <cmath>
// !((x1+x2)*!(x2*!x3))
// !((x1+x2)*(!(x2*!x3)))
// ! ( ( x1 + x2 ) *  ! ( x2 * ! x3 )  )
//     ( x1 + x2 ) *  ! ( x2 * ! x3 ) 
//     ( x1 + x2 )
//				      ! ( x2 * ! x3 ) 
//				        ( x2 * ! x3 )
//					           ! x3
class FormulaTree 
{
	class TreeElement
	{
	public:
		bool is_not = false, conjunction = false, disjunction = false;
		TreeElement* leftElement, * rightElement;
		std::string atomicFormula = "";
		void formTree(std::string data);
		int oneValue(std::vector<int> data);
	};
	TreeElement root;
	std::string inputFormula;
	std::vector<std::vector<int>> truthTable;

public:
	void createTree(std::string data);
	std::vector<std::vector<int>> formTable();
	std::string returnSKNF();
	std::string returnSDNF();
	std::string returnSKNFInBinary();
	std::string returnSDNFInBinary();
	std::string returnSKNFInDecimal();
	std::string returnSDNFInDecimal();
};

int main()
{
	std::vector<std::vector<int>> table;
	std::string input;
	FormulaTree formula;
	std::cin >> input;
	formula.createTree(input);
	table = formula.formTable();
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table.at(i).size(); j++) 
		{
			std::cout << table.at(i).at(j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << "SDNF\n" << formula.returnSDNF();
	std::cout << "\nSKNF\n" << formula.returnSKNF();
	std::cout << "\nSDNF in binary\n" << formula.returnSDNFInBinary();
	std::cout << "\nSKNF in binary\n" << formula.returnSKNFInBinary();
	std::cout << "\nSDNF in decimal\n" << formula.returnSDNFInDecimal();
	std::cout << "\nSKNF in decimal\n" << formula.returnSKNFInDecimal();
	return 1;
}


void FormulaTree::createTree(std::string data)
{
	this->inputFormula = data;

	root.formTree(data);
}

std::vector<std::vector<int>> FormulaTree::formTable()
{
	std::vector<int> bufferVector;
	for (int i = 0; i < 8; i++)
	{
		if(i == 0)
		{
			bufferVector.push_back(0);
			bufferVector.push_back(0);
			bufferVector.push_back(0);
			bufferVector.push_back(root.oneValue(bufferVector));
			this->truthTable.push_back(bufferVector);
			bufferVector.clear();
		}
		if (i == 1)
		{
			bufferVector.push_back(0);
			bufferVector.push_back(0);
			bufferVector.push_back(1);
			bufferVector.push_back(root.oneValue(bufferVector));
			this->truthTable.push_back(bufferVector);
			bufferVector.clear();
		}
		if (i == 2)
		{
			bufferVector.push_back(0);
			bufferVector.push_back(1);
			bufferVector.push_back(0);
			bufferVector.push_back(root.oneValue(bufferVector));
			this->truthTable.push_back(bufferVector);
			bufferVector.clear();
		}
		if (i == 3)
		{
			bufferVector.push_back(0);
			bufferVector.push_back(1);
			bufferVector.push_back(1);
			bufferVector.push_back(root.oneValue(bufferVector));
			this->truthTable.push_back(bufferVector);
			bufferVector.clear();
		}
		if (i == 4)
		{
			bufferVector.push_back(1);
			bufferVector.push_back(0);
			bufferVector.push_back(0);
			bufferVector.push_back(root.oneValue(bufferVector));
			this->truthTable.push_back(bufferVector);
			bufferVector.clear();
		}
		if (i == 5)
		{
			bufferVector.push_back(1);
			bufferVector.push_back(0);
			bufferVector.push_back(1);
			bufferVector.push_back(root.oneValue(bufferVector));
			this->truthTable.push_back(bufferVector);
			bufferVector.clear();
		}
		if (i == 6)
		{
			bufferVector.push_back(1);
			bufferVector.push_back(1);
			bufferVector.push_back(0);
			bufferVector.push_back(root.oneValue(bufferVector));
			this->truthTable.push_back(bufferVector);
			bufferVector.clear();
		}
		if (i == 7)
		{
			bufferVector.push_back(1);
			bufferVector.push_back(1);
			bufferVector.push_back(1);
			bufferVector.push_back(root.oneValue(bufferVector));
			this->truthTable.push_back(bufferVector);
			bufferVector.clear();
		}
	}

	return this->truthTable;
}

std::string setPartOfSDNF(std::vector<int> data)
{
	std::string result = "";
	for (int i = 0; i < 3; i++)
	{
		if (data.at(i) == 1)
		{
			result += "x" + std::to_string(i + 1);
		}
		else
		{
			result += "!x" + std::to_string(i + 1);
		}
		
	}
	return result;
}

std::string setPartOfSKNF(std::vector<int> data)
{
	std::string result = "";
	for (int i = 0; i < 3; i++)
	{
		if (data.at(i) == 1)
		{
			result += "x" + std::to_string(i + 1);
		}
		else
		{
			result += "!x" + std::to_string(i + 1);
		}
		if (i != 2)
		{
			result += " V ";
		}
		
	}
	return result;
}

std::string setPartOfSDNFInDecimal(std::vector<int> data)
{
	std::string result = "";
	for (int i = 0; i < 3; i++)
	{
		if (data.at(i) == 1)
		{
			result += "1";
		}
		else
		{
			result += "0";
		}

	}
	return result;
}

std::string setPartOfSKNFInDecimal(std::vector<int> data)
{
	std::string result = "";
	for (int i = 0; i < 3; i++)
	{
		if (data.at(i) == 1)
		{
			result += "1";
		}
		else
		{
			result += "0";
		}
		if (i != 2)
		{
			result += " V ";
		}
	}
	return result;
}

std::string FormulaTree::returnSKNF()
{
	std::string SKNF;
	for (int i = 0; i < this->truthTable.size(); i++)
	{
		
		if (this->truthTable.at(i).at(3) == 0) 
		{
			if (SKNF != "") SKNF += " * ";
			SKNF += setPartOfSKNF(this->truthTable.at(i));
		}
		else
		{
			continue;
		}
		
	}
	return SKNF;
}



std::string FormulaTree::returnSDNF()
{
	std::string SDNF;
	for (int i = 0; i < this->truthTable.size(); i++)
	{
		if (this->truthTable.at(i).at(3) == 1)
		{
			if (SDNF != "")	SDNF += " V ";
			SDNF += setPartOfSDNF(this->truthTable.at(i));
		}
		else
		{
			continue;
		}
		
	}
	return SDNF;
}

std::string FormulaTree::returnSKNFInBinary()
{
	std::string SKNF;
	for (int i = 0; i < this->truthTable.size(); i++)
	{

		if (this->truthTable.at(i).at(3) == 0)
		{
			if (SKNF != "") SKNF += " * ";
			SKNF += setPartOfSKNFInDecimal(this->truthTable.at(i));
		}
		else
		{
			continue;
		}

	}
	return SKNF;
}

std::string FormulaTree::returnSDNFInBinary()
{
	std::string SDNF;
	for (int i = 0; i < this->truthTable.size(); i++)
	{
		if (this->truthTable.at(i).at(3) == 1)
		{
			if (SDNF != "")	SDNF += " V ";
			SDNF += setPartOfSDNFInDecimal(this->truthTable.at(i));
		}
		else
		{
			continue;
		}

	}
	return SDNF;
}

std::string FormulaTree::returnSDNFInDecimal()
{
	std::string SDNF = "";
	for (int i = 0; i < this->truthTable.size(); i++)
	{
		if(this->truthTable.at(i).at(3) == 1)
		{
			if (SDNF != "") SDNF += ", ";
			SDNF += std::to_string(i);
		}
	}
	return SDNF;
}

std::string FormulaTree::returnSKNFInDecimal()
{
	std::string SDNF = "";
	for (int i = 0; i < this->truthTable.size(); i++)
	{
		if (this->truthTable.at(i).at(3) == 0)
		{
			if (SDNF != "") SDNF += ", ";
			SDNF += std::to_string(i);
		}
	}
	return SDNF;
}

int FormulaTree::TreeElement::oneValue(std::vector<int> data)
{
	int result = 0;
	if(this->conjunction)
	{
		if(leftElement->oneValue(data) == 0 or rightElement->oneValue(data) == 0)
		{
			result = 0;
		}
		else
		{
			result = 1;
		}
	}
	if(this->disjunction)
	{
		if (leftElement->oneValue(data) == 1 or rightElement->oneValue(data) == 1)
		{
			result = 1;
		}
		else
		{
			result = 0;
		}
	}
	if(atomicFormula != "")
	{
		result = data.at(static_cast<int>(atomicFormula.at(1)) - 49);
	}
	if(this->is_not)
	{
		if (result == 0)
		{
			result = 1;
		}
		else
		{
			result = 0;
		}
	}
	return result;
}

void FormulaTree::TreeElement::formTree(std::string data)
{

	int openedBracked = 0;
	for(int i = 0; i < data.size(); i++)
	{
		if (data.at(i) == '!' and openedBracked == 0)
		{
			this->is_not = true;
			data.erase(i, 1);
			i--;
			continue;
		}
		if(data.at(i) == '(')
		{
			openedBracked++;
		}
		if (data.at(i) == ')')
		{
			openedBracked--;
		}
		if (data.at(i) == '*' and openedBracked <= 1)
		{
			std::string bufferSTR = "";
			TreeElement* newElement1 = new TreeElement, * newElement2 = new TreeElement;
			this->conjunction = true;
			for (int j = 1; j < i; j++)
			{
				bufferSTR += data.at(j);
			}
			newElement1->formTree(bufferSTR);
			bufferSTR = "";
			for (int j = i + 1; j < data.size() - 1; j++)
			{
				bufferSTR += data.at(j);
			}
			newElement2->formTree(bufferSTR);
			this->leftElement = newElement1;
			this->rightElement = newElement2;
			return;
		}
		if (data.at(i) == '+' and openedBracked <= 1)
		{
			std::string bufferSTR = "";
			TreeElement* newElement1 = new TreeElement, * newElement2 = new TreeElement;
			this->disjunction = true;
			for (int j = 1; j < i; j++)
			{
				bufferSTR += data.at(j);
			}
			newElement1->formTree(bufferSTR);
			bufferSTR = "";
			for (int j = i + 1; j < data.size() - 1; j++)
			{
				bufferSTR += data.at(j);
			}
			newElement2->formTree(bufferSTR);
			this->leftElement = newElement1;
			this->rightElement = newElement2;
			return;
		}
		if ((data.at(i) != '(' or data.at(i) != ')' or data.at(i) != '*' or data.at(i) != '+' or data.at(i) != '!') and data.size() < 5)
		{
			this->atomicFormula = data;
			return;
		}
	}
	return;
}
