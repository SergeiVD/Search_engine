#include "../include/search_engine.h"
#include <stdexcept>
#include <vector>
#include <exception>

void SearchEngine::run()
{
	_converter = new ConverterJSON;
	
	_index = new InvertedIndex;
	_index->UpdateDocumentBase(_converter->GetTextDocuments());

	_search_server = new SearchServer(*SearchEngine::_index);
	_search_server->SetMaxResponses(_converter->GetResponsesLimint());
	
	_converter->putAnswers(_search_server->search(_converter->GetRequests()));		
}

SearchEngine::~SearchEngine()
{
	delete _converter;
	delete _search_server;
	delete _index;
}    
