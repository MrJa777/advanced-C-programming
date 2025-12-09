#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define MAX_WORDS 1000

using namespace std;

char **foo(const char *filename)
{
    char **list = (char**)malloc(sizeof(char*) * MAX_WORDS);

    char tmp[100];
    int i = 0;

    FILE *fp = fopen(filename, "r");
    if (!fp) return nullptr;

    while (fscanf(fp, "%s", tmp) == 1) {
        list[i] = (char*)malloc(strlen(tmp) + 1);
        strcpy(list[i], tmp);
        i++;
    }

    fclose(fp);
    return list;
}

int main()
{
    char **words = foo("data.txt");
    for (int i = 0; i < MAX_WORDS && words[i] != NULL; i++)
    {
        cout << words[i] << endl;
        free(words[i]);
    }
    return 0;
}