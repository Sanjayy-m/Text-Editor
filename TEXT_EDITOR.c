#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<ctype.h>

struct node {
    char val;
    struct node * next;
}* undo, * redo, * hd1, * hd2, * run, * cursor;
int cnt = 0;
void reverse() {
    struct node * nw = hd1;
    struct node * current;
    struct node * next;
    struct node * prev;
    current = nw;
    next = NULL;
    prev = NULL;
    while (current != NULL) {
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next;
    }
    hd1 = prev;
}
void undopush(char st) {
    struct node * temp1;
    temp1 = (struct node * ) malloc(sizeof(struct node));
    temp1 -> val = st;
    temp1 -> next = NULL;
    if (hd1 == NULL) {
        hd1 = temp1;
    } else {
        temp1 -> next = hd1;
        hd1 = temp1;
    }
}
void redopush(char st) {
    struct node * temp1;
    temp1 = (struct node * ) malloc(sizeof(struct node));
    temp1 -> val = st;
    temp1 -> next = NULL;
    if (hd2 == NULL) {
        hd2 = temp1;
    } else {
        temp1 -> next = hd2;
        hd2 = temp1;
    }
}
char undotop() {

    if (hd1 == NULL) {
        return '\0';
    } else {
        return hd1 -> val;
    }
}
char redotop() {
    if (hd2 == NULL) {
        return '\0';
    } else {
        return hd2 -> val;
    }
}
void undopop() {

    if (hd1 == NULL) {
        printf("");
    } else {
        hd1 = hd1 -> next;
    }
}
void redopop() {
    if (hd2 == NULL) {
        printf("");
    } else {
        hd2 = hd2 -> next;
    }

}
void WRITE(char a) {
    struct node * temp;
    temp = (struct node * ) malloc(sizeof(struct node));
    temp -> val = a;
    temp -> next = NULL;
    if (hd1 == NULL) {
        hd1 = temp;
    } else {
        temp -> next = hd1;
        hd1 = temp;
    }
    printf("\nWritten Successfully!\n");
    cnt++;
}
void UNDO() {
    char a = undotop();
    undopop();
    redopush(a);
    cnt--;
}
void REDO() {
    char a = redotop();
    redopop();
    undopush(a);
    cnt++;
}
void READ() {
    reverse();
    struct node * run = hd1;
    while (run) {
        printf("%c", run -> val);
        run = run -> next;
    }
    printf("\n");
    reverse();

}
void LOWER() {
    struct node * run = hd1;
    while (run) {
        run -> val = tolower(run -> val);
        run = run -> next;
    }
}
void UPPER() {
    struct node * run = hd1;
    while (run) {
        run -> val = toupper(run -> val);
        run = run -> next;
    }
}
void saveToFile(const char *filename) {
    reverse();
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct node *run = hd1;
    while (run) {
        fputc(run->val, file);
        run = run->next;
    }

    fclose(file);
    printf("Text saved to %s successfully!\n", filename);
    reverse();
}

void QUERY(char * q) {
    if (strcmp(q, "UNDO") == 0) {
        UNDO();
    } else if (strcmp(q, "REDO") == 0) {
        REDO();
    } else if (strcmp(q, "READ") == 0) {
        READ();
    } else if (strcmp(q, "LOWER") == 0) {
        LOWER();
    } else if (strcmp(q, "UPPER") == 0) {
        UPPER();
    } else if (strcmp(q, "REVERSE") == 0) {
        struct node * run = hd1;
        while (run) {
            printf("%c", run -> val);
            run = run -> next;
        }
        printf("\n");
    } else if (strcmp(q, "MOVE") == 0) {
        int x;
    printf("Enter the position to move:");
    scanf("%d", & x);
    if(x<=cnt){ if (x == 1) {
      cursor = NULL;
      return;
    } 
    else if (x < cnt / 2) {
      x = x + cnt / 2;
    }
    else if(x==cnt){
        cursor = hd1;
        return;
    }
    else {
      x = (cnt + 1) - x;
    }
    struct node * run = hd1;
    for (int i = 0; i < x - 2; i++) {
      run = run -> next;
    }
    cursor = run;
    }
    else{
      printf("\nEnter the Valid position!!!\n");
    }
    } else if (strcmp(q, "DELETE") == 0) {
        if (cursor == NULL) {
            struct node * prev = NULL;
            struct node * current = hd1;
            while (current -> next != NULL) {
                prev = current;
                current = current -> next;
            }
            free(current);
            prev -> next = NULL;
            cnt--;
            printf("Deleted!!\n");
            return;
        }
        else if(cursor==hd1){
            hd1 = cursor->next;
            cursor->next = NULL;
            free(cursor);
            printf("Deleted!!\n");
            cnt--;
            return;
        }
    struct node * temp;
    temp = cursor -> next;
    cursor -> next = temp -> next;
    free(temp);
    cnt--;
    printf("Deleted!!\n");
    } else if (strcmp(q, "INSERT") == 0) {
        char n;
        struct node * temp = (struct node * ) malloc(sizeof(struct node));
        printf("Enter the data:");
        scanf(" %[^\n]", & n);
        temp -> val = n;
        temp -> next = NULL;
        if (cursor == NULL) {
            struct node * run = hd1;
            while (run -> next != NULL) {
                run = run -> next;
            }
            run -> next = temp;
            cnt++;
            printf("Inserted Successfully!!\n");
            return;
        }
        else if(cursor==hd1){
            temp->next = hd1;
            hd1 = temp;
            cnt++;
            printf("Inserted Successfully!!\n");
            return;
        }
        temp -> next = cursor -> next;
        cursor -> next = temp;
        cnt++;
        printf("Inserted Successfully!!\n");
    } else {
        WRITE(q[6]);
    }
}
int main() {
    char q[100000];
    int ch;
    char filename[100]; 
    printf("\n---------------------Welcome to TEXT EDITOR---------------------\n\n\n");
    printf("Enter your choice(to continue 1 / to exit 0):");
    scanf("%d", & ch);
    while (ch) {
        printf("Enter your query:");
        scanf(" %[^\n]", q);
        QUERY(q);
        printf("\nEnter your choice(to continue 1 / to exit 0):");
        scanf("%d", & ch);
    }
    printf("Enter the filename to save the text: ");
    scanf("%s", filename);
    saveToFile(filename);

    printf("\n");
    printf("\nProgram exited successfully!!");

    return 0;
}
