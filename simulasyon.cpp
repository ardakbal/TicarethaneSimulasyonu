#include <iostream> 
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
const string aylar[12] = { "Ocak","Şubat","Mart","Nisan","Mayıs","Haziran","Temmuz","Ağustos","Eylül","Ekim","Kasım","Aralık" };

struct firmaUrun {
	string urunAdi;           // Ürünün adı
	double alisFiyatlari;     // Ürünün alış fiyatı
	double satisFiyatlari;    // Ürünün KDV'siz satış fiyatı
	double kdvdahilfiyat;     // Ürünün KDV'li satış fiyatı
	int    satisAdedi;        // Ürünün bir ayda kaç adet satıldığı
	double maliyet;           // Ürünün maliyet toplamı
	double karzararOrani;     // Kar/zarar yüzdesi
	int    stokMiktari;       // Stoktaki ürün sayısı
	int    kalanStok;         // Satışlardan sonra kalan ürün sayısı
	double urunCirosu;        // Ürün satışından elde edilen toplam gelir
	double kdvMiktari;        // Ürün satışından elde edilen toplam KDV
	double urunKarZararı;     // Ürünün toplam kar/zarar miktarı
	double urunGideri;        // Ürünün toplam gider miktarı
};

int main() {
	setlocale(LC_ALL, "Turkish");   // Türkçe karakter desteği sağlanıyor.
	srand(time(0)); 	       // Rastgele sayılar için başlangıç noktası belirleniyor.
	cout.precision(2);            // Ondalıklı sayılar için 2 basamak gösteriliyor.
	cout << fixed; 	             // Ondalıklı sayılar sabit formatta yazdırılıyor.

	cout << "Merhaba, ticarethane simülasyon panelimize hoş geldiniz! Simülasyon paneli" << endl
		<< "üzerinden ürünlerimizin stok miktarının, satış miktarının, kâr oranının, ödenen KDV tutarının," << endl
		<< "alış fiyatının ve karar verdiğiniz alış fiyatı artış sıklığı üzerinden satış" << endl
		<< "fiyatının 12 aylık dökümünü görebileceksiniz!" << endl << endl

		<< "Simülasyona devam edebilmek için alış fiyatı değerinin kaç ayda bir" << endl
		<< "artacağına karar vermeniz gerekmektedir. En az 1, en fazla 4 ayda bir" << endl
		<< "artış yapılabilmektedir. Lütfen 1 ile 4 arasında bir sayı giriniz: ";

	int artisPeriyodu;
	cin >> artisPeriyodu;
	cout << "\n";

	bool kosul = artisPeriyodu != 1 && artisPeriyodu != 2 && artisPeriyodu != 3 && artisPeriyodu != 4;
	if (kosul) {
		cout << "\nHatalı giriş yaptınız. Lütfen tekrar deneyiniz.";
		return 0;
	}

	firmaUrun urun;
	string urunAdi[5] = { "Fare", "Monitör", "Klavye", "Laptop", "Telefon" };

	int ocakfiyatlar[5] = { 1000,6800,2400,39000,18000 };
	int stok[5] = { 100,110,120,130,140 };

	for (int k = 0; k < 12; k++) {
		int satislar[5] = {};
		int holder1 = 0;
		int holder2 = 0;
		int enCokSatan = satislar[0]; // En çok satan ürünü 1. ürün olarak belirledik, bunu ileride değiştirmek üzere kullanacağız.
		int enAzSatan = satislar[0]; // En az satan ürünü 1. ürün olarak belirledik, bunu ileride değiştirmek üzere kullanacağız.

		cout << "[--------------------------------" << aylar[k] << "--------------------------------]" << endl;
		if (k == 0) {
			cout << "İlk ay sabit fiyatlar:\n";
			for (int b = 0; b < 5; b++) {
				cout << urunAdi[b] << ": " << ocakfiyatlar[b] << " TL\n\n";
			}
		}

		else if (k % artisPeriyodu == 0) {
			for (int p = 0; p < 5; p++) {
				double artisOrani = (1 + rand() % 100) / 100.0;;
				ocakfiyatlar[p] += ocakfiyatlar[p] * artisOrani;
				cout << urunAdi[p] << " ürününün alış fiyatı %" << artisOrani * 100 << " arttı. Yeni alış fiyatı: " << ocakfiyatlar[p] << " TL\n\n";
			}
		}

		int    aylikSatisToplami = 0;
		double aylikCiroToplami = 0;
		double aylikKDVToplami = 0;
		double aylikGiderToplami = 0;
		double aylikKarToplami = 0;

		for (int i = 0; i < 5; i++) {
			urun.urunAdi = urunAdi[i];
			urun.alisFiyatlari = ocakfiyatlar[i];
			urun.satisFiyatlari = urun.alisFiyatlari * 1.3 + fmod(rand(), (urun.alisFiyatlari * 0.2));
			urun.kdvdahilfiyat = urun.satisFiyatlari * 1.2;
			urun.stokMiktari = stok[i];
			urun.satisAdedi = urun.stokMiktari * 0.6 + fmod(rand(), (urun.stokMiktari * 0.2));
			urun.kalanStok = urun.stokMiktari - urun.satisAdedi;
			urun.maliyet = urun.alisFiyatlari * urun.stokMiktari;
			urun.urunCirosu = urun.kdvdahilfiyat * urun.satisAdedi;
			urun.kdvMiktari = ((urun.kdvdahilfiyat - urun.satisFiyatlari) * urun.satisAdedi);
			urun.urunGideri = ((urun.kdvdahilfiyat - urun.satisFiyatlari) * urun.satisAdedi) + (urun.maliyet);
			urun.urunKarZararı = urun.urunCirosu - urun.urunGideri;
			urun.karzararOrani = 100 * (urun.urunKarZararı / urun.urunGideri);

			aylikSatisToplami += urun.satisAdedi;
			aylikCiroToplami += urun.urunCirosu;
			aylikKDVToplami += urun.kdvMiktari;
			aylikGiderToplami += urun.urunGideri + 100000;
			aylikKarToplami += urun.urunKarZararı;

			satislar[i] = urun.satisAdedi;

			cout << urun.urunAdi << endl
				<< "Alış Fiyatı : " << urun.alisFiyatlari << "TL" << endl
				<< "KDV'siz Satış Fiyatı: " << urun.satisFiyatlari << "TL" << endl
				<< "KDV'li Satış Fiyatı : " << urun.kdvdahilfiyat << endl
				<< "Stok Miktarı : " << urun.stokMiktari << endl
				<< "Satış Adedi  : " << urun.satisAdedi << endl
				<< "Kalan Stok   : " << urun.kalanStok << endl
				<< "Ürün Cirosu  : " << urun.urunCirosu << endl
				<< "Toplam KDV   : " << urun.kdvMiktari << endl
				<< "Ürün Maliyeti: " << urun.maliyet << endl
				<< "Ürün Gideri  : " << urun.urunGideri << endl
				<< "Kar - Zarar Miktarı: " << urun.urunKarZararı << "TL" << endl
				<< "Kar - Zarar Oranı  : " << "%" << urun.karzararOrani << endl << endl;

			int stokyenileme = (2 * urun.kalanStok) + urun.satisAdedi * 0.7 + fmod(rand(), urun.satisAdedi * 0.3);
			stok[i] = stokyenileme;

			for (int j = 0; j < 5; j++) {
				if (enCokSatan < satislar[j]) { // En çok satanı bulduran if bloğu
					enCokSatan = satislar[j];
					holder1 = j;
				}
			}

			for (int z = 0; z < 5; z++) {
				if (enAzSatan > satislar[z]) {
					enAzSatan = satislar[z];
					holder2 = z;
				}
			}

		}
		cout << "Ayın en çok satan ürünü = " << urunAdi[holder1] << endl
			<< "Ayın en az satan ürünü   = " << urunAdi[holder2] << endl
			<< "Ayın Satış Adedi   = " << aylikSatisToplami << endl
			<< "Ayın Cirosu        = " << aylikCiroToplami << "TL" << endl
			<< "Ayın KDV Toplamı   = " << aylikKDVToplami << "TL" << endl
			<< "Ayın Gider Toplamı = " << "Ürün Maliyetleri(" << aylikGiderToplami << "TL) + Kira + Personel + Elektrik + Su + KDV Bedelleri = " << aylikGiderToplami << "TL + " << "100000TL + " << aylikKDVToplami << "TL = " << aylikGiderToplami + 100000 + aylikKDVToplami << "TL" << endl
			<< "Ayın Kar-Zararı    = " << aylikKarToplami << "TL" << endl
			<< "Ayın Yüzdesel Kar-Zararı = %" << 100 * (aylikKarToplami / (urun.urunGideri + 100000)) << endl << endl;
	}
	return 0;
}
