#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <cstddef>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <memory>

#include "../include/utils.h"

struct Entry
{
	/** номер элемента в векторе docs по которому хранится текст.*/
    size_t doc_id;
	/** число, которое обозначает, сколько раз ключевае слово встретилось в документе doc_id. */    
    size_t count;
	/** Оператор для проведения тестовых сценариев */
	bool operator == (const Entry& other) const
		{
			return (doc_id == other.doc_id && count == other.count );
		}
};

class InvertedIndex
{
public:
    InvertedIndex();

    virtual ~InvertedIndex();

	/**
	 * Обновить или заполнить базу документов, по которой будем совершать поиск
	 * @param texts_input содержимое документов
	 */
	void UpdateDocumentBase(std::vector<std::string> input_docs);

	/** Метод определяет количество вхождений слова word в загруженной базе документов
	 * @param word слово, частоту вхождений которого необходимо определить
	 * @return возвращает подготовленный список с частотой слов
	 */
	std::vector<Entry> GetWordCount(const std::string& word);

	/**
	 * Функция просмотра частотного словаря (для отладки)
	 */
	void list_freq_dictionary();
	
	
 private:
   /**
    * Функция создает для каждого слова коллекции вектор структур Entry
    * @param word слово частоту вхождений которого необходимо определить
	* @return список с частотой вхождения слова в коллекцию документов docs
	 */
	std::vector<Entry> index_word(const std::string& word);

	/**
	 * Функция разбиения входного документа на отдельные слова и определения вхождения каждого слова в документ
	 * @param документ коллекции
	 */        
	void process_document(const std::string& document);

	/**
	 * Функция добавления элементов в частотный словарь
	 * @param word - слово
	 * @param vec_entry_for_word - список вхождений слова word в докумет
	 */
	void AddWordToFreqDictionary(const std::string& word, const std::vector<Entry>& vec_entry_for_word);

	/**
	 * Коллекция документов, в которой номер элемента в векторе определяет doc_id
	 * для формирования результата запроса,
	 * сам элемент это текст документа
	 */
	std::vector<std::string> docs;

	/**
	 * Частотный словарь - это коллекция для хранения частоты слов, встречаемых в тексте.
	 */
	std::map<std::string, std::vector<Entry>> freq_dictionary;

};




#endif /* INVERTED_INDEX_H */
