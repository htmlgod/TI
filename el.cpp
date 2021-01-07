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

std::string encrypt(int number) {
	std::string bin = getBinary(number);
	std::string bin_len = getBinary(bin.length());

	std::string el;
	el.append(bin_len.length() - 1, '0');
	el.append(bin_len);
	el.append(bin,1,bin.length()); 
	
	return el;
}
void decrypt(std::string input) {
	if (input.length() > 0) {
		if (input[0] == '1') {
			if (input[1] == '1') {
				std::cout << "1" << " ";
			}	
			else {
				std::cout << "0" << " ";
			}
			input.erase(0,2);
		}
		else {
			int bin_len_len = 0;
			while (input[0] == '0') {
				bin_len_len++;
				input.erase(0,1);
			}

			std::string bin_len = input.substr(0, ++bin_len_len);
			input.erase(0, bin_len.length());

			int len = getNumber(bin_len);
			std::string number = "1";
			number += input.substr(0, len - 1);
			std::cout << getNumber(number) << " ";
			input.erase(0,number.length() - 1);
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
