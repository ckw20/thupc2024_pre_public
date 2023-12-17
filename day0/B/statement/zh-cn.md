{{ self.title() }}

{{ s('description') }}

这里有一棵树，具体的，这是一张有 $n$ 个节点和 $n-1$ 条边组成的无向联通图。

每个节点初始颜色为白色，你需要恰好将其中 $k$ 个节点染成黑色，定义一条边的权值是，断开这条边之后，两个连通块的黑色节点个数之差，定义一棵树的权值为所有边的权值求和，你需要最小化整棵树的权值。

{{ s('input format') }}

第一行两个正整数 $n,k$（$1\leq k\leq n\leq 5\times10^5$）。

接下来 $n-1$ 行，每行两个正整数 $x,y$ 表示树上的一条边。

{{ s('output format') }}

输出共 $1$ 行，表示最优的染色方案下，这棵树的权值的最小值。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

下图展示了一种满足条件的染色方案，边上的数字表示边权。

{{ img('pic.png', size = 1, align = 'middle', inline = False, label='fig:sample') }}