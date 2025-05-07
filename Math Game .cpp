#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4};
enum enOperationType {Add = 1, Sub = 2, Mul = 3, Division = 4, mix = 5};

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[10];
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	short NumberOfQuestions = 0;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPass = true;
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

int ReadHowManyQuestions()
{
	int NumberOfQuestions = 0;

	cout << "How Many Questions do you want to answer ? ";
	cin >> NumberOfQuestions;

	return NumberOfQuestions;
}

enQuestionLevel EnterOperationLevel()
{
	int QuestionLevel = 0;
	
	cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ?";
	cin >> QuestionLevel;

	return enQuestionLevel(QuestionLevel);
}

enOperationType EnterOperationType()
{
	int OperationTypeAnswer = 0;

	cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul , [4] Div, [5] Mix ";
	cin >> OperationTypeAnswer;

	return enOperationType(OperationTypeAnswer);
}

enOperationType GetRandomOperationType()
{
	return enOperationType(RandomNumber(1 , 4));
}

int SolveTheQuestion(int Num1, int Num2 , enOperationType OperationType)
{
	switch (OperationType)
	{
	case Add:
		return Num1 + Num2;
	case Sub:
		return Num1 - Num2;
	case Mul:
		return Num1 * Num2;
	case Division:
		return Num1 / Num2;
	}
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = enQuestionLevel(RandomNumber(1, 3));
	}

	if (OperationType == enOperationType::mix)
	{
		OperationType = GetRandomOperationType();
	}

	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{
	case Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SolveTheQuestion(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;

		return Question;

	case Med:
		Question.Number1 = RandomNumber(11, 50);
		Question.Number2 = RandomNumber(11, 50);

		Question.CorrectAnswer = SolveTheQuestion(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;

		return Question;

	case Hard:
		Question.Number1 = RandomNumber(51, 100);
		Question.Number2 = RandomNumber(51, 100);

		Question.CorrectAnswer = SolveTheQuestion(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;

		return Question;
	}
}

void GenerateQuizzQuestions(stQuizz &Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OperationType);
	}
}

string GetOperationString(enOperationType OperationType)
{
	string arrOperationType[5] = {"Add", "Sub", "Mul", "Div", "Mix"};
	return arrOperationType[OperationType - 1];
}

string GetLevelString(enQuestionLevel QuestionLevel)
{
	string arrQuestionsLevel[4] = { "Easy", "Med", "Hard", "Mix" };
	return arrQuestionsLevel[QuestionLevel - 1];
}

int GenerateQuestionsNumber(stQuizz &Quizz)
{
	if (Quizz.QuestionLevel == enQuestionLevel::Mix)
	{
		Quizz.QuestionLevel = enQuestionLevel(RandomNumber(1, 3));
	}

	switch (Quizz.QuestionLevel)
	{
	case Easy:
		return RandomNumber(1, 10);
		break;
	case Med:
		return RandomNumber(11, 50);
		break;
	case Hard:
		return RandomNumber(51, 100);
		break;
	}
}

int ReadQuestoinAnswer()
{
	int Number = 0;

	cin >> Number;
	return Number;
}

void PrintOperationMark(enOperationType OperationType)
{
	switch (OperationType)
	{
	case Add:
		cout << "+";
		break;
	case Sub:
		cout << "-";
		break;
	case Mul:
		cout << "*";
		break;
	case Division:
		cout << "/";
		break;
	}
}

void SetScreenColor(bool Right)
{
	switch (Right)
	{
	case true:
		system("color 2F");
		break;
	case false:
		system("color 4F");
		cout << "\a";
		break;
	}
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << endl;
	PrintOperationMark(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n___________\n\n";
}

void CorrectTheQuestionAnswer(stQuizz &Quizz , short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}
	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz &Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz , QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestoinAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
	{
		return "PASS  :-)\n";
	}
	else
	{
		return "FAIL :-(\n";
	}
}

void PrintTheFinalFormat(stQuizz& Quizz)
{
	cout << "\n\n______________________________________\n\n";
	cout << "Final   Result   Is   ";
	cout << GetFinalResultsText(Quizz.isPass);
	cout << "______________________________________\n\n";
}

void PrintQuizzResults(stQuizz Quizz)
{
	PrintTheFinalFormat(Quizz);

	cout << "Number Of Questions    : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level	    : " << GetLevelString(Quizz.QuestionLevel) << endl;
	cout << "Operation Type	        : " << GetOperationString(Quizz.OperationType) << endl;
	cout << "Number Of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "____________________________________________________________\n";
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.OperationType = EnterOperationType();
	Quizz.QuestionLevel = EnterOperationLevel();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);

	PrintQuizzResults(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}