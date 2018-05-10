#include "Test.h"

Test createSampleTest()
{
	Test t;

	YesNoQuestion q1("Obicash li da qdesh pizza?", 30, true);

	MultipleChoice q2("Koi geroi sa ot Pod Igoto?", 35,
		std::vector<std::string>{"Rada Gospojina", "Pe6o", "Boicho Ognqnov", "Hitler"},
		std::vector<int>{0, 2});


	t.addQuestion(q1);
	t.addQuestion(q2);

	return t;
}

void test()
{
	Test t = createSampleTest();
	t.doTest();
	std::cout << "Your points are: " << t.gradeTest() << std::endl;
}

int main()
{
	test();

	return 0;
}
