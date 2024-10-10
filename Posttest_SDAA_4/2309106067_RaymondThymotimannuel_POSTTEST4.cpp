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
        cout << "4. Kembali\n";
        cout << "Pilih opsi: ";
        cin >> subPilihan;
        if (cin.fail() || subPilihan < 1 || subPilihan > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return subPilihan;
        }
    }
}

void menuUtama() {
    Node* TOP = nullptr;
    Node *FRONT = nullptr, *REAR = nullptr;
    int pilihan;
    do {
        pilihan = inputMenuUtama();
        switch (pilihan) {
            case 1: {
                int subPilihan;
                do {
                    subPilihan = inputSubMenu("Stack");
                    switch (subPilihan) {
                        case 1: push(&TOP); break;
                        case 2: pop(&TOP); break;
                        case 3: displayStack(TOP); break;
                        case 4: break;
                    }
                } while (subPilihan != 4);
                break;
            }
            case 2: {
                int subPilihan;
                do {
                    subPilihan = inputSubMenu("Queue");
                    switch (subPilihan) {
                        case 1: enqueue(&FRONT, &REAR); break;
                        case 2: dequeue(&FRONT); break;
                        case 3: displayQueue(FRONT); break;
                        case 4: break;
                    }
                } while (subPilihan != 4);
                break;
            }
            case 3:
                cout << "Terima kasih telah menggunakan program ini!\n";
                break;
        }
    } while (pilihan != 3);
}

int main() {
    menuUtama();
    return 0;
}