#include <iostream>
#include <fstream>
#include <algorithm>

// Address решил объ€вить как структуру, потому что она не нуждаетс€ в скрытии реализации и у неЄ всего 1 метод
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

// »нкапсул€ци€ про€вл€етс€ в данном классе, который полностью скрывает свою реализацию
// и предоставл€ет пользователю ограниченный интерфейс дл€ взаимодействи€ с логикой класса
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

// ‘ункци€ main лишь пользуетс€ интерфейсом созданного нами класса
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