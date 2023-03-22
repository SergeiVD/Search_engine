#ifndef SEARCH_SERVER_H
#define SEARCH_SERVER_H


#include <string>
#include <vector>

#include "../include/inverted_index.h"
#include "../include/converter_json.h"

struct RelativeIndex
{
    size_t doc_id;
	float rank;

	bool operator == (const RelativeIndex& other)const
		{
			return (doc_id == other.doc_id && rank == other.rank);
		}
};

class SearchServer
{
public:

	/**
	 * @param idx a reference to the Invertedindex class is passed to the class constructor
	 * so that Searchserver can find out the frequency of words found in the query
	 */
    SearchServer(InvertedIndex& idx) : _index(idx) {};
	
    virtual ~SearchServer() = default;

    /**
	 * Search query processing method
	 * @param queries_input search queries taken from the requests.json file
	 * @return returns a sorted list of relevant responses for given queries
	 */
	std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

	/**
	 * Method for setting the maximum number of responses per request
	 */
	void SetMaxResponses(const int& max_responses);

private:
  /**
   * Internal method for getting unique query words
   * @param queri - search query
   * return - list of unique query words
   */
	std::vector<std::string> unique_queri_words(const std::string& queri);

	/**
	 * Internal Method for Calculating Query Relevance
	 * @param entries - list of inverted indices of search query words
	 * @return - query relevance list
	 */
	std::vector<RelativeIndex> compute_relative(const std::vector<Entry>& entries);

	/** Maximum number of responses to search queries*/
	unsigned int _max_responses{5};

	/** Inverted Index*/
	InvertedIndex _index;

};



#endif /* SEARCH_SERVER_H */
