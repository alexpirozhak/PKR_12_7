#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Структура для зберігання інформації про абітурієнта
struct Abiturient {
    string surname;
    int score;
    string documentType;
    Abiturient* next;
};

// Функція для створення нового елемента списку
Abiturient* createNode(string surname, int score, string documentType) {
    Abiturient* newNode = new Abiturient();
    newNode->surname = surname;
    newNode->score = score;
    newNode->documentType = documentType;
    newNode->next = nullptr;
    return newNode;
}

// Функція для додавання елемента до списку
void appendNode(Abiturient*& head, string surname, int score, string documentType) {
    Abiturient* newNode = createNode(surname, score, documentType);
    if (!head) {
        head = newNode;
    } else {
        Abiturient* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Функція для друку списку
void printList(Abiturient* head) {
    Abiturient* temp = head;
    while (temp) {
        cout << "Surname: " << temp->surname << ", Score: " << temp->score << ", Document: " << temp->documentType << endl;
        temp = temp->next;
    }
}

// Функція для створення списку рекомендованих абітурієнтів
Abiturient* filterList(Abiturient* head, int passingScore) {
    Abiturient* newHead = nullptr;
    Abiturient* temp = head;
    while (temp) {
        if (temp->score >= passingScore) {
            appendNode(newHead, temp->surname, temp->score, temp->documentType);
        }
        temp = temp->next;
    }
    return newHead;
}

int main() {
    Abiturient* head = nullptr;
    string inputChoice;

    cout << "Read data from file or input manually? (file/manual): ";
    cin >> inputChoice;

    if (inputChoice == "file") {
        ifstream inputFile("abiturients.txt");
        if (inputFile.is_open()) {
            string surname;
            int score;
            string documentType;
            while (inputFile >> surname >> score >> documentType) {
                appendNode(head, surname, score, documentType);
            }
            inputFile.close();
        } else {
            cout << "Unable to open file." << endl;
            return 1;
        }
    } else if (inputChoice == "manual") {
        string surname;
        int score;
        string documentType;
        char continueInput;
        do {
            cout << "Enter surname: ";
            cin >> surname;
            cout << "Enter score: ";
            cin >> score;
            cout << "Enter document type (original/duplicate): ";
            cin >> documentType;
            appendNode(head, surname, score, documentType);
            cout << "Continue input? (y/n): ";
            cin >> continueInput;
        } while (continueInput == 'y');
    } else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    cout << "Original list of abiturients:" << endl;
    printList(head);

    int passingScore;
    cout << "Enter the passing score: ";
    cin >> passingScore;

    Abiturient* recommendedList = filterList(head, passingScore);

    cout << "List of recommended abiturients:" << endl;
    printList(recommendedList);

    return 0;
}
