#include <stdio.h>
#include <windows.h>

// efek delay saat print
void print_with_delay(const char *text, int delay_ms)
{
  while (*text)
  {
    putchar(*text);
    fflush(stdout);
    Sleep(delay_ms);
    text++;
  }
}

// struct mengakreditasi
typedef struct
{
  char *akreditasi;
  float total_skor;
} AccreditationResult;

// Fungsi untuk menghitung akreditasi
AccreditationResult calculate_accreditation(float ndtps, float pgblk, float kurikulum_A, float kurikulum_B, float kurikulum_C,
                                            int spmi_aspects, int tracer_study_aspects, float bidang_kerja,
                                            float ri, float rn, float rl)
{
  AccreditationResult result;

  // 1. Hitung Skor DTPS
  float skor_dtps = (ndtps >= 6) ? 4 : (ndtps >= 3) ? (2.0f * ndtps) / 3
                                                    : 0;

  // 2. Hitung Skor Jabatan Akademik
  float skor_pgblk = (pgblk >= 70) ? 4 : 2 + (20.0f * (pgblk / 100)) / 7;

  // 3. Hitung Skor Kurikulum
  float skor_kurikulum = (kurikulum_A + (2 * kurikulum_B) + (2 * kurikulum_C)) / 5.0f;

  // 4. Hitung Skor SPMI
  float skor_spmi = spmi_aspects;

  // 5. Hitung Skor Tracer Study
  float skor_tracer = tracer_study_aspects;
  float skor_bidang_kerja = (bidang_kerja >= 60) ? 4 : (20.0f * (bidang_kerja / 100)) / 3;

  // 6. Hitung Skor Publikasi
  float skor_publikasi = (ri >= 2) ? 4 : (ri < 2 && rn >= 20)           ? 3 + (ri / 2.0f)
                                     : (ri == 0 && rn == 0 && rl >= 70) ? 2
                                                                        : (2.0f * rl) / 70;

  // Hitung Total Skor
  result.total_skor = (skor_dtps + skor_pgblk + skor_kurikulum + skor_spmi + skor_tracer + skor_bidang_kerja + skor_publikasi) / 7;

  // Tentukan akreditasi
  if (result.total_skor >= 3.5)
    result.akreditasi = "A";
  else if (result.total_skor >= 2.5)
    result.akreditasi = "B";
  else if (result.total_skor >= 1.5)
    result.akreditasi = "C";
  else
    result.akreditasi = "Tidak Terakreditasi";

  return result;
}

// Fungsi utama
int main()
{
  printf("==================================================================\n");
  printf("         SISTEM PENILAIAN AKREDITASI MAGISTER DAN TERAPAN         \n");
  printf("==================================================================\n");
  printf("\nPetunjuk: Silakan baca ketentuan penilaian di:\n");
  printf("https://www.banpt.or.id/wp-content/uploads/2020/03\nLampiran-H-PerBAN-PT-2-2020-ISK-Matriks-Penilaian\n-ISK-APS-Magister-dan-Magister-Terapan.pdf\n");
  printf("==================================================================\n");

  print_with_delay("\nSelamat datang di sistem penilaian akreditasi magister dan terapan\n", 35);
  print_with_delay("Sistem ini akan membantu Anda menghitung akreditasi program studi.\n", 35);
  print_with_delay("Silakan tekan Enter untuk memulai...\n", 35);

  char input;
  do
  {
    input = getchar();
  } while (input != '\n');

  print_with_delay("\nMemulai sistem...........\n", 35);
  Sleep(1000);

  // Input data

  float ndtps, pgblk, kurikulum_A, kurikulum_B, kurikulum_C, bidang_kerja, ri, rn, rl;
  int spmi_aspects, tracer_study_aspects;

  printf("\nMasukkan data berikut dengan hati-hati:\n");
  printf("------------------------------------------------------------------\n");

  printf("Masukkan Jumlah Dosen Tetap\n==>  ");
  scanf("%f", &ndtps);
  printf("Masukkan Persentase Jabatan Akademik (PGBLK)\n==>  ");
  scanf("%f", &pgblk);
  printf("Masukkan Skor Keterlibatan Pemangku Kepentingan\n==>  ");
  scanf("%f", &kurikulum_A);
  printf("Masukkan Skor Kesesuaian Capaian Pembelajaran\n==>  ");
  scanf("%f", &kurikulum_B);
  printf("Masukkan Skor Ketepatan Struktur Kurikulum\n==>  ");
  scanf("%f", &kurikulum_C);
  printf("Masukkan Jumlah Aspek SPMI yang Terpenuhi\n==>  ");
  scanf("%d", &spmi_aspects);
  printf("Masukkan Jumlah Aspek Tracer Study yang Terpenuhi\n==>  ");
  scanf("%d", &tracer_study_aspects);
  printf("Masukkan Persentase Kesesuaian Bidang Kerja\n==>  ");
  scanf("%f", &bidang_kerja);
  printf("Masukkan Persentase Publikasi Internasional (RI)\n==>  ");
  scanf("%f", &ri);
  printf("Masukkan Persentase Publikasi Nasional (RN)\n==>  ");
  scanf("%f", &rn);
  printf("Masukkan Persentase Publikasi Lokal (RL)\n==>  ");
  scanf("%f", &rl);

  // ala ala Proses akreditasi
  printf("\n==================================================================\n");
  printf("                    MEMPROSES DATA PENILAIAN                      \n");
  printf("==================================================================\n");
  Sleep(1000);
  print_with_delay("Menghitung skor total............\n", 35);
  Sleep(1000);
  print_with_delay("Menentukan akreditasi............\n", 35);
  Sleep(1000);

  AccreditationResult result = calculate_accreditation(ndtps, pgblk, kurikulum_A, kurikulum_B, kurikulum_C,
                                                       spmi_aspects, tracer_study_aspects, bidang_kerja, ri, rn, rl);

  // hasil
  
  char buffer[100];
  sprintf(buffer, "Program Studi anda Mendapatkan Akreditasi: %s        \ndengan nilai: %.2f\n", result.akreditasi, result.total_skor);
  printf("\n==================================================================\n");
  printf("                   HASIL PENILAIAN AKREDITASI                     \n");
  printf("==================================================================\n");
  Sleep(1000);
  print_with_delay(buffer, 45);
  printf("==================================================================\n");
  sleep(1);
  printf("          TERIMAKASIH TELAH MENGGUNAKAN PROGRAM KAMI  :)");
  sleep(2);

  return 0;
}
