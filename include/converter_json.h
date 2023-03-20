#ifndef CONVERTER_JSON_H
#define CONVERTER_JSON_H

/**
 *  Класс для работы с JSON-файлами
*/


#include <nlohmann/json.hpp>
#include <utility>
#include <vector>
#include <string>

struct RelativeIndex;

class ConverterJSON
{
public:
   ConverterJSON() = default;
   virtual ~ConverterJSON();

   /**
    * Метод получения содержимого файла
    * @return Возвращает список с содержимом файлов перечисленных в config.json
    */
   std::vector<std::string> GetTextDocuments();

   /**
    * Метод считывает поле max_responses для определения предельного колличества
    * ответов на один запрос
    * @return
	*/
   int GetResponsesLimint();

   /**
	* Метод считывает поле name из файла config.json
	*/
	std::string GetNameSearchEngine();

	/**
	 * Метод считывает поле version из файла config.json
	 */
	std::string GetVersionSearchEngine();

   /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
   std::vector<std::string> GetRequests();

   /**
    * Положить в файл answers.json результаты поисковых запросов
    */
	void putAnswers(std::vector<std::vector<RelativeIndex>> answers);
   
   private:
	nlohmann::json load_config(const std::string& valid_key);
	std::string load_text_file(const std::string& file_path);
	std::string create_request_name(const int& num_request);

	std::string m_valid_key{"config"};
};



#endif /* CONVERTER_JSON_H */
