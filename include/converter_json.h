#ifndef CONVERTER_JSON_H
#define CONVERTER_JSON_H

/**
 * Class for working with JSON files
*/

#include <nlohmann/json.hpp>
#include <vector>
#include <string>

struct RelativeIndex;

class ConverterJSON
{
public:
   ConverterJSON() = default;
   virtual ~ConverterJSON();

   /**
    * Method for getting file content
    * @return Returns a list with the contents of the files listed in config.json
    */
   std::vector<std::string> GetTextDocuments();

   /**
    * The method reads the max_responses field to determine the limit
    * @return responses to one request
	*/
   int GetResponsesLimint();

   /**
	* The method reads the name field from the config.json file
	*/
	std::string GetNameSearchEngine();

	/**
	 * The method reads the version field from the config.json file
	 */
	std::string GetVersionSearchEngine();

   /**
    * Method for receiving requests from the requests.json file
    * @return returns a list of requests from the requests.json file
    */
   std::vector<std::string> GetRequests();

   /**
    * Put search results in answers.json file
    */
	void putAnswers(std::vector<std::vector<RelativeIndex>> answers);
   
   private:
	nlohmann::json load_config(const std::string& valid_key);
	std::string load_text_file(const std::string& file_path);
	std::string create_request_name(const int& num_request);

	std::string m_valid_key{"config"};
};



#endif /* CONVERTER_JSON_H */
