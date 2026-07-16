# 概要
ミューオンの測定の解析をするためのコード。
波形の描画と崩壊時間のグラフの描画をする。

# 環境
gcc version 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04.1)

ROOT Version: 6.36.12

GNU Make 4.3

# コンパイル
データファイルは`./datalist.txt`内にpathを入力する。
root path環境下で以下を実行する。
```bash
make
```

# ファイル
`draw_graph`:ピークが二つあるグラフを表示していく。

`decayhist`:崩壊時間のグラフを書く。

`makehist`:波高のデータをプロットする。

`makehist.hpp`:ヘッダーファイル。`class: highthist`を定義。

`func.hpp`:`class: highthist`を記述