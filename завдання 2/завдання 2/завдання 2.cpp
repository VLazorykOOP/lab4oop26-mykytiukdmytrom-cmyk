#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

// Структура, яка представляє пару асоційованих сутностей
struct Product {
    std::string name;
    int inventoryNumber;
};

// Клас асоціативного масиву
class InventoryDictionary {
private:
    std::vector<Product> data; // Внутрішнє сховище товарів
    int dummy;                 // Фіктивна змінна для безпечного повернення посилання при помилці

public:
    int CodeError; // Змінна для збереження коду помилки (0 - ОК, 1 - не знайдено)

    // Конструктор
    InventoryDictionary() : CodeError(0), dummy(-1) {}

    // Метод для додавання однієї асоціативної сутності
    void addEntity(const std::string& name, int invNum) {
        data.push_back({ name, invNum });
    }

    // Перевантаження операції індексації []
    int& operator[](const std::string& key) {
        CodeError = 0; // Скидаємо помилку перед пошуком
        for (auto& item : data) {
            if (item.name == key) {
                return item.inventoryNumber; // Повертаємо посилання на знайдену сутність
            }
        }
        CodeError = 1; // Якщо не знайдено, встановлюємо код помилки
        return dummy;  // Повертаємо фіктивну змінну
    }

    // Перевантаження операції виклику функції () (альтернативне звернення)
    int& operator()(const std::string& key) {
        return (*this)[key]; // Повторно використовуємо логіку перевантаженого оператора []
    }

    // Дружня операція виведення <<
    friend std::ostream& operator<<(std::ostream& out, const InventoryDictionary& dict) {
        if (dict.data.empty()) {
            out << "Склад порожній.\n";
            return out;
        }
        out << "--------------------------------------\n";
        for (const auto& item : dict.data) {
            out << "Товар: " << item.name << "\t| Інв. номер: " << item.inventoryNumber << "\n";
        }
        out << "--------------------------------------\n";
        return out;
    }

    // Дружня операція введення >>
    friend std::istream& operator>>(std::istream& in, InventoryDictionary& dict) {
        std::string name;
        int invNum;
        std::cout << "Введіть назву товару: ";
        in >> name;
        std::cout << "Введіть інвентарний номер: ";
        in >> invNum;

        dict.addEntity(name, invNum);
        return in;
    }
};

// Функція створення базового набору асоціативних сутностей
void createInitialSet(InventoryDictionary& dict) {
    dict.addEntity("Ноутбук", 10001);
    dict.addEntity("Монітор", 10002);
    dict.addEntity("Клавіатура", 10003);
    dict.addEntity("Миша", 10004);
}

int main() {
    // Налаштування консолі для коректного відображення української мови у Visual Studio
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    InventoryDictionary warehouse;

    // 1. Створення набору сутностей
    std::cout << "=== Ініціалізація складу ===\n";
    createInitialSet(warehouse);
    std::cout << warehouse;

    // 2. Демонстрація перевантаженої операції індексації []
    std::cout << "\n=== Пошук через оператор [] ===\n";
    std::string searchKey1 = "Монітор";
    int inv1 = warehouse[searchKey1];

    if (warehouse.CodeError == 0) {
        std::cout << "Знайдено: [" << searchKey1 << "] має інвентарний номер " << inv1 << "\n";
    }
    else {
        std::cout << "Помилка! Товар [" << searchKey1 << "] не знайдено.\n";
    }

    // Демонстрація роботи системи помилок (пошук неіснуючого товару)
    std::string searchKey2 = "Принтер";
    int inv2 = warehouse[searchKey2];

    if (warehouse.CodeError == 0) {
        std::cout << "Знайдено: [" << searchKey2 << "] має інвентарний номер " << inv2 << "\n";
    }
    else {
        std::cout << "Помилка (CodeError = " << warehouse.CodeError << ")! Товар [" << searchKey2 << "] не знайдено.\n";
    }

    // 3. Демонстрація альтернативного звернення через оператор ()
    std::cout << "\n=== Пошук через оператор () ===\n";
    std::string searchKey3 = "Ноутбук";
    int inv3 = warehouse(searchKey3);

    if (warehouse.CodeError == 0) {
        std::cout << "Знайдено: (" << searchKey3 << ") має інвентарний номер " << inv3 << "\n";
    }

    // 4. Демонстрація перевантаженого оператора введення >>
    std::cout << "\n=== Додавання нового товару через оператор >> ===\n";
    std::cin >> warehouse;

    std::cout << "\nОновлений стан складу:\n";
    std::cout << warehouse;

    return 0;
}