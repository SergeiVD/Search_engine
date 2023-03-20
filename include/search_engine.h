#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "converter_json.h"
#include "search_server.h"
#include "inverted_index.h"

class SearchEngine
{
public:
    SearchEngine() = default;
    virtual ~SearchEngine();
	
	void run();

private:
	ConverterJSON* _converter{nullptr};
	SearchServer* _search_server{nullptr};
	InvertedIndex* _index{nullptr};
};


#endif /* SEARCH_ENGINE_H */
