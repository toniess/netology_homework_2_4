#include <iostream>
#include <fstream>
#include <algorithm>

// Address ����� �������� ��� ���������, ������ ��� ��� �� ��������� � ������� ���������� � � �� ����� 1 �����
struct Address
{
	std::string city;
	std::string street;
	std::string bilding;
	std::string flat;

	std::string format()
	{
		return city + ", " + street + ", " + bilding + ", " + flat;
	}
};

// ������������ ����������� � ������ ������, ������� ��������� �������� ���� ����������
// � ������������� ������������ ������������ ��������� ��� �������������� � ������� ������
class AddressFormatter
{
private:
	Address* adr;
	int count;
public:
	bool load(std::string filename)
	{
		std::ifstream file;
		file.open(filename);
		if (!file.is_open())
		{
			return false;
		}
		file >> count;
		adr = new Address[count];
		for (int i = 0; i < count; ++i)
		{
			file >> adr[i].city;
			file >> adr[i].street;
			file >> adr[i].bilding;
			file >> adr[i].flat;
		}
		return true;
	}

	bool sortAndSaveFormatted(std::string filename)
	{
		std::ofstream file;
		file.open(filename);
		if (!file.is_open())
		{
			return false;
		}
		std::sort(adr, adr + count, [](Address& a, Address& b) {
			return a.city > b.city;
			});
		file << count << '\n';
		for (int i = count - 1; i >= 0; --i)
		{
			file << adr[i].format() << '\n';
		}
		return true;
	}

	~AddressFormatter()
	{
		delete[] adr;
	}
};

// ������� main ���� ���������� ����������� ���������� ���� ������
int main()
{
	AddressFormatter af;
	if (!af.load("in.txt"))
	{
		std::cout << "Fail to load the file!" << std::endl;
		return 0;
	}
	if (!af.sortAndSaveFormatted("out.txt"))
	{
		std::cout << "Fail to save the file!" << std::endl;
		return 0;
	}
	std::cout << "Data is successfuly formatted and saved!";
}