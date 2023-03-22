#include "../include/search_server.h"

#include <iostream>
#include <numeric>
#include <set>
#include <algorithm>


std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input)
{
	std::vector<std::vector<Entry>> queri_results(queries_input.size());

	std::vector<std::vector<RelativeIndex>> relative_indexes(queri_results.size());	

	for (size_t i = 0; i < queries_input.size(); ++i)
	{
		std::vector<std::string> u_queri_words{unique_queri_words(queries_input.at(i))};
		
		for(const auto& word : u_queri_words)
		{		
			std::vector<Entry> entries = _index.GetWordCount(word);
			for(auto& entry : entries)
			{
				queri_results.at(i).push_back(entry);
			}								
		}

		if(compute_relative(queri_results.at(i)).size() <= _max_responses)
		{
			relative_indexes.at(i) = compute_relative(queri_results.at(i));			
		}
		else
		{
			std::vector<RelativeIndex> max_respons_relativ(_max_responses);
			for (size_t j = 0; j < _max_responses; ++j)
			{
				max_respons_relativ.at(j) = compute_relative(queri_results.at(i)).at(j);
			}

			relative_indexes.at(i) = std::move(max_respons_relativ);
		}

	}
	
	return relative_indexes;	
}

void SearchServer::SetMaxResponses(const int& max_responses)
{
	_max_responses = max_responses;
}


std::vector<std::string> SearchServer::unique_queri_words(const std::string& queri)
{
	std::vector<std::string> unique_queri_words;
	std::set<std::string> unique_words;
	
	for (size_t i = 0; i < utils::doc_to_word(queri).size(); ++i)
	{
		unique_words.insert(utils::doc_to_word(queri).at(i));
	}

	unique_queri_words.assign(unique_words.begin(),unique_words.end());
	
	return unique_queri_words;
}

std::vector<RelativeIndex> SearchServer::compute_relative(const std::vector<Entry>& entries)
{
	std::vector<RelativeIndex> relative;

	float abs_relative{0};
	unsigned int max_abs_relative{0};

	std::set<size_t> documents_id;
	
	for (size_t i = 1; i < entries.size(); ++i)
	{
		documents_id.insert(entries.at(i).doc_id);
	}
	
	for(const auto& doc_id : documents_id)
	{
		abs_relative = 0;
		for (size_t i = 0; i < entries.size(); ++i)
		{
			if(entries.at(i).doc_id == doc_id)
			{
				abs_relative += entries.at(i).count;
			}
		}
		
		if(max_abs_relative < abs_relative) max_abs_relative = abs_relative;
	}
	
	for(const auto& doc_id : documents_id)
	{
		abs_relative = 0;
		for (size_t i = 0; i < entries.size(); ++i)
		{
			if(entries.at(i).doc_id == doc_id)
			{
				abs_relative += entries.at(i).count;
			}
		}

		relative.push_back({doc_id, (abs_relative / max_abs_relative)});
	}

	std::sort(relative.begin(), relative.end(),[](const RelativeIndex& l_entry, const RelativeIndex& r_entry)
		{
			if(l_entry.rank != r_entry.rank)
			{
				return l_entry.rank > r_entry.rank;				
			}
			else
			{
				return l_entry.doc_id < r_entry.doc_id;
			}
		});

	return relative;
}
