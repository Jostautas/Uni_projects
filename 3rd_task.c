#include <stdio.h>
#include <stdlib.h>

int check_txt(unsigned int current_size, char *F_name){
    for (unsigned int i = 1; i < current_size; ++i){
        if (F_name[i] == '.' && F_name[i + 1] == 't' && F_name[i + 2] == 'x' && F_name[i + 3] == 't'){
            printf("Entered file name is - %s\n", F_name);
            return 1;
        }
    }
    return 0;
}

char *reading(char *F_name, unsigned int default_len, unsigned int current_size){
    int bool = 0;
    do{
        if(F_name != NULL){
            char c = EOF;
            unsigned int i = 0;
            while((c = getchar()) != '\n' && c != EOF){
                F_name[i] = c;
                ++i;
                if(i == current_size){
                    current_size += default_len;
                    F_name = (char *) realloc(F_name, current_size);
                    if(F_name == NULL){
                        printf("ERROR0 - error reallocating memory\n");
                        return 0;
                    }
                }
            }
            ++i;
            F_name[i] = '\0';
            bool = check_txt(current_size, F_name);
        }
        else{
            printf("ERROR1 - please enter a correct file name\n");
        }
        if(bool == 0){
            printf("ERROR2 - please enter a correct file name\n");
        }
    }while(bool == 0);
    return F_name;
}

void clear_outpup_file(FILE **Out_file, char *Output_f){
    *Out_file = fopen(Output_f, "w");
    fclose(*Out_file);
}

void check_and_print(char *Temp, unsigned int *i, FILE **Out_file, char *Output_f){
    *Out_file = fopen(Output_f, "a");

    if(*Out_file != 0){
        if(Temp[0] != Temp[*i-2]){
            for(unsigned int j = 0; j < *i; ++j){
                fputc(Temp[j], *Out_file);
            }
        }
        fputc(' ', *Out_file);
        *i = 0;
    }
    else{
        printf("ERROR3 - I/O error\n");
    }

    fclose(*Out_file);
}

void print_one(unsigned int *i, FILE **Out_file, char *Output_f, char temp){
    *Out_file = fopen(Output_f, "a");

    if(*Out_file != 0){
        fputc(temp, *Out_file);
        fputc(' ', *Out_file);
        *i = 0;
    }
    else{
        printf("ERROR3 - I/O error\n");
    }

    fclose(*Out_file);
}

void print_space(unsigned int *i, FILE **Out_file, char *Output_f){
    *Out_file = fopen(Output_f, "a");

    if(*Out_file != 0){
        fputc(' ', *Out_file);
    }
    else{
        printf("ERROR3 - I/O error\n");
    }

    fclose(*Out_file);
    *i = 0;
}

void rewrite(char *Input_f, char *Output_f, unsigned int default_len){
    char temp, *Temp = malloc(default_len);
    unsigned int i = 0, current_size = default_len;

    FILE *In_file;
    FILE *Out_file;
    In_file = fopen(Input_f, "r");

    free(Input_f);
    Input_f = NULL;

    clear_outpup_file(&Out_file, Output_f);

    if(In_file != 0 && Out_file != 0){
        while(((temp = fgetc(In_file)) != 0)){
            if(feof(In_file) != 0){
                check_and_print(Temp, &i, &Out_file, Output_f);
                break;
            }
            else if(temp != ' '){
                Temp[i] = temp;
                ++i;
                if(i == current_size){
                    current_size += default_len;
                    Temp = realloc(Temp, current_size);
                }
            }
            else if(i > 1){
                check_and_print(Temp, &i, &Out_file, Output_f);
            }
            else if(i == 1){
                print_one(&i, &Out_file, Output_f, Temp[0]);
            }
            else{
                print_space(&i, &Out_file, Output_f);
            }
        }
        fclose(In_file);

        free(Temp);
        Temp = NULL;
    }
    else{
        printf("ERROR4 - I/O error\n");
        return;
    }
    printf("Result successfuly printed to %s\n", Output_f);

    free(Output_f);
    Output_f = NULL;
}

int main(){
    unsigned int default_len = 30;
    unsigned int in_f_len = default_len, out_f_len = default_len;
    char *Input_f = (char *) malloc(default_len), *Output_f = (char *) malloc(default_len);
    
    printf("Enter input file name (with extention \".txt\")\n");
    Input_f = (char*) reading(Input_f, default_len, in_f_len);
    if(Input_f == NULL){
        printf("ERROR5 - error returning reallocated memory address");
        return 0;
    }

    printf("Enter output file name (with extention \".txt\")\n");
    Output_f =(char*) reading(Output_f, default_len, out_f_len);
    if(Output_f == NULL){
        printf("ERROR6 - error returning reallocated memory address");
        return 0;
    }
    
    rewrite(Input_f, Output_f, default_len);

    return 0;
}