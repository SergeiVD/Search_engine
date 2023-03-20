#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>

#include <thread>
#include <iostream>

namespace utils
{
	/**
	 * Функция разделения строки на отдельные слова
	 * @param input_docs строка содержащая текст документа
	 * @return std::vector<std::string> - вектор отдельных слов
	 */

	std::vector<std::string> doc_to_word(const std::string& input_doc);

	/**
	 * Вспомогательная функция для подсчета колличества слов встречающихся в тексте
	 * @return - колличество совпадений слова word в тексте text    
	 */

	size_t word_counter(const std::string& text, const std::string& word);

}

#endif /* UTILS_H */
