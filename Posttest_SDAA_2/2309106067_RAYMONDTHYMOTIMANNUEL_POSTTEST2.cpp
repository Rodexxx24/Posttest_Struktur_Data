#include <iostream>
#include <string>
using namespace std;

const int panjang_menu = 100;

struct Makanan {
    int id;
    string nama;
    int harga;
};

Makanan* daftarMenu[panjang_menu];
int jumlahMenu = 0;

// Fungsi untuk menampilkan semua menu
void tampilkanMenu() {
    if (jumlahMenu == 0) {
        cout << "Tidak ada menu yang tersedia." << endl;
        return;
    }

    cout << "\nDaftar Menu Kantin Teknik Baru:\n";
    for (int i = 0; i < jumlahMenu; i++) {
        cout << "ID: " << daftarMenu[i]->id << ", Nama: " << daftarMenu[i]->nama << ", Harga: Rp" << daftarMenu[i]->harga << endl;
    }
}

// Fungsi untuk menambahkan menu baru
void tambahMenu() {
    if (jumlahMenu >= panjang_menu) {
        cout << "Kapasitas menu sudah penuh." << endl;
        return;
    }

    Makanan* menuBaru = new Makanan;
    cout << "Masukkan ID menu: ";
    cin >> menuBaru->id;
    cin.ignore(); 
    cout << "Masukkan nama makanan: ";
    getline(cin, menuBaru->nama);
    cout << "Masukkan harga makanan: ";
    cin >> menuBaru->harga;

    daftarMenu[jumlahMenu] = menuBaru;
    jumlahMenu++;

    cout << "Menu berhasil ditambahkan!" << endl;
}

// Fungsi untuk menghapus menu berdasarkan ID
void hapusMenu() {
    if (jumlahMenu == 0) {
        cout << "Tidak ada menu yang dapat dihapus." << endl;
        return;
    }

    int id;
    cout << "Masukkan ID menu yang ingin dihapus: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < jumlahMenu; i++) {
        if (daftarMenu[i]->id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Menu dengan ID tersebut tidak ditemukan." << endl;
        return;
    }

    delete daftarMenu[index]; 
    for (int i = index; i < jumlahMenu - 1; i++) {
        daftarMenu[i] = daftarMenu[i + 1];
    }

    jumlahMenu--;
    cout << "Menu berhasil dihapus!" << endl;
}

// Fungsi untuk mengubah data menu
void ubahMenu() {
    if (jumlahMenu == 0) {
        cout << "Tidak ada menu yang dapat diubah." << endl;
        return;
    }

    int id;
    cout << "Masukkan ID menu yang ingin diubah: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < jumlahMenu; i++) {
        if (daftarMenu[i]->id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Menu dengan ID tersebut tidak ditemukan." << endl;
        return;
    }

    cout << "Masukkan nama makanan baru: ";
    cin.ignore();
    getline(cin, daftarMenu[index]->nama);
    cout << "Masukkan harga makanan baru: ";
    cin >> daftarMenu[index]->harga;

    cout << "Menu berhasil diubah!" << endl;
}

// Fungsi untuk menampilkan menu utama
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