/*
menampilkan tombol pada keypad yang ditekan pada serial monitor
*/
const int numRows = 4; //jumlah baris pada keypad
const int numCols = 4; //jumlah kolom pada keypad
const int debounceTime = 20; /*waktu dalam mili detik untuk menunggu tombol ke kondisi stabil keymap menentukan char apa yang muncul apabila suatu tombol ditekan*/

const char keymap[numRows][numCols] = {
                                      { '1', '2', '3', 'A' } ,
                                      { '4', '5', '6', 'B' } ,
                                      { '7', '8', '9', 'C' } ,
                                      { '*', '0', '#', 'D' }
                                      };
                                      
//array ini menetukan pin yang akan digunakan untuk baris dan kolom pada keypad
const int rowPins[numRows] = { 9, 8, 7, 6 }; //baris 0 sampai 3
const int colPins[numCols] = { 5, 4, 3, 2 }; //kolom 0 sampai 3

void setup(){
  Serial.begin(9600);
  for (int row = 0; row < numRows; row++){
    pinMode(rowPins[row], INPUT); //set baris sebagai input
    digitalWrite(rowPins[row], HIGH); //buat semua baris tidak aktif
  }
  for (int column = 0; column < numCols; column++){
  pinMode(colPins[column],OUTPUT); //set kolom sebagai input
  digitalWrite(colPins[column], HIGH); //buat semua kolom menjadi tidak aktif
  }
}

void loop()
{
  char key = getKey();
  if( key != 0) { //jika key tidak 0,
                  //maka ada tombol yang ditekan
    Serial.print("Got key ");
    Serial.println(key);
  }
}

//mengembalikan tombol yang ditekan, 0 bila tidak ada yang ditekan
char getKey()
{
  char key = 0; //0 menunjukkan tidak ada tombol yang ditekan
  for(int column = 0; column < numCols; column++){
    digitalWrite(colPins[column],LOW); //aktifkan kolom sekarang
    for(int row = 0; row < numRows; row++){ //scan semua baris apakah
                                            // ada tombol yang ditekan
      if(digitalRead(rowPins[row]) == LOW) //jika tombol ditekan
      {
        delay(debounceTime); //debounce
        while(digitalRead(rowPins[row]) == LOW)
        ; //menunggu hingga tombol tidak dalam kondisi ditekan
        key = keymap[row][column]; //mengingat tombol apa yang ditekan
        }
   }
    digitalWrite(colPins[column],HIGH); //membuat kolom sekarang menjadi tidak aktif
  }
  
  return key; //mengembalikan tombol yang ditekan, 0 jika tidak ada yang ditekan
}
