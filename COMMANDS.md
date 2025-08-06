### **`SerialTFT` ライブラリ コマンド一覧**

このライブラリがサポートする主なコマンドの一覧です。

---

#### **初期化と設定 (Initialization & Settings)**

*   `void begin(int baud)`
    *   シリアル通信を開始します。`baud`でボーレートを指定します。
*   `void setRotation(int angle)`
    *   画面の向きを `angle` (0, 90, 180, 270度) に設定します。
*   `void setBrightness(int8_t brightness)`
    *   画面の明るさを `brightness` (0-255) で設定します。
*   `int16_t width()`
    *   画面の幅を取得します。
*   `int16_t height()`
    *   画面の高さを取得します。

---

#### **描画コマンド (Drawing Commands)**

*   `void fillScreen(uint16_t color)`
    *   画面全体を指定した `color` で塗りつぶします。
*   `void drawPixel(int16_t x, int16_t y, uint16_t color)`
    *   座標 `(x, y)` に指定した `color` で点を描画します。
*   `void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)`
    *   座標 `(x0, y0)` から `(x1, y1)` まで指定した `color` で線を描画します。
*   `void drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color)`
    *   指定した `color` で高速に垂直線を描画します。
*   `void drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color)`
    *   指定した `color` で高速に水平線を描画します。
*   `void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)`
    *   指定した `color` で四角形の枠を描画します。
*   `void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)`
    *   指定した `color` で四角形を塗りつぶします。
*   `void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color)`
    *   指定した `color` で角の丸い四角形の枠を描画します。
*   `void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color)`
    *   指定した `color` で角の丸い四角形を塗りつぶします。
*   `void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)`
    *   指定した `color` で円の枠を描画します。
*   `void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)`
    *   指定した `color` で円を塗りつぶします。
*   `void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)`
    *   指定した `color` で三角形の枠を描画します。
*   `void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)`
    *   指定した `color` で三角形を塗りつぶします。

---

#### **テキスト関連 (Text Commands)**

*   `void setCursor(uint16_t x0, uint16_t y0)`
    *   テキスト描画のカーソル位置を設定します。
*   `void setTextSize(uint8_t size)`
    *   テキストのサイズを設定します。
*   `void setTextColor(uint16_t color)`
    *   テキストの色を設定します。
*   `void setTextColor(uint16_t color, uint16_t backgroundcolor)`
    *   テキストの色と背景色を設定します。
*   `void setTextWrap(boolean w)`
    *   テキストが画面の端に達したときに折り返すかどうかを設定します。
*   `void drawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg, uint8_t size)`
    *   指定した位置に1文字を描画します。
*   `void print(String text)`
    *   現在のカーソル位置に文字列を描画します。
*   `void println(String text)`
    *   文字列を描画し、カーソルを次の行に移動します。
*   `void drawCentreString(String text, int dX, int poY, int font)`
    *   中央揃えで文字列を描画します。
*   `void drawRightString(String text, int dX, int poY, int font)`
    *   右揃えで文字列を描画します。

---

#### **色関連 (Color Commands)**

*   `uint16_t color565(uint8_t r, uint8_t g, uint8_t b)`
    *   RGB値から16ビットカラー（RGB565形式）を生成します。
*   `uint8_t color16to8(uint16_t c)`
    *   16ビットカラーを8ビットカラーに変換します。
*   `uint16_t color8to16(uint8_t color)`
    *   8ビットカラーを16ビットカラーに変換します。

---

#### **その他 (Other Commands)**

*   `void progressBar(int x, int y, int w, int h, uint8_t val)`
    *   プログレスバーを描画します。
*   `void qrcode(String text, uint16_t x, uint16_t y, uint8_t width, uint8_t version)`
    *   QRコードを描画します。
