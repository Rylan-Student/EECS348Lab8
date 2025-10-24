/*
Lab8.c
• Description: Problem one of lab8
• Sources: Chatgpt
(Most code authored by me, used chatGPT to debug when I faced problems and sometimes used its outputs.)
• Rylan Moore
• 10/23/2025
*/

#include <stdio.h>

int main(void) {
    int score;

    while (1) {
        printf("Enter the NFL score (Enter 1 to stop): ");
        if (scanf("%d", &score) != 1) {
            /* test for int input */
            printf("Invalid input. Please enter an integer score.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }
            continue;
        }

        /* sentinel to stop */
        if (score == 1) {
            printf("Stopping.\n");
            break;
        }

        /* validation for negative scores */
        if (score < 0) {
            printf("Invalid score. Score cannot be negative.\n");
            continue;
        }

        printf("Possible combinations of scoring plays if a team's score is %d:\n", score);

        int found = 0;

        /*
           a = number of TD + 2pt
           b = number of TD + FG  
           c = number of TD       
           d = number of 3pt FG   
           e = number of Safety   
           Search a,b,c,d and compute e from the remainder.
        */

        for (int a = 0; a <= score / 8; ++a) {
            for (int b = 0; b <= score / 7; ++b) {
                for (int c = 0; c <= score / 6; ++c) {
                    for (int d = 0; d <= score / 3; ++d) {
                        int remainder = score - (8*a + 7*b + 6*c + 3*d);
                        if (remainder < 0) continue;
                        /* remainder must be achievable*/
                        if (remainder % 2 == 0) {
                            int e = remainder / 2;
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                                   a, b, c, d, e);
                            found = 1;
                        }
                    }
                }
            }
        }

        if (!found) {
            printf("No combinations of legal scoring plays produce %d.\n", score);
        }
    }

    return 0;
}

