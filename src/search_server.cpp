#include "../include/search_server.h"

#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include <map>
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


















// std::vector<std::vector<std::string>> SearchServer::requests_result(const std::vector<std::string>& queri_input)
// {
// 	std::vector<std::vector<std::string>> requests(queri_input.size());

// 	for (size_t i = 0; i < queri_input.size(); ++i)
// 	{
// 		std::vector<std::string> u_queri_words{unique_queri_words(queri_input.at(i))};
		
// 		for(const auto& word : u_queri_words)
// 		{		
// 			for(auto& entry : _index.GetWordCount(word))
// 			{
// 				requests.at(i).push_back(word);
// 			}								
// 		}
// 	}
// 	return requests;
// }



// std::map<std::string, std::vector<Entry>> frequnecy;


// std::vector<std::vector<std::string>> requests(requests_result(queries_input));


	// requests = requests_result(queries_input);
	
	// for(auto& result : queri_results)
	// {
	// 	std::sort(result.begin(),result.end(),[](const Entry& l_entry, const Entry& r_entry)
	// 		{
	// 			return l_entry.count > r_entry.count;
	// 		});
	// }

	
	// for(size_t i = 0; i < requests.size(); ++i)
	// {
	// 	for (size_t j = 0; j < requests.at(i).size(); ++j)
	// 	{
	// 		frequnecy.insert({requests.at(i).at(j), _index.GetWordCount(requests.at(i).at(j))});
	// 	}

	// }
	
	// for(const auto& element : frequnecy)
	// {
	// 	std::cout<<element.first<<":"<<std::endl;
	// 	for(const auto& elem : element.second)
	// 	{
	// 		std::cout<<elem.doc_id<<" : "<<elem.count<<std::endl;
	// 	}
	// }

	// for(size_t i = 0; i < queri_results.size(); ++i)
	// {
		// for (size_t j = 0; j < queri_results.at(i).size(); ++j)
		// {
			// if(queri_results.at(i).empty())
			// {
			// 	std::cout<<"false"<<std::endl;
			// 	// continue;
			// }
			// std::cout<<"request "<<i<<" word: "<<requests.at(i).at(j)<<" doc_id: "<<queri_results.at(i).at(j).doc_id<<" count: " <<queri_results.at(i).at(j).count<<std::endl;
			// std::cout<<"request "<<i<<" doc_id: "<<queri_results.at(i).at(j).doc_id<<" count: " <<queri_results.at(i).at(j).count<<std::endl;
		// }

	// }


