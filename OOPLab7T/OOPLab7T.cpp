#include <iostream>
#include <cstring>
#include <clocale>

        using namespace std;


// ЗАВДАННЯ 1.5: Функція-шаблон для пошуку мінімуму в масиві

template <typename T>
T find_min(T * arr, int size) {
    T min_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

template <>
char* find_min<char*>(char** arr, int size) {
    char* min_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (strcmp(arr[i], min_val) < 0) {
            min_val = arr[i];
        }
    }
    return min_val;
}



// ЗАВДАННЯ 2.5: Бінарний пошук та просте сортування


template <typename T>
void sort_array(T* arr, int size) {
   
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

template <typename T>
int binary_search(T* arr, int size, T key) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == key) {
            return mid; 
        }
        if (arr[mid] < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; 
}

template <>
void sort_array<char*>(char** arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


template <>
int binary_search<char*>(char** arr, int size, char* key) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(arr[mid], key);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}


// 3.5: Клас Матриця

template <typename T>
class Matrix {
public:
    int rows;
    int cols;
    T** data; 

    Matrix(int r, int c) {
        rows = r;
        cols = c;
        data = new T * [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0; 
            }
        }
    }

  
    Matrix(const Matrix& other) {
        rows = other.rows;
        cols = other.cols;
        data = new T * [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

   
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;

        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;

        rows = other.rows;
        cols = other.cols;
        data = new T * [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    T* operator[](int index) {
        return data[index];
    }

    Matrix operator+(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Помилка: Розмiри матриць не спiвпадають!" << endl;
            return *this;
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix& operator+=(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Помилка: Розмiри матриць не спiвпадають!" << endl;
            return *this;
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return *this;
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};


// 4.5: Список (List) та Ітератор


template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head; 

public:
    List() {
        head = nullptr;
    }

    ~List() {
        
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void push_back(T val) {
        Node* newNode = new Node;
        newNode->data = val;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) {
            current = node;
        }

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};


// Перевірка роботи коду

int main() {
    setlocale(LC_CTYPE, "ukr");

    cout << "--- Тест 1.5: Пошук мiнiмуму ---\n";
    int int_arr[] = { 40, 20, 10, 50, 30 };
    cout << "Мiнiмум в масивi int: " << find_min(int_arr, 5) << endl;

    char* str_arr[] = { (char*)"cherry", (char*)"apple", (char*)"banana" };
    cout << "Мiнiмальний рядок: " << find_min(str_arr, 3) << endl << endl;


    cout << "--- Тест 2.5: Сортування та бiнарний пошук ---\n";
    double double_arr[] = { 5.5, 1.1, 3.3, 2.2, 4.4 };
    sort_array(double_arr, 5); 

    cout << "Вiдсортований масив double: ";
    for (int i = 0; i < 5; i++) cout << double_arr[i] << " ";
    cout << endl;

    cout << "Iндекс елемента 3.3: " << binary_search(double_arr, 5, 3.3) << endl << endl;


    cout << "--- Тест 3.5: Робота з Матрицею ---\n";
    Matrix<int> M1(2, 2);
    M1[0][0] = 1; M1[0][1] = 2;
    M1[1][0] = 3; M1[1][1] = 4;

    Matrix<int> M2(2, 2);
    M2[0][0] = 10; M2[0][1] = 20;
    M2[1][0] = 30; M2[1][1] = 40;

    cout << "Матриця M1:\n"; M1.print();
    cout << "Матриця M2:\n"; M2.print();

    Matrix<int> M3 = M1 + M2;
    cout << "Результат додавання M1 + M2:\n"; M3.print();
    cout << endl;


    cout << "--- Тест 4.5: Список та Iтератор ---\n";
    List<int> my_list;
    my_list.push_back(100);
    my_list.push_back(200);
    my_list.push_back(300);

    cout << "Елементи списку через iтератор: ";
    for (List<int>::Iterator it = my_list.begin(); it != my_list.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
