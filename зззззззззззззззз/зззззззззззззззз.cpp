#include <iostream>
#include <new>

using namespace std;

class VectorInt {
private:
    int* data;
    int size;
    int codeError; // 0 - OK, 1 - Memory Error, 2 - Out of Bounds, 3 - Size Mismatch
    static int objectCount;

public:
    // --- Конструктори та деструктор ---

    // Без параметрів
    VectorInt() : size(1), codeError(0) {
        data = new (nothrow) int[size];
        if (!data) codeError = 1;
        else data[0] = 0;
        objectCount++;
    }

    // З одним параметром (розмір)
    VectorInt(int s) : size(s), codeError(0) {
        data = new (nothrow) int[size];
        if (!data) codeError = 1;
        else {
            for (int i = 0; i < size; i++) data[i] = 0;
        }
        objectCount++;
    }

    // З двома параметрами (розмір та значення)
    VectorInt(int s, int val) : size(s), codeError(0) {
        data = new (nothrow) int[size];
        if (!data) codeError = 1;
        else {
            for (int i = 0; i < size; i++) data[i] = val;
        }
        objectCount++;
    }

    // Конструктор копіювання
    VectorInt(const VectorInt& other) : size(other.size), codeError(other.codeError) {
        data = new (nothrow) int[size];
        if (!data) codeError = 1;
        else {
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        objectCount++;
    }

    // Деструктор
    ~VectorInt() {
        delete[] data;
        objectCount--;
    }

    // Статична функція для отримання кількості об'єктів
    static int getObjectCount() { return objectCount; }

    // --- Унарні оператори ---

    // Префіксний ++
    VectorInt& operator++() {
        for (int i = 0; i < size; i++) data[i]++;
        return *this;
    }

    // Постфіксний ++
    VectorInt operator++(int) {
        VectorInt temp(*this);
        ++(*this);
        return temp;
    }

    // Префіксний --
    VectorInt& operator--() {
        for (int i = 0; i < size; i++) data[i]--;
        return *this;
    }

    // Постфіксний --
    VectorInt operator--(int) {
        VectorInt temp(*this);
        --(*this);
        return temp;
    }

    // Логічне !
    bool operator!() const {
        return size != 0;
    }

    // Побітове ~
    VectorInt operator~() const {
        VectorInt temp(size);
        for (int i = 0; i < size; i++) temp.data[i] = ~data[i];
        return temp;
    }

    // Арифметичний мінус
    VectorInt operator-() const {
        VectorInt temp(size);
        for (int i = 0; i < size; i++) temp.data[i] = -data[i];
        return temp;
    }

    // --- Оператори присвоєння ---

    VectorInt& operator=(const VectorInt& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        codeError = other.codeError;
        data = new (nothrow) int[size];
        if (!data) codeError = 1;
        else {
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }

    VectorInt& operator+=(const VectorInt& other) {
        if (size != other.size) { codeError = 3; return *this; }
        for (int i = 0; i < size; i++) data[i] += other.data[i];
        return *this;
    }

    VectorInt& operator-=(const VectorInt& other) {
        if (size != other.size) { codeError = 3; return *this; }
        for (int i = 0; i < size; i++) data[i] -= other.data[i];
        return *this;
    }

    VectorInt& operator*=(int val) {
        for (int i = 0; i < size; i++) data[i] *= val;
        return *this;
    }

    VectorInt& operator/=(int val) {
        if (val == 0) { codeError = 2; return *this; }
        for (int i = 0; i < size; i++) data[i] /= val;
        return *this;
    }

    VectorInt& operator%=(int val) {
        for (int i = 0; i < size; i++) data[i] %= val;
        return *this;
    }

    VectorInt& operator|=(const VectorInt& other) {
        if (size != other.size) { codeError = 3; return *this; }
        for (int i = 0; i < size; i++) data[i] |= other.data[i];
        return *this;
    }

    VectorInt& operator^=(const VectorInt& other) {
        if (size != other.size) { codeError = 3; return *this; }
        for (int i = 0; i < size; i++) data[i] ^= other.data[i];
        return *this;
    }

    VectorInt& operator&=(const VectorInt& other) {
        if (size != other.size) { codeError = 3; return *this; }
        for (int i = 0; i < size; i++) data[i] &= other.data[i];
        return *this;
    }

    // --- Арифметичні бінарні ---

    VectorInt operator+(const VectorInt& other) const {
        VectorInt res(*this); res += other; return res;
    }

    VectorInt operator-(const VectorInt& other) const {
        VectorInt res(*this); res -= other; return res;
    }

    VectorInt operator*(int val) const {
        VectorInt res(*this); res *= val; return res;
    }

    VectorInt operator/(int val) const {
        VectorInt res(*this); res /= val; return res;
    }

    VectorInt operator%(int val) const {
        VectorInt res(*this); res %= val; return res;
    }

    // --- Побітові бінарні ---

    VectorInt operator|(const VectorInt& other) const {
        VectorInt res(*this); res |= other; return res;
    }

    VectorInt operator^(const VectorInt& other) const {
        VectorInt res(*this); res ^= other; return res;
    }

    VectorInt operator&(const VectorInt& other) const {
        VectorInt res(*this); res &= other; return res;
    }

    // --- Оператори порівняння ---

    bool operator==(const VectorInt& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) if (data[i] != other.data[i]) return false;
        return true;
    }

    bool operator!=(const VectorInt& other) const { return !(*this == other); }

    bool operator>(const VectorInt& other) const {
        int minS = (size < other.size) ? size : other.size;
        for (int i = 0; i < minS; i++) if (data[i] <= other.data[i]) return false;
        return size > other.size;
    }

    bool operator>=(const VectorInt& other) const {
        return (*this > other) || (*this == other);
    }

    bool operator<(const VectorInt& other) const { return !(*this >= other); }
    bool operator<=(const VectorInt& other) const { return !(*this > other); }

    // --- Індексація та виклик ---

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 2;
            return data[size - 1];
        }
        return data[index];
    }

    void operator()() const {
        cout << "Vector Size: " << size << ", Error Code: " << codeError << endl;
    }

    // --- New та Delete ---

    void* operator new(size_t size) {
        void* p = ::operator new(size);
        return p;
    }

    void operator delete(void* p) {
        ::operator delete(p);
    }

    // --- Дружні функції введення/виведення ---

    friend ostream& operator<<(ostream& os, const VectorInt& v) {
        for (int i = 0; i < v.size; i++) os << v.data[i] << " ";
        return os;
    }

    friend istream& operator>>(istream& is, VectorInt& v) {
        for (int i = 0; i < v.size; i++) is >> v.data[i];
        return is;
    }
};

// Ініціалізація статичної змінної
int VectorInt::objectCount = 0;

int main() {
    cout << "--- Testing VectorInt ---" << endl;

    VectorInt v1(3, 10);
    VectorInt v2(3, 5);

    cout << "Initial v1: " << v1 << endl;
    cout << "Initial v2: " << v2 << endl;

    v1 += v2;
    cout << "v1 += v2: " << v1 << endl;

    v1 *= 2;
    cout << "v1 *= 2: " << v1 << endl;

    VectorInt v3 = v1 + v2;
    cout << "v3 (v1 + v2): " << v3 << endl;

    cout << "Unary minus v2: " << -v2 << endl;

    cout << "Testing prefix ++ on v2: " << ++v2 << endl;

    cout << "Index access v1[1]: " << v1[1] << endl;

    cout << "Testing Out of Bounds v1[10]: ";
    int& ref = v1[10];
    v1(); // Виклик оператора () для перевірки стану

    cout << "Objects created so far: " << VectorInt::getObjectCount() << endl;

    VectorInt* vPtr = new VectorInt(2, 100);
    cout << "Dynamic vector: " << *vPtr << endl;
    cout << "Objects count with dynamic: " << VectorInt::getObjectCount() << endl;
    delete vPtr;
    cout << "Objects count after delete: " << VectorInt::getObjectCount() << endl;

    return 0;
}