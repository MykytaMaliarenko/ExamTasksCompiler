//
// Created by Mykyta Maliarenko on 13.05.2020.
//

#include "questions_compiler.h"
#include "linked_list.h"

long long int factorial(int n)
{
    long long int res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

long long int calculateMaxNumberOfCombinations(int n, int k)
{
    long long int maxNumOfCombinations = factorial(n);
    maxNumOfCombinations /= factorial(k);
    maxNumOfCombinations /= factorial(n - k);
    return maxNumOfCombinations;
}

void combinationUtil(LinkedList* res, LinkedList* currentCombination,
                     Questions questions, int questionsCurrentIndex,
                     int numberOfQuestionsInExamPaper);

void removeRedundantCombinations(LinkedList* allCombinations, int numberOfRequiredCombinations);

int sortByTotalLevelOfDifficulty(LinkedListNode* a, LinkedListNode* b);


bool canQuestionsBeCompiled(Questions questions, int numberOfExamPapers, int numberOfQuestionsInExamPaper)
{
    if (questions->size <= numberOfQuestionsInExamPaper)
        return false;

    if (calculateMaxNumberOfCombinations(questions->size, numberOfQuestionsInExamPaper) < numberOfExamPapers)
        return false;

    return true;
}

ExamPapers compileQuestions(Questions questions, int numberOfExamPapers, int numberOfQuestionsInExamPaper)
{
    LinkedList* rawRes = createList();
    combinationUtil(rawRes, NULL, questions, 0, numberOfQuestionsInExamPaper);
    removeRedundantCombinations(rawRes, numberOfExamPapers);

    ExamPapers examPapers = createExamPapers();
    for (int i = 0;i < rawRes->size; i++)
    {
        LinkedList* current = listGet(rawRes, i);
        ExamPaperPtr examPaper = createExamPaper();
        for (int j = 0; j < current->size; j++)
        {
            QuestionPtr questionPtr = listGet(current, j);
            examPaperAddQuestionId(examPaper, questionGetId(questionPtr));
        }

        listAdd(examPapers, examPaper);
    }

    return examPapers;
}

/**
 * @brief All possible combinations of questions without repetitions.
 *
 * @param res linked list of linked lists in which all possible combinations of QuestionPtr will be written.
 * @param currentCombination temp param for recursion, which keeps current combination.
 * @param questions questions to combine.
 * @param questionsCurrentIndex temp param for recursion.
 * @param numberOfQuestionsInExamPaper number of questions in one exam paper.
 */
void combinationUtil(LinkedList* res, LinkedList* currentCombination,
                     Questions questions, int questionsCurrentIndex,
                     int numberOfQuestionsInExamPaper)
{
    if (currentCombination == NULL)
        currentCombination = createList();


    for (int i=questionsCurrentIndex; i < questions->size; i++)
    {
        listAdd(currentCombination, listGet(questions, i));
        if (currentCombination->size == numberOfQuestionsInExamPaper)
        {
            LinkedList* copy = listCopy(currentCombination);
            listAdd(res, copy);
        }
        else
        {
            combinationUtil(res, currentCombination,
                            questions, i+1,
                            numberOfQuestionsInExamPaper);
        }

        listDelete(currentCombination, currentCombination->size - 1);
    }
}


/**
 * @brief Removes most difficult combinations.
 */
void removeRedundantCombinations(LinkedList* allCombinations, int numberOfRequiredCombinations)
{
    if (allCombinations->size == numberOfRequiredCombinations)
        return;

    listSort(allCombinations, sortByTotalLevelOfDifficulty);
    while (allCombinations->size != numberOfRequiredCombinations)
        listDelete(allCombinations, allCombinations->size - 1);
}


int sortByTotalLevelOfDifficulty(LinkedListNode* a, LinkedListNode* b)
{
    LinkedList* aList = a->value;
    LinkedList* bList = b->value;

    int aTotalLevelOfDifficulty = 0;
    for (int i = 0;i < aList->size; i++)
        aTotalLevelOfDifficulty += questionGetLevelOfDifficulty((QuestionPtr)listGet(aList, i));


    int bTotalLevelOfDifficulty = 0;
    for (int i = 0;i < bList->size; i++)
        bTotalLevelOfDifficulty += questionGetLevelOfDifficulty((QuestionPtr)listGet(bList, i));

    return bTotalLevelOfDifficulty - aTotalLevelOfDifficulty;
}