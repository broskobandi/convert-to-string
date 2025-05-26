# convert-to-string
Converts the content of the input file(s) into a single c string and saves it in a file. The output file can be optionally formatted as a C header file.

## Installation

The application has only one dependency, c-string:
https://github.com/broskobandi/c-string.git. Make sure it is installed before proceeding.

Once c-string is installed, clone and cd into this repository:
```bash
git clone https://github.com/broskobandi/convert-to-string.git &&
cd convert-to-string
```

Create make files:
```bash
mkdir build &&
cd build &&
cmake ..
```

Compile and install app:
```bash
make && sudo make install
```

## Usage
```bash
convert-to-c-string [input_file_1] [input_file_2] [...] [output_file] [options]

Options:

    --help      Print this message
    --header    Save output as C header file
```
