# Benchmark for HTML Parsers

[![Build Status](https://travis-ci.org/lexborisov/benchmark-html-persers.svg?branch=master)](https://travis-ci.org/lexborisov/benchmark-html-persers)

Benchmark for HTML Parsers conformant with the [HTML5 specification]

## Build and Usage

### For Mac OS X && Linux

Before build this program make and install three libraries: [myhtml], [gumbo], [html2html_lib] (C binding for Rust html5ever (Servo))

**build**
```shell
make
```

**usage**
```shell
bm /path/to/dir/with/html/files
```

After starting the program we have "result" directory with the result appears


## Issues and Recommendations

Leave here or send e-mail: Alexander Borisov <lex.borisov@gmail.com>


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


