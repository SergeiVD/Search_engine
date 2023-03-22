#include "../include/converter_json.h"
#include "../include/search_server.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <iostream>

ConverterJSON::~ConverterJSON() {}

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
	nlohmann::json data = load_config(m_valid_key);

	std::vector<std::string> vec_text_docum;
	
	if(data.contains("files"))
	{
		vec_text_docum.resize(data["files"].size());
		for(int i = 0; i < data["files"].size(); ++i)
		{
			vec_text_docum.at(i) = load_text_file(data["files"].at(i));
		}
	}
	
	return vec_text_docum;
}

int ConverterJSON::GetResponsesLimint()
{
	nlohmann::json data = load_config(m_valid_key);
	if(data["config"].contains("max_responses")) return  data["config"]["max_responses"].get<int>();

	return -1;
}

std::string ConverterJSON::GetNameSearchEngine()
{
	nlohmann::json data = load_config(m_valid_key);
	if(data["config"].contains("name")) return data["config"]["name"].get<std::string>();
	return {};
}

std::string ConverterJSON::GetVersionSearchEngine()
{
	nlohmann::json data = load_config(m_valid_key);
	if(data["config"].contains("version")) return data["config"]["version"].get<std::string>();
	return {};
}

std::vector<std::string> ConverterJSON::GetRequests()
{
	std::string file_path_requests{"../json/requests.json"};
	std::ifstream f(file_path_requests);
	if(!f)
	{
		throw std::runtime_error("No open requests file " + file_path_requests);
	}

	nlohmann::json requests_data = nlohmann::json::parse(f);
	if(!requests_data.contains("requests"))
	{
		throw std::runtime_error("Error requests file " + file_path_requests);
	}
	
	std::vector<std::string> requests(requests_data["requests"].size());
	for (int i = 0; i < requests_data["requests"].size(); ++i)
	{
		requests.at(i) = requests_data["requests"].at(i);
	}
	return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers)
{
	if(answers.size() != GetRequests().size()) throw std::runtime_error("Error!!! Requests size no equal answers size!");

	std::string file_path_answers{"../json/answers.json"};
	std::ofstream ofs(file_path_answers, std::ios::out);
	if(!ofs)throw "No create file " + file_path_answers;

	nlohmann::json j_answers;
	j_answers["answers"];

	for (size_t i = 0; i < answers.size(); ++i)
	{
		if(answers.at(i).empty())
		{
			j_answers["answers"][create_request_name(i+1)]["result"] = false;
			continue;
		}
		else
		{
			j_answers["answers"][create_request_name(i+1)]["result"] = true;
			if(answers.at(i).size() > 1)
			{
				for (int j = 0; j < answers.at(i).size(); ++j)
				{
					j_answers["answers"][create_request_name(i+1)]["relevance"][std::to_string(answers.at(i).at(j).doc_id)] = answers.at(i).at(j).rank;
				}
			}
			else
			{
				j_answers["answers"][create_request_name(i+1)][std::to_string(answers.at(i).at(0).doc_id)] = answers.at(i).at(0).rank;				
			}
		}
	}

	ofs<<j_answers.dump(4);
}

nlohmann::json ConverterJSON::load_config(const std::string& valid_key)
{
	std::ifstream f("../json/config.json");
	if(!f) throw std::runtime_error("Error! Confir file is missing!");
	nlohmann::json data = nlohmann::json::parse(f);
	if(!data.contains(valid_key)) throw std::runtime_error("config file is empty");

	return data;
}

std::string ConverterJSON::load_text_file(const std::string& file_path)
{
	std::ifstream ifs(file_path);
	if(!ifs)
	{
		std::cout<<std::string{"File "+ file_path + " not found!"}<<std::endl;
		return {};
	}
	std::ostringstream ss;
	ss<<ifs.rdbuf();
	
	return ss.str();
}

std::string ConverterJSON::create_request_name(const int& num_request)
{	
	std::stringstream ss;
	ss<<std::setw(3)<<std::setfill('0')<<num_request;
	return std::string{"request"} + ss.str();
}

