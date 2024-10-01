//Raymond Thymotimannuel
//2309106067
//Informatika B1'23

#include <iostream>
#include <string>
using namespace std;

struct Makanan {
    int id;
    string nama;
    int harga;
    Makanan* next;
};
Makanan* head = nullptr;
void tampilkanMenu() {
    if (head == nullptr) {
        cout << "Tidak ada menu yang tersedia." << endl;
        return;
    }
    cout << "\nDaftar Menu Kantin Teknik Baru:\n";
    Makanan* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->id << ", Nama: " << current->nama << ", Harga: Rp" << current->harga << endl;
        current = current->next;
    }
}
void tambahMenu() {
    Makanan* menuBaru = new Makanan;
    cout << "Masukkan ID menu: ";
    cin >> menuBaru->id;
    cin.ignore();
    cout << "Masukkan nama makanan: ";
    getline(cin, menuBaru->nama);
    cout << "Masukkan harga makanan: ";
    cin >> menuBaru->harga;
    menuBaru->next = nullptr;
    if (head == nullptr) {
        head = menuBaru;
    } else {
        Makanan* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = menuBaru;
    }
    cout << "Menu berhasil ditambahkan!" << endl;
}
void hapusMenu() {
    if (head == nullptr) {
        cout << "Tidak ada menu yang dapat dihapus." << endl;
        return;
    }
    int id;
    cout << "Masukkan ID menu yang ingin dihapus: ";
    cin >> id;
    Makanan* current = head;
    Makanan* previous = nullptr;
    while (current != nullptr && current->id != id) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Menu dengan ID tersebut tidak ditemukan." << endl;
        return;
    }
    if (current == head) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    delete current;
    cout << "Menu berhasil dihapus!" << endl;
}
void ubahMenu() {
    if (head == nullptr) {
        cout << "Tidak ada menu yang dapat diubah." << endl;
        return;
    }
    int id;
    cout << "Masukkan ID menu yang ingin diubah: ";
    cin >> id;
    Makanan* current = head;
    while (current != nullptr && current->id != id) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Menu dengan ID tersebut tidak ditemukan." << endl;
        return;
    }
    cout << "Masukkan nama makanan baru: ";
    cin.ignore();
    getline(cin, current->nama);
    cout << "Masukkan harga makanan baru: ";
    cin >> current->harga;
    cout << "Menu berhasil diubah!" << endl;
}
void menuUtama() {
    int pilihan;
    do {
        cout << "\n=== Pendataan Menu Makanan Kantin Teknik Baru ===\n";
        cout << "1. Tampilkan semua menu\n";
        cout << "2. Tambah menu baru\n";
        cout << "3. Ubah menu\n";
        cout << "4. Hapus menu\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid. Silakan coba lagi." << endl;
            continue;
        }
        switch (pilihan) {
            case 1:
                tampilkanMenu();
                break;
            case 2:
                tambahMenu();
                break;
            case 3:
                ubahMenu();
                break;
            case 4:
                hapusMenu();
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 5);
}
int main() {
    menuUtama();
    return 0;
}