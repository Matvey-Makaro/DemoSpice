#pragma once
#include<iostream>
template<typename T>
void correctInput(T& value)
{
	std::cin >> value;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "�������� ����. ���������� ��� ���: ";
		std::cin >> value;
	}
}