#include "../include/utils.h"
#include <cstddef>
#include <thread>

namespace utils
{	
	std::vector<std::string> doc_to_word(const std::string& input_doc)
	{
		std::vector<std::string> words_from_doc;
		std::istringstream iss(input_doc);
		if(!iss)throw std::runtime_error("Error!!! No read input document: " + std::string(input_doc));
	
		std::string word;

		while (iss >> word)
		{
			while (std::ispunct(word.back()))
			{
				// Удаляем знаки препинания в конце слова
				word.pop_back();
			}
		
			// Удаляем знаки препинания в начале слова
			while (!word.empty() && std::ispunct(word.front()))
			{
				word.erase(0,1);
			}
		
			words_from_doc.push_back(word);
		}

		return words_from_doc;
	}

	size_t word_counter(const std::string& text, const std::string& word)
	{
		std::istringstream iss(text);
		if(!iss)throw std::runtime_error("Error!!! no read text for word counted");
		std::string t_word;
		int count{0};
		while (iss >> t_word)
		{
			while (std::ispunct(word.back()))
			{
				// Удаляем знаки препинания в конце слова
				t_word.pop_back();
			}
		
			// Удаляем знаки препинания в начале слова
			while (!word.empty() && std::ispunct(word.front()))
			{
				t_word.erase(0,1);
			}
		
			if(word == t_word) ++count;
		}
		return count;
	}



}    // end utils

