# 概要
ミューオンの測定の解析をするためのコード。
波形の描画と崩壊時間のグラフの描画をする。

# 環境
gcc version 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04.1)

ROOT Version: 6.36.12

make

# コンパイル
データファイルは`./data/`内におく。
root path環境下で以下を打つ。
```bash
$ make
```

# ファイル
`draw_graph`:ピークが二つあるグラフを表示していく。

`decayhist`:崩壊時間のグラフを書く。

`makehist`:波高のデータをプロットする。

`makehist.hpp`:ヘッダーファイル。`class: highthist`を定義。

`func.hpp`:`class: highthist`を記述