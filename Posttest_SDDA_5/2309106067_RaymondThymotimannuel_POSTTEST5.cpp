//Raymond Thymotimannuel
//2309106067
//Informatika B1'23


#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Makanan {
    int id;
    string nama;
    int harga;
    Makanan* next;
};
Makanan* head = nullptr;

struct Node {
    Makanan data;
    Node* next;
};

bool idExistsInStack(Node* top, int id) {
    while (top != nullptr) {
        if (top->data.id == id) return true;
        top = top->next;
    }
    return false;
}

bool idExistsInQueue(Node* front, int id) {
    while (front != nullptr) {
        if (front->data.id == id) return true;
        front = front->next;
    }
    return false;
}

int inputValidID() {
    int id;
    while (true) {
        cout << "Masukkan ID menu: ";
        cin >> id;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input ID harus berupa angka. Silakan coba lagi.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return id;
        }
    }
}

int inputValidHarga() {
    int harga;
    while (true) {
        cout << "Masukkan harga makanan: ";
        cin >> harga;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harga harus berupa angka. Silakan coba lagi.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return harga;
        }
    }
}

void push(Node** top) {
    int id = inputValidID();
    if (idExistsInStack(*top, id)) {
        cout << "ID " << id << " sudah ada di Stack.\n";
        return;
    }
    Makanan menuBaru;
    menuBaru.id = id;

    cout << "Masukkan nama makanan: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, menuBaru.nama);

    menuBaru.harga = inputValidHarga();
    Node* nodeBaru = new Node();
    nodeBaru->data = menuBaru;
    nodeBaru->next = *top;
    *top = nodeBaru;
    cout << "Menu berhasil ditambahkan ke Stack!\n";
}

void pop(Node** top) {
    if (*top == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }
    Node* temp = *top;
    *top = (*top)->next;
    delete temp;
    cout << "Data teratas berhasil dihapus dari Stack.\n";
}

void displayStack(Node* top) {
    if (!top) {
        cout << "Stack kosong.\n";
        return;
    }
    cout << "\nDaftar Menu di Stack:\n";
    while (top) {
        cout << "ID: " << top->data.id << ", Nama: " << top->data.nama << ", Harga: Rp" << top->data.harga << endl;
        top = top->next;
    }
}

void enqueue(Node** front, Node** rear) {
    int id = inputValidID();
    if (idExistsInQueue(*front, id)) {
        cout << "ID " << id << " sudah ada di Queue.\n";
        return;
    }
    Makanan menuBaru;
    menuBaru.id = id;

    cout << "Masukkan nama makanan: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, menuBaru.nama);
    
    menuBaru.harga = inputValidHarga();
    Node* nodeBaru = new Node();
    nodeBaru->data = menuBaru;
    nodeBaru->next = nullptr;
    if (*rear == nullptr) {
        *front = nodeBaru;
    } else {
        (*rear)->next = nodeBaru;
    }
    *rear = nodeBaru;
    cout << "Menu berhasil ditambahkan ke Queue!\n";
}

void dequeue(Node** front) {
    if (!*front) {
        cout << "Queue kosong.\n";
        return;
    }
    Node* temp = *front;
    *front = (*front)->next;
    delete temp;
    cout << "Data terdepan berhasil dihapus dari Queue.\n";
}

void displayQueue(Node* front) {
    if (!front) {
        cout << "Queue kosong.\n";
        return;
    }
    cout << "\nDaftar Menu di Queue:\n";
    while (front) {
        cout << "ID: " << front->data.id << ", Nama: " << front->data.nama << ", Harga: Rp" << front->data.harga << endl;
        front = front->next;
    }
}

Node* mergeSorted(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;
    
    if (left->data.id <= right->data.id) {
        left->next = mergeSorted(left->next, right);
        return left;
    } else {
        right->next = mergeSorted(left, right->next);
        return right;
    }
}

Node* mergeSort(Node* head) {
    if (!head || !head->next) return head;
    
    Node* slow = head;
    Node* fast = head->next;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    Node* mid = slow->next;
    slow->next = nullptr;
    
    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);
    
    return mergeSorted(left, right);
}

void sortStackAscending(Node** top) {
    *top = mergeSort(*top);
    cout << "Stack telah diurutkan secara ascending berdasarkan ID!\n";
}

Node* getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr) cur = cur->next;
    return cur;
}

Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = nullptr, *cur = head, *tail = pivot;
    
    while (cur != pivot) {
        if (cur->data.id > pivot->data.id) {
            if (*newHead == nullptr) *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            Node* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }
    if (*newHead == nullptr) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) return head;
    
    Node *newHead = nullptr, *newEnd = nullptr;
    Node* pivot = partition(head, end, &newHead, &newEnd);
    
    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;
        newHead = quickSortRecur(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }
    
    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

void sortQueueDescending(Node** front) {
    *front = quickSortRecur(*front, getTail(*front));
    cout << "Queue telah diurutkan secara descending berdasarkan ID!\n";
}

int inputMenuUtama() {
    int pilihan;
    while (true) {
        cout << "\n=== Pendataan Menu Makanan Kantin Teknik Baru ===\n";
        cout << "1. Stack\n";
        cout << "2. Queue\n";
        cout << "3. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;
        if (cin.fail() || pilihan < 1 || pilihan > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Pilih opsi 1, 2, atau 3.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return pilihan;
        }
    }
}

int inputSubMenu(const string& menuName) {
    int subPilihan;
    while (true) {
        cout << "\n=== Menu " << menuName << " ===\n";
        cout << "1. " << (menuName == "Stack" ? "Push" : "Enqueue") << endl;
        cout << "2. " << (menuName == "Stack" ? "Pop" : "Dequeue") << endl;
        cout << "3. Tampilkan " << menuName << endl;
        cout << "4. Urutkan " << menuName << endl;
        cout << "5. Kembali\n";
        cout << "Pilih opsi: ";
        cin >> subPilihan;
        if (cin.fail() || subPilihan < 1 || subPilihan > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Pilih opsi 1, 2, 3, 4, atau 5.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return subPilihan;
        }
    }
}

void menuStack() {
    Node* top = nullptr;
    while (true) {
        int subPilihan = inputSubMenu("Stack");
        if (subPilihan == 1) push(&top);
        else if (subPilihan == 2) pop(&top);
        else if (subPilihan == 3) displayStack(top);
        else if (subPilihan == 4) sortStackAscending(&top);
        else break;
    }
}

void menuQueue() {
    Node* front = nullptr;
    Node* rear = nullptr;
    while (true) {
        int subPilihan = inputSubMenu("Queue");
        if (subPilihan == 1) enqueue(&front, &rear);
        else if (subPilihan == 2) dequeue(&front);
        else if (subPilihan == 3) displayQueue(front);
        else if (subPilihan == 4) sortQueueDescending(&front);
        else break;
    }
}

int main() {
    while (true) {
        int pilihan = inputMenuUtama();
        if (pilihan == 1) menuStack();
        else if (pilihan == 2) menuQueue();
        else break;
    }
    return 0;
}
