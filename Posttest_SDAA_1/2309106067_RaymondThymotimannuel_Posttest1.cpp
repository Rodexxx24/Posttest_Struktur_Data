#include <iostream>
using namespace std;

void hanoi(int n, char asal, char tujuan, char sementara) {
    if (n == 1) {
        cout << "Pindahkan piringan 1 dari menara " << asal << " ke menara " << tujuan << endl;
        return;
    }
    cout << "Pindahkan piringan " << n << " dari menara " << asal << " ke menara " << tujuan << endl;
    hanoi(n - 1, sementara, tujuan, asal);
}

void tampilkanPosisiAwal() {
    cout << "\nPosisi awal piringan pada Menara A:" << endl;
    cout << "Piringan 3 di bawah, Piringan 2 di tengah, Piringan 1 di atas" << endl;
    cout << "Menara B dan Menara C kosong.\n" << endl;
}

int main() {
    char pilihan;
    do {
        cout << "Nama : Raymond Thymotimannuel" << endl;
        cout << "NIM  : 2309106067" << endl;
        cout << "\nMenu Program Menara Hanoi:" << endl;
        cout << "1. Tampilkan posisi piringan sebelum diurutkan" << endl;
        cout << "2. Tampilkan langkah-langkah pengurutan piringan" << endl;
        cout << "3. Keluar" << endl;
        cout << "Masukkan pilihan (1, 2, atau 3): ";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                tampilkanPosisiAwal();
                break;

            case '2':
                cout << "\nMenara Asal  (A): Tempat awal piringan." << endl;
                cout << "Menara Tujuan (C): Tempat akhir semua piringan harus dipindahkan." << endl;
                cout << "Menara Sementara (B): Digunakan sebagai menara perantara selama pemindahan.\n" << endl;
                cout << "Langkah-langkah pengurutan piringan Menara Hanoi untuk 3 piringan:\n" << endl;
                hanoi(3, 'A', 'C', 'B');  // Menara A sebagai asal, C sebagai tujuan, dan B sebagai menara sementara
                break;

            case '3':
                cout << "\nKeluar dari program." << endl;
                break;

            default:
                cout << "Pilihan tidak valid. Silakan masukkan pilihan yang benar." << endl;
        }
    } while (pilihan != '3');

    return 0;
}