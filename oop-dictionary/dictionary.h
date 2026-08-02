/***********************************************************************
// dictionary Module
// File	dictionary.h
// Date	2026/01/29 
// Author Risa Hanada
//
// Declares the Dictionary class and related types used to store
// and search word definitions loaded from a CSV dictionary file.
//
// Responsibilities:
// - Load dictionary entries from a CSV file
// - Store them in a dynamic array
// - Search for words and print definitions
***********************************************************************/
#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H
#include <string>
#include <iostream>

namespace seneca {

    // represents the part of speech for a word
	enum class PartOfSpeech
	{
		Unknown,
		Noun,
		Pronoun,
		Adjective,
		Adverb,
		Verb,
		Preposition,
		Conjunction,
		Interjection,
	};

    // represents a single dictionary entry
	struct Word
	{
		std::string m_word{}; // the word itself
		std::string m_definition{}; // its definition
		PartOfSpeech m_pos = PartOfSpeech::Unknown; // part of speech
	};

	class Dictionary {
		Word* wordArray; // pointer to dynamic array of words
		size_t m_num; // number of loaded words

        // converts a POS string from the file into a PartOfSpeech enum
		PartOfSpeech getPos(const std::string& pos);
	public:
        // constructors
		Dictionary();
        Dictionary(const char* filename);

        // copy operations 
        Dictionary(const Dictionary& src);
		Dictionary& operator=(const Dictionary& src);

        // move operations
		Dictionary(Dictionary&& src) noexcept;
		Dictionary& operator=(Dictionary&& src) noexcept;

        // destructor
		~Dictionary();

        // searches for a word and prints its definitions
		void searchWord(const char* word);
	};
}

#endif