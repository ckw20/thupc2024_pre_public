{{ self.title() }}

{{ s('description') }}

我们定义一个集合的 $\operatorname{mex}$ 是最小的不在 $S$ 中的非负整数。

给定一个序列 $a_1,\dots,a_n$，对于每个 $1\leq k\leq n$，我们按照如下方式定义 $b_k$：

- 对于 $a$ 的所有长为 $k$ 的子区间，求出这个子区间构成的数集的 $\operatorname{mex}$。
- 对于求出的所有 $\operatorname{mex}$，求出这个数集自己的 $\operatorname{mex}$，记为 $b_k$。

请你求出序列 $b$。

{{ s('input format') }}

{{ self.input_file() }}

第一行输入一个正整数 $n$（$1\leq n\leq 10^5$）。

第二行输入 $n$ 个整数 $a_1,\dots,a_n$（$0\leq a_i\leq n$）。

{{ s('output format') }}

{{ self.output_file() }}

一行输出 $n$ 个整数 $b_1,\dots,b_n$。

{{ s('sample', 1) }}

{{ self.sample_text() }}
