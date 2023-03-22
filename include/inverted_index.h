#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <vector>
#include <string>
#include <map>

#include "../include/utils.h"

struct Entry
{
	/** the number of the element in the docs vector by which the text is stored.*/
    size_t doc_id;
	/** a number that indicates the number of times the keyword occurs in the doc_id document. */    
    size_t count;
	/** Operator for carrying out test scenarios */
	bool operator == (const Entry& other) const
		{
			return (doc_id == other.doc_id && count == other.count );
		}
};

class InvertedIndex
{
public:
    InvertedIndex();

    virtual ~InvertedIndex();

	/**
	 * Update or fill in the database of documents on which we will search
	 * @param texts_input document content
	 */
	void UpdateDocumentBase(std::vector<std::string> input_docs);

	/** The method determines the number of occurrences of the word word in the loaded document base
	 * @param word - is a word whose occurrence frequency is to be determined
	 * @return returns a prepared list with word frequency
	 */
	std::vector<Entry> GetWordCount(const std::string& word);

	/**
	 * Frequency dictionary browsing function (for debugging)
	 */
	void list_freq_dictionary();
	
	
 private:
   /**
    * The function creates a vector of Entry structures for each word in the collection.
    * @param word -  word whose occurrence frequency is to be determined
	* @return a list with the frequency of occurrence of a word in a collection of docs documents
	 */
	std::vector<Entry> index_word(const std::string& word);

	/**
	 * The function of splitting the input document into separate words and determining the occurrence of each word in the document
	 * @param collection document
	 */        
	void process_document(const std::string& document);

	/**
	 * The function of adding elements to the frequency dictionary
	 * @param word - word
	 * @param vec_entry_for_word - list of occurrences of the word word in the document
	 */
	void AddWordToFreqDictionary(const std::string& word, const std::vector<Entry>& vec_entry_for_word);

	/**
	 * A collection of documents where the element number in the vector specifies doc_id
	 * to generate the query result,
	 * the element itself is the text of the document
	 */
	std::vector<std::string> docs;

	/**
	 * A frequency dictionary is a collection for storing the frequency of words found in a text.
	 */
	std::map<std::string, std::vector<Entry>> freq_dictionary;

};




#endif /* INVERTED_INDEX_H */
