{{ self.title() }}

{{ s('background') }}

// 如果验题人看到这条注释，请联系出题人补全。这里没写完的题目背景理论上不影响选手做题。

// 如果搬到比赛平台上时这条注释还在，那说明出题人写不完了，把题目背景去掉即可。

{{ s('description') }}

K 家里有一条不成文的规矩。如果家里只有 K 和 H 两个人，那么两个人会通过一种叫作“三步棋”的游戏来决定谁做饭。三步棋的规则与五子棋有一些相似之处。众所周知，五子棋是一种先连出五枚己方棋子者获胜的游戏。与五子棋相同的是，三步棋中双方也轮流在网格状的棋盘上摆放棋子，并根据是否连成指定的图案决定胜负。与五子棋不同的是：

1. 三步棋不区分双方的棋子，即可以认为双方执同色棋子进行游戏；

2. 在判定时，指定的图案不能旋转；

3. 如果连成指定的图案时，棋盘上的棋子数量恰好为 $3$ 的倍数，则连成指定的图案的一方获胜，否则判定该方负（即对方获胜）。

例如，如果指定的图案为

```
.o
oo
```

且当前盘面为

```
o..o.
o.o..
oo...
o.o..
o..o.
```

时，认为没有连成给定的折线形图案，其中 `o` 表示棋子，`.` 表示空格；但若接下来在第二行第二列放一枚棋子，则连成了给定的图案，对应的棋子使用 `@` 表示：

```
o..o.
o@o..
@@...
o.o..
o..o.
```

此时盘面上恰有 $11$ 枚棋子，而 $11$ 不是 $3$ 的倍数，所以判定放这枚棋子的玩家，也即先手输掉本局。

在 K 家，为了节约时间，通常使用 $5\times 5$ 的初始为空的棋盘进行三步棋。同时，每次也只会随机选择一个由不超过 $4$ 枚棋子组成的四连通图案。显然三步棋不存在平局，所以 K 和 H 约定由输的一方负责做饭。K 想知道，如果自己和 H 都足够聪明，那么以选中的图案进行的三步棋游戏是否为**先手必胜**；因为如果她更容易赢，她就要偷偷地给自己的妹妹放水。

{{ s('input format') }}

{{ self.input_file() }}

输入文件包含多组数据。

输入的第一行包含一个正整数 $T$，表示数据组数。保证 $1\le T\le 200$。

对于每组数据，输入包含 $5$ 行，每行包括一个长度为 $5$ 且仅含 `.` 及 `o` 的字符串，表示指定的图案。保证每组数据中 `o` 至少出现一次，且所有 `o` 组成一个大小不超过 $4$ 的四连通块。

{{ s('output format') }}

{{ self.output_file() }}

对于每组数据输出一行。如果输入的图案为**先手必胜**，则输出 `Far`，否则输出 `Away`。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

该样例包含三组数据。

第一组数据输入的图案为 $1$ 行 $2$ 列的 `oo`。显然，无论先手将棋子放在棋盘上的哪个位置，后手都只有两种策略：

- 和先手的棋子连成 `oo`，此时棋盘上只有 $2$ 枚棋子，故后手立即输掉游戏；

- 不和先手的棋子连成 `oo`，但是接下来轮到先手时，先手可以任意连成 `oo`，此时棋盘上恰有 $3$ 枚棋子，故先手取胜。

无论是哪种策略，后手都无法取胜，故对于 `oo` 而言**先手必胜**。

第二组数据输入的图案为 $2$ 行 $1$ 列的图案，与 `oo` 同理，可知为**先手必胜**。

第三组数据输入的图案为 $1$ 行 $3$ 列的 `ooo`，可以证明为先手必败。

{{ s('subtasks') }}

保证 $1\le T\le 200$。对于每组数据，保证输入的 $5\times 5$ 的由 `.` 和 `o` 组成的字符矩阵中至少含有一个 `o`，且所有 `o` 组成一个大小不超过 $4$ 的四连通块。