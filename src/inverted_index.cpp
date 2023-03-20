#include "../include/inverted_index.h"

#include <iostream>
#include <iterator>
#include <mutex>

#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

#include <thread>
#include <future>
#include <algorithm>


InvertedIndex::InvertedIndex()
{	
}    

InvertedIndex::~InvertedIndex()
{
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
	docs = std::move(input_docs);
	freq_dictionary.clear();

	std::vector<std::thread> v_threads;

	for (size_t i = 0; i < docs.size(); ++i)
	{
		v_threads.push_back(std::thread(&InvertedIndex::process_document,this, docs.at(i)));
	}

	for(auto& thread : v_threads)
	{
		thread.join();
	}	
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word)
{	
	if(freq_dictionary.count(word)) return freq_dictionary.at(word);

	return std::vector<Entry>();
}

std::vector<Entry> InvertedIndex::index_word(const std::string& word)
{
	std::vector<Entry> vec_entry;

	for (size_t i = 0; i < docs.size(); ++i)
	{
		if(utils::word_counter(docs.at(i), word))
		{
			vec_entry.push_back({i, utils::word_counter(docs.at(i), word)});
		}
	}

	return vec_entry;	
}

void InvertedIndex::process_document(const std::string& document)
{
	for (size_t i = 0; i < utils::doc_to_word(document).size(); ++i)
	{
		AddWordToFreqDictionary(utils::doc_to_word(document).at(i), index_word(utils::doc_to_word(document).at(i)));
	}
}

void InvertedIndex::list_freq_dictionary()
{
	for(std::map<std::string,std::vector<Entry>>::iterator it = freq_dictionary.begin(); it != freq_dictionary.end(); ++it)
	{
		std::cout<<it->first<<":"<<std::endl;
		for(const auto& element : it->second)
		{
			std::cout<<"doc_id: "<<element.doc_id<<" count: "<< element.count<<std::endl;
		}
	}
}

void InvertedIndex::AddWordToFreqDictionary(const std::string& word, const std::vector<Entry>& vec_entry_for_word)
{
	static std::mutex _mutex;
	std::lock_guard<std::mutex>lg(_mutex);
	freq_dictionary.insert({word, vec_entry_for_word});
}


