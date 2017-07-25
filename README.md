# Benchmark for HTML Parsers

Benchmark for HTML Parsers conformant with the [HTML5 specification]

![time on html_samples](/images/time_html_samples.png)

![time on large_html_4mb](/images/time_large_html_4mb.png)

![memory on large_html_4mb](/images/memory_large_html_4mb.png)

## Build and Usage

### For Mac OS X && Linux

**prerequisite** 

Install these libraries: [myhtml], [gumbo].

**build**
```shell
# build html5ever_parse_capi
(cd html5ever_parse_capi && cargo build --release)
make
```

**usage**
```shell
./bm /path/to/dir/with/html/files # e.g. ./bm html_samples
```

As an artefact of this invocation we will have a "result" directory with csv files.

CSV format: page name; file size; time (s); memory (peak rss in bytes).

To plot the results use `gnuplot`:
```shell
gnuplot time.gnuplot # produces result/time.png
gnuplot mem.gnuplot  # produces result/mem.png
```


## Troubleshooting

Q: I get an error:

```shell
./bm: error while loading shared libraries: libmyhtml.so: cannot open shared object file: No such file or directory
```

A: Find the libmyhtml.so and set the environment variable `LD_LIBRARY_PATH`:

```shell
$ sudo updatedb
$ locate libmyhtml.so
/usr/local/lib/libmyhtml.so
$ export LD_LIBRARY_PATH=/usr/local/lib # <-- your path to libmyhtml.so
```

## AUTHOR

Alexander Borisov <lex.borisov@gmail.com>

## COPYRIGHT AND LICENSE

Copyright 2016 Alexander Borisov

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and limitations under the License.


[HTML5 specification]: https://html.spec.whatwg.org/multipage/
[myhtml]: https://github.com/lexborisov/myhtml
[gumbo]: https://github.com/google/gumbo-parser
[html2html_lib]: https://github.com/swizard0/html2html_lib


