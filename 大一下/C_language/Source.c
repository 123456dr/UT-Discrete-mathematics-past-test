#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>  // 提供 strtok, strcat, strcspn
#include <stdlib.h>  // 提供 atoi, atol
#include <time.h>
#include <stdbool.h>
/*
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
char toDirChar[] = {'N', 'E', 'S', 'W'};

int getDir(char c){
    if(c == 'N')return 0;
    if(c == 'E')return 1;
    if(c == 'S')return 2;
    if(c == 'W')return 3;
}
*/
struct dataStruct {
    int number;
    float one;
    float two;
    char worker[100];
    char y;
};
int main() {
    puts("================================================");
    puts("員工工作與出勤績效管理系統");
    puts("================================================");
    puts("1. 輸入員工績效\n2. 顯示所有員工績效\n3. 顯示平均績效\n4. 顯示工作高於平均績效員工\n5. 顯示出勤高於平均績效員工\n0. 離開系統");
    int a;
    while (true) {
        printf("請選擇: ");
        scanf("%d", &a);
        if (a >= 0 && a <= 5) break;
        else puts("錯誤 請重新輸入 ");
    }
    
    char name[100];
    printf("請輸入績效檔案名稱: ");
    scanf("%s", &name);

    struct dataStruct data = { 0, 0.0, 0.0, "", ""};
    if (a == 1) {
        FILE* wfin = fopen(name, "r");
        if (wfin == NULL) return 1;
        rewind(wfin);
        while (data.number!=0) {
            printf("輸入員工編號: ");
            fseek(wfin, (data.number - 1) * sizeof(struct dataStruct), SEEK_SET);
            scanf("%d", &data.number);
            fwrite(&data, sizeof(struct dataStruct), 1, wfin);

            printf("輸入員工姓名: ");
            scanf("%s", &data.worker);
            fwrite(&data, sizeof(struct dataStruct), 1, wfin);

            printf("輸入工作績效(0~100): ");
            scanf("%f", &data.one);
            fwrite(&data, sizeof(struct dataStruct), 1, wfin);

            printf("輸入出勤績效(0~100): ");
            scanf("&f", &data.two);
            fwrite(&data, sizeof(struct dataStruct), 1, wfin);
            
            printf("是否繼續輸入(y/n)? ");
            scanf("%c", &data.y);
            fwrite(&data, sizeof(struct dataStruct), 1, wfin);
            if (data.y == 'y') {
                puts("\n");
                puts("資料已存入檔案!");
                break;
            }
            else {
                puts("資料已存入檔案!");
                break;
            }
        }
        fclose(wfin);
    }
    else if (a == 2) {
        FILE* fin = fopen(name, "r");
        if (fin == NULL) return 1;
        puts("================================================");
        puts("編號  姓名      工作績效  出勤績效");
        puts("================================================");
        int ex = 0;
        while (true) {
            fscanf(fin, "%d %s %f %f", &data.number, &data.worker, &data.one, &data.two);
            if (ex == data.number) break;
            ex = data.number;
            printf("%3d%8s%10.2f%10.2f\n", data.number, data.worker, data.one, data.two);
        }
        fclose(fin);
    }
    else if (a == 3) {
        FILE* fin = fopen(name, "r");
        if (fin == NULL) return 1;
        float ans = 0;
        float ans2 = 0;
        float count = 0;
        int ex = 0;
        while (true) {
            fscanf(fin, "%d %s %f %f", &data.number, &data.worker, &data.one, &data.two);
            if (ex == data.number) break;
            ex = data.number;
            ans += data.one;
            ans2 += data.two;
            count++;
        }
        ans = ans / count;
        ans2 = ans2 / count;
        printf("%s", "平均工作績效: ");
        printf("%.2f", ans);
        puts("");
        printf("%s", "平均出勤績效: ");
        printf("%.2f", ans2);
        fclose(fin);
    }
    else if (a == 4) {
        FILE* fin = fopen(name, "r");
        if (fin == NULL) return 1;
        float ans = 0;
        float count = 0;
        int ex = 0;
        puts("===============工作高於平均績效的員工=================");
        puts("編號  姓名      工作績效  出勤績效");
        while (true) {
            fscanf(fin, "%d %s %f %f", &data.number, &data.worker, &data.one, &data.two);
            if (ex == data.number) break;
            ex = data.number;
            ans += data.one;
            count++;
        }
        fclose(fin);
        fin = fopen(name, "r");
        if (fin == NULL) return 1;
        ans = ans / count;
        ex = -1;
        while (true) {
            fscanf(fin, "%d %s %f %f", &data.number, &data.worker, &data.one, &data.two);
            if (ex == data.number) break;
            ex = data.number;
            if (data.one > ans) {
                printf("%3d%8s%10.2f%10.2f\n", data.number, data.worker, data.one, data.two);
            }
        }
        fclose(fin);
    }
    else if (a == 5) {
        FILE* fin = fopen(name, "r");
        if (fin == NULL) return 1;
        float ans2 = 0;
        float count = 0;
        int ex = 0;
        puts("===============出勤高於平均績效的員工=================");
        puts("編號  姓名      工作績效  出勤績效");
        while (true) {
            fscanf(fin, "%d %s %f %f", &data.number, &data.worker, &data.one, &data.two);
            if (ex == data.number) break;
            ex = data.number;
            ans2 += data.two;
            count++;
        }
        ans2 = ans2 / count;
        ex = -1;
        fclose(fin);
        fin = fopen(name, "r");
        if (fin == NULL) return 1;
        while (true) {
            fscanf(fin, "%d %s %f %f", &data.number, data.worker, &data.one, &data.two);

            if (ex == data.number) break;
            ex = data.number;
            if (data.two > ans2) {
                printf("%3d%8s%10.2f%10.2f\n", data.number, data.worker, data.one, data.two);
            }
        }
        fclose(fin);
    }
    else if (a == 0) {
        puts("程式結束!");
    }
    return 0;
}



