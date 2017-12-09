//
//  main.c
//  treestruct
//
//  Created by 津田準 on 2017/12/08.
//  Copyright © 2017 津田準. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct EMPLOYEE {
    char name[10];
    struct EMPLOYEE *next;
};

struct DEPARTMENT {
    struct DEPARTMENT *child;
    struct DEPARTMENT *sibling;
    char name[10];
    struct EMPLOYEE *employee;
};

struct DEPARTMENT head;
struct EMPLOYEE owner;

void error(char *s){
    fprintf(stderr, s);
    exit(1);
}

void initialize(){
    strcpy(owner.name, "syatyo");
    head.employee = &owner;
    strcpy(head.name, "CEO");
}

struct DEPARTMENT* search(struct DEPARTMENT *department, char name[20]){
    struct DEPARTMENT *current;
    if(strcmp(name, "CEO") == 0)
        return &head;
    current = department -> child;
    if(current == NULL)
        return NULL;
    while( current != NULL){
        if(strcmp(current -> name, name) == 0)
            return current;
        struct DEPARTMENT *result = search(current, name);
        if(result == NULL){
            current = current -> sibling;
        }else{
            return result;
        }
    }
    
    return NULL;
}

int addEmployee(char department[20], char name[20]){
    struct DEPARTMENT *dep = search(&head, department);
    struct EMPLOYEE *new = malloc(sizeof(struct EMPLOYEE));
    if(dep == NULL)
        error("部署が存在しません\n");
    if(dep -> employee == NULL){
        strcpy(new -> name, name);
        new -> next = NULL;
        dep -> employee = new;
    }else{
        strcpy(new -> name, name);
        new -> next = dep -> employee;
        dep -> employee = new;
    }
    return 1;
}

void listEmoloyee(char name[20]){
    struct DEPARTMENT *dep = search(&head, name);
    if(dep == NULL)
        return;
    struct EMPLOYEE *emp;
    for(emp = dep -> employee; emp != NULL; emp = emp -> next){
        printf("%s\n", emp -> name);
    }
    
}

int addDepartment(struct DEPARTMENT *parent, char name[20]){
    if(parent == NULL)
        error("the department doesnt exist\n");
    struct DEPARTMENT *p = malloc(sizeof(struct DEPARTMENT));
    if(parent -> child == NULL){
        strcpy(p -> name, name);
        p -> sibling = NULL;
        p -> child = NULL;
        p -> employee = NULL;
        parent -> child = p;
    }else{
        p -> sibling = parent -> child;
        p -> child = NULL;
        p -> employee = NULL;
        strcpy(p -> name, name);
        parent -> child = p;
    }
    return 1;
}

void listDepartment(struct DEPARTMENT *department){
    if(department == NULL)
        return;
    struct DEPARTMENT *p;
    printf("%s\n", department -> name);
    for(p = department -> child; p != NULL; p = p -> sibling){
        listDepartment(p);
    }
}

int main(int argc, const char * argv[]) {
    initialize();
    int flg = 1;
    while(flg){
        int a = 0;
        char parent[20] = "\0";
        char name[20] = "\0";
        char dep[20] = "\0";
        printf("部署を追加 : 1\n");
        printf("社員を追加 : 2\n");
        printf("部署一覧を表示 : 3\n");
        printf("社員一覧を表示 : 4\n");
        printf("終了 : 5\n");
        scanf("%d", &a);
        switch(a){
            case 1:
                printf("親となる部署名を入力してください\n");
                scanf("%s", parent);
                printf("部署名を入力してください\n");
                scanf("%s", name);
                addDepartment(search(&head,parent), name);
                printf("部署が追加されました\n");
                break;
            case 2:
                printf("追加する部署名を入力してください\n");
                scanf("%s", dep);
                printf("社員名を入力してください\n");
                scanf("%s", name);
                addEmployee(dep, name);
                printf("社員が追加されました\n");
                break;
            case 3:
                printf("部署一覧は以下の通りです\n");
                listDepartment(&head);
                break;
            case 4:
                printf("一覧を表示する部署名を入力してください\n");
                scanf("%s", dep);
                printf("%sの社員は以下の通りです\n", dep);
                listEmoloyee(dep);
                break;
            case 5:
                flg = 0;
                break;
            default:
                flg = 1;
                break;
        }
    }
    
    return 0;
}
