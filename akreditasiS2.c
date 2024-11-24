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
AccreditationResult calculate_accreditation(float ndtps, float pgblk, float ndgb, float ndlk, float kurikulum_A, float kurikulum_B, float kurikulum_C,
                                            int spmi_aspects, int tracer_study_aspects, float bidang_kerja,
                                            float ri, float rn, float rl, float sn_dikti, float sangat_baik, float baik, float cukup, float kurang,
                                            int aspek, int hasil_tracer_study)
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

  // 7. Hitung Skor SN-DIKTI
  float skor_sn_dikti = (sn_dikti >= 4) ? 4 : (sn_dikti >= 3) ? 3
                                          : (sn_dikti >= 2)   ? 2
                                                              : 1;

  // 8. Hitung Skor Kepuasan Pengguna
  if (aspek < 1 || aspek > 7)
  {
    aspek = 7;
  }
  float TKi = (4 * (sangat_baik / 100)) + (3 * (baik / 100)) + (2 * (cukup / 100)) + (kurang / 100);
  float kepuasan_pengguna = TKi / aspek;
  float skor_kepuasan = kepuasan_pengguna;
  // 9. Hitung Skor Hasil Tracer Study
  float skor_hasil_tracer = (hasil_tracer_study >= 5) ? 4 : (hasil_tracer_study >= 3) ? 3
                                                                                      : 2;

  // Hitung Total Skor
  result.total_skor = (skor_dtps + skor_pgblk + skor_kurikulum + skor_spmi + skor_tracer + skor_bidang_kerja +
                       skor_publikasi + skor_sn_dikti + skor_kepuasan + skor_hasil_tracer) /
                      10;

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
  printf("======================================================================================\n");
  printf("                   SISTEM PENILAIAN AKREDITASI MAGISTER DAN TERAPAN                   \n");
  printf("======================================================================================\n");
  printf("\nPetunjuk: Silakan baca ketentuan penilaian di:\n");
  printf("https://www.banpt.or.id/wp-content/uploads/2020/03Lampiran-H-PerBAN-PT-2-2020-ISK\n      -Matriks-Penilaian-ISK-APS-Magister-dan-Magister-Terapan.pdf\n");
  printf("======================================================================================\n");

  print_with_delay("\nSelamat datang di sistem penilaian akreditasi magister dan terapan\n", 35);
  print_with_delay("Sistem ini akan membantu Anda menghitung akreditasi program studi.\n", 35);
  print_with_delay("Silakan tekan Enter untuk memulai...\n", 35);

  char input;
  do
  {
    input = getchar();
  } while (input != '\n');

  print_with_delay("\nMemulai sistem...............\n", 35);
  Sleep(1000);

  // Input data

  float ndtps, pgblk, ndgb, ndlk, kurikulum_A, kurikulum_B, kurikulum_C, bidang_kerja, ri, rn, rl, sn_dikti, sangat_baik, baik, cukup, kurang, kepuasan_pengguna;
  ;
  int spmi_aspects, tracer_study_aspects, hasil_tracer_study, aspek;

  printf("\nMasukkan data berikut dengan hati-hati:\n");
  printf("---------------------------------------------------------------------------------------\n");
  printf("1. Jumlah Dosen Tetap (DTPS):\n");
  printf("==>  ");
  scanf("%f", &ndtps);
  printf("--------------------------------------------------------------------------------------\n");

  printf("2. Persentase Jabatan Akademik (PGBLK):\n");
  printf("   Masukkan Jumlah DTPS yang memiliki jabatan akademik Guru Besar (NDGB)\n");
  printf("==>  ");
  scanf("%f", &ndgb);
  printf("   Masukkan Jumlah DTPS yang memiliki jabatan akademik Lektor Kepala (NDLK)\n");
  printf("==>  ");
  scanf("%f", &ndlk);
  if (ndtps > 0)
  {
    pgblk = ((ndgb + ndlk) / ndtps) * 100;
  }
  else
  {
    printf("Peringatan: Jumlah NDTPS tidak boleh nol. PGBLK diatur ke 0.\n");
    pgblk = 0;
  }
  printf("--------------------------------------------------------------------------------------\n");

  printf("3. Keterlibatan Pemangku Kepentingan:\n");
  printf("   - 4: Pemutakhiran melibatkan internal, eksternal, dan pakar setiap 4-5 tahun\n");
  printf("   - 3: Melibatkan internal dan eksternal\n");
  printf("   - 2: Melibatkan internal saja\n");
  printf("==>  ");
  scanf("%f", &kurikulum_A);
  printf("--------------------------------------------------------------------------------------\n");

  printf("4. Kesesuaian Capaian Pembelajaran:\n");
  printf("   - 4: Capaian sesuai profil lulusan, KKNI, dan dimutakhirkan tiap 4-5 tahun\n");
  printf("   - 3: Capaian sesuai profil dan KKNI tetapi tanpa mutakhir secara berkala\n");
  printf("   - 2: Capaian sesuai profil lulusan tetapi tidak memenuhi KKNI\n");
  printf("   - 1: Tidak sesuai dengan profil lulusan\n");
  printf("==>  ");
  scanf("%f", &kurikulum_B);
  printf("--------------------------------------------------------------------------------------\n");

  printf("5. Ketepatan Struktur Kurikulum:\n");
  printf("   - 4: Struktur kurikulum sesuai dengan peta capaian pembelajaran lulusan:\n");
  printf("            * Memuat keterkaitan antara mata kuliah dan capaian pembelajaran lulusan.\n");
  printf("            * Semua capaian pembelajaran mata kuliah mendukung capaian pembelajaran\n              lulusan.\n");
  printf("   - 3: Struktur kurikulum cukup baik, sebagian besar mendukung capaian pembelajaran\n        lulusan.\n");
  printf("   - 2: Struktur kurikulum hanya menggambarkan sebagian keterkaitan antara mata kuliah\n        dan capaian pembelajaran.\n");
  printf("   - 1: Struktur kurikulum tidak sesuai dengan capaian pembelajaran lulusan.\n");
  printf("==>  ");
  scanf("%f", &kurikulum_C);
  printf("--------------------------------------------------------------------------------------\n");

  printf("6. Jumlah Aspek SPMI yang Terpenuhi (1-5):\n");
  printf("==>  ");
  scanf("%d", &spmi_aspects);
  printf("--------------------------------------------------------------------------------------\n");

  printf("7. Jumlah Aspek Tracer Study yang Terpenuhi (1-5):\n");
  printf("==>  ");
  scanf("%d", &tracer_study_aspects);
  printf("--------------------------------------------------------------------------------------\n");

  printf("8. Persentase Kesesuaian Bidang Kerja:\n");
  printf("==>  ");
  scanf("%f", &bidang_kerja);
  printf("--------------------------------------------------------------------------------------\n");

  printf("9. Persentase Publikasi Internasional (RI):\n");
  printf("==>  ");
  scanf("%f", &ri);
  printf("--------------------------------------------------------------------------------------\n");

  printf("10. Persentase Publikasi Nasional (RN):\n");
  printf("==>  ");
  scanf("%f", &rn);
  printf("--------------------------------------------------------------------------------------\n");

  printf("11. Persentase Publikasi Lokal (RL):\n");
  printf("==>  ");
  scanf("%f", &rl);
  printf("--------------------------------------------------------------------------------------\n");

  printf("12. Skor Pelampauan SN-DIKTI (1-4):\n");
  printf("==>  ");
  scanf("%f", &sn_dikti);
  printf("--------------------------------------------------------------------------------------\n");

  printf("13. Skor Kepuasan Pengguna Lulusan:\n");
  printf("    -Masukkan persentase responden dengan penilaian 'Sangat Baik' (ai)\n");
  printf("==>  ");
  scanf("%f", &sangat_baik);
  printf("    -Masukkan persentase responden dengan penilaian 'Baik' (bi)\n");
  printf("==>  ");
  scanf("%f", &baik);
  printf("    -Masukkan persentase responden dengan penilaian 'Cukup' (ci)\n ");
  printf("==>  ");
  scanf("%f", &cukup);
  printf("    -Masukkan persentase responden dengan penilaian 'Kurang' (di)\n ");
  printf("==>  ");
  scanf("%f", &kurang);
  printf("    -Berapa jumlah aspek yang dinilai untuk kepuasan pengguna? (1-7): ");
  scanf("%d", &aspek);

  // Validasi jumlah aspek
  if (aspek < 1 || aspek > 7)
  {
    printf("  -Jumlah aspek harus antara 1 hingga 7.  nilai default: 7.\n");
  }
  printf("--------------------------------------------------------------------------------------\n");

  printf("14. Skor Hasil Tracer Study (1-5):\n");
  printf("   - 5: Hasil tracer study digunakan sepenuhnya untuk pengembangan kurikulum\n");
  printf("   - 4: Hasil digunakan sebagian besar\n");
  printf("   - 3: Hasil digunakan untuk beberapa aspek\n");
  printf("   - 2: Hasil digunakan secara terbatas\n");
  printf("   - 1: Hasil tidak digunakan sama sekali\n");
  printf("==>  ");
  scanf("%d", &hasil_tracer_study);
  printf("--------------------------------------------------------------------------------------\n");

  // ala ala Proses akreditasi
  printf("======================================================================================\n");
  printf("                              MEMPROSES DATA PENILAIAN                                \n");
  printf("======================================================================================\n");
  Sleep(1000);
  print_with_delay("Menghitung skor total.......................\n", 35);
  Sleep(1000);
  print_with_delay("Menentukan akreditasi.............................\n", 35);
  Sleep(1000);

  AccreditationResult result = calculate_accreditation(ndtps, pgblk, ndgb, ndlk, kurikulum_A, kurikulum_B, kurikulum_C,
                                                       spmi_aspects, tracer_study_aspects, bidang_kerja, ri, rn, rl,
                                                       sn_dikti, sangat_baik, baik, cukup, kurang, kepuasan_pengguna, hasil_tracer_study);

  // hasil

  char buffer[100];
  sprintf(buffer, "Program Studi anda Mendapatkan Akreditasi: %s        \ndengan nilai: %.2f\n", result.akreditasi, result.total_skor);
  printf("======================================================================================\n");
  printf("                             HASIL PENILAIAN AKREDITASI                               \n");
  printf("======================================================================================\n");
  Sleep(1000);
  print_with_delay(buffer, 45);
  printf("======================================================================================\n");
  sleep(1);
  printf("                    TERIMAKASIH TELAH MENGGUNAKAN PROGRAM KAMI  :)");
  sleep(2);

  return 0;
}
