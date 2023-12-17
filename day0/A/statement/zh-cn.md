{{ self.title() }}

{{ s('description') }}

由于你是排序大师，你经常被路过的游客刁难，要求用一些奇怪的操作给序列排序。

由于你是远近闻名的排序大师，邻国的排序萌新小 I 慕名前来拜访，留下了一个长度为 $n$ 的排列 $a_1, a_2 \cdots, a_n$，并要求你用以下操作将排列升序排序：

- 定义 $a_{i \sim j} = \{a_i,a_{i+1},\cdots, a_j\}$。选定 $1 \le i \le j < k \le l \le n$，交换 $a_{i \sim j}$ 和 $a_{k \sim l}$，即交换过后序列变为 $a_{1 \sim i-1}, a_{k \sim l}, a_{j+1 \sim k-1}, a_{i \sim j}, a_{l+1 \sim n}$。

由于你是因精益求精而远近闻名的排序大师，你需要给出一个排序方案**最小化**操作次数。

{{ s('input format') }}

{{ self.input_file() }}

输入的第一行一个整数 $n(1 \le n \le {{tl.hn(args['n'])}})$ 表示序列长度，第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n (1 \le a_i \le n)$ 描述排列。

{{ s('output format') }}

{{ self.output_file() }}

输出的第一行一个整数 $s$ 表示你给出的方案的步数，接下来 $s$ 行每行四个整数 $i,j,k,l$ 表示一次操作。若有多个方案，输出任意一个即可。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

选定 $i = 2, j = 3, k = 5, l = 5$，$1 \textcolor{blue}{4 5} 3 \textcolor{red}{2} 6$ 变为 $1 \textcolor{red}{2} 3 \textcolor{blue}{4 5} 6$。
