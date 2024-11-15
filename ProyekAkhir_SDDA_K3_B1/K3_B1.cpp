#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Roti {
    int id;
    string nama;
    int harga;
};

class Node {
public:
    Roti data;
    Node* next;
    Node(Roti r) : data(r), next(nullptr) {}
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Roti r) {
        Node* newNode = new Node(r);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Roti dengan ID " << r.id << " berhasil ditambahkan ke queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue kosong! Tidak ada data yang dihapus.\n";
        } else {
            Node* temp = front;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            cout << "Roti dengan ID " << temp->data.id << " dihapus dari queue.\n";
            delete temp;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue kosong!\n";
        } else {
            Node* current = front;
            cout << "\nData Queue:\n";
            while (current) {
                cout << "ID: " << current->data.id << ", Nama: " << current->data.nama << ", Harga: " << current->data.harga << endl;
                current = current->next;
            }
        }
    }

    int panjang() {
        int count = 0;
        Node* current = front;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    Roti* cariBerdasarkanId(int id) {
        Node* current = front;
        while (current) {
            if (current->data.id == id) {
                return &current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    Roti* jumpSearchHarga(int harga) {
        int n = panjang();
        int step = sqrt(n);
        int prev = 0;
        Node* current = front;

        while (current && current->data.harga < harga) {
            for (int i = 0; i < step && current; ++i) {
                current = current->next;
            }
            if (!current) return nullptr;
        }

        current = front;
        for (int i = 0; i < prev && current; ++i) {
            current = current->next;
        }

        while (current && current->data.harga < harga) {
            current = current->next;
        }

        if (current && current->data.harga == harga) {
            return &current->data;
        }
        return nullptr;
    }

    void boyerMooreSearchNama(string pattern) {
        const int NO_OF_CHARS = 256;
        int m = pattern.size();
        int badChar[NO_OF_CHARS];
        for (int i = 0; i < NO_OF_CHARS; i++) {
            badChar[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            badChar[(int)pattern[i]] = i;
        }

        Node* current = front;
        bool found = false;
        while (current) {
            string text = current->data.nama;
            int n = text.size();
            int s = 0;

            while (s <= (n - m)) {
                int j = m - 1;
                while (j >= 0 && pattern[j] == text[s + j]) {
                    j--;
                }
                if (j < 0) {
                    cout << "Roti ditemukan: " << current->data.nama << " dengan ID: " << current->data.id << " dan Harga: " << current->data.harga << endl;
                    found = true;
                    break;
                } else {
                    s += max(1, j - badChar[(int)text[s + j]]);
                }
            }
            current = current->next;
        }
        if (!found) {
            cout << "Roti dengan nama tersebut tidak ditemukan.\n";
        }
    }

    void quickSort(bool ascending = true) {
        if (front == nullptr || front->next == nullptr) {
            return;
        }
        front = quickSortRec(front, ascending);
        Node* current = front;
        while (current->next) {
            current = current->next;
        }
        rear = current;
    }

private:
    Node* quickSortRec(Node* head, bool ascending) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* pivot = head;
        Node* current = head->next;
        Node* lessHead = nullptr, *lessTail = nullptr;
        Node* greaterHead = nullptr, *greaterTail = nullptr;

        while (current) {
            if ((ascending && current->data.id < pivot->data.id) || (!ascending && current->data.id > pivot->data.id)) {
                if (!lessHead) {
                    lessHead = lessTail = current;
                } else {
                    lessTail->next = current;
                    lessTail = current;
                }
            } else {
                if (!greaterHead) {
                    greaterHead = greaterTail = current;
                } else {
                    greaterTail->next = current;
                    greaterTail = current;
                }
            }
            current = current->next;
        }

        if (lessTail) lessTail->next = nullptr;
        if (greaterTail) greaterTail->next = nullptr;

        lessHead = quickSortRec(lessHead, ascending);
        greaterHead = quickSortRec(greaterHead, ascending);

        Node* newHead = nullptr;
        if (lessHead) {
            newHead = lessHead;
            Node* temp = lessHead;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = pivot;
        } else {
            newHead = pivot;
        }
        pivot->next = greaterHead;
        return newHead;
    }
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    bool idSudahAda(int id) {
        Node* current = top;
        while (current) {
            if (current->data.id == id) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void push(Roti r) {
        Node* newNode = new Node(r);
        newNode->next = top;
        top = newNode;
        cout << "Roti dengan ID " << r.id << " berhasil ditambahkan ke stack.\n";
    }

    void pop() {
        if (top) {
            Node* temp = top;
            top = top->next;
            cout << "Roti dengan ID " << temp->data.id << " dihapus dari stack.\n";
            delete temp;
        } else {
            cout << "Stack kosong! Tidak ada data yang dihapus.\n";
        }
    }

    void display() {
        if (!top) {
            cout << "Stack kosong!\n";
            return;
        }
        Node* current = top;
        cout << "\nData Stack:\n";
        while (current) {
            cout << "ID: " << current->data.id << ", Nama: " << current->data.nama << ", Harga: " << current->data.harga << endl;
            current = current->next;
        }
    }

    Roti* cariBerdasarkanId(int id) {
        Node* current = top;
        while (current) {
            if (current->data.id == id) {
                return &current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    Roti* jumpSearchHarga(int harga) {
        int n = panjang();
        int step = sqrt(n);
        int prev = 0;
        vector<Roti*> data;
        Node* current = top;
        while (current) {
            data.push_back(&current->data);
            current = current->next;
        }
        reverse(data.begin(), data.end());

        while (data[min(step, n) - 1]->harga < harga) {
            prev = step;
            step += sqrt(n);
            if (prev >= n) return nullptr;
        }

        while (data[prev]->harga < harga) {
            prev++;
            if (prev == min(step, n)) return nullptr;
        }

        if (data[prev]->harga == harga) {
            return data[prev];
        }
        return nullptr;
    }

    void boyerMooreSearchNama(string pattern) {
        const int NO_OF_CHARS = 256;
        int m = pattern.size();
        int badChar[NO_OF_CHARS];
        for (int i = 0; i < NO_OF_CHARS; i++) {
            badChar[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            badChar[(int)pattern[i]] = i;
        }

        Node* current = top;
        bool found = false;
        while (current) {
            string text = current->data.nama;
            int n = text.size();
            int s = 0;

            while (s <= (n - m)) {
                int j = m - 1;
                while (j >= 0 && pattern[j] == text[s + j]) {
                    j--;
                }
                if (j < 0) {
                    cout << "Roti ditemukan: " << current->data.nama << " dengan ID: " << current->data.id << " dan Harga: " << current->data.harga << endl;
                    found = true;
                    break;
                } else {
                    s += max(1, j - badChar[(int)text[s + j]]);
                }
            }
            current = current->next;
        }
        if (!found) {
            cout << "Roti dengan nama tersebut tidak ditemukan.\n";
        }
    }

    int panjang() {
        int count = 0;
        Node* current = top;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    Node* mergeSort(Node* head, bool ascending = true) {
        if (!head || !head->next)
            return head;

        Node* middle = getMiddle(head);
        Node* nextOfMiddle = middle->next;
        middle->next = nullptr;

        Node* left = mergeSort(head, ascending);
        Node* right = mergeSort(nextOfMiddle, ascending);

        return merge(left, right, ascending);
    }

    void sortStack(bool ascending) {
        top = mergeSort(top, ascending);
    }

private:
    Node* getMiddle(Node* head) {
        if (head == nullptr) return head;
        Node* slow = head;
        Node* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node* merge(Node* left, Node* right, bool ascending) {
        if (!left) return right;
        if (!right) return left;

        Node* result = nullptr;

        if (ascending ? (left->data.id < right->data.id) : (left->data.id > right->data.id)) {
            result = left;
            result->next = merge(left->next, right, ascending);
        } else {
            result = right;
            result->next = merge(left, right->next, ascending);
        }
        return result;
    }
};

template <typename T>
T ambilInput(const string& prompt = "") {
    T value;
    while (true) {
        if (!prompt.empty()) {
            cout << prompt;
        }
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Input tidak valid. Silakan coba lagi.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

template <>
string ambilInput<string>(const string& prompt) {
    string value;
    while (true) {
        if (!prompt.empty()) {
            cout << prompt;
        }
        getline(cin, value);
        if (!value.empty()) {
            return value;
        } else {
            cout << "Input tidak boleh kosong. Silakan coba lagi.\n";
        }
    }
}

int main() {
    Stack stackRoti;
    Queue queueRoti;
    int pilihanUtama;

    do {
        cout << "\n====== Menu Utama ======\n";
        cout << "1. Kelola Stack\n";
        cout << "2. Kelola Queue\n";
        cout << "3. Keluar\n";
        pilihanUtama = ambilInput<int>("Opsi saya [1/2/3]: ");

        switch (pilihanUtama) {
            case 1: {
                int pilihanStack;
                do {
                    cout << "\n====== Manajemen Stack Penjualan Roti ======\n";
                    cout << "1. Tambah Data ke Stack (Push)\n";
                    cout << "2. Tampilkan Data Stack (Display)\n";
                    cout << "3. Hapus Data dari Stack (Pop)\n";
                    cout << "4. Cari Data di Stack (Search)\n";
                    cout << "5. Urutkan Data Stack (Sorting)\n";
                    cout << "6. Kembali ke Menu Utama\n";
                    pilihanStack = ambilInput<int>("Opsi saya [1-6]: ");

                    switch (pilihanStack) {
                        case 1: {
                            Roti roti;
                            roti.id = ambilInput<int>("Masukkan ID (Int): ");

                            if (roti.id <= 0 || stackRoti.idSudahAda(roti.id)) {
                                cout << "ID harus unik dan lebih besar dari 0!\n";
                                break;
                            }

                            roti.nama = ambilInput<string>("Masukkan Nama Roti (String): ");

                            roti.harga = ambilInput<int>("Masukkan Harga Roti (Int): ");

                            if (roti.harga <= 0) {
                                cout << "Harga harus lebih besar dari 0!\n";
                                break;
                            }

                            stackRoti.push(roti);
                            break;
                        }
                        case 2:
                            stackRoti.display();
                            break;
                        case 3:
                            stackRoti.pop();
                            break;
                        case 4: {
                            int pilihanCari;
                            cout << "\nPilih metode pencarian:\n";
                            cout << "1. Pencarian berdasarkan ID\n";
                            cout << "2. Pencarian berdasarkan Harga\n";
                            cout << "3. Pencarian berdasarkan Nama\n";
                            cout << "4. Kembali\n";
                            pilihanCari = ambilInput<int>("Opsi saya [1/2/3/4]: ");

                            if (pilihanCari == 1) {
                                int id = ambilInput<int>("Masukkan ID yang dicari: ");
                                Roti* ditemukan = stackRoti.cariBerdasarkanId(id);
                                if (ditemukan) {
                                    cout << "Roti ditemukan:\n";
                                    cout << "ID: " << ditemukan->id << ", Nama: " << ditemukan->nama << ", Harga: " << ditemukan->harga << endl;
                                } else {
                                    cout << "Roti tidak ditemukan.\n";
                                }
                            } else if (pilihanCari == 2) {
                                int harga = ambilInput<int>("Masukkan Harga yang dicari: ");
                                Roti* ditemukan = stackRoti.jumpSearchHarga(harga);
                                if (ditemukan) {
                                    cout << "Roti ditemukan:\n";
                                    cout << "ID: " << ditemukan->id << ", Nama: " << ditemukan->nama << ", Harga: " << ditemukan->harga << endl;
                                } else {
                                    cout << "Roti dengan harga tersebut tidak ditemukan.\n";
                                }
                            } else if (pilihanCari == 3) {
                                string nama = ambilInput<string>("Masukkan Nama yang dicari: ");
                                stackRoti.boyerMooreSearchNama(nama);
                            } else if (pilihanCari == 4) {
                                break;
                            } else {
                                cout << "Pilihan tidak valid!\n";
                            }
                            break;
                        }
                        case 5: {
                            int pilihanUrutkan;
                            cout << "\nPilih metode urutkan (Merge Sort ID):\n";
                            cout << "1. Ascending\n";
                            cout << "2. Descending\n";
                            cout << "3. Kembali\n";
                            pilihanUrutkan = ambilInput<int>("Opsi saya [1/2/3]: ");

                            if (pilihanUrutkan == 1) {
                                stackRoti.sortStack(true);
                                cout << "Stack diurutkan secara ascending.\n";
                            } else if (pilihanUrutkan == 2) {
                                stackRoti.sortStack(false);
                                cout << "Stack diurutkan secara descending.\n";
                            } else if (pilihanUrutkan == 3) {
                                break;
                            } else {
                                cout << "Pilihan tidak valid!\n";
                            }
                            break;
                        }
                        case 6:
                            break;
                        default:
                            cout << "Pilihan tidak valid! Coba lagi.\n";
                    }
                } while (pilihanStack != 6);
                break;
            }
            case 2: {
                int pilihanQueue;
                do {
                    cout << "\n====== Manajemen Queue Penjualan Roti ======\n";
                    cout << "1. Tambah Data ke Queue (Enqueue)\n";
                    cout << "2. Hapus Data dari Queue (Dequeue)\n";
                    cout << "3. Tampilkan Data Queue (Display)\n";
                    cout << "4. Cari Data di Queue (Search)\n";
                    cout << "5. Urutkan Data (Sorting)\n";
                    cout << "6. Kembali ke Menu Utama\n";
                    pilihanQueue = ambilInput<int>("Opsi saya [1-6]: ");

                    switch (pilihanQueue) {
                        case 1: {
                            Roti roti;
                            roti.id = ambilInput<int>("Masukkan ID (Int): ");

                            if (roti.id <= 0) {
                                cout << "ID harus lebih besar dari 0!\n";
                                break;
                            }

                            roti.nama = ambilInput<string>("Masukkan Nama Roti (String): ");

                            roti.harga = ambilInput<int>("Masukkan Harga Roti (Int): ");

                            if (roti.harga <= 0) {
                                cout << "Harga harus lebih besar dari 0!\n";
                                break;
                            }

                            queueRoti.enqueue(roti);
                            break;
                        }
                        case 2:
                            queueRoti.dequeue();
                            break;
                        case 3:
                            queueRoti.display();
                            break;
                        case 4: {
                            int pilihanCari;
                            cout << "\nPilih metode pencarian:\n";
                            cout << "1. Pencarian berdasarkan ID\n";
                            cout << "2. Pencarian berdasarkan Harga\n";
                            cout << "3. Pencarian berdasarkan Nama\n";
                            cout << "4. Kembali\n";
                            pilihanCari = ambilInput<int>("Opsi saya [1/2/3/4]: ");

                            if (pilihanCari == 1) {
                                int id = ambilInput<int>("Masukkan ID yang dicari: ");
                                Roti* ditemukan = queueRoti.cariBerdasarkanId(id);
                                if (ditemukan) {
                                    cout << "Roti ditemukan:\n";
                                    cout << "ID: " << ditemukan->id << ", Nama: " << ditemukan->nama << ", Harga: " << ditemukan->harga << endl;
                                } else {
                                    cout << "Roti tidak ditemukan.\n";
                                }
                            } else if (pilihanCari == 2) {
                                int harga = ambilInput<int>("Masukkan Harga yang dicari: ");
                                Roti* ditemukan = queueRoti.jumpSearchHarga(harga);
                                if (ditemukan) {
                                    cout << "Roti ditemukan:\n";
                                    cout << "ID: " << ditemukan->id << ", Nama: " << ditemukan->nama << ", Harga: " << ditemukan->harga << endl;
                                } else {
                                    cout << "Roti dengan harga tersebut tidak ditemukan.\n";
                                }
                            } else if (pilihanCari == 3) {
                                string nama = ambilInput<string>("Masukkan Nama yang dicari: ");
                                queueRoti.boyerMooreSearchNama(nama);
                            } else if (pilihanCari == 4) {
                                break;
                            } else {
                                cout << "Pilihan tidak valid!\n";
                            }
                            break;
                        }
                        case 5: {
                            int pilihanUrutkan;
                            cout << "\nPilih metode urutkan (Quick Sort ID):\n";
                            cout << "1. Ascending\n";
                            cout << "2. Descending\n";
                            cout << "3. Kembali\n";
                            pilihanUrutkan = ambilInput<int>("Opsi saya [1/2/3]: ");

                            if (pilihanUrutkan == 1) {
                                queueRoti.quickSort(true);
                                cout << "Queue diurutkan secara ascending.\n";
                            } else if (pilihanUrutkan == 2) {
                                queueRoti.quickSort(false);
                                cout << "Queue diurutkan secara descending.\n";
                            } else if (pilihanUrutkan == 3) {
                                break;
                            } else {
                                cout << "Pilihan tidak valid!\n";
                            }
                            break;
                        }
                        case 6:
                            break;
                        default:
                            cout << "Pilihan tidak valid! Coba lagi.\n";
                    }
                } while (pilihanQueue != 6);
                break;
            }
            case 3:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid! Coba lagi.\n";
        }
    } while (pilihanUtama != 3);

    return 0;
}