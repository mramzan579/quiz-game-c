/*
 * quiz_game.c
 * Quiz Game
 * Add the quiz loop that runs all questions, checks answers,
 * gives instant feedback, and tracks the score.
 */

#include <stdio.h>
#include <ctype.h>

//Constants 
#define TOTAL_QUESTIONS  5
#define OPTIONS_PER_Q    4

// ── Question struct
typedef struct {
    const char *question;
    const char *options[OPTIONS_PER_Q];
    char        answer;
} Question;

// ── Question bank
Question quiz[TOTAL_QUESTIONS] = {
    {
        "What is the capital of France?",
        {"Berlin", "Madrid", "Paris", "Rome"},
        'C'
    },
    {
        "Which language is known as the mother of all programming languages?",
        {"Python", "C", "Assembly", "FORTRAN"},
        'B'
    },
    {
        "What does CPU stand for?",
        {"Central Process Unit", "Computer Personal Unit",
         "Central Processing Unit", "Core Processing Unit"},
        'C'
    },
    {
        "How many bits are in one byte?",
        {"4", "16", "32", "8"},
        'D'
    },
    {
        "Which planet is known as the Red Planet?",
        {"Venus", "Jupiter", "Mars", "Saturn"},
        'C'
    }
};

/* ================================================================
   clear_input_buffer()
   Drains leftover characters from stdin after every scanf.
================================================================ */
void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ================================================================
   get_valid_choice()
   Keeps asking until the player enters A, B, C, or D.
   Returns the validated uppercase character.
================================================================ */
char get_valid_choice(void)
{
    char input;

    while (1) {
        printf("Enter your choice (A/B/C/D): ");
        scanf(" %c", &input);
        clear_input_buffer();

        input = toupper(input);

        if (input == 'A' || input == 'B' ||
            input == 'C' || input == 'D') {
            return input;
        }

        printf("  Invalid choice! Please enter A, B, C, or D.\n\n");
    }
}

/* ================================================================
   display_question()
   Prints one question with its four labeled options.
================================================================ */
void display_question(int index, const Question *q)
{
    int  i;
    char label = 'A';

    printf("\nQuestion %d of %d:\n", index + 1, TOTAL_QUESTIONS);
    printf("----------------------------------------\n");
    printf("%s\n\n", q->question);

    for (i = 0; i < OPTIONS_PER_Q; i++) {
        printf("  %c) %s\n", label + i, q->options[i]);
    }
    printf("\n");
}

/* ================================================================
   run_quiz()
   Loops through every question in the quiz array.
   For each question:
     - displays it
     - reads the player's answer
     - checks if it is correct
     - prints instant feedback
     - shows the running score
   Returns the total number of correct answers.
================================================================ */
int run_quiz(void)
{
    int  i;
    int  score = 0;   /* counts correct answers */
    char choice;

    for (i = 0; i < TOTAL_QUESTIONS; i++) {

        /* Show the question */
        display_question(i, &quiz[i]);

        // Get a valid answer from the player
        choice = get_valid_choice();

        //Check the answer and give instant feedback 
        if (choice == quiz[i].answer) {
            printf("\n  Correct! Well done.\n");
            score++;   // only increments on correct answer 
        } else {
            //Show what the correct answer was 
            printf("\n  Wrong! The correct answer was %c) %s\n",
                   quiz[i].answer,
                   quiz[i].options[quiz[i].answer - 'A']);
        }

        // Show running score after every question 
        printf("  Score so far: %d / %d\n", score, i + 1);
    }

    return score;
}

// ── Main
int main(void)
{
    int score = 0;

    //Welcome banner 
    printf("========================================\n");
    printf("              QUIZ GAME                 \n");
    printf("========================================\n");
    printf("  Answer %d multiple-choice questions.\n", TOTAL_QUESTIONS);
    printf("  Each question has 4 options: A B C D.\n");
    printf("========================================\n");

    /* Run the full quiz and get the final score */
    score = run_quiz();

    //Temporary score print — proper summary added next commit 
    printf("\n----------------------------------------\n");
    printf("  You scored %d out of %d!\n", score, TOTAL_QUESTIONS);
    printf("----------------------------------------\n");

    return 0;
}