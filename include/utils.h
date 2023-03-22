#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

namespace utils
{
	/**
	 * Function to split a string into separate words
	 * @param input_docs a string containing the text of the document
	 * @return std::vector<std::string> - isolated word vector
	 */
	std::vector<std::string> doc_to_word(const std::string& input_doc);

	/**
	 * Helper function for counting the number of words found in a text
	 * @return - number of matches of the word word in the text text
	 */
	size_t word_counter(const std::string& text, const std::string& word);

}

#endif /* UTILS_H */
