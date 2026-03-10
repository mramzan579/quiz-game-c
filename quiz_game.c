/*
 * quiz_game.c
 *
 * A console-based multiple-choice quiz game written in C.
 * Tests the player on general knowledge with 5 questions,
 * tracks the score, gives instant feedback, and allows replay.
    */

#include <stdio.h>
#include <ctype.h>

// ── Constants 
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
   Parameters:
     index — question number (0-based, shown as 1-based to player)
     q     — pointer to the Question to display
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
   Loops through every question, displays it, reads the answer,
   checks if correct, prints feedback, and tracks the score.
   Returns total number of correct answers.
================================================================ */
int run_quiz(void)
{
    int  i;
    int  score = 0;
    char choice;

    for (i = 0; i < TOTAL_QUESTIONS; i++) {

        display_question(i, &quiz[i]);

        choice = get_valid_choice();

        if (choice == quiz[i].answer) {
            printf("\n  Correct! Well done.\n");
            score++;
        } else {
            printf("\n  Wrong! The correct answer was %c) %s\n",
                   quiz[i].answer,
                   quiz[i].options[quiz[i].answer - 'A']);
        }

        printf("  Score so far: %d / %d\n", score, i + 1);
    }

    return score;
}

/* ================================================================
   show_final_score()
   Displays the end-of-round summary with tiered feedback
   based on how many questions the player got correct.
   Parameters:
     score — number of correct answers this round
================================================================ */
void show_final_score(int score)
{
    printf("\n========================================\n");
    printf("            QUIZ COMPLETE               \n");
    printf("========================================\n");
    printf("  Your final score: %d / %d\n\n", score, TOTAL_QUESTIONS);

    /* Tiered feedback based on performance */
    if (score == TOTAL_QUESTIONS) {
        printf("  PERFECT SCORE! Outstanding!\n");
    } else if (score >= 4) {
        printf("  Excellent! Almost perfect!\n");
    } else if (score >= 3) {
        printf("  Good job! Solid performance.\n");
    } else if (score >= 2) {
        printf("  Not bad. Keep practicing!\n");
    } else {
        printf("  Keep studying — you will improve!\n");
    }

    printf("========================================\n");
}

/* ================================================================
   ask_play_again()
   Asks the player if they want another round.
   Validates input — only accepts Y or N.
   Returns 1 for yes, 0 for no.
================================================================ */
int ask_play_again(void)
{
    char choice;

    while (1) {
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &choice);
        clear_input_buffer();

        choice = toupper(choice);

        if (choice == 'Y') return 1;   /* yes — play another round */
        if (choice == 'N') return 0;   /* no  — exit the loop      */

        printf("  Please enter Y or N.\n");
    }
}

/* ================================================================
   main()
   Entry point. Prints the welcome banner, then runs the quiz
   in a loop until the player decides to quit.
   Tracks the best score across all rounds.
================================================================ */
int main(void)
{
    int score      = 0;
    int best_score = 0;
    int round      = 1;

    /* ── Welcome banner ──────────────────────────────────────── */
    printf("========================================\n");
    printf("              QUIZ GAME                 \n");
    printf("========================================\n");
    printf("  Answer %d multiple-choice questions.\n", TOTAL_QUESTIONS);
    printf("  Each question has 4 options: A B C D.\n");
    printf("========================================\n");

    // ── Main replay loop 
    do {
        printf("\n--- Round %d ---\n", round);

        /* Run a full quiz and store the score */
        score = run_quiz();

        /* Show the end of round summary */
        show_final_score(score);

        /* Update best score if this round was better */
        if (score > best_score) {
            best_score = score;
        }

        round++;

    } while (ask_play_again());

    // ── Final goodbye summary 
    printf("\n========================================\n");
    printf("  Thanks for playing!\n");
    printf("  Rounds played : %d\n", round - 1);
    printf("  Best score    : %d / %d\n", best_score, TOTAL_QUESTIONS);
    printf("========================================\n");
    printf("  Goodbye! Come back and beat your score.\n\n");

    return 0;
}