/***********************************************************************
// dictionary Module
// File	dictionary.cpp
// Date	2026/01/29 
// Author Risa Hanada
***********************************************************************/
#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

namespace seneca {
    /*
    Converts a POS string from the file into a PartOfSpeech enum.
    */
	PartOfSpeech Dictionary::getPos(const std::string& pos){
		if (pos == "n." || pos == "n. pl.")
			return PartOfSpeech::Noun;
		if (pos == "adv.")
			return PartOfSpeech::Adverb;
		if (pos == "a.")
			return PartOfSpeech::Adjective;
		if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.")
			return PartOfSpeech::Verb;
		if (pos == "prep.")
			return PartOfSpeech::Preposition;
		if (pos == "pron.")
			return PartOfSpeech::Pronoun;
		if (pos == "conj.")
			return PartOfSpeech::Conjunction;
		if (pos == "interj.")
			return PartOfSpeech::Interjection;
		return PartOfSpeech::Unknown;
	}

    /*
    Initializes an empty dictionary.
    */
	Dictionary::Dictionary() {
		wordArray = nullptr;
		m_num = 0;
	}

    /*
    Loads all words from the given CSV file.
    */
	Dictionary::Dictionary(const char* filename) {
		std::ifstream fin(filename);
		std::string str, word, pos, def;
		m_num = 0;
		if (fin.is_open()) {
			while (std::getline(fin, str)) {
				m_num++;
			}
			if (m_num == 0) {
				wordArray = nullptr;
				return;
			}

			fin.clear();
			fin.seekg(0);
			wordArray = new Word[m_num];
			for (size_t i = 0; i < m_num; i++) {
				std::getline(fin, str);
				std::stringstream ss(str);
				std::getline(ss, word, ',');
				std::getline(ss, pos, ',');
				std::getline(ss, def);

				wordArray[i].m_word = word;
				wordArray[i].m_pos = getPos(pos);
				wordArray[i].m_definition = def;
			}
		}
		else {
			wordArray = nullptr;
			m_num = 0;
		}

	}

    /*
    Copy cosntructor
    */
	Dictionary::Dictionary(const Dictionary& src) {
		m_num = src.m_num;
		wordArray = new Word[m_num];
		for (size_t i = 0; i < m_num; i++) {
			wordArray[i] = src.wordArray[i];
		}
	}
    
    /*
    Copy assinement operator
    */
	Dictionary& Dictionary::operator=(const Dictionary& src) {
        if (this != &src) {
            Word* temp = new Word[src.m_num];
            for (size_t i = 0; i < src.m_num; i++) {
                temp[i] = src.wordArray[i];
            }

            delete[] wordArray;

            wordArray = temp;
            m_num = src.m_num;
        }
        return *this;
    }

    /*
    Move constructor: transfers ownership of the word array.
    */
	Dictionary::Dictionary(Dictionary&& src) noexcept {
		wordArray = src.wordArray;
		m_num = src.m_num;
		src.wordArray = nullptr;
		src.m_num = 0;
	}

    /*
    Move assignment operator: cleans up current data and takes ownership.
    */
	Dictionary& Dictionary::operator=(Dictionary&& src) noexcept {
		if (this != &src) {
            delete[] wordArray;

            wordArray = src.wordArray;
            m_num = src.m_num;

            src.wordArray = nullptr;
            src.m_num = 0;
        }
        return *this;
    }

    /*
    Releases the dynamically allocated word array.
    */
    Dictionary::~Dictionary() {
		delete[] wordArray;
	}

    /*
    Searches for a word and prints its definitions.
    */
	void Dictionary::searchWord(const char* word) {
		bool result = false;
		int len = std::string(word).length();

		for (size_t i = 0; i < m_num; i++) {
			if (wordArray[i].m_word == word) {
				if (result) {
					std::cout << std::setw(len) << ' ';
					std::cout << " - ";
				}
				else {
					std::cout << wordArray[i].m_word;
					std::cout << " - ";
					result = true;
				}
				if (g_settings.m_verbose && wordArray[i].m_pos != PartOfSpeech::Unknown) {
					std::cout << "(";
					switch (wordArray[i].m_pos) {
						case PartOfSpeech::Noun:
							std::cout << "noun";
							break;
						case PartOfSpeech::Adverb:
							std::cout << "adverb";
							break;
						case PartOfSpeech::Adjective:
							std::cout << "adjective";
							break;
						case PartOfSpeech::Verb:
							std::cout << "verb";
							break;
						case PartOfSpeech::Preposition:
							std::cout << "preposition";
							break;
						case PartOfSpeech::Pronoun:
							std::cout << "pronoun";
							break;
						case PartOfSpeech::Conjunction:
							std::cout << "conjunction";
							break;
						default:
							std::cout << "interjection";
							break;
					}
					std::cout << ") ";
				}
				std::cout << wordArray[i].m_definition << std::endl;
				if (!g_settings.m_show_all) {
					return;
				}
			}	
		}
		if (!result) {
			std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
		}
	}
}