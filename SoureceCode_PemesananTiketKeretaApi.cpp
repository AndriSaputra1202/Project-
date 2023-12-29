// NAMA : ANDRI SAPUTRA
// NIM  : 23343004
// Project Pratikum Algoritma Pemograman

#include <iostream>
#include <iomanip> // ->Menentukan lebar kolom dan baris "setw"



//Variabel global
const int MAX_BARIS = 3; //Untuk menyimpan Seri kursi
const int MAX_KOLOM = 4; //Untuk mneyimpan no kursi
const int MAX_RIWAYAT = 12; // Maksimum riwayat
const int HARGA_TIKET = 5000; // Harga tiket

using namespace std;

// Struck untuk informasi pelanggan dan pemesanan tiket
struct PemesananTiket {
    char baris;
    int kolom;
    string noKursi;
    string namaPelanggan;
    string noTelepon;
    string tempatKeberangkatan;
    string tujuan;
    int harga;
};

// Fungsi untuk menampilkan status kursi
void tampilkanKursi(int kursi[MAX_BARIS][MAX_KOLOM]) {
    cout << "  "; // Memberikan spasi untuk menyesuaikan
    //Untuk kolom
    for (int kolom = 0; kolom < MAX_KOLOM; kolom++) {
        cout << setw(3) << kolom+1 ; //Kolom+1 untuk memulai nilai kolom dari 1
    }
    cout << endl;
    //untuk baris
    for (int baris = 0; baris < MAX_BARIS; ++baris) {
        cout << char('A' + baris) << " "; // Memberikan label

        //Menampilkan kursi kosong atau terisi dengan X dan -
        for (int kolom = 0; kolom < MAX_KOLOM; kolom++) {
            cout << setw(3) << (kursi[baris][kolom] ? "X" : "-"); 
        }
        cout << endl; // Memberikan spasi untuk masuk ke baris baru
    }
}

// Fungsi untuk memesan kursi
bool pesanKursi(int kursi[MAX_BARIS][MAX_KOLOM], char baris, int kolom, PemesananTiket& pemesanan, PemesananTiket riwayat[MAX_RIWAYAT], int& countRiwayat) {
    int indeksBaris = baris - 'A'; // Menyesuaikan posisi baris agar sesuai

    //Memeriksa input kursi oleh user benar atau salah
    if (indeksBaris < 0 || indeksBaris >= MAX_BARIS || kolom < 1 || kolom > MAX_KOLOM) {
        cout << "Pilihan kursi tidak valid.\n";
        return false; //Jika kondisi false ,program akan di ulang
    }

    if (kursi[indeksBaris][kolom - 1] == 0){ // Memeriksa kursi pada "kolom-1" masih tersedia atau bernilai '0/false'
        kursi[indeksBaris][kolom - 1] = 1;//Mengubah nilai pada posisi yang sesuai dari "0" menjadi "1"/Sudah terpesan

        //Menyimpan informasi ke struck PemesananTiket
        pemesanan.baris = baris; //Menyimpan label baris yang diinputkan
        pemesanan.kolom = kolom; //Menyimpan no kusri yang diinputkan 
        pemesanan.noKursi = baris + to_string(kolom); //Menyatukan char baris dan no kursi(Diubah jadi string)

        cout << "Masukkan nama pelanggan       : ";
        cin.ignore();
        getline(cin, pemesanan.namaPelanggan);

        cout << "Masukkan no telepon           : ";
        getline(cin, pemesanan.noTelepon);

        cout << "Masukkan tempat keberangkatan : ";
        getline(cin, pemesanan.tempatKeberangkatan);

        cout << "Masukkan tujuan               : ";
        getline(cin, pemesanan.tujuan);

        pemesanan.harga = HARGA_TIKET;

        cout << endl ; //Output ketika semua telah diinputkan
        cout << "==========================================================" << endl;
        cout << "|  Pemesanan tiket berhasil untuk kursi " << baris << kolom << "." << endl;
        cout << "|  Detail Pemesanan                   : " << endl;
        cout << "|  Nomor Kursi                        : " << pemesanan.noKursi << endl;
        cout << "|  Nama                               : " << pemesanan.namaPelanggan << endl;
        cout << "|  No Telepon                         : " << pemesanan.noTelepon <<  endl;
        cout << "|  Tempat Keberangkatan               : " << pemesanan.tempatKeberangkatan << endl;
        cout << "|  Tujuan                             : " << pemesanan.tujuan << endl;
        cout << "|  Harga Tiket                        : Rp. " << pemesanan.harga << endl;;
        cout << "==========================================================" << endl;

        // Menambahkan ke riwayat
        if (countRiwayat < MAX_RIWAYAT) {
            riwayat[countRiwayat] = pemesanan;
            countRiwayat++;
        }

        return true;
    } else {
        cout << "Maaf, kursi " << baris << kolom << " sudah dipesan. Silakan pilih kursi lain.\n";
        return false;
    }
}

// Fungsi untuk menampilkan riwayat pemesanan
void tampilkanRiwayat(const PemesananTiket riwayat[MAX_RIWAYAT], int countRiwayat) {
    if (countRiwayat == 0) {
        cout << "Riwayat pemesanan kosong.\n";
    } else {
        cout << "Riwayat Pemesanan Tiket:\n";
        cout << setw(10) << "No Kursi" << setw(20) << "Nama Pelanggan" << setw(25) << "No Telepon" << setw(25) << "Tempat Keberangkatan" << setw(20) << "Tujuan" << setw(20) << "Harga Tiket(Rp)" << "\n";
        for (int i = 0; i < countRiwayat; ++i) {
            const PemesananTiket& pemesanan = riwayat[i];
            cout << setw(10) << pemesanan.noKursi << setw(20) << pemesanan.namaPelanggan << setw(25) << pemesanan.noTelepon << setw(25) << pemesanan.tempatKeberangkatan << setw(20) << pemesanan.tujuan << setw(20) << pemesanan.harga << "\n";
        }
    }
}

int main() {
    int kursi[MAX_BARIS][MAX_KOLOM] = {0}; // Inisialisasi nilai awal 0 untuk menandakan kursi kosong
    PemesananTiket riwayat[MAX_RIWAYAT];
    int countRiwayat = 0;

    char pilihan;
    do {
        cout << endl;
        cout << "=================================" << endl;
        cout << " \t\t Menu                 " << endl;
        cout << "  1. Lihat Kursi            " << endl;
        cout << "  2. Pesan Tiket            " << endl;
        cout << "  3. Lihat Riwayat Pemesanan" << endl;
        cout << "  4. Keluar                 " << endl;
        cout << "=================================" << endl;
        cout << "Masukkan Pilihan (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                tampilkanKursi(kursi);
                break;

            case '2': {
                PemesananTiket pemesanan;
                char baris;
                int kolom;
                cout << "Masukkan baris (A-C)          : ";
                cin >> baris;
                cout << "Masukkan Kolom (1-4)          : ";
                cin >> kolom;
                pesanKursi(kursi, baris, kolom, pemesanan, riwayat, countRiwayat);
            } break;

            case '3':
                tampilkanRiwayat(riwayat, countRiwayat);
                break;

            case '4':
                cout << "Terima kasih dan Sampai jumpa!" << endl;;
                break;

            default:
                cout << "Pilihan tidak ada. Silakan pilih lagi !!" << endl;;
        }

    } while (pilihan != '4');

    return 0;
}
