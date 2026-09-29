#include<stdio.h>
#include<string.h>

int main(){
    char kata[200001]; // O(1) space
    int alphabet[26] = {0};
    int counter = 0;
    
    // Kompleksitas Waktu: O(N), di mana N adalah panjang string
    // Kompleksitas Ruang: O(N) untuk menyimpan input
    scanf("%s", kata); 
    int length = strlen(kata);
    
    // O(N) - Menghitung frekuensi karakter
    for(int i = 0 ; i<length; i++){
        alphabet[kata[i] - 'a']++;
    }
    
    // O(26) -> O(1) - Menghitung karakter yang jumlahnya ganjil
    for(int i = 0 ; i<26; i++){
        if(alphabet[i] % 2 != 0){
            counter++;
        }
    }
    
    // Logika penentuan jumlah palindrom
    if(counter == 0) counter = 1;
    printf("%d\n", counter); // Output jumlah palindrom minimum

    char oddChars[26];
    int oddCount = 0;
    // O(1) - Mengambil satu karakter ganjil untuk jadi 'tengah' palindrom
    for(int i = 0; i < 26; i++){
        if(alphabet[i] % 2 != 0){
            oddChars[oddCount++] = 'a' + i;
            alphabet[i]--; 
        }
    }

    /* KRITIK KERAS: 
       Bagian di bawah ini adalah O(N) secara logika, 
       TAPI 'char Parts[counter][100001]' sangat berbahaya.
       Jika counter = 200.000, maka 200.000 * 100.000 = 20 GB memori. 
       Ini bakal STACK OVERFLOW / Memory Limit Exceeded!
    */
    char Parts[counter][100001]; 
    int PL[counter];
    for(int i = 0; i < counter; i++){
        PL[i] = 0;
        Parts[i][0] = '\0';
    }
    
    // O(N) - Mendistribusikan pasangan karakter ke tiap bagian palindrom
    int curr = 0;
    for(int i = 25; i >= 0; i--){
        while(alphabet[i] > 0){
            Parts[curr][PL[curr]++] = 'a' + i;
            alphabet[i] -= 2;
            curr = (curr + 1) % counter;
        }
    }

    // O(N) - Mencetak hasil akhir
    for(int k = 0; k < counter; k++){
        // Cetak setengah bagian awal
        for(int i = 0; i < PL[k]; i++)   printf("%c", Parts[k][i]);
        // Cetak karakter tengah (jika ada)
        if(k < oddCount) printf("%c", oddChars[k]);
        // Cetak setengah bagian akhir (mirror)
        for(int i = PL[k] - 1; i >= 0; i--) printf("%c", Parts[k][i]);
        printf("\n");
    }
    
    return 0;
}

/*
   TOTAL COMPLEXITY:
   Time Complexity: O(N) 
   Space Complexity: O(N * counter) -> Secara teoritis buruk (bisa O(N^2))
*/