/**
 * @file main.c
 * @author Kevin de la Coba
 * @brief Main program for reading all the results and getting the info
 * @version 0.1
 * @date 2020-01-07
 * 
 * @author Kevin de la Coba Malam
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/* el que mas frecuencia Y lleva mucho sin aparecer */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * @brief Structure to store the combinations
 * 
 */
typedef struct {
    int **combinations;         /* Array where the combinations are */
    int stored_combinations;    /* Number of stored combinations */
} numbers_t;

/**
 * @brief Stores in the structure all the results
 * @author Kevin de la Coba Malam
 *
 * @param filename Name of the file with all the results
 * @return numbers_t structure with all the results
 */
numbers_t *read_numbers_from(char *filename) {

    FILE *pf = NULL;
    int number[7], i = 0, j = 0;
    numbers_t *num = NULL;  

    /* Checking arguments */
    if (filename == NULL) return NULL;

    /* Reserving memory for the numbers */
    num = (numbers_t*)malloc(sizeof(numbers_t));
    if (num == NULL) {

        printf("Error while reserving memory for the number structure in read_numbers_from.\n");
        return NULL;
    }

    num->stored_combinations = 0;
    num->combinations = NULL;

    pf = fopen(filename, "r");
    if (pf == NULL) {

        printf("Error while openning the file in read_numbers_from.\n");
        return NULL;
    }

    /* At the end of the file is going to be an 'a' */
    j = 0;
    while(fscanf(pf, "%d|%d|%d|%d|%d|%d|%d\n", &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]) != EOF){

        num->stored_combinations += 1;
        num->combinations = (int**)realloc(num->combinations, num->stored_combinations*sizeof(int**));
        if (num->combinations == NULL) {

            printf("Error while reallocating in read_numbers_from");
            return NULL;
        }

        /* Allocating memory for the entire combination */
        num->combinations[j] = (int*) malloc(7*sizeof(int));
        if (num->combinations[j] == NULL) {

            printf("Error while doing malloc to num->combinations[j] in read_numbers_from.\n");
            return NULL;
        }

        for (i = 0; i < 7; i++){

            num->combinations[j][i] = number[i];
        }

        j++;
    }

    fclose(pf);

    return num;
}

/**
 * @brief Counts how many times does each star appear in all the results
 * @author Kevin de la Coba Malam
 * 
 * @param num Structure with all the results
 * @return int* Array with the numbers
 */
int* check_numbers(numbers_t *num) {

    int *numbers = NULL, i = 0, n = 0, j = 0;

    /* Checking arguments */
    if (num == NULL) {

        printf("Error with the arguments in check_numbers.\n");    
        return NULL;
    }

    numbers = (int*)malloc(50*sizeof(int));
    if (numbers == NULL) {
        
        printf("Error while reserving memory in check_numbers");
        return NULL;
    }

    /* Initializing the array */
    for(i = 0; i < 50; i++) numbers[i] = 0;

    /* Looking for all the numbers */
    for(i = 0; i < 50; i++) {

        for (n = 0; n < num->stored_combinations; n++) {

            /* Looking for the numbers stored in the combinations */ 
            for (j = 0; j < 5; j++) {

                if (num->combinations[n][j] == i + 1) numbers[i] += 1;
            }
        }
    }

    return numbers;
}

/**
 * @brief Counts how many times does each star appear in all the results
 * @author Kevin de la Coba Malam
 * 
 * @param num Structure with all the results
 * @return int* Array with the stars
 */
int* check_stars(numbers_t *num) {

    int *stars = NULL, i = 0, n = 0, j = 0;

    /* Checking arguments */
    if (num == NULL) return NULL;

    stars = (int*)malloc(12*sizeof(int));
    if (stars == NULL) {
        
        printf("Error while reserving memory in check_stars");
        return NULL;
    }

    /* Initializing the array */
    for(i = 0; i < 12; i++) stars[i] = 0;

    /* Looking for all the stars */
    for(i = 0; i < 12; i++) {

        for (n = 0; n < num->stored_combinations; n++) {

            /* Looking for the stars stored in the combinations */ 
            for (j = 5; j < 7; j++) {

                if (num->combinations[n][j] == i + 1) stars[i] += 1;
            }
        }
    }

    return stars;
}

/**
 * @brief Stores in an array the stars that appear less
 * @author Kevin de la Coba Malam
 * 
 * @param numb Array with the times that each star appears.
 *              numb[0] = 4, the star 1 appears 4 times
 * @param quantity Variable with how many stars do we want to store
 * @return int* Array with the stored stars
 */
int* appear_less_stars (int *numb, int quantity) {

    int *appear_less_stars = NULL, i = 0, n = 0, j = 0, smallest = 100, BOOL_v = 0;

    if (numb == NULL || quantity <= 0) return NULL;

    appear_less_stars = (int*)calloc(quantity,sizeof(int));
    if (appear_less_stars == NULL) {

        printf("Error while reserving memory for the stars that appear less.\n");
        return NULL;
    }

    /* Initializing the array */
    for (i = 0; i < quantity; i++) appear_less_stars[i] = 0;

    for(i = 0; i < quantity; i++) {

        for (n = 0; n < 12; n++) {

            if (numb[n] < smallest) {
                                
                for (j = 0; j < i; j++) if (n+1 == appear_less_stars[j]) BOOL_v = 1;
                if (BOOL_v == 0) {
                
                    appear_less_stars[i] = n + 1;
                    smallest = numb[n];
                }
                BOOL_v = 0;
            }
        }

        smallest = 4000;
        
    }

    return appear_less_stars;
}

/**
 * @brief Stores in an array the numbers that appear less
 * @author Kevin de la Coba Malam
 * 
 * @param numb Array with the times that each number appears.
 *              numb[0] = 4, the number 1 appears 4 times
 * @param quantity Variable with how many numbers do we want to store
 * @return int* Array with the stored numbers
 */
int* appear_less_numbers (int *numb, int quantity) {

    int *appear_less_numbers = NULL, i = 0, n = 0, j = 0, smallest = 3000, BOOL_v = 0;

    if (numb == NULL || quantity <= 0) return NULL;

    appear_less_numbers = (int*)calloc(quantity, sizeof(int));
    if (appear_less_numbers == NULL) {

        printf("Error while reserving memory for the numbers that appear less.\n");
        return NULL;
    }

    /* Initializing the array */
    for (i = 0; i < quantity; i++) appear_less_numbers[i] = 0;

    for(i = 0; i < quantity; i++) {

        for (n = 0; n < 50; n++) {

            if (numb[n] < smallest) {

                for (j = 0; j < i; j++) if (n+1 == appear_less_numbers[j]) BOOL_v = 1; 
                if (BOOL_v == 0) {
                
                    appear_less_numbers[i] = n + 1;
                    smallest = numb[n];
                }
                BOOL_v = 0;
            }
        }

        smallest = 3000;
    }

    return appear_less_numbers;
}

/**
 * @brief Gives an array checking the number of weeks that the numbers appear in that amount of time
 * @author Kevin de la Coba Malam
 * 
 * @param *num Combinations
 * @return int* array with the times that each number of weeks have numbers repeated
 */
long* check_weeks_numbers(numbers_t* num) {

    long i = 0, j = 0, k = 0, n = 0, s = 0, *repeated = NULL, numbers[5];

    if (num == NULL) return NULL;

    /* We are just going to have at maximum a 9 weeks range */
    repeated = (long*)calloc(9, sizeof(long));
    if (repeated == NULL) {

        printf("Error while reserving memory in check_weeks_numbers.\n");
        return NULL;
    }
    for (i = 0; i < 9; i++) repeated[i] = 0;


    for (i = num->stored_combinations - 1; i >= 0; i--) {

        /* First copying the data */
        for(k = 0; k < 5; k++) numbers[k] = num->combinations[i][k];

        /* looking for every number in the combination if it is there */
        for (k = 0; k < 5; k++) {

            for(j = i - 1, s = 0; j >= i - 9; j--, s++) {

                if(j < 0) break;
                for(n = 0; n < 5; n++) {
                    
                    if(numbers[k] == num->combinations[j][n]) repeated[s] += 1;
                }
                
            }
        }   
    }
    for (i = 1; i < 9; i++) repeated[i] += repeated[i-1];

    return repeated;
}

/**
 * @brief Gives an array checking the number of weeks that the stars appear in that amount of time
 * @author Kevin de la Coba Malam
 * 
 * @param *num Structure with all the results
 * @return int* array with the times that each number of weeks have stars repeated
 */
long* check_weeks_stars(numbers_t* num) {

    long i = 0, j = 0, k = 0, n = 0, s = 0, *repeated = NULL, stars[2];

    if (num == NULL) return NULL;

    /* We are just going to have at maximum a 4 weeks range */
    repeated = (long*)calloc(4, sizeof(long));
    if (repeated == NULL) {

        printf("Error while reserving memory in check_weeks_stars.\n");
        return NULL;
    }
    for (i = 0; i < 4; i++) repeated[i] = 0;

    for (i = num->stored_combinations - 1; i >= 0; i--) {

        /* First copying the data */
        for(k = 5; k < 7; k++) stars[k-5] = num->combinations[i][k];

        /* looking for every number in the combination if it is there */
        for (k = 5; k < 7; k++) {

            for(j = i - 1, s = 0; j >= i - 4; j--, s++) {

                if(j < 0) break;
                for(n = 5; n < 7; n++) {
                    
                    if(stars[k-5] == num->combinations[j][n]) repeated[s] += 1;
                }
            }
        }   
    }

    for (i = 1; i < 4; i++) repeated[i] += repeated[i-1];

    return repeated;
}

/**
 * @brief Gives an array with just the stars that we are going to use
 * @author Kevin de la Coba Malam
 * 
 * @param num Structure with all the results
 * @param weeks_to_remove Number of weeks to remove
 * @return int* 
 */
int* remove_stars_from_weeks(numbers_t* num, int weeks_to_remove) {

    int i = 0, n = 0, j = 0, *stars_to_use = NULL;

    if (num == NULL || weeks_to_remove <= 0) {

        printf("Error with the arguments in remove_stars_from_weeks\n");
        return NULL;
    }

    stars_to_use = (int*)calloc(12, sizeof(int));
    if (stars_to_use == NULL) {

        printf("Error while reserving memory for the stars to use in remove_stars_from_weeks.");
        return NULL;
    }

    /* Initializing the array */
    for (i = 0; i < 12; i++) stars_to_use[i] = i + 1;

    for (i = num->stored_combinations - 1; i > num->stored_combinations - 1 - weeks_to_remove; i--) {

        for (n = 0; n < 12; n++) {

            for (j = 5; j < 7; j++) {

                if (stars_to_use[n] == num->combinations[i][j]) stars_to_use[n] = 0; 
            }
        }
    }

    return stars_to_use;
}

/**
 * @brief Gives an array with just the numbers that we are going to use
 * @author Kevin de la Coba Malam
 * 
 * @param num Structure with all the results
 * @param weeks_to_remove Numbers of weeks to remove
 * @return int* Numbers that are == 0 are not used
 */
int* remove_numbers_from_weeks(numbers_t* num, int weeks_to_remove) {

    int i = 0, n = 0, j = 0, *numbers_to_use = NULL;

    if (num == NULL || weeks_to_remove <= 0) {

        printf("Error with the arguments in remove_stars_from_weeks\n");
        return NULL;
    }

    numbers_to_use = (int*)calloc(50, sizeof(int));
    if (numbers_to_use == NULL) {

        printf("Error while reserving memory for the stars to use in remove_stars_from_weeks.");
        return NULL;
    }

    /* Initializing the array */
    for (i = 0; i < 50; i++) numbers_to_use[i] = i + 1;

    for (i = num->stored_combinations - 1; i > num->stored_combinations - 1 - weeks_to_remove; i--) {

        for (n = 0; n < 50; n++) {

            for (j = 0; j < 5; j++) {

                if (numbers_to_use[n] == num->combinations[i][j]) numbers_to_use[n] = 0; 
            }
        }
    }

    return numbers_to_use;
}

/**
 * @brief Checks from a given array the times that these numbers appear with another one
 * @author Kevin de la Coba Malam
 * 
 * @param num structure with all the results
 * @param numbers array with the numbers to check
 * @return int** Array with all the times that each star appears with another number
 */
int** check_number_combinations(numbers_t *num) {

    int i = 0, j = 0, k = 0, **all_n = NULL, bool_v = 0;

    if (num == NULL) {

        printf("Error with the number of arguments check_number_combinations.\n");
        return NULL;
    } 

    /* Reserving memory */
    all_n = (int**)malloc(50*sizeof(int*));
    if (all_n == NULL) {

        printf("Error reserving memory in check_number_combinations.");
        return NULL;
    }

    for (i = 0; i < 50; i++) {
    
        all_n[i] = (int*)malloc(50*sizeof(int));
        if (all_n[i] == NULL) {

            printf("Error reserving memory in check_number_combinations.");
            return NULL;
        }
    }

    for (i = 0; i < 50; i++) {
        
        for (j = 0; j < 50; j++) {

            all_n[i][j] = 0;
        }
    }

    /* Loop for checking the every number */
    for (i = 0; i < 50; i++) {

        /* Checking the numbers in the result */
        for (j = 0; j < num->stored_combinations; j++) {

            bool_v = 0;

            /* Looking for the i number in the result */
            for (k = 0; k < 5; k++) {

                if (i+1 == num->combinations[j][k]) bool_v = 1;
            }

            if (bool_v == 1) {

                for (k = 0; k < 5; k++) {

                    if (num->combinations[j][k] != i+1) {
                        
                        all_n[i][num->combinations[j][k]-1] += 1;
                    }
                }
            }
        }
    }

    return all_n;
}

/**
 * @brief Stores in an array all the times that each star appears with another number
 * @author Kevin de la Coba Malam
 * 
 * @param num Structure with the all the result
 * @return int** Array with all the times that each star appears with another number
 */
int** check_star_combinations(numbers_t *num) {

    int i = 0, j = 0, k = 0, **all_n = NULL, bool_v = 0;

    if (num == NULL) {

        printf("Error with the number of arguments check_star_combinations.\n");
        return NULL;
    } 

    /* Reserving memory */
    all_n = (int**)malloc(12*sizeof(int*));
    if (all_n == NULL) {

        printf("Error reserving memory in check_star_combinations.");
        return NULL;
    }

    for (i = 0; i < 12; i++) {
    
        all_n[i] = (int*)malloc(12*sizeof(int));
        if (all_n[i] == NULL) {

            printf("Error reserving memory in check_star_combinations.");
            return NULL;
        }
    }

    for (i = 0; i < 12; i++) {
        
        for (j = 0; j < 12; j++) {

            all_n[i][j] = 0;
        }
    }

    /* Loop for checking every number */
    for (i = 0; i < 12; i++) {

        /* Checking the numbers in the result */
        for (j = 0; j < num->stored_combinations; j++) {

            bool_v = 0;

            /* Looking for the i number in the result */
            for (k = 5; k < 7; k++) {

                if (i+1 == num->combinations[j][k]) bool_v = 1;
            }

            if (bool_v == 1) {

                for (k = 5; k < 7; k++) {

                    if (num->combinations[j][k] != i+1) {
                        
                        all_n[i][num->combinations[j][k] - 1] += 1;
                    } 
                }
            }
        }
    }

    printf("\n");

    return all_n;
}

/**
 * @brief Prints how many times does a number appear with every other number
 * @author Kevin de la Coba Malam
 * 
 * @param comb Array with the info about all the numbers
 * @param star_to_show Star to show the info
 * @return int flag
 */
int print_combination_number(int **comb, int number_to_show) {

    int n = 0;

    if (comb == NULL || number_to_show < 0) {

        printf("Error with arguments in print_combination_number.\n");
        return -1;
    }

    /* Printing combinations */
    for (n = 0; n < 50; n++) {

        if (comb[number_to_show - 1][n] != 0) {
            
            printf("The number ");
            printf("\033[0;36m");
            printf("%d", number_to_show);
            printf("\033[0m");
            printf(" with the number ");
            printf("\033[0;32m");
            printf("%d", n+1);
            printf("\033[0m");
            printf(" appeared ");
            printf("\033[0;33m");
            printf("%d", comb[number_to_show - 1][n]);
            printf("\033[0m");
            printf(" times.\n");
        }
    }
    printf("\n");

    return 0;
}

/**
 * @brief Prints how many times does a star appear with every other number
 * @author Kevin de la Coba Malam
 * 
 * @param comb Array with the info about all the numbers
 * @param star_to_show Star to show the info
 * @return int flag
 */
int print_combination_star(int **comb, int star_to_show) {

    int n = 0;

    if (comb == NULL || star_to_show < 0) {

        printf("Error with arguments in print_combination_star.\n");
        return -1;
    }

    /* Printing combinations */
    for (n = 0; n < 12; n++) {

        if (comb[star_to_show - 1][n] != 0) {
            
            printf("The number ");
            printf("\033[0;36m");
            printf("%d", star_to_show);
            printf("\033[0m");
            printf(" with the number ");
            printf("\033[0;32m");
            printf("%d", n+1);
            printf("\033[0m");
            printf(" appeared ");
            printf("\033[0;33m");
            printf("%d", comb[star_to_show - 1][n]);
            printf("\033[0m");
            printf(" times.\n");
        }
    }
    printf("\n");

    return 0;
}

/**
 * @brief Checks a combination, printing how many times has the number appeared with other numbers
 * @author Kevin de la Coba Malam
 * 
 * @param num Strcuture with all the results
 * @return int flag
 */
int check_combination_input_number(numbers_t *num) {

    int i = 0, n = 0, *input = NULL, quantity = 0, **comb = NULL;

    if (num == NULL) {

        printf("Error with arguments in check_combination_input_number.\n");
        return -1;
    }

    do {

        /* Asking the user how many numbers does he want to introduce */
        printf("How many numbers do you want to check.\nInput must be between 1 - 5: ");
        scanf("\n%d", &quantity);

    } while (quantity < 1 || quantity > 5 );

    input = (int*)malloc(quantity*sizeof(int));
    if (input == NULL) {

        printf("Error while reserving memory in check_combination_input_number.\n");
        return -1;
    };

    /* Asking the user to introduce the numbers */
    printf("Introduce the numbers: ");

    for (i = 0; i < quantity; i++) {
        
        RE_INTRODUCE: scanf("\n%d", &input[i]);
        if (input[i] < 1 || input[i] > 50) {

            if (i > 0) {
                
                if (input[i-1] == input[i]) goto RE_INTRODUCE;
            }
            printf("Wrong input, numbers must be between 1 - 50\n");
            goto RE_INTRODUCE;
        }
    }

    comb = check_number_combinations(num);
    if (comb == NULL) {

        printf("Error calling check_number_combinations in check_combination_input_number.\n");
        return -1;
    }

    for (i = 0; i < quantity; i++){

        for (n = 0; n < quantity; n++) {

            if (n == i) n++;
            if (n == quantity) break;

            printf("The number ");
            printf("\033[0;36m");
            printf("%d", input[i]);
            printf("\033[0m");
            printf(" with the number ");
            printf("\033[0;32m");
            printf("%d", input[n]);
            printf("\033[0m");
            printf(" appeared ");
            printf("\033[0;33m");
            printf("%d", comb[input[i] - 1][input[n] - 1]);
            printf("\033[0m");
            printf(" times.\n");
        }

        printf("\n");
    }

    for (i = 0; i < 50; i++) free(comb[i]);
    free(comb);
    free(input);

    return 0;
}

/**
 * @brief Checks a combination, printing how many times has the star appeared with other stars
 * @author Kevin de la Coba Malam
 * 
 * @param num Structure with all the results 
 * @return int flag
 */
int check_combination_input_star(numbers_t *num) {

    int i = 0, input[2], **comb = NULL;

    if (num == NULL) {

        printf("Error with arguments in check_combination_input_star.\n");
        return -1;
    }

    /* Asking the user to introduce the numbers */
    printf("Introduce the Stars: ");

    for (i = 0; i < 2; i++) {
        
        RE_INTRODUCE: scanf("\n%d", &input[i]);
        if (input[i] < 1 || input[i] > 12) {

            if (i > 0) {
                
                if (input[i-1] == input[i]) goto RE_INTRODUCE;
            }
            printf("Wrong input, numbers must be between 1 - 12\n");
            goto RE_INTRODUCE;
        }
    }

    comb = check_star_combinations(num);
    if (comb == NULL) {

        printf("Error calling check_star_combinations in check_combination_input_star.\n");
        return -1;
    }

    printf("The number ");
    printf("\033[0;36m");
    printf("%d", input[0]);
    printf("\033[0m");
    printf(" with the number ");
    printf("\033[0;32m");
    printf("%d", input[1]);
    printf("\033[0m");
    printf(" appeared ");
    printf("\033[0;33m");
    printf("%d", comb[input[0] - 1][input[1] - 1]);
    printf("\033[0m");
    printf(" times.\n");
    printf("\n");
    

    for (i = 0; i < 12; i++) free(comb[i]);
    free(comb);

    return 0;
}

/**
 * @brief Prints the success rate of the program
 * @author Kevin de la Coba Malam
 * 
 * @param num Structure with all the results
 * @return int flag
 */
int success_rate_numbers(numbers_t *num) {

    int i = 0, n = 0, j = 0, k = 0, m = 0, bool_v = 0;
    double weeks[9], substract_value = 0; 

    if (num == NULL) {

        printf("Error with the arguments in success_rate_numbers.\n");
        return -1;
    }

    for (i = 0; i < 9; i++) weeks[i] = 0;

    /* Loop for checking every result */
    for (i = num->stored_combinations - 1; i >= 0; i--) {
        
        /* Checking every result with every previous week */
        for(n = i - 1, k = 0; n >= i - 9 && n >= 0 && k < 9; n--, k++) {
           
            for (j = 0; j < 5; j++) {
                
                bool_v = 0;
                for (m = 0; m < 5; m++) {

                    if (num->combinations[i][j] == num->combinations[n][m]) {
                        
                        bool_v = 1;
                        break;
                    }
                }

                if (bool_v == 0) weeks[k] += 1;
                
            }
        }
    }

    for (i = 0; i < 9; i++) {

        weeks[i] = (weeks[i]/763);
    }

    for (i = 1; i < 9; i++) {

        substract_value = 5 - weeks[i-1];
        weeks[i] -= substract_value; 
    }

    for (i = 0; i < 9; i++) {
    
        printf("The ");
        printf("\033[0;32m");
        printf("SUCCESS RATE ");
        printf("\033[0m");
        printf("for ");
        printf("\033[0;34m");  
        printf("%d ", i + 1); 
        printf("\033[0m");
        printf("weeks deletion is: ");
        printf("\033[0;32m");
        printf("%f", weeks[i]);
        printf("\033[0m");
        printf(" of 5 numbers.\n");
    }

    return 0;
}

/**
 * @brief Prints the success rate of the program
 * @author Kevin de la Coba Malam
 * 
 * @param num Structure with all the results
 * @return int Flag
 */
int success_rate_stars(numbers_t *num) {

    int i = 0, n = 0, j = 0, k = 0, m = 0, bool_v = 0;
    double weeks[5], substract_value = 0; 

    if (num == NULL) {

        printf("Error with the arguments in success_rate_numbers.\n");
        return -1;
    }

    for (i = 0; i < 5; i++) weeks[i] = 0;

    /* Loop for checking every result */
    for (i = num->stored_combinations - 1; i >= 0; i--) {
        
        /* Checking every result with every previous week */
        for(n = i - 1, k = 0; n >= i - 5 && n >= 0 && k < 5; n--, k++) {
           
            for (j = 5; j < 7; j++) {
                
                bool_v = 0;
                for (m = 5; m < 7; m++) {

                    if (num->combinations[i][j] == num->combinations[n][m]) {
                        
                        bool_v = 1;
                        break;
                    }
                }

                if (bool_v == 0) weeks[k] += 1;
                
            }
        }
    }

    for (i = 0; i < 5; i++) {

        weeks[i] = (weeks[i]/763);
    }

    for (i = 1; i < 5; i++) {

        substract_value = 2 - weeks[i-1];
        weeks[i] -= substract_value; 
    }

    for (i = 0; i < 5; i++) {
    
        printf("The ");
        printf("\033[0;32m");
        printf("SUCCESS RATE ");
        printf("\033[0m");
        printf("for ");
        printf("\033[0;34m");  
        printf("%d ", i + 1); 
        printf("\033[0m");
        printf("weeks deletion is: ");
        printf("\033[0;32m");
        printf("%f", weeks[i]);
        printf("\033[0m");
        printf(" of 2 stars.\n");
    }

    return 0;
}

int main (int argc, char **argv) {

    numbers_t *num = NULL;
    int *numbers = NULL, *stars = NULL, i = 0, k = 0, j = 0, flag = 0, **combinations = NULL, **combinations_s = NULL,
    *appear_less_n = NULL, *appear_less_s = NULL, quantity = 0 , q_S = 0, q_N = 0, input = 0, 
    weeks_to_remove = 0, *numbers_to_use = NULL, *stars_to_use = NULL, n = 0, bool_v = 0, *stars_to_bet = NULL;
    long *repeated_num = NULL, *repeated_stars = NULL, big_num;
    
    /* First we read the file and store all the info in the structure */
    num = read_numbers_from(argv[1]);
    if (num == NULL) {

        printf("Error while reading.\n");
        return -1;
    }

    /* Checking which are the most likely to appear numbers */
    numbers = check_numbers(num);
    if (numbers == NULL) {

        printf("Error while checking numbers.\n");
        return -1;
    }

    /* Checking which are the most likely to appear stars */
    stars = check_stars(num);
    if (stars == NULL) {

        printf("Error while checking stars.\n");
        return -1;
    }

    /* Printing stars */
    printf("S  T  A  R  S  :\n");
    k = 1;
    for (i = 0; i < 12; i++) {
        
        printf("\033[0;34m");
        printf("%d", i + 1);
        printf("\033[0m");
        printf(" : %d | ", stars[i]);
        if (k == 4){

            printf("\n");
            k = 0;
        }
        k++;
    }

    printf("\n\n");

    /* Printing numbers */
    printf("N  U  M  B  E  R  S  :\n");
    k = 1;
    for (i = 0; i < 50; i++) {
        
        printf("\033[0;34m");
        if (i < 9) printf("%d ", i + 1);
        else printf("%d", i + 1);
        printf("\033[0m");
        printf(" : %d | ", numbers[i]);
        if (k == 5){

            printf("\n");
            k = 0;
        }
        k++;
    }
    printf("\n\n");

    /* Asking for how many numbers the user wants to remove */
    REM_STAR: printf("How many STARS do you want to remove?\nThe STARS that are going to be removed are the ones that appear less. MAX = 3. ");
    scanf("%d", &quantity);
    q_S = quantity;
    if (quantity > 3 || quantity <= 0) {

        printf("Wrong input. Put a range between 0 - 3.\n");
        goto REM_STAR;
    }

    /* Taking the 5 stars that appear less */
    appear_less_s = appear_less_stars(stars, quantity);
    if (appear_less_s == NULL) {

        printf("Error while taking the stars that appear less\n");
        return -1;
    }

    printf("\nD E L E T E D   S T A R S\n\n");
    printf("\033[01;33m");
    for (i = 0; i < quantity; i++) printf("%d\t", appear_less_s[i]);
    printf("\033[0m");
    printf("\n\n");

    REM_NUM: printf("How many NUMBERS do you want to remove?\nThe numbers that are going to be removed are the ones that appear less. MAX = 5. ");
    scanf("%d", &quantity);
    q_N = quantity;
    if (quantity > 5 || quantity <= 0) {

        printf("Wrong input. Put a range between 0 - 5.\n");
        goto REM_NUM;
    }

    /* Taking the 5 numbers that appear less */
    appear_less_n = appear_less_numbers(numbers, quantity);
    if (appear_less_n == NULL) {

        printf("Error while taking the numbers that appear less\n");
        return -1;
    }   

    printf("\nD E L E T E D   N U M B E R S\n\n");
    printf("\033[01;33m");
    for (i = 0; i < quantity; i++) printf("%d\t", appear_less_n[i]);
    printf("\033[0m");

    /* Checking numbers repeated in the previous weeks */
    repeated_num = check_weeks_numbers(num);
    if (repeated_num == NULL) {

        printf("Error while taking the repeated numbers in weeks.\n");
        return -1;
    }

    /* Printing the number of times that the same numbers appears in a x week range  */
    printf("\n\n\nNumber of times that the same NUMBER in a combination appears in a X week range: \n\n");
    for (i = 0; i < 9; i++) {

        printf("For %d week range, there were ", i+1);
        printf("\033[0;35m");
        printf("%ld ", repeated_num[i]);
        printf("\033[0m");
        big_num = num->stored_combinations * 5 * (i+2);
        printf("repetitions, from %.0ld checked numbers.", big_num);
        printf("\n");
        printf("Using this range there is a ");
        printf("\033[0;35m");
        printf("%0.2f%c", (double)repeated_num[i]/big_num * 100, '%');
        printf("\033[0m");
        printf(" probability that the numbers in the range appear in the next bet.\n\n");
    }

    /* Checking stars repeated in the previous weeks */
    repeated_stars = check_weeks_stars(num);

    /* Printing the number of times that the same numbers appears in a x week range  */
    printf("\n\nNumber of times that the same S T A R in a combination appears in a X week range: \n\n");
    for (i = 0; i < 4; i++) {

        printf("For %d week range, there were ", i+1);
        printf("\033[0;35m");
        printf("%ld ", repeated_stars[i]);
        printf("\033[0m");
        big_num = num->stored_combinations * 2 * (i+2);
        printf("repetitions, from %.0ld stars checked", big_num);
        printf("\n");
        printf("Using this range there is a ");
        printf("\033[0;35m");
        printf("%f%c", ((double)repeated_num[i]/big_num) * 100, '%');
        printf("\033[0m");
        printf(" probability that the stars in the range appear in the next bet.\n\n");
    }

    flag = success_rate_numbers(num);
    if (flag == -1) {

        printf("Error in success_rate_numbers.\n");
        return -1;
    }

    printf("\n");

    flag = success_rate_stars(num);
    if (flag == -1) {

        printf("Error in success_rate_stars.\n");
        return -1;
    }

    /* Asking the user how many numbers from X weeks does he want to remove */
    ASK_NUM_W: printf("How many weeks do you want to remove?\nWith this you will be removing every number in this range of weeks.\nM  A  X  I  M  U  M  ====>>>  9  W  E  E  K  S\n");
    scanf("%d", &weeks_to_remove);
    if (weeks_to_remove > 9 || weeks_to_remove <= 0){

        printf("Wrong input.\n");
        goto ASK_NUM_W;
    }

    /* Getting an array with just the numbers we want to use */
    numbers_to_use = remove_numbers_from_weeks(num, weeks_to_remove);
    if (numbers_to_use == NULL) {

        printf("Error while removing the numbers from weeks.\n");
        return -1;
    }

    /* Printing the deleted numbers */
    printf("These are the deleted numbers.\n\n");
    printf("\033[01;33m");
    for (i = 0; i < 50; i++) if (numbers_to_use[i] == 0) printf("%d  ", i+1);
    printf("\033[0m");
    printf("\n\n");

    /* Asking the user how many stars from X weeks does he want to remove */
    ASK_STAR_W: printf("How many weeks do you want to remove?\nWith this you will be removing every star in this range of weeks.\nM  A  X  I  M  U  M  ====>>>  4  W  E  E  K  S\n");
    scanf("%d", &weeks_to_remove);
    if (weeks_to_remove > 4 || weeks_to_remove <= 0){

        printf("Wrong input.\n");
        goto ASK_STAR_W;
    }

    /* Getting an array with just the numbers we want to use */
    stars_to_use = remove_stars_from_weeks(num, weeks_to_remove);
    if (stars_to_use == NULL) {

        printf("Error while removing the stars from weeks.\n");
        return -1;
    }

    /* Printing the deleted stars */
    printf("These are the deleted S T A R S.\n\n");
    printf("\033[01;33m");
    for (i = 0; i < 12; i++) if (stars_to_use[i] == 0) printf("%d  ", i+1);
    printf("\033[0m");
    printf("\n\n");

    /* Printing the numbers deleted and non-deleted */
    printf("N O T  U S E D / D E L E T E D   ");
    printf("\033[1;31m");
    printf("N U M B E R S");
    printf("\033[0m");
    printf(" - ");
    printf("\033[0;35m");
    printf("S T A R S\n\n");
    printf("\033[1;31m");
    k = 0;
    for (i = 0; i < 50; i++) if (numbers_to_use[i] == 0){
    
        k++;
        printf("%d  ", i+1);
        if (k == 5) {

            printf("\n");
            k = 0;
        }
    }
    printf("\n");
    printf("\033[0m");
    printf("Numbers that appear less: ");
    printf("\033[1;31m");
    for (i = 0; i < q_N; i++) printf("%d  ", appear_less_n[i]);
    printf("\n\n");
    printf("\033[0;35m");
    for (i = 0; i < 12; i++) if (stars_to_use[i] == 0) printf("%d  ", i+1);
    printf("\n");
    printf("\033[0m");
    printf("Stars that appear less: ");
    printf("\033[1;35m");
    for (i = 0; i < q_S; i++) printf("%d  ", appear_less_s[i]);
    printf("\033[0m");

    printf("\n\nN U M B E R S  T O  B E T\n");
    printf("Numbers with the times that each one appeared.\n");
    printf("\033[0;32m");
    k = 0;
    for (i = 0, j = 0, n = 0; i < 50; i++) {
        
        for (n = 0; n < q_N; n++) {

            if (numbers_to_use[i] == 0 || appear_less_n[n] == i+1){
            
                bool_v = 1;
                break;
            }
            else bool_v = 0;
        }
        if (bool_v == 0){
            
            j++;
            k++;
            printf("%d: ", i+1);
            printf("\033[0m");
            printf("%d  ", numbers[i]);
            printf("\033[0;32m");
            if (k == 5){
            
                printf("\n");
                k = 0;
            }
            stars_to_bet = (int*)realloc(stars_to_bet, j*sizeof(int));
            stars_to_bet[j-1] = i+1;
        }
        
        bool_v = 0;
    }
    printf("\033[0m");

    printf("\n\nS T A R S  T O  B E T\n");
    printf("\033[0;36m");
    for (i = 0, k = 0; i < 12; i++) {
        
        for (n = 0; n < q_S; n++) {

            if (stars_to_use[i] == 0 || appear_less_s[n] == i+1){
            
                bool_v = 1;
                break;
            }
            else bool_v = 0;
        }
        if (bool_v == 0){
            
            k++;
            printf("%d: ", i+1);
            printf("\033[0m");
            printf("%d  ", stars[i]);
            printf("\033[0;36m");
            stars_to_bet = (int*)realloc(stars_to_bet, k*sizeof(int));
            stars_to_bet[k-1] = i+1;
        }
        bool_v = 0;
    }
    printf("\033[0m");
    printf("\n");

    /* Checking all the possible combinations */
    combinations = check_number_combinations(num);
    if (combinations == NULL) {

        printf("Error while checking combinations in line 46.\n");
        return -1;
    }

    /* Printing the combinations */
COMB:    printf("Which number do you want to see the combinations?\n");
    scanf("%d", &input);
    if (input > 50 || input < 0) {

        printf("Error with the input try a number between 1 - 50.\n");
        goto COMB;
    }

    flag = print_combination_number(combinations, input);
    if (flag == -1) {

        printf("Error in print_combination_number.\n");
        return -1;
    }

    /* Checking all the possible combinations */
    combinations_s = check_star_combinations(num);
    if (combinations_s == NULL) {

        printf("Error while checking combinations in line 46.\n");
        return -1;
    }

    /* Printing the combinations */
COMB_2:    printf("Which star do you want to see the combinations?\n");
    scanf("%d", &input);
    if (input > 12 || input < 1) {

        printf("Error with the input try a number between 1 - 12.\n");
        goto COMB_2;
    }

    flag = print_combination_star(combinations_s, input);
    if (flag == -1) {

        printf("Error in print_combination_star.\n");
        return -1;
    }

    flag = check_combination_input_number(num);
    if (flag == -1) {

        printf("Error in check_combination_input_number.\n");
        return -1;
    }

    flag = check_combination_input_star(num);
    if (flag == -1) {

        printf("Error in check_combination_input_star.\n");
        return -1;
    }

    for (i = 0; i < num->stored_combinations; i++) free(num->combinations[i]);
    free(num);
    for (i = 0; i < 50; i++) free(combinations[i]);
    free(combinations);
    for (i = 0; i < 12; i++) free(combinations_s[i]);
    free(combinations_s);
    free(stars);
    free(numbers);
    free(appear_less_n);
    free(appear_less_s);
    free(repeated_num);
    free(repeated_stars);
    free(stars_to_use);
    free(numbers_to_use);

    return 0;
}