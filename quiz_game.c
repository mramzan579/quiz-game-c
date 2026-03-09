/*
 * quiz_game.c
 * Quiz Game in C
 * Add the Question struct, question bank, display function,
 * and input validation so the player can answer questions.
 */

#include <stdio.h>
#include <ctype.h>   /* toupper() — converts a/b/c/d to A/B/C/D */

/* ── Constants ──────────────────────────────────────────────── */
#define TOTAL_QUESTIONS  5
#define OPTIONS_PER_Q    4

/* ── Question struct ────────────────────────────────────────── */
/* A struct groups related data together.
   Each question has: the text, four options, and the correct answer. */
typedef struct {
    const char *question;               /* the question text       */
    const char *options[OPTIONS_PER_Q]; /* four answer choices     */
    char        answer;                 /* correct answer: A/B/C/D */
} Question;

/* ── Question bank ──────────────────────────────────────────── */
/* All 5 questions stored in one array.
   Easy to add more questions later — just extend this array. */
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
   Prevents infinite loops on bad input.
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
   Accepts both upper and lowercase input.
   Returns the validated uppercase character.
================================================================ */
char get_valid_choice(void)
{
    char input;

    while (1) {
        printf("Enter your choice (A/B/C/D): ");
        scanf(" %c", &input);    /* space before %c skips whitespace */
        clear_input_buffer();

        input = toupper(input);  /* convert to uppercase */

        if (input == 'A' || input == 'B' ||
            input == 'C' || input == 'D') {
            return input;        /* valid — return it */
        }

        printf("  Invalid choice! Please enter A, B, C, or D.\n\n");
    }
}

/* ================================================================
   display_question()
   Prints one question with its four options labeled A to D.
   Parameters:
     index — question number (0-based, shown as 1-based to player)
     q     — pointer to the Question to display
================================================================ */
void display_question(int index, const Question *q)
{
    int  i;
    char label = 'A';   /* starting label — goes A, B, C, D */

    printf("\nQuestion %d of %d:\n", index + 1, TOTAL_QUESTIONS);
    printf("----------------------------------------\n");
    printf("%s\n\n", q->question);

    /* Loop through all 4 options and print each with its letter */
    for (i = 0; i < OPTIONS_PER_Q; i++) {
        printf("  %c) %s\n", label + i, q->options[i]);
    }
    printf("\n");
}

/* ── Main function ──────────────────────────────────────────────── */
int main(void)
{
    //Welcome banner
    printf("========================================\n");
    printf("              QUIZ GAME                 \n");
    printf("========================================\n");
    printf("  Answer %d multiple-choice questions.\n", TOTAL_QUESTIONS);
    printf("  Each question has 4 options: A B C D.\n");
    printf("========================================\n");

    //Temporary: shows first question to test display function
    display_question(0, &quiz[0]);
    get_valid_choice();

    printf("\n[DEBUG] Display and input validation working.\n");

    return 0;
}