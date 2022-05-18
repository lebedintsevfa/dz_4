#include <stdio.h>
#include <stdlib.h>

int check_symmetry(int** matrix, int N); //проверяет, симметричную лиматрицу мы ввели
void create_graphviz(int** matrix, int N); //создает файл graphviz в папке с этимфайлом с названием new_graph.dot
void sort_top(int** matrix, int N); //сортирует в порядке убывания вершины счетными степенями
//сами функции в конце программы

struct Top // эта структура используется в ф-ии sort_top и хранит в себе вершину и ее степень 
{
    int name_top;
    int degree_top;

};

int main(){
    int i = 0, j = 0, num = 0;
    char symbol;
    int** mass = (int**)calloc(i + 1, sizeof(int*) );
    mass[i] = (int*)calloc(i + 1, sizeof(int));
    printf("Enter the adjacency matrix:\n");// запоняем матрицу смежности
    while ((symbol = getchar()) != '\n'){
        if ((symbol <= '9') && (symbol >= '0')){
            num = num * 10 + (int)(symbol - '0');
        }
        if (symbol == ' '){
            mass[i][j++] = num;
             num = 0;
             mass[i] = (int*)realloc(mass[i], sizeof(int) * (j + 1));
        }
    }
    mass[i][j] = num;
    i++;
    int size;
    size = j + 1;
    mass = (int**)realloc(mass, sizeof(int*) * size);
    for (int i = 1; i < size; i++){
        mass[i] = (int*)malloc(sizeof(int) * size);
    }
    for (int i = 1; i < size; i++){
        for (int j = 0; j < size; j++){
            scanf("%d", &mass[i][j]);
        }
    }
    if (check_symmetry(mass, size)) { // проверяем на симметричность
        printf("Your matrix not symmetrical! Try again!\n");
        return 0;
    }
    create_graphviz(mass, size); // создаем файл в graphviz
    sort_top(mass, size); // сортируем вершины в порядке убывания четных степеней
    for (int i = 0; i < size; i++) { // очищаем за собой динамическую память
        free(mass[i]);
    }
    free(mass);
    return 0;
}

int check_symmetry(int** matrix, int N){ // Функция проверки на симметричность нашей матрицы
    for (int i = 0; i < N; i++){
        for (int j = 0; j < i; j++){
            if (matrix[i][j] != matrix[j][i])
            return 1;
        }
    }
    return 0;
}

void create_graphviz(int** matrix, int N){
    FILE* file_graph;
    file_graph = fopen("new_graph.gv", "w+"); //создаем файл или открываем файл для записи
    fprintf(file_graph, " graph Graph {\n");
    for (int i = 0; i < N; i++) { // записываем в него вершины
        for (int j = 0; j <= i; j++){
            for (int x = 0; x < matrix[i][j]; x++){
                fprintf(file_graph, "%d--%d\n", i, j);
            }
        }
    }
    fprintf(file_graph, "}");
    fclose(file_graph); //закрываем файл
}

void sort_top(int** matrix, int N){
    int size_array = 0;
    struct Top* array = (struct Top*)calloc(size_array + 1, sizeof(struct Top)); // создаем динамический массив структуры Top
    for (int i = 0; i < N; i++) { // заполняем динамический массив структуры Top 
        int step = 0;
        for (int j = 0; j < N; j++){
            if (i == j){
                step = step + matrix[i][j] * 2;
            }
            else{
                step += matrix[i][j];
            }
        }
        if (step % 2 == 0) {
            array[size_array].name_top = i;
            array[size_array].degree_top = step;
            size_array++;
            array = (struct Top*)realloc(array, sizeof(struct Top) * (size_array + 1));
        }
    }
    for (int i = 1; i < size_array; i++) { // сортируем динамический массив структуры Top
        for (int j = i; j > 0; j--){
            if (array[j].degree_top > array[j - 1].degree_top){
                int tmp = array[j].degree_top;
                array[j].degree_top = array[j - 1].degree_top;
                array[j - 1].degree_top = tmp;
                tmp = array[j].name_top;
                array[j].name_top = array[j - 1].name_top;
                array[j - 1].name_top = tmp;
            }
        }
    }
    printf("\nSorted tops by even degrees:\n");
    for (int i = 0; i < size_array; i++) { // выводим результат
        printf("Top %d -- degree = %d\n", array[i].name_top, array[i].degree_top);
    } 
    printf("\n");
    system("dot new_graph.gv -Tpng -o new_graph.png");
    system("new_graph.png");
    free(array); // чистим за собой память, выделенную динамически
}








