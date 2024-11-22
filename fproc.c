#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

FILE *fptr, *output_fptr;
char content[1000];  


int is_valid_float(const char *str) {
    char *endptr;
    strtod(str, &endptr);  
    return *endptr == 0; 
}

int main() {
    
    fptr = fopen("data.txt", "r");

    if (fptr != NULL) {
        printf("File opened successfully.\n");

        
        output_fptr = fopen("output.txt", "w");
        if (output_fptr == NULL) {
            printf("Error opening output file.\n");
            fclose(fptr);
            return 1;
        }

        int invalid_count = 0;
        long position;  
        fseek(fptr, 0, SEEK_END);
        while (fgets(content, 1000, fptr)) {
           

            
            if (is_valid_float(content)) {
                float value;
                sscanf(content, "%f", &value);
                fprintf(output_fptr, "%f\n", value);  
            } else {
            
                invalid_count++;
            }

        }

       
        if (ferror(fptr)) {
            printf("Error occurred while reading the file.\n");
            fclose(fptr);
            fclose(output_fptr);
            return 1;
        }

        
        if (feof(fptr)) {
            printf("End of file reached.\n");
        }

       
        fclose(fptr);
        fclose(output_fptr);

        
        printf("Number of invalid float values: %d\n", invalid_count);
    } else {
        printf("File not opened\n");
        return 1;
    }

    return 0;
}
