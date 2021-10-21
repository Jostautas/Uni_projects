#include <stdio.h>

int reading_n();
int *reading_2d_array(int n);
int reading_with_validation();
int *smallest_numbers(int n, int *elements);
int biggest_from_smallest(int n, int *small_elem);
void printing(int n, int biggest, int *elements);

int main(){
    int biggest, *elements, *small_elem;
    int n = reading_n();
    elements = reading_2d_array(n);
    small_elem = smallest_numbers(n, *&elements);
    biggest = biggest_from_smallest(n, *&small_elem);
    printing(n, biggest, *&elements);
    return 0;
}

int reading_n(){
    printf("Please enter the size of a data square\n");
    int n = reading_with_validation(0);
    return n;
}

int *reading_2d_array(int n){
    int temp;
    int *pointer = malloc(n*n*sizeof(int));
    printf("You have entered %d successfuly\nNow please enter your data in a %d by %d square (from left to right, from top to bottom)\n", n, n, n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            temp = reading_with_validation(1);
            *(pointer+i*n+j) = temp;
        }
    }
    return *&pointer;
}

int reading_with_validation(int allow_negative_numbers){
    int input;
    while(1){
        if((scanf("%d", &input) == 1) && (getchar() == '\n')){
            if((allow_negative_numbers == 0) && (input > 0))
                return input;
            else
                return input;
        }
        printf("INPUT ERROR\n");
        while(getchar() != '\n'); // clearing buffer, so that scanf() can take another value
    }
}

int *smallest_numbers(int n, int *elements){
    int min;
    int *pointer = malloc(n*sizeof(int));
    for(int i = 0; i < n; ++i){
        min = *(elements+i*n);
        for(int j = 1; j < n; ++j){
            if(min > *(elements+i*n+j)){
                min = *(elements+i*n+j);
            }
        }
        *(pointer+i) = min;
    }
    return *&pointer;
}

int biggest_from_smallest(int n, int *small_elem){
    int max = *small_elem;
    for(int i = 1; i < n; ++i){
        if(*(small_elem+i) > max){
            max = *(small_elem+i);
        }
    }
    return max;
}

void printing(int n, int biggest, int *elements){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(*(elements+i*n+j) == biggest){
                printf("The number coordinates are (%d; %d)(row; column) and the number is %d\n", i+1, j+1, biggest);
                return;
            }
        }
    }
}