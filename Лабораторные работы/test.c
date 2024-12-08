#include <stdio.h>
#include <ctype.h>
#include <string.h>

int startsWithVowel(const char* word) {
    if (!word || word[0] == '\0') return 0;
    
    char first = tolower((unsigned char)word[0]);

    return (first == 'a' || first == 'e' || first == 'i' || first == 'o' || 
            first == 'u' || first == 'y' || first == 'а' || first == 'е' || 
            first == 'ё' || first == 'и' || first == 'о' || first == 'у' || 
            first == 'ы' || first == 'э' || first == 'ю' || first == 'я');
}
int main() {
    const char* words[] = {"привет", "apple", "арбуз", "ёлка", "море", "umbrella"};
    
    for (int i = 0; i < 6; i++) {
        printf("Слово: %s, начинается с гласной: %s\n", 
               words[i], startsWithVowel(words[i]) ? "Да" : "Нет");
    }
    
    return 0;
}
