/*
Lab8.c
• Description: Problem two of lab8
• Sources: Chatgpt
(Most code authored by me, used chatGPT to debug when I faced problems and sometimes used its outputs. For this one used GPT to find the right C libraries to use)
• Rylan Moore
• 10/23/2025
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Convert various scales to Celsius */
int to_celsius(double value, char scale, double *out_c) {
    scale = toupper((unsigned char)scale);
    if (scale == 'C') {
        *out_c = value;
        return 1;
    } else if (scale == 'F') {
        *out_c = (value - 32.0) * 5.0 / 9.0;
        return 1;
    } else if (scale == 'K') {
        if (value < 0.0) return 0; /* invalid Kelvin */
        *out_c = value - 273.15;
        return 1;
    }
    return 0; /* unknown scale */
}

/* Convert Celsius to target scale */
int from_celsius(double c, char target, double *out_val) {
    target = toupper((unsigned char)target);
    if (target == 'C') {
        *out_val = c;
        return 1;
    } else if (target == 'F') {
        *out_val = c * 9.0 / 5.0 + 32.0;
        return 1;
    } else if (target == 'K') {
        double k = c + 273.15;
        if (k < 0.0) return 0; /* should not happen for valid inputs so works to filter invalid ones */
        *out_val = k;
        return 1;
    }
    return 0;
}

/* Determine category and advisory based on Celsius value */
void category_and_advisory(double c, char *category, size_t catlen,
                           char *advisory, size_t advlen) {
    if (c < 0.0) {
        strncpy(category, "Freezing", catlen-1); category[catlen-1] = '\0';
        strncpy(advisory, "Stay indoors and bundle up!", advlen-1); advisory[advlen-1] = '\0';
    } else if (c >= 0.0 && c < 10.0) {
        strncpy(category, "Cold", catlen-1); category[catlen-1] = '\0';
        strncpy(advisory, "Wear a jacket.", advlen-1); advisory[advlen-1] = '\0';
    } else if (c >= 10.0 && c < 25.0) {
        strncpy(category, "Comfortable", catlen-1); category[catlen-1] = '\0';
        strncpy(advisory, "Nice weather: Enjoy!", advlen-1); advisory[advlen-1] = '\0';
    } else if (c >= 25.0 && c <= 35.0) {
        strncpy(category, "Hot", catlen-1); category[catlen-1] = '\0';
        strncpy(advisory, "Drink lots of water!", advlen-1); advisory[advlen-1] = '\0';
    } else { /* c > 35 */
        strncpy(category, "Extreme Heat", catlen-1); category[catlen-1] = '\0';
        strncpy(advisory, "Extreme heat: stay hydrated and avoid prolonged sun exposure!", advlen-1);
        advisory[advlen-1] = '\0';
    }
}

int main(void) {
    double input_val;
    char orig_scale[8];
    char target_scale[8];
    int scanf_result;

    /* Read temp value and validate */
    while (1) {
        printf("Enter the temperature value: ");
        scanf_result = scanf("%lf", &input_val);
        if (scanf_result == 1) {
            /* clear trailing input */
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }
            break;
        } else {
            printf("Invalid input. Please enter a numeric temperature value.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }
        }
    }

    /* Read original scale */
    while (1) {
        printf("Enter the original scale (C, F, or K): ");
        if (fgets(orig_scale, sizeof(orig_scale), stdin) == NULL) {
            printf("Input error. Try again.\n");
            continue;
        }
        /* strip */
        orig_scale[strcspn(orig_scale, "\r\n")] = '\0';
        if (strlen(orig_scale) == 0) {
            printf("No input provided. Please enter C, F, or K.\n");
            continue;
        }
        /* designate inputs to accept */
        char c = toupper((unsigned char)orig_scale[0]);
        if (c == 'C' || c == 'F' || c == 'K') {
            orig_scale[0] = c;
            orig_scale[1] = '\0';
            break;
        } else {
            printf("Invalid scale. Please enter C, F, or K.\n");
        }
    }

    /* checks invalid input. K cant be negative */
    if (orig_scale[0] == 'K' && input_val < 0.0) {
        printf("Invalid temperature: Kelvin cannot be negative.\n");
        return 1;
    }

    /* Read target scale */
    while (1) {
        printf("Enter the scale to convert to (C, F, or K): ");
        if (fgets(target_scale, sizeof(target_scale), stdin) == NULL) {
            printf("Input error. Try again.\n");
            continue;
        }
        target_scale[strcspn(target_scale, "\r\n")] = '\0';
        if (strlen(target_scale) == 0) {
            printf("No input provided. Please enter C, F, or K.\n");
            continue;
        }
        char c = toupper((unsigned char)target_scale[0]);
        if (c == 'C' || c == 'F' || c == 'K') {
            target_scale[0] = c;
            target_scale[1] = '\0';
            break;
        } else {
            printf("Invalid scale. Please enter C, F, or K.\n");
        }
    }

    /* Convert input to Celsius */
    double celsius;
    if (!to_celsius(input_val, orig_scale[0], &celsius)) {
        printf("Conversion error: unknown original scale.\n");
        return 1;
    }

    /* Convert Celsius to target */
    double result;
    if (!from_celsius(celsius, target_scale[0], &result)) {
        printf("Conversion error: cannot convert to target scale (out of range?).\n");
        return 1;
    }

    /* Display converted temperature */
    printf("Converted temperature: %.2f %c\n", result, target_scale[0]);

    /* Determine category based on C temp */
    char category[32];
    char advisory[128];
    category_and_advisory(celsius, category, sizeof(category), advisory, sizeof(advisory));

    printf("Temperature category: %s\n", category);
    printf("Weather advisory: %s\n", advisory);

    return 0;
}

