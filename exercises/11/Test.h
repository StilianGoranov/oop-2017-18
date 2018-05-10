#ifndef _TEST_H
#define _TEST_H

#include "Question.h"

class Test
{
private:
	std::vector<Question*> questions;

	void copy(Test const& other)
	{
		for (Question* question : other.questions)
			questions.push_back(question->clone());
	}

	void clear()
	{
		for (Question* question : questions)
			delete question;
	}

public:
	Test()
	{}

	Test(Test const& other)
	{
		copy(other);
	}

	Test& operator=(Test const& other)
	{
		if (this != &other)
		{
			clear();
			copy(other);
		}

		return *this;
	}

	~Test()
	{
		clear();
	}

	void addQuestion(Question const& newQuestion)
	{
		questions.push_back(newQuestion.clone());
	}

	void doTest()
	{
		for (Question* question : questions)
			question->ask();
	}

	int gradeTest() const
	{
		int result = 0;
		for (Question* question : questions)
			result += question->grade();

		return result;
	}

};

#endif 
