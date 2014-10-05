#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::stoi;
using std::stack;

unsigned concatenate(unsigned x, unsigned y) {
	unsigned pow = 10;
	while (y >= pow)
		pow *= 10;
	return x * pow + y;
}

unsigned int obtain_decode_count(unsigned int number)
{
	unsigned int decode_count = 0;

	if (number < 10)
	{
		decode_count++;
		return decode_count;
	}
	else if (number <= 26)
	{
		decode_count += 2;
		return decode_count;
	}
	else if (number < 100)
	{
		decode_count++;
		return decode_count;
	}

	decode_count++;

	stack<int> digits;
	while (number != 0)
	{
		int digit = number % 10;
		digits.push(digit);
		number /= 10;
	}

	unsigned int digit_one = digits.top();
	digits.pop();
	unsigned int digit_two = digits.top();
	digits.pop();
	number = concatenate(digit_one, digit_two);

	if (number <= 26)
	{
		decode_count++;
	}

	while (!digits.empty())
	{
		digit_one = digit_two;
		digit_two = digits.top();
		digits.pop();
		number = concatenate(digit_one, digit_two);
		if (number <= 26)
		{
			decode_count++;
		}
	}

	return decode_count;
}
int main(int argc, char *argv[])
{
	string input_file;

	// Check first argument if it exists for input file, otherwise ask user
	if (argc > 1)
	{
		input_file = argv[1];
	}
	else
	{
		cout << "Please enter the path to your input file: " << endl;
		cin >> input_file;
	}

	// Open input file and check if successfully opened
	ifstream ifs(input_file);
	if (!ifs)
	{
		cout << "Failed to open input file." << endl;
		return 1;
	}

	string line;
	while (getline(ifs, line))
	{
		if (line == "" || line == "0")
		{
			continue;
		}
		unsigned int number = stoi(line);
		unsigned int decode_count = obtain_decode_count(number);
		cout << decode_count << endl;
	}
	return 0;
}