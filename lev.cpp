#include <iostream>
#include <string>
#include <vector>
#include <cmath>

int getNumber(std::string bin) {
	int number = 0;

	for (int i = 0; i < bin.length(); i++) {
		if (bin[i] == '1') {
			number += pow(2, bin.length() - 1 - i); 
		}
	}
	return number;
}
std::string getBinary(int number) {
	std::vector<bool> buff;
	if (number == 0) {
		return "0";
	}
	while (number > 0) {
		buff.push_back(number % 2);
		number /= 2;
	}
	std::string bin;
	for (int i = buff.size() - 1; i >= 0; i--) {
		bin.append(1,buff[i] == 1 ? '1' : '0');
	}
	return bin;	
}
std::vector<int> getLengthLogs(int number) {
	std::vector<int> vec;
	while (number != 0) {
		number = static_cast<int>(std::log2(number));
		vec.push_back(number);
	}
	return vec;
}
std::string encrypt(int number) {
	std::string result;
	std::vector<int> Logs = getLengthLogs(number);

	result.append(Logs.size(),'1');
	result += '0';
	for (int i = Logs.size() - 3; i >= 0; i--) {
		std::string b_len = getBinary(Logs[i]);
		b_len.erase(0,1);
		result += b_len;
	}	
	std::string bin = getBinary(number);
	bin.erase(0,1);
	result += bin;
	return result;
}
void decrypt(std::string input) {
	if (input.length() > 0) {
		if (input[0] == '0') {
			std::cout << "0" << " ";
			input.erase(0,1);
		}
		else {
			int k = 0;
			int init_len = 1;

			while (input[0] != '0') {
				k++;
				input.erase(0,1);
			}
			input.erase(0,1);
			if (k > 1) {
				for (int i = 1; i < k - 1; i++) {
					std::string len = "1" + input.substr(0,init_len);
					init_len = getNumber(len);
					input.erase(0,len.length() - 1);
				}
				std::string number = "1" + input.substr(0,init_len);
				input.erase(0, number.length() - 1);
				std::cout << getNumber(number) << " ";
			}
			else {
				std::cout << "1" << " ";
			}
		}
		decrypt(input);
	}
}
auto main(int argc, char** argv) -> int {

	if (*argv[1] == 'e') {
		std::cout << "encrypt " << argv[2] << std::endl;
		std::cout << encrypt(atoi(argv[2])) << std::endl;
	}
	else {
		std::cout << "decrypt " << argv[2] << std::endl;
		decrypt(argv[2]);
		std::cout << std::endl;
	}
	return 0;
}
