#ifndef SEARCH_SERVER_H
#define SEARCH_SERVER_H

#include <iostream>
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
	 * @param idx в конструктор класса передается ссылка на класс Invertedindex
	 * чтобы Searchserver мог узнать частоту слов встречаемых в запросе
	 */
    SearchServer(InvertedIndex& idx) : _index(idx) {};
	
    virtual ~SearchServer() = default;

    /**
	 * Метод обработки поисковых запросов
	 * @param queries_input поисковые запросы взятые из файлаrequests.json
	 * @return возвращает отсортированный список релевантных ответов для заданных запросов
	 */
	std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

	/**
	 * Метод установки максимального колличества ответов на один запросе
	 */
	void SetMaxResponses(const int& max_responses);

private:
  /**
   * Внутренний метод получения уникальных слов запроса
   * @param queri - поисковый запрос
   * return - список уникальных слов запроса
   */
	std::vector<std::string> unique_queri_words(const std::string& queri);

	/**
	 * Внутренний метод расчета релевантности запроса
	 * @param entries - список инвертированных индексов слов поискового запроса
	 * @return - список релевантности запроса
	 */
	std::vector<RelativeIndex> compute_relative(const std::vector<Entry>& entries);

	/** Максимальное колличество ответов на поисковые запросы*/
	unsigned int _max_responses{5};

	/** Инвертированный индекс*/
	InvertedIndex _index;

};



#endif /* SEARCH_SERVER_H */
