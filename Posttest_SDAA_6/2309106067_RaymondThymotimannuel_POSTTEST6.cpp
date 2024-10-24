#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Makanan {
    int id;
    string nama;
    int harga;
};

class Simpul {
public:
    Makanan data;
    Simpul* berikut;
    Simpul(Makanan m) : data(m), berikut(nullptr) {}
};

class Tumpukan {
private:
    Simpul* atas;

public:
    Tumpukan() : atas(nullptr) {}

    void tambahkan(Makanan m) {
        Simpul* simpulBaru = new Simpul(m);
        simpulBaru->berikut = atas;
        atas = simpulBaru;
    }

    void keluarkan() {
        if (atas) {
            Simpul* sementara = atas;
            atas = atas->berikut;
            delete sementara;
        }
    }

    void tampilkan() {
        Simpul* sekarang = atas;
        while (sekarang) {
            cout << "ID: " << sekarang->data.id << ", Nama: " << sekarang->data.nama << ", Harga: " << sekarang->data.harga << endl;
            sekarang = sekarang->berikut;
        }
    }

    Makanan* cariBerdasarkanId(int id) {
        Simpul* sekarang = atas;
        while (sekarang) {
            if (sekarang->data.id == id) {
                return &sekarang->data;
            }
            sekarang = sekarang->berikut;
        }
        return nullptr;
    }

    void cariBerdasarkanNama(string nama) {
        Simpul* sekarang = atas;
        bool ditemukan = false;
        while (sekarang) {
            if (sekarang->data.nama == nama) {
                cout << "ID: " << sekarang->data.id << ", Nama: " << sekarang->data.nama << ", Harga: " << sekarang->data.harga << endl;
                ditemukan = true;
            }
            sekarang = sekarang->berikut;
        }
        if (!ditemukan) {
            cout << "Data tidak ditemukan.\n";
        }
    }

    void cariBerdasarkanHarga(int harga) {
        Simpul* sekarang = atas;
        bool ditemukan = false;
        while (sekarang) {
            if (sekarang->data.harga == harga) {
                cout << "ID: " << sekarang->data.id << ", Nama: " << sekarang->data.nama << ", Harga: " << sekarang->data.harga << endl;
                ditemukan = true;
            }
            sekarang = sekarang->berikut;
        }
        if (!ditemukan) {
            cout << "Data tidak ditemukan.\n";
        }
    }

    bool idSudahAda(int id) {
        Simpul* sekarang = atas;
        while (sekarang) {
            if (sekarang->data.id == id) {
                return true;
            }
            sekarang = sekarang->berikut;
        }
        return false;
    }
};

class Antrean {
private:
    vector<Makanan> item;

public:
    void tambahkan(Makanan m) {
        item.push_back(m);
    }

    void tampilkan() {
        for (const auto& m : item) {
            cout << "ID: " << m.id << ", Nama: " << m.nama << ", Harga: " << m.harga << endl;
        }
    }

    Makanan* cariBerdasarkanId(int id) {
        for (auto& m : item) {
            if (m.id == id) {
                return &m;
            }
        }
        return nullptr;
    }

    void cariBerdasarkanNama(string nama) {
        bool ditemukan = false;
        for (auto& m : item) {
            if (m.nama == nama) {
                cout << "ID: " << m.id << ", Nama: " << m.nama << ", Harga: " << m.harga << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "Data tidak ditemukan.\n";
        }
    }

    void cariBerdasarkanHarga(int harga) {
        bool ditemukan = false;
        for (auto& m : item) {
            if (m.harga == harga) {
                cout << "ID: " << m.id << ", Nama: " << m.nama << ", Harga: " << m.harga << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "Data tidak ditemukan.\n";
        }
    }

    bool idSudahAda(int id) {
        for (const auto& m : item) {
            if (m.id == id) {
                return true;
            }
        }
        return false;
    }
};

template <typename T>
T ambilInput() {
    T input;
    cin >> input;
    cin.ignore();
    return input;
}

int main() {
    Tumpukan tumpukan;
    Antrean antrean;
    int pilihan;

    do {
        cout << "====== Selamat datang di program pendataan menu kantin teknik! ======\n";
        cout << "1. Manajemen Menu Makanan dengan Tumpukan\n";
        cout << "2. Manajemen Menu Makanan dengan Antrean\n";
        cout << "3. Keluar\n";
        cout << "Opsi saya [1/2/3]: ";
        pilihan = ambilInput<int>();

        switch (pilihan) {
            case 1: {
                int pilihanTumpukan;
                do {
                    cout << "\nManajemen Menu Makanan dengan Tumpukan:\n";
                    cout << "1. Tambah Menu Makanan\n";
                    cout << "2. Tampilkan Menu\n";
                    cout << "3. Cari Menu Makanan\n";
                    cout << "4. Kembali\n";
                    cout << "Opsi saya [1/2/3/4]: ";
                    pilihanTumpukan = ambilInput<int>();

                    if (pilihanTumpukan == 1) {
                        Makanan makanan;
                        cout << "Masukkan ID: ";
                        makanan.id = ambilInput<int>();

                        if (tumpukan.idSudahAda(makanan.id)) {
                            cout << "ID sudah ada! Silakan masukkan ID yang berbeda.\n";
                            continue;
                        }

                        cout << "Masukkan Nama: ";
                        getline(cin, makanan.nama);
                        cout << "Masukkan Harga: ";
                        makanan.harga = ambilInput<int>();
                        tumpukan.tambahkan(makanan);
                    } else if (pilihanTumpukan == 2) {
                        tumpukan.tampilkan();
                    } else if (pilihanTumpukan == 3) {
                        int pilihanCari;
                        cout << "Pilih metode pencarian:\n";
                        cout << "1. Pencarian berdasarkan ID\n";
                        cout << "2. Pencarian berdasarkan Harga\n";
                        cout << "3. Pencarian berdasarkan Nama\n";
                        cout << "Opsi saya [1/2/3]: ";
                        pilihanCari = ambilInput<int>();

                        if (pilihanCari == 1) {
                            int id;
                            cout << "Masukkan ID yang dicari: ";
                            id = ambilInput<int>();
                            Makanan* ditemukan = tumpukan.cariBerdasarkanId(id);
                            if (ditemukan) {
                                cout << "Menu ditemukan:\n";
                                cout << "ID: " << ditemukan->id << ", Nama: " << ditemukan->nama << ", Harga: " << ditemukan->harga << endl;
                            } else {
                                cout << "Menu tidak ditemukan.\n";
                            }
                        } else if (pilihanCari == 2) {
                            int harga;
                            cout << "Masukkan harga yang dicari: ";
                            harga = ambilInput<int>();
                            tumpukan.cariBerdasarkanHarga(harga);
                        } else if (pilihanCari == 3) {
                            string nama;
                            cout << "Masukkan nama yang dicari: ";
                            getline(cin, nama);
                            tumpukan.cariBerdasarkanNama(nama);
                        } else {
                            cout << "Pilihan tidak valid!\n";
                        }
                    } else if (pilihanTumpukan == 4) {
                        cout << "Kembali ke menu utama.\n";
                    } else {
                        cout << "Pilihan tidak valid!\n";
                    }
                } while (pilihanTumpukan != 4);
                break;
            }
            case 2: {
                int pilihanAntrean;
                do {
                    cout << "\nManajemen Menu Makanan dengan Antrean:\n";
                    cout << "1. Tambah Menu Makanan\n";
                    cout << "2. Tampilkan Menu\n";
                    cout << "3. Cari Menu Makanan\n";
                    cout << "4. Kembali\n";
                    cout << "Opsi saya [1/2/3/4]: ";
                    pilihanAntrean = ambilInput<int>();

                    if (pilihanAntrean == 1) {
                        Makanan makanan;
                        cout << "Masukkan ID: ";
                        makanan.id = ambilInput<int>();

                        if (antrean.idSudahAda(makanan.id)) {
                            cout << "ID sudah ada! Silakan masukkan ID yang berbeda.\n";
                            continue;
                        }

                        cout << "Masukkan Nama: ";
                        getline(cin, makanan.nama);
                        cout << "Masukkan Harga: ";
                        makanan.harga = ambilInput<int>();
                        antrean.tambahkan(makanan);
                    } else if (pilihanAntrean == 2) {
                        antrean.tampilkan();
                    } else if (pilihanAntrean == 3) {
                        int pilihanCari;
                        cout << "Pilih metode pencarian:\n";
                        cout << "1. Pencarian berdasarkan ID\n";
                        cout << "2. Pencarian berdasarkan Harga\n";
                        cout << "3. Pencarian berdasarkan Nama\n";
                        cout << "Opsi saya [1/2/3]: ";
                        pilihanCari = ambilInput<int>();

                        if (pilihanCari == 1) {
                            int id;
                            cout << "Masukkan ID yang dicari: ";
                            id = ambilInput<int>();
                            Makanan* ditemukan = antrean.cariBerdasarkanId(id);
                            if (ditemukan) {
                                cout << "Menu ditemukan:\n";
                                cout << "ID: " << ditemukan->id << ", Nama: " << ditemukan->nama << ", Harga: " << ditemukan->harga << endl;
                            } else {
                                cout << "Menu tidak ditemukan.\n";
                            }
                        } else if (pilihanCari == 2) {
                            int harga;
                            cout << "Masukkan harga yang dicari: ";
                            harga = ambilInput<int>();
                            antrean.cariBerdasarkanHarga(harga);
                        } else if (pilihanCari == 3) {
                            string nama;
                            cout << "Masukkan nama yang dicari: ";
                            getline(cin, nama);
                            antrean.cariBerdasarkanNama(nama);
                        } else {
                            cout << "Pilihan tidak valid!\n";
                        }
                    } else if (pilihanAntrean == 4) {
                        cout << "Kembali ke menu utama.\n";
                    } else {
                        cout << "Pilihan tidak valid!\n";
                    }
                } while (pilihanAntrean != 4);
                break;
            }
            case 3:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid! Coba lagi.\n";
        }
    } while (pilihan != 3);

    return 0;
}
