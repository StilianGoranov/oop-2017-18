#ifndef _QUESTION_H
#define _QUESTION_H

#include <string>
#include <iostream>
#include <vector>

class Question
{
protected:
	std::string text;
	int points;

public:
	Question(std::string const& _text, int _points)
		: text{ _text }, points{ _points }
	{}

	virtual void ask() = 0;
	virtual int grade() const = 0;
	virtual Question* clone() const = 0;
};

class YesNoQuestion : public Question
{
private:
	bool const answer;
	bool answerFromUser;

public:
	YesNoQuestion(std::string const& _text, int _points, bool _answer)
		: answer{ _answer }, Question(_text, _points)
	{}

	virtual Question* clone() const override
	{
		return new YesNoQuestion(*this);
	}

	virtual void ask() override
	{
		std::cout << text << std::endl;
		std::cout << "Answer with Y or N: ";

		char a;
		do
		{
			std::cin >> a;
		} while (a != 'Y' && a != 'N');

		switch (a)
		{
		case 'Y': answerFromUser = true; break;
		case 'N': answerFromUser = false; break;
		}
	}

	virtual int grade() const override
	{
		return answer == answerFromUser ? points : 0;
	}
};

class MultipleChoice : public Question
{
private:
	std::vector<std::string> possibleAnswers;
	std::vector<int> rightAnswers;
	std::vector<int> answersFromUser;

	virtual Question* clone() const override
	{
		return new MultipleChoice(*this);
	}

	bool indexIsCorrect(int index) const
	{
		return index >= 0 && index < possibleAnswers.size();
	}

	bool member(std::vector<int> const& v, int x) const
	{
		for (auto const& elem : v)
			if (elem == x)
				return true;

		return false;
	}

public:
	MultipleChoice(std::string const& _text, int _points,
		std::vector<std::string> const& _possibleAnswers, std::vector<int> const& _rightAnswers)
		: Question(_text, _points), possibleAnswers{ _possibleAnswers }, rightAnswers{ _rightAnswers }
	{}

	virtual void ask() override
	{
		std::cout << text << std::endl;
		std::cout << "Possible answers: \n";
		int n = 0;
		for (auto const& possibleAnswer : possibleAnswers)
			std::cout << n++ << ": " << possibleAnswer << std::endl;

		int answerFromUser;
		std::cout << "Enter -1 to stop answering\n";
		do
		{
			std::cin >> answerFromUser;
			if (!indexIsCorrect(answerFromUser))
			{
				if (answerFromUser != -1)
					std::cout << "Invalid answer! Answer again.\n";
			}
			else if (member(answersFromUser, answerFromUser))
				std::cout << "Already in answers!" << std::endl;
			else answersFromUser.push_back(answerFromUser);

		} while (answerFromUser != -1);
	}

	virtual int grade() const override
	{
		int result{ 0 };
		for (auto const& answer : answersFromUser)
		{
			if (member(rightAnswers, answer))
				result += points;
			else
				result -= points;
		}
			
		return result;
	}

};

#endif 
